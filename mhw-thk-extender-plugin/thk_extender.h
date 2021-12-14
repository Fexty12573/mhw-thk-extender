
#include <map>

typedef unsigned char byte;

struct THKSegment
{
	byte NodeEndRandom;
	byte InterruptType;
	byte SegmentType;
	byte unk1;
	uint32_t unk2;
	uint32_t CheckType;
	uint32_t Parameter1;
	uint32_t unk3;
	uint32_t unk4;
	uint32_t unk5;
	uint32_t unk6;
	uint32_t Parameter2;
	uint32_t NodeEndingData;
	uint32_t ExtRefThkID;
	uint32_t ExtRefNodeID;
	uint64_t LocalRefNodeIndex;
	uint32_t unk7;
	uint32_t unk8;
	uint32_t unk9;
	uint32_t unk10;
	uint32_t unk11;
	uint32_t ActionID;
	uint32_t ActionUnknown[3];
	uint32_t unk12;
	uint32_t ActionUnknown3;
	uint32_t ActionUnknown4;
	uint32_t unkExtra[6];
};

typedef bool(*THKFunction_t)(void* cThinkEm, THKSegment* segment, void* cThinkMgr);

class THKExtender
{
public:
	THKExtender(const THKExtender&) = delete;
	THKExtender(THKExtender&&) noexcept = delete;
	THKExtender& operator=(const THKExtender&) = delete;
	THKExtender& operator=(THKExtender&&) noexcept = delete;

	static void Initialize(bool bInitMinHook = true);
	static void AddThkFunction(THKFunction_t function, uint32_t funcId);

private:
	static uint64_t AiCheckHook(void* cThinkEm, THKSegment* segment, void* cThinkMgr);
	static THKFunction_t s_OriginalTHKFunction;
	static THKFunction_t s_Target;

	static std::map<uint32_t, THKFunction_t> s_THKFunctions;
};
