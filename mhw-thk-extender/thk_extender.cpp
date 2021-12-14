
#include "thk_extender.h"

#include <MinHook.h>

std::map<uint32_t, THKFunction_t> THKExtender::s_THKFunctions;
THKFunction_t THKExtender::s_OriginalTHKFunction = nullptr;
THKFunction_t THKExtender::s_Target = (THKFunction_t)0x141343650;


uint64_t THKExtender::AiCheckHook(void* cThinkEm, THKSegment* segment, void* cThinkMgr)
{
	uint64_t result = s_OriginalTHKFunction(cThinkEm, segment, cThinkMgr);

	if (segment->CheckType < 0x3)
		return result;

	if (s_THKFunctions.find(segment->CheckType) != s_THKFunctions.end())
		result = s_THKFunctions[segment->CheckType](cThinkEm, segment, cThinkMgr);

	return result;
}

void THKExtender::Initialize(bool bInitMinHook)
{
	if (bInitMinHook) MH_Initialize();

	MH_CreateHook(s_Target, AiCheckHook, reinterpret_cast<void**>(&s_OriginalTHKFunction));
	MH_EnableHook(s_Target);
}

void THKExtender::AddThkFunction(THKFunction_t function, uint32_t funcId)
{
	s_THKFunctions[funcId] = function;
}
