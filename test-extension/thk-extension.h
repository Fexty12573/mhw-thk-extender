
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

template<typename _Ty, typename _Ty2 = void*>
inline _Ty OffsetPointer(_Ty2 _Ptr, size_t _Offset)
{
	static_assert(std::is_pointer_v<_Ty>, "operation only supported on pointer types");
	return reinterpret_cast<_Ty>(((byte*)_Ptr + _Offset));
}

inline void* GetParentMonster(void* cThinkEm)
{
	static void* (*_GetParent)(void*) = (decltype(_GetParent))0x140a197b0;
	return _GetParent(*(void**)((char*)cThinkEm + 0x630));
}

#define THK_EXPORT extern "C" __declspec(dllexport)
