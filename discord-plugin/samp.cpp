#include "samp.h"
#include <iostream>

Samp* pSamp;

Samp::Samp()
{
	dwSAMP_Addr = NULL;
	stSAMP* SAMP = nullptr;
}

bool Samp::Init()
{
	if (dwSAMP_Addr == NULL) dwSAMP_Addr = (DWORD)GetModuleHandleA("samp.dll");
	if (dwSAMP_Addr == NULL) return false;

	//if (SAMP == nullptr) SAMP = *(stSAMP**)(dwSAMP_Addr + SAMP_INFO_OFFSET);
	if (SAMP == nullptr) SAMP = *reinterpret_cast<stSAMP**>(dwSAMP_Addr + SAMP_INFO_OFFSET);
	if (SAMP == nullptr) return false;

	if (g_Chat == nullptr) g_Chat = *reinterpret_cast<stChatInfo**>(dwSAMP_Addr + SAMP_CHAT_INFO_OFFSET);
	if (g_Chat == nullptr) return false;

	if (SAMP->iGameState != 5) return false;

	return true;
}

void Samp::UpdateScoresPingsIps()
{
	reinterpret_cast<void(__thiscall*)(void*)>(getBase() + 0x8BA0)(SAMP);
}

DWORD Samp::getBase()
{
	return dwSAMP_Addr;
}

stPlayerPool* Samp::GetPlayerPool()
{
	return SAMP->pPools->pPlayer;
}

std::string Samp::GetServerIp()
{
	return SAMP->szIP;
}
void Samp::addMessageToChat(DWORD cColor, char* szMsg, ...) {
	if (g_Chat == nullptr)
		return;

#if defined (SAMP_R1_COMPILE)
	void(__thiscall * AddToChatWindowBuffer) (const void* _this, int iType, char* szText, char* szPrefix, DWORD cColor, DWORD cPrefixColor) =
		(void(__thiscall*) (const void*, int, char*, char*, DWORD, DWORD)) (sampAddr + 0x064010);//r3 0x67460 | r1 0x064010
#elif defined (SAMP_R3_COMPILE)
	void(__thiscall * AddToChatWindowBuffer) (const void* _this, int iType, char* szText, char* szPrefix, DWORD cColor, DWORD cPrefixColor) =
		(void(__thiscall*) (const void*, int, char*, char*, DWORD, DWORD)) (dwSAMP_Addr + 0x067460);//r3 0x67460 | r1 0x064010
#endif

	if (szMsg == NULL)
		return;

	va_list ap;
	char tmp[512];
	memset(tmp, 0, 512);
	va_start(ap, szMsg);
	vsnprintf(tmp, sizeof(tmp) - 1, szMsg, ap);
	va_end(ap);

	return AddToChatWindowBuffer((void*)g_Chat, 8, tmp, NULL, cColor, 0x00);
};
std::string Samp::GetServerName()
{
	return SAMP->szHostname;
}