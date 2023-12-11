
#include <cinttypes>
#include <type_traits>

struct THKSegment;
typedef unsigned char byte;
typedef bool(*THKFunction_t)(void* cThinkEm, THKSegment* segment, void* cThinkMgr);

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

template<typename T, typename TPtr = void*>
inline T* OffsetPointer(TPtr ptr, size_t offset)
{
	return reinterpret_cast<T*>(((byte*)ptr + offset));
}

inline void* GetParentMonster(void* cThinkEm)
{
	const auto ai = *OffsetPointer<void*>(cThinkEm, 0x630);
	return *OffsetPointer<void*>(ai, 0x138);
}

#define THK_EXPORT extern "C" __declspec(dllexport)
