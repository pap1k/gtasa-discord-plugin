#include "dllmain.h"

enum server {
	rpg = 0,
	rp1,
	rp2,
	unk
};

struct stServerInfo {
	server serverMode;
	std::string largeImageKey;
	std::string largeImageText;
	std::string smallImageKey;
	std::string smallImageText;
	std::string playerInfo;
};

server GetServerMode(std::string szIP)
{
	if (szIP == "185.169.134.83")
		return server::rpg;
	if (szIP == "185.169.134.84")
		return server::rp1;
	if (szIP == "185.169.134.85")
		return server::rp2;
	return server::unk;
}

stServerInfo* UpdateServerInfo(Samp* pSamp) {
	auto ServerInfo = new stServerInfo();

	ServerInfo->serverMode = GetServerMode(pSamp->GetServerIp());
	if (ServerInfo->serverMode == server::unk)
		return 0;

	ServerInfo->smallImageKey = "trinity";
	ServerInfo->smallImageText = "Trinity GTA";

	if (ServerInfo->serverMode == server::rp1)
	{
		ServerInfo->largeImageKey = "rp1";
		ServerInfo->largeImageText = "Server: Role Play 1";
	}
	else if (ServerInfo->serverMode == server::rp2)
	{
		ServerInfo->largeImageKey = "rp2";
		ServerInfo->largeImageText = "Server: Role Play 2";
	}
	else
	{
		ServerInfo->largeImageKey = "rpg";
		ServerInfo->largeImageText = "Server: RPG";
	}

	auto infostr = pSamp->GetPlayerPool()->strLocalPlayerName + "[" + std::to_string(pSamp->GetPlayerPool()->sLocalPlayerID) + "]";

	if (pSamp->GetPlayerPool()->iLocalPlayerScore != 0)
		infostr += " || " + std::to_string(pSamp->GetPlayerPool()->iLocalPlayerScore) + " LVL";

	ServerInfo->playerInfo = infostr;

	return ServerInfo;
}

void MainThread()
{
	bool display_pos = false;

	//init settings

	mINI::INIFile sets(INI_FILE);
	mINI::INIStructure ini;

	sets.read(ini);

	if (ini["discord_activity"]["display_location"] == "")
	{
		ini["discord_activity"]["display_location"] = "1";
		sets.write(ini);
	}
	display_pos = ini["discord_activity"]["display_location"] == "1";

	while (*(DWORD*)0xC8D4C0 != 9)
		Sleep(350);

	pGame = new Game();
	
	bool dsloop = true;
	time_t lastUpdatetime = time(0);
	time_t startTimestamp = time(0);

	DiscordRichPresence drp;

	drp = { 0 };
	drp.startTimestamp = startTimestamp;

	Discord_Initialize(DISCORD_APPLICATION_ID, 0, 0, 0);
	
	if (GetModuleHandleA("samp.dll")) // only samp
	{
		pSamp = new Samp();

		while (!pSamp->Init())
			Sleep(350);

		// Getting player information
		if (!pSamp->GetPlayerPool())
			return;

		bool isFirst = true;

		while (dsloop)
		{
			if (pGame->IsPedExists())
			{
				stServerInfo* ServerInfo = UpdateServerInfo(pSamp);
				
				if (display_pos)
				{
					char buf[128];
					pGame->GetCurrentZone(buf);
					drp.details = buf;
				}
				else {
					drp.details = u8"Не принимает сигналы со спутника";
				}
				drp.state = ServerInfo->playerInfo.c_str();
				drp.smallImageText = ServerInfo->smallImageText.c_str();
				drp.smallImageKey = ServerInfo->smallImageKey.c_str();
				drp.largeImageText = ServerInfo->largeImageText.c_str();
				drp.largeImageKey = ServerInfo->largeImageKey.c_str();

				Discord_UpdatePresence(&drp);
				lastUpdatetime = time(0);

				Sleep(1000*DISCORD_SENDRATE);
			}
			if (lastUpdatetime + DISCORD_TURNOFF_DELAY_SEC < time(0))
			{
				pSamp->addMessageToChat(-1, "[by papercut] За последние %d секунд не удалось обновить данные.", DISCORD_TURNOFF_DELAY_SEC);
				pSamp->addMessageToChat(-1, "[by papercut] Плагин завершает работу.");
				dsloop = false;
				Discord_Shutdown();
			}
		}
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
        CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(MainThread), 0, 0, 0);
	}
	else if (reason == DLL_PROCESS_DETACH)
        Discord_Shutdown();

	return TRUE;
}