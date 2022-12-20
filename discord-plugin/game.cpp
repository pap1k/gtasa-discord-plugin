#include "game.h"

Game* pGame;

bool Game::IsAnyMissionActive()
{
	return *reinterpret_cast<int*>(0x96ABA0);
}

std::string Game::GetCurrentMission()
{
	// 0xA7A974 - times
	// 0x96ABA0 - mission status (on/off)
	if (!pGame->IsAnyMissionActive())
		return "None";
	
	char gxtMissionName[8];
	memcpy(gxtMissionName, (void*)(0xC1B364), 8);

	if (gxtMissionName == "")
		return "None";

	if (missionNames[gxtMissionName] == "")
		return "None";

	return missionNames[gxtMissionName];
}

void Game::GetCurrentZone(char *buf)
{
	if (GetCurrentInterior() != 0)
	{
		sprintf_s(buf, 128, u8"�� ��������� ������� �� ��������");
		return;
	}
	const float position_x = *reinterpret_cast<float*>(0xB6F2E4),
				position_y = *reinterpret_cast<float*>(0xB6F2E8),
				position_z = *reinterpret_cast<float*>(0x8CCC44);

	for (int i = 0; i < sizeof(zone) / sizeof(zone[0]); i++)
	{
		if (position_x > zone[i].min_x && position_y > zone[i].min_y && position_z > zone[i].min_z && position_x < zone[i].max_x && position_y < zone[i].max_y && position_z < zone[i].max_z)
		{
			if (IsPedInVehicle())
				sprintf_s(buf, 128, u8"���� %s", zone[i].zone_name.c_str());
			else
				sprintf_s(buf, 128, u8"����� %s", zone[i].zone_name.c_str());
			return;
		}

	}
	sprintf_s(buf, 128, u8"���-�� � San Andreas...");
}

int Game::GetCurrentInterior()
{
	return *reinterpret_cast<int*>(0xA4ACE8);
}

float Game::GetProgress()
{
	return *reinterpret_cast<float*>(0xA4A61C);
}

int Game::GetPassedDays()
{
	return *reinterpret_cast<int*>(0xB79038);
}

int Game::GetCurrentWeapon()
{
	return *reinterpret_cast<int*>(0xBAA410);
}

bool Game::IsPedExists()
{
	return *reinterpret_cast<int*>(0xB6F5F0);
}

bool Game::IsPedInVehicle()
{
	return *reinterpret_cast<int*>(0xBA18FC) != 0;
}

std::map <std::string, std::string> missionNames =
{
	{"AMBULAE", "Paramedic (Sub-Mission)"},
	{"BCESAR2", "King in Exile"},
	{"BCESAR4", "Wu Zi Mu"},
	{"BCOU", "Courier (Sub-Mission)"},
	{"BCRASH1", "Badlands"},
	{"BLOOD", "Blood Ring (Sub-Mission)"},
	{"BOAT", "Boat School"},
	{"BS", "Bike School"},
	{"BURGLAR", "Burglar"},
	{"CASIN10", "Saint Mark's Bistro"},
	{"CASINO1", "Fender Ketchup"},
	{"CASINO2", "Explosive Situation"},
	{"CASINO3", "You've Had Your Chips"},
	{"CASINO4", "Don Peyote"},
	{"CASINO5", "Intensive Care"},
	{"CASINO6", "The Meat Business"},
	{"CASINO7", "Fish in a Barrel"},
	{"CASINO9", "Freefall"},
	{"CAT", "Catalina missions"},
	{"CESAR1", "High Stakes, Low Rider"},
	{"COPCAR", "Vigilante (Sub-Mission)"},
	{"CRASH1", "Burning Desire"},
	{"CRASH2", "Doberman"},
	{"CRASH3", "Gray Imports"},
	{"DOC2", "Madd Dogg"},
	{"DS", "Back to School"},
	{"DSERT10", "Green Goo"},
	{"DSERT3", "Interdiction"},
	{"DSERT4", "Verdant Meadows"},
	{"DSERT5", "Learning to Fly"},
	{"DSERT6", "N.O.E."},
	{"DSERT8", "Black Project"},
	{"DSERT9", "Stowaway"},
	// {"DUAL", "Videogame"},
	{"FARLIE2", "T-Bone Mendez"},
	{"FARLIE3", "Mike Toreno"},
	{"FARLIE4", "Ran Fa Li"},
	{"FARLIE5", "Lure"},
	{"FIRETRK", "Firefighter (Sub-Mission)"},
	{"FTRAIN", "Freight Sub-Mission"},
	{"GARAGE1", "Wear Flowers In Your Hair"},
	{"GARAGE2", "Deconstruction"},
	// {"GRAV", "Let's Get Ready To Bumble (Video Game)"},
	{"GROVE1", "Beat Down on B Dup"},
	{"GROVE2", "Grove 4 Life"},
	// {"GYM", "Gym"},
	{"HEIST1", "Architectural Espionage"},
	{"HEIST2", "Dam And Blast"},
	{"HEIST3", "Key To Her Heart"},
	{"HEIST4", "Cop Wheels"},
	{"HEIST5", "Up, Up and Away!"},
	{"HEIST9", "Breaking the Bank at Caligula's"},
	{"INTRO1", "In the Beginning"},
	{"INTRO2", "Ryder"},
	{"KICKSTT", "Kickstart (Stadium)"},
	{"LAFIN1", "Reuniting The Families"},
	{"LAFIN2", "The Green Sabre"},
	{"LOWR", "Lowrider"},
	{"MAN_1", "A Home In The Hills"},
	{"MAN_2", "Vertical Bird"},
	{"MAN_3", "Home Coming"},
	{"MAN_5", "Cut Throat Business"},
	// {"OTB", "Inside Track (Horse Race Betting)"},
	{"PIMP", "Pimping (Sub-Mission)"},
	// {"POOL", "Pool (Mini-Game)"},
	{"QUARRY", "Quarry (Sub-Mission)"},
	{"RACETOR", "Race"},
	{"RIOT1", "Riot"},
	{"RIOT2", "Los Desperados"},
	{"RIOT4", "End Of The Line"},
	{"RYDER1", "Home Invasion"},
	{"RYDER2", "Robbing Uncle Sam"},
	{"RYDER3", "Catalyst"},
	{"SCRASH2", "Snail Trail"},
	// {"SHTR", "Go Go Space Monkey (Video Game)"},
	{"SMOKE1", "OG Loc"},
	{"SMOKE2", "Running Dog"},
	{"SMOKE3", "Wrong Side of the Tracks"},
	{"SMOKE4", "Just Business"},
	{"STREAL1", "Zeroing In"},
	{"STEAL2", "Test Drive"},
	{"STEAL4", "Customs Fast Track"},
	{"STEAL5", "Puncture Wounds"},
	{"STRAP1", "Life's a Beach"},
	{"STRAP2", "Madd Dogg's Rhymes"},
	{"STRAP3", "Management Issues"},
	{"STRAP4", "House Party"},
	// {"STUNT", "BMX/NRG-500 (Stunt)"},
	{"SWEET1", "Tagging Up Turf"},
	{"SWEET1B", "Cleaning The Hood"},
	{"SWEET2", "Nines And AK's"},
	{"SWEET3", "Drive-Thru"},
	{"SWEET4", "Drive-By"},
	{"SWEET5", "Sweet's Girl"},
	{"SWEET6", "Cesar Vialpando"},
	{"SWEET7", "Los Sepulcros"},
	{"SYN1", "Photo Opportunity"},
	{"SYN2", "Jizzy"},
	{"SYN3", "Outrider"},
	{"SYN4", "Ice Cold Killa"},
	{"SYN5", "Pier 69"},
	{"SYN6", "Toreno's Last Flight"},
	{"SYN7", "Yay Ka-Boom-Boom"},
	{"TAXI1", "Taxi Driver (Sub-Mission)"},
	{"TORENO1", "Monster"},
	{"TORENO2", "Highjack"},
	{"TRU1", "Body Harvest"},
	{"TRU2", "Are you going to San Fierro?"},
	{"TRUCK", "Trucking (Sub-Mission)"},
	{"VALET1", "555 We Tip"},
	{"VCR1", "Misappropriation"},
	{"VCR2", "High Noon"},
	{"WUZI1", "Mountain Cloud Boys"},
	{"WUZI2", "Amphibious Assault"},
	{"WUZI4", "The Da Nang Thang"},
	{"ZERO1", "Air Raid"},
	{"ZERO2", "Supply Lines..."},
	{"ZERO3", "Tanked Up"},
	{"ZERO4", "New Model Army"}
};