#include <Windows.h>
#include "thk-extension.h"

THK_EXPORT bool TestExtension(void* cThinkMgr, THKSegment* segment, void* cThinkEm)
{
	void* monster = GetParentMonster(cThinkEm);

	auto id = *OffsetPointer<uint32_t*>(monster, 0x12280);
	return id == 1;
}


BOOL APIENTRY DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
	return TRUE;
}
