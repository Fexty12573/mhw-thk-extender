
#include "thk_extender.h"

#include <MinHook.h>

std::map<uint32_t, THKFunction_t> THKExtender::s_THKFunctions;
THKFunction_t THKExtender::s_OriginalTHKFunction = nullptr;
THKFunction_t THKExtender::s_Target = (THKFunction_t)0x1413339d0;


uint64_t THKExtender::AiCheckHook(void* cThinkEm, THKSegment* segment, void* cThinkMgr)
{
	int32_t check = segment->CheckType;

	if (check < 0)
		segment->CheckType = -segment->CheckType;

	uint64_t result = s_OriginalTHKFunction(cThinkEm, segment, cThinkMgr);

	if (segment->CheckType < 0x3)
		return result;

	if (s_THKFunctions.contains(segment->CheckType))
		result = s_THKFunctions.at(segment->CheckType)(cThinkEm, segment, cThinkMgr);

	if (check < 0)
	{
		segment->CheckType = -segment->CheckType;
		result = !result;
	}

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
