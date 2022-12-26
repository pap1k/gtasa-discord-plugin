#pragma once
#include <string>
#include <vector>
#include <ctime>
#include <windows.h>
#include <iostream>
#include <fstream>

#include "discord-rpc.h"
#include "Game.h"
#include "Samp.h"
#include "ini.hpp"

#pragma comment(lib, "urlmon.lib")
#include <urlmon.h>

#define DISCORD_APPLICATION_ID "1044737446958616589"
#ifdef TEST
#define DISCORD_SENDRATE 3
#else
#define DISCORD_SENDRATE 15
#endif
#define DISCORD_TURNOFF_DELAY_SEC 180
#define INI_FILE "scripts\\plugins_settings.ini"
#define JSON_FILE "locations.json"