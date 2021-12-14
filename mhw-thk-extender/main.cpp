
#include "thk_extender.h"


bool IsMonsterID_Eq_Param1(void* cThinkEm, THKSegment* segment, void* cThinkMgr)
{
	void* monster = *(void**)((*(char**)((char*)cThinkEm + 0x630)) + 0x138);
	return *(uint32_t*)((char*)monster + 0x12280) == segment->Parameter1;
}


int main()
{
	THKExtender::Initialize();
	THKExtender::AddThkFunction(&IsMonsterID_Eq_Param1, 0x200);
}
