#include "stdafx.h"
Createmove_Hacks CM_Hacks;
PaintTraverse_Hacks PT_Hacks;
Draw_Model_Exec_Hacks DMEHacks;
player_info_t* Info = new player_info_t;

/*
NOTE:

TRY TO KEEP AMOUNT OF .CPP FILES TO A LOW AMOUND, OR IT TAKES A LONG TIME TO COMPILE

TO DO THIS, WE ARE KEEPING MOST FEATURES IN ONE .CPP SO WE DONT HAVE TO HAVE A .CPP
FOR EVERY FEATURE.

AIMBOTS HAVE THERE OWN CPP THOUGH.

*/

extern void dolegitshit();

#pragma region Create Move

bool bTeleportSwitch;
bool bTeleportZSwitch;
bool bTeleportInvertSwitch;
BYTE byteCorrupt[] = { 0xBE, 0x120 };
BYTE byteDeCorrupt[] = { 0xBE, 0x20 };
void Teleport()
{
	bool bTeleport = false;
	if (GetAsyncKeyState(Settings.GetSetting(Tab_Misc, Misc_Teliport)))
		bTeleport = true;

	if (bTeleport && !Settings.GetBoolSetting(Tab_Misc, Misc_Anti_Untrust))
	{
		BYTE* nulldata;
		static DWORD dwAddr = Utils.PatternSearch("client.dll", (PBYTE)"\xBE\x00\x00\x00\x00\x2B\xF1\x3B\xF3\x7D\x1F\x8B\x55\x0C\x8B\xC3", "x????xxxxxxxxxxx", NULL, NULL);
		auto bByte = bTeleportSwitch ? byteCorrupt : byteDeCorrupt;
		DWORD virtualProtect;
		VirtualProtect((LPVOID)(dwAddr), 4, PAGE_READWRITE, &virtualProtect);
		memcpy((LPVOID)(dwAddr), bByte, sizeof(bByte));
		VirtualProtect(reinterpret_cast<void*>(dwAddr), 4, virtualProtect, &virtualProtect);
		bTeleportSwitch = !bTeleportSwitch;
	}
}

void TeleportZ(Vector &angle)
{
	bool bTeleportZ = false;
	if (GetAsyncKeyState(Settings.GetSetting(Tab_Misc, Misc_Teliport)))
		bTeleportZ = true;

	if (bTeleportZ && !Settings.GetBoolSetting(Tab_Misc, Misc_Anti_Untrust))
	{
		angle.z = 99999999999999999999999.99999999999f;
		bTeleportZSwitch = !bTeleportZSwitch;
	}
}

void TeleportInvert(Vector &angle)
{
	Vector views = Hacks.CurrentCmd->viewangles;
	bool bTeleportInvert = false;
	static int invert = 9999999999999999999;
	if (GetAsyncKeyState(Settings.GetSetting(Tab_Misc, Misc_Teliport)))
		bTeleportInvert = true;

	if (bTeleportInvert && !Settings.GetBoolSetting(Tab_Misc, Misc_Anti_Untrust))
	{
		angle.y = -99999999999999999999999.99999999999f;
		angle.x = -99999999999999999999999.99999999999f;
		bTeleportInvertSwitch = !bTeleportInvertSwitch;
	}
}

//majmun18
bool bhopping = false;
void Createmove_Hacks::BunnyHop()
{
	bhopping = false;
	if ((Hacks.CurrentCmd->buttons & IN_JUMP))
	{
		bhopping = true;
		if (!(Hacks.LocalPlayer->GetFlags() & FL_ONGROUND))
			Hacks.CurrentCmd->buttons &= ~IN_JUMP;
		else
		{
			if (Settings.GetSetting(Tab_Ragebot, Ragebot_Duck == 2))
				Hacks.CurrentCmd->buttons &= ~IN_DUCK;
			UnLagNextTick = true;
			Hacks.SendPacket = true;
		}
	}
}

void Createmove_Hacks::AutoStrafer()
{
	if (bhopping) {
		if (Hacks.LocalPlayer->GetVecVelocity().Length2D() == 0 && (Hacks.CurrentCmd->forwardmove == 0 && Hacks.CurrentCmd->sidemove == 0)) {
			Hacks.CurrentCmd->forwardmove = 450.f;
		}
		else if (Hacks.CurrentCmd->forwardmove == 0 && Hacks.CurrentCmd->sidemove == 0) {
			if (Hacks.CurrentCmd->mousedx > 0 || Hacks.CurrentCmd->mousedx < -0) {
				Hacks.CurrentCmd->sidemove = Hacks.CurrentCmd->mousedx < 0.f ? -450.f : 450.f;
			}
			else {
				float temp1 = 5850.f / Hacks.LocalPlayer->GetVecVelocity().Length2D();
				Hacks.CurrentCmd->forwardmove = temp1;
				if (Hacks.CurrentCmd->forwardmove > 450)
					Hacks.CurrentCmd->forwardmove = 450;
				float temp = 450 - (temp1 - Hacks.CurrentCmd->forwardmove);
				if (temp < 450)
					temp = 450;
				Hacks.CurrentCmd->sidemove = (Hacks.CurrentCmd->command_number % 2) == 0 ? -temp : temp;
			}
		}
	}
}

float moveangle(Vector angles) {
	if (angles.x == 0 || angles.y == 0)
		return 0;
	float rise = angles.x;
	float run = angles.y;
	float value = rise / run;
	float theta = atan(value);
	theta = RAD2DEG(theta) + 90;
	return theta;
}
bool Createmove_Hacks::CircleStrafer(Vector &angles) {
	if (Settings.GetSetting(Tab_Misc, Misc_CircleStrafe_Enabled)) {
		static int add = 0;
		if (Settings.GetSetting(Tab_Misc, Misc_CircleStrafe_Mode)) {
			if (angles.y - add > 360)
				add -= 360;
			static bool shouldspin = false;
			static bool enabled = false;
			if (GetAsyncKeyState((int)Settings.GetSetting(Tab_Misc, Misc_CircleStrafe_Key))) {
				enabled = true;
			}
			else {
				enabled = false;
			}
			if (enabled) {
				shouldspin = true;
			}
			if (shouldspin) {
				Vector Dir;
				g_Math.angleVectors(Vector(0, add, 0), Dir);
				Dir *= 8218;
				Ray_t ray;
				CTraceWorldOnly filter;
				trace_t trace;
				ray.Init(Hacks.LocalPlayer->GetEyePosition(), Hacks.LocalPlayer->GetVecOrigin() + Dir);
				Interfaces.pTrace->TraceRay(ray, MASK_SHOT, &filter, &trace);
				auto temp = 3.4f / ((trace.endpos - Hacks.LocalPlayer->GetVecOrigin()).Length() / 100.f);
				if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 415) {
					if (temp < 3.4f)
						temp = 3.4f;
				}
				else if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 200) {
					if (temp < 6.8f)
						temp = 6.8f;
				}
				else {
					if (temp < 10.2f)
						temp = 10.2f;
				}
				if (enabled) {
					add += temp;
					Hacks.CurrentCmd->sidemove = -450;
				}
				else {
					if (angles.y - add < temp) {
						add = angles.y;
						shouldspin = false;
					}
					else
						add += temp;
				}
				angles.y = add;
			}
			else {
				add = angles.y;
				return false;
			}
		}
		else {
			if (angles.y - add > 360)
				add -= 360;
			static bool shouldspin = false;
			static bool enabled = false;
			if (GetAsyncKeyState((int)Settings.GetSetting(Tab_Misc, Misc_CircleStrafe_Key))) {
				enabled = true;
			}
			else {
				enabled = false;
			}
			if (enabled) {
				shouldspin = true;
			}
			if (shouldspin) {
				Vector Dir;
				g_Math.angleVectors(Vector(0, add, 0), Dir);
				Dir *= 8218;
				Ray_t ray;
				CTraceWorldOnly filter;
				trace_t trace;
				ray.Init(Hacks.LocalPlayer->GetEyePosition(), Hacks.LocalPlayer->GetVecOrigin() + Dir);
				Interfaces.pTrace->TraceRay(ray, MASK_SHOT, &filter, &trace);
				auto temp = 3.4f / ((trace.endpos - Hacks.LocalPlayer->GetVecOrigin()).Length() / 100.f);
				if (temp < 3.4f)
					temp = 3.4f;
				if (enabled) {
					add += temp;
					Hacks.CurrentCmd->sidemove = -450;
				}
				else {
					if (angles.y - add < temp) {
						add = angles.y;
						shouldspin = false;
					}
					else
						add += temp;
				}
				angles.y = add;
			}
			else {
				add = angles.y;
				return false;
			}
		}
	}
}

void Airstuck() {
	static bool enabled = false;
	static bool check = false;
	if (Settings.GetSetting(Tab_Misc, Misc_Airstuck_Enabled)) {
		if (GetAsyncKeyState((int)Settings.GetSetting(Tab_Misc, Misc_Airstuck_Key))) {
			if (!check) {
				enabled = !enabled;
				check = true;
			}
		}
		else {
			check = false;
		}
		if (enabled) {
			float ServerTime = Hacks.LocalPlayer->GetTickBase() * Interfaces.pGlobalVars->interval_per_tick;
			float NextPrimaryAttack = Hacks.LocalWeapon->NextPrimaryAttack();

			bool Shooting = false;
			if (NextPrimaryAttack > ServerTime)
				Shooting = true;


			if (!Shooting) {
				Hacks.CurrentCmd->tick_count = 99999999;
			}
		}
	}
}
void SetClanTag(const char* tag, const char* name)//190% paste
{

	static auto pSetClanTag = reinterpret_cast<void(__fastcall*)(const char*, const char*)>(((DWORD)(Utils.PatternSearch("engine.dll", (PBYTE)"\x53\x56\x57\x8B\xDA\x8B\xF9\xFF\x15\x00\x00\x00\x00\x6A\x24\x8B\xC8\x8B\x30", "xxxxxxxxx????xxxxxx", NULL, NULL))));

	pSetClanTag(tag, name);

}

void Clan_Tag() {

	if (Settings.GetSetting(Tab_Misc, Misc_Clan_Active)) {
		static int counter = 0;

		int value = Settings.GetSetting(Tab_Misc, Misc_Clan_Index);
		switch (value)
		{
		case 0:
		case 1: SetClanTag("DingoSquad.", "DingoSquadV1"); break;
		case 2: SetClanTag("DINGOSQUAD \r", "DingoSquadV1"); break;
			//case 2: SetClanTag("[VALV\xE1\xB4\xB1]", "Valve"); break;

		case 3:
		{
			if (Hacks.CurrentCmd->buttons & IN_ATTACK)
				SetClanTag("Aimbotting", "DingoSquadV1");
			else if (Hacks.CurrentCmd->buttons & IN_JUMP)
				SetClanTag("Bouncing", "DingoSquadV1");
			else if (Hacks.CurrentCmd->buttons & IN_DUCK)
				SetClanTag("Getting Low", "DingoSquadV1");
			else
				SetClanTag("DingoSquad.", "DingoSquadV1");
		}
		break;

		case 4:
		{
			static int motion = 0;
			int ServerTime = (float)Hacks.LocalPlayer->GetTickBase() * Interfaces.pGlobalVars->interval_per_tick;

			if (counter % 48 == 0)
				motion++;
			int value = ServerTime % 23;
			switch (value) {
			case 0:SetClanTag("                ", "DingoSquadV1"); break;
			case 1:SetClanTag("               D", "DingoSquadV1"); break;
			case 2:SetClanTag("              Di", "DingoSquadV1"); break;
			case 3:SetClanTag("            Din", "DingoSquadV1"); break;
			case 4:SetClanTag("           Ding", "DingoSquadV1"); break;
			case 5:SetClanTag("         Dingo", "DingoSquadV1"); break;
			case 6:SetClanTag("        DingoS", "DingoSquadV1"); break;
			case 7:SetClanTag("       DingoSq", "DingoSquadV1"); break;
			case 8:SetClanTag("     DingoSqu", "DingoSquadV1"); break;
			case 9:SetClanTag("    DingoSqua", "DingoSquadV1"); break;
			case 10:SetClanTag("  DingoSquad", "DingoSquadV1"); break;
			case 11:SetClanTag(" DingoSquad.", "DingoSquadV1"); break;
			case 12:SetClanTag("DingoSquad. ", "DingoSquadV1"); break;
			case 13:SetClanTag("ingoSquad.   ", "DingoSquadV1"); break;
			case 14:SetClanTag("ngoSquad.    ", "DingoSquadV1"); break;
			case 15:SetClanTag("goSquad.      ", "DingoSquadV1"); break;
			case 16:SetClanTag("oSquad.       ", "DingoSquadV1"); break;
			case 17:SetClanTag("Squad.         ", "DingoSquadV1"); break;
			case 18:SetClanTag("quad.          ", "DingoSquadV1"); break;
			case 19:SetClanTag("uad.             ", "DingoSquadV1"); break;
			case 20:SetClanTag("ad.               ", "DingoSquadV1"); break;
			case 21:SetClanTag("d.                ", "DingoSquadV1"); break;
			case 22:SetClanTag(".                  ", "DingoSquadV1"); break;
			case 23:SetClanTag("                   ", "DingoSquadV1"); break;
			}
			counter++;
		}
		break;

		case 5:
		{
			static int motion = 0;
			if (counter % 48 == 0)
				motion++;
			int ServerTime = (float)Hacks.LocalPlayer->GetTickBase() * Interfaces.pGlobalVars->interval_per_tick;

			int value = ServerTime % 8;
			switch (value) {
			case 0:SetClanTag("\r DingoSquad.", "DingoSquadV1"); break;
			case 1:SetClanTag("DingoSquad. \r", "DingoSquadV1"); break;
			case 2:SetClanTag("\r DingoSquad.", "DingoSquadV1"); break;
			case 3:SetClanTag("DingoSquad. \r", "DingoSquadV1"); break;
			case 4:SetClanTag("\r DingoSquad.", "DingoSquadV1"); break;
			case 5:SetClanTag("DingoSquad. \r", "DingoSquadV1"); break;
			case 6:SetClanTag("\r DingoSquad.", "DingoSquadV1"); break;
			case 7:SetClanTag("DingoSquad. \r", "DingoSquadV1"); break;
			}
			counter++;
		}
		break;
		}
	}
}
void Spamer() {
	int switchval = Settings.GetSetting(Tab_Misc, Misc_Spam_Index);
	stringstream message;
	message << "say";
	int static counter = 1;

	switch (switchval) {
	case 0:
	case 1: {
		int value = counter % 3;
		switch (value) {
		case 1: message << " DINGOSQUAD.COM | Premium Rage/Legit CSGO Cheat"; break;
		case 2: message << " DingoSquad > you"; break;
		case 3: message << " DINGOSQUAD.COM"; break;

		}

	}break;
	case 2:
	{
		int value = counter % 100 + 1;
		switch (value) {
		case 0:
		case 01: message << " dont upsetti hav some spagetti"; break;
		case 02: message << " eat my asse like a bufet (3 corse meal xd)"; break;
		case 03: message << " i ownt u in ur gay butth0le"; break;
		case 04: message << " umade noobe?"; break;
		case 05: message << " le troled hard"; break;
		case 06: message << " go wach naturo and play wif urself fag REKT"; break;
		case 07: message << " LOL i fuckd u so hard just like ur mum lst nit fag"; break;
		case 8: message << " u play liek a blynd stefen hawkin haha"; break;
		case 9: message << " ARE U GUEYS NEW??"; break;
		case 10: message << " are u as bad at life as u are in csgo??"; break;
		case 11: message << " omg this is 2 ezy are U even trying??"; break;
		case 12: message << " why dont u go play halo an fist ur butthol faget"; break;
		case 13: message << " hey granma is that u???? LOL so bad"; break;
		case 14: message << " time for you 2 uninstale the game shit stane"; break;
		case 15: message << " congrtulations ur the worlds worst csgo player"; break;
		case 16: message << " dose ur aim come in NOT NOOBE? LMAO"; break;
		case 17: message << " lol i troled u so hard *OWNED*"; break;
		case 18: message << " 'i lik 2 eat daddys logs of poo for lucnh while jackn off 2 naturo'- u"; break;
		case 19: message << " take a se4t faget $hitstain u got OWNDE"; break;
		case 20: message << " LOL scrub ur gettin rekt hardcroe"; break;
		case 21: message << " R u mad becouse ur bad nooby?"; break;
		case 22: message << " LMAO did u go to da buthurt king an g3t urself a butthurt with fries?!?"; break;
		case 23: message << " why dont u go and play manoppoly you noob"; break;
		case 24: message << " you hav no lyfe you cant evan play csgo propaly"; break;
		case 25: message << " im hi rite now on ganj but im stil ownen u xD"; break;
		case 26: message << " if u want my cum bake ask ur mum LOL"; break;
		case 27: message << " butdocter prognoses: OWND"; break;
		case 28: message << " cry 2 ur dads dick forver noob"; break;
		case 29: message << " lol troled autismal faget"; break;
		case 30: message << " LOL N3RD owned"; break;
		case 31: message << " 'i love to drink sprems all day'- u"; break;
		case 32: message << " crushd nerd do u want a baindaid for that LOL"; break;
		case 33: message << " lol rectal rekage ur so sh1t lol"; break;
		case 34: message << " ass states - [_] NOT REKT [X] REKT"; break;
		case 35: message << " lmao do u even try????"; break;
		case 36: message << " are u slippan off ur chaire cos ur ass is bleeding so hard??"; break;
		case 37: message << " u better get a towel for all ur tears faget"; break;
		case 38: message << " u got ass asassenated by me rofl"; break;
		case 39: message << " u wont shit agen thats how rekt ur ass is"; break;
		case 40: message << " i bet youre anus is sore from me ownen u LOL"; break;
		case 41: message << " im gonna record a fragshow so i can watch me pwn u ova and ova LMAO"; break;
		case 42: message << " i almost feel sorry for you hahahaha"; break;
		case 43: message << " lol why dont u play COD so i can own you there too"; break;
		case 44: message << " how dose it feel to be owneded so hartd??"; break;
		case 45: message << " rekt u lol another one for the fraghsow"; break;
		case 46: message << " if i was as bade as u i would kil myself"; break;
		case 47: message << " dont fell bad not ervry one can be goode"; break;
		case 48: message << " do u need some loob for ur butt so it doesnt hurt so much when i fuck u"; break;
		case 49: message << " spesciall delivary for CAPTEN BUTTHURT"; break;
		case 50: message << " wats wrong cant play wif ur dads dik in ur mouth????"; break;
		case 51: message << " maybe if u put down the cheseburgers u could kill me lol fat nerd"; break;
		case 52: message << " getting mad u virgan nerd??"; break;
		case 53: message << " butt docta prognosis: buttfustrated"; break;
		case 54: message << " <<< OWEND U >>>"; break;
		case 55: message << " if u were a fish you wuld be a sperm whael LOL"; break;
		case 56: message << " >mfw i ownd u"; break;
		case 57: message << " rekt u noob *OWNED*"; break;
		case 58: message << " ur gonna have 2 wear dipers now cos ur ass got SHREDED by me"; break;
		case 59: message << " y dont u take a short strole to the fagot store and buy some skills scrub"; break;
		case 60: message << " school3d by a 13yo lol u r rely bad"; break;
		case 61: message << " ur pathetic nerd its like u have parkensons"; break;
		case 62: message << " u just got promoted 2 cumcaptain prestige "; break;
		case 63: message << " lol pwnd"; break;
		case 64: message << " u just got butt raped lol TROLLED U"; break;
		case 65: message << " did u learn 2 aim from stevie wondar??? LOL"; break;
		case 66: message << " tell ur mum to hand the keyboard and mosue back"; break;
		case 67: message << " how does it feel to be shit on by a 13 yer old"; break;
		case 68: message << " r u into scat porns or some thing cos it feel's like u want me 2 shit on u"; break;
		case 69: message << " u play csgo like my granpa and hes ded"; break;
		case 70: message << " are u new or just bad?? noobe"; break;
		case 71: message << " u play csgo lik a midget playin basket ball"; break;
		case 72: message << " welcome to the noob scoole bus first stop ur house <<PWND>>"; break;
		case 73: message << " >mfw i rek u"; break;
		case 74: message << " 'i got my ass kiked so hard im shittn out my mouf' - u"; break;
		case 75: message << " <-(0.0)-<   dats u gettn ownd LOL"; break;
		case 76: message << " u just got ur ass ablitterated <<<RECKT>>>"; break;
		case 77: message << " c=3 (dats ur tiney dik rofl)"; break;
		case 78: message << " just leeve the game and let the real mans play"; break;
		case 79: message << " ur so bad u make ur noobe team look good"; break;
		case 80: message << " CONGRASTULATIONS YOU GOT FRIST PRIZE IN BEING BUTT MAD (BUT LAST IN PENIS SIZE LMAO)"; break;
		case 81: message << " im not even trying to pwn u its just so easy"; break;
		case 82: message << " im only 13 an im better than u haha XD"; break;
		case 83: message << " u just got raped"; break;
		case 84: message << " some one an ambulance cos u just got DE_STROYED"; break;
		case 85: message << " i hope u got birth control coz u got rapped"; break;
		case 86: message << " lol pwnd scrubb"; break;
		case 87: message << " you play lik a girl"; break;
		case 88: message << " 'i got fukd so hard dat im cummin shit n shittn cum'- u"; break;
		case 89: message << " ur gonna need tampons for ur ass afta that ownage"; break;
		case 90: message << " {{ scoooled u }}"; break;
		case 91: message << " (O.o) ~c======3 dats me jizzan on u"; break;
		case 92: message << " dont worry at least ur tryan XD"; break;
		case 93: message << " cya noob send me a post card from pwnd city ROFL"; break;
		case 94: message << " its ok if u keep practasing u will get bettar lol #rekt"; break;
		case 95: message << " 'evry time i fart 1 liter of cum sqerts out' - u"; break;
		case 96: message << " rofl i pwnd u scrub #420 #based #mlgskill"; break;
		case 97: message << " u fail, just like ur dads condom"; break;
		case 98: message << " if i pwnd u any harder it wud be animal abuse"; break;
		case 99: message << " uploaden this fragshow roflmao"; break;
		}
	}break;
	case 3:
	{
		static int lasti = 0;
		bool hasone = false;
		if (lasti > 98)
			lasti = 0;
		CBaseEntity * Player = Hacks.LocalPlayer;
		for (int i = lasti + 1; i < 99; i++) {
			Player = Interfaces.pEntList->GetClientEntity(i);
			if (!Player) continue;
			if (!Player->isAlive()
				|| Player->GetHealth() <= 0
				|| Player->IsDormant()
				|| (Player->GetTeam() == Hacks.LocalPlayer->GetTeam())
				|| Player == Hacks.LocalPlayer
				|| Player->HasGunGameImmunity())continue;
			if (!Interfaces.pEntList->GetClientEntity(i)) continue;

			Interfaces.pEngine->GetPlayerInfo(i, Info);
			char * name = Info->m_szPlayerName;
			char * place = Player->LastPlaceName();
			int health = Player->GetHealth();
			message << " " << name << " is " << place << " with " << health << "HP";
			lasti = i;
			hasone = true;
			break;
		}
		if (!hasone) {
			for (int i = 0; i < 99; i++) {
				Player = Interfaces.pEntList->GetClientEntity(i);
				if (!Player) continue;
				if (!Player->isAlive()
					|| Player->GetHealth() <= 0
					|| Player->IsDormant()
					|| (Player->GetTeam() == Hacks.LocalPlayer->GetTeam())
					|| Player == Hacks.LocalPlayer
					|| Player->HasGunGameImmunity())continue;
				if (!Interfaces.pEntList->GetClientEntity(i)) continue;

				Interfaces.pEngine->GetPlayerInfo(i, Info);
				char * name = Info->m_szPlayerName;
				char * place = Player->LastPlaceName();
				int health = Player->GetHealth();
				message << " " << name << " is " << place << " with " << health << "HP";
				lasti = i;
				hasone = true;
				break;
			}

		}

	}break;
	case 4:
	{
		static int lasti = 0;
		bool hasone = false;
		if (lasti > 98)
			lasti = 0;
		CBaseEntity * Player = Hacks.LocalPlayer;
		for (int i = lasti + 1; i < 99; i++) {
			Player = Interfaces.pEntList->GetClientEntity(i);
			if (!Player) continue;
			if (!Player->isAlive()
				|| Player->GetHealth() <= 0
				|| Player->IsDormant()
				|| (Player->GetTeam() != Hacks.LocalPlayer->GetTeam())
				|| Player == Hacks.LocalPlayer
				|| Player->HasGunGameImmunity())continue;
			if (!Interfaces.pEntList->GetClientEntity(i)) continue;

			Interfaces.pEngine->GetPlayerInfo(i, Info);
			char * name = Info->m_szPlayerName;
			char * place = Player->LastPlaceName();
			int health = Player->GetHealth();
			message << " " << name << " is " << place << " with " << health << "HP";
			lasti = i;
			hasone = true;
			break;
		}
		if (!hasone) {
			for (int i = 0; i < 99; i++) {
				Player = Interfaces.pEntList->GetClientEntity(i);
				if (!Player) continue;
				if (!Player->isAlive()
					|| Player->GetHealth() <= 0
					|| Player->IsDormant()
					|| (Player->GetTeam() == Hacks.LocalPlayer->GetTeam())
					|| Player == Hacks.LocalPlayer
					|| Player->HasGunGameImmunity())continue;
				if (!Interfaces.pEntList->GetClientEntity(i)) continue;

				Interfaces.pEngine->GetPlayerInfo(i, Info);
				char * name = Info->m_szPlayerName;
				char * place = Player->LastPlaceName();
				int health = Player->GetHealth();
				message << " " << name << " is " << place << " with " << health << "HP";
				lasti = i;
				hasone = true;
				break;
			}

		}

	}break;
	}
	counter++;
	string str(message.str());
	char * send = new char[str.length() + 1];
	std::strcpy(send, str.c_str());

	if (send != "say") {
		Interfaces.pEngine->ClientCmd_Unrestricted(send, 0);

	}
}


void Chat_Spamer() {
	if (Settings.GetSetting(Tab_Misc, Misc_Spam_Active)) {
		static int delay = 1;

		int modval = (Settings.GetSetting(Tab_Misc, Misc_Spam_Speed) + 1) * 10;
		if (delay % modval == 0) {
			Spamer();
		}
		delay++;
	}
}
void Name_Stealer()
{
	Clan_Tag();
	Chat_Spamer();

	if (Settings.GetBoolSetting(Tab_Misc, Misc_NameStealer))
	{
		stringstream NewName;
		int Index = Settings.GetSetting(Tab_Misc, Misc_NameStealer_Index);

		switch (Index)
		{
		case 0:
		case 1: NewName << "DINGOSQUAD.COM"; break;
		case 2: NewName << "AIMJUNKIES.NET"; break;
		case 3: NewName << " "; break;
		}

		int ran = rand() % 2;
		for (int i = 0; i < ran; i++)
		{
			NewName << " ";
		}
		if (Settings.GetSetting(Tab_Misc, Misc_NameStealer_Invis)) {
			NewName << " \r";
		}
		ConVar* Name = Interfaces.g_ICVars->FindVar("name");
		if (Name)
		{
			*(int*)((DWORD)&Name->fnChangeCallback + 0xC) = 0;
			Name->SetValue(NewName.str().c_str());
		}
	}
}
void Createmove_Hacks::CorrectMovement(Vector vOldAngles, CInput::CUserCmd* pCmd, Vector Viewangs)
{
	Vector vMove(pCmd->forwardmove, pCmd->sidemove, pCmd->upmove);
	float flSpeed = sqrt(vMove.x * vMove.x + vMove.y * vMove.y), flYaw;
	Vector vMove2;
	g_Math.VectorAngles3D(vMove, vMove2);

	flYaw = DEG2RAD(Viewangs.y - vOldAngles.y + vMove2.y);
	pCmd->forwardmove = cos(flYaw) * flSpeed;
	pCmd->sidemove = sin(flYaw) * flSpeed;

	if (Viewangs.x < -90.f || Viewangs.x > 90.f)
		pCmd->forwardmove = -pCmd->forwardmove;
}
extern Vector GetHitboxPOS(CPlayer* Enemy, int HitboxID);

bool anyAlive()
{
	for (INT i = 0; i <= Interfaces.pEntList->GetHighestEntityIndex(); i++)
	{
		CBaseEntity* pEntity = (CBaseEntity*)Interfaces.pEntList->GetClientEntity(i);
		if (pEntity == NULL)
			continue;
		if (!pEntity->isAlive())
			continue;
		if (pEntity == Hacks.LocalPlayer)
			continue;
		if (pEntity->IsDormant())
			continue;
		if (pEntity->GetTeam() == Hacks.LocalPlayer->GetTeam())
			continue;
		player_info_t info;
		if (!(Interfaces.pEngine->GetPlayerInfo(pEntity->GetIndex(), &info)))
			continue;
		return true;
	}
	return false;
}

void Createmove_Hacks::MovePacket(CInput* thisptr, void* _EAX, int sequence_number, float input_sample_frametime, bool active)
{
	if (Interfaces.pEngine->IsConnected() && Interfaces.pEngine->IsInGame())
	{
#pragma region Get User Cmd
		CInput::CUserCmd* cmdlist = *(CInput::CUserCmd**)((DWORD)Interfaces.pInput + 0xEC);
		CInput::CUserCmd* cmd = &cmdlist[sequence_number % 150];
		CInput::CVerifiedUserCmd* verifiedCmdList = *(CInput::CVerifiedUserCmd**)((DWORD)Interfaces.pInput + 0xF0);
		CInput::CVerifiedUserCmd* VerifiedCmd = &verifiedCmdList[sequence_number % 150];
#pragma endregion

#pragma region Sort Out Hack Manger
		Hacks.CurrentCmd = cmd;
		Name_Stealer();

		Vector oldAngles = Hacks.CurrentCmd->viewangles;
		if (!Hacks.LocalPlayer)return;
		Hacks.LocalWeapon = Hacks.LocalPlayer->GetActiveBaseCombatWeapon();
		if (!Hacks.LocalWeapon) return;
#pragma endregion
		Vector OrigAng = Hacks.CurrentCmd->viewangles;
#pragma region Do Hacks
		if (Hacks.LocalPlayer)
		{

			if (Hacks.LocalPlayer->isAlive())
			{
				bool alive = anyAlive();


				Settings.weaponconfigs();

				// Had to comment this out since you didn't push code for snakestrafer. 
				/*
				if (Settings.GetSetting(Tab_Misc, Misc_CircleStrafe_Mode))
				SnakeStrafer(OrigAng);
				*/

				if (!CircleStrafer(OrigAng)) {
					if (Settings.GetBoolSetting(Tab_Misc, Misc_Auto_Strafer))
						AutoStrafer();
				}

				if (Settings.GetBoolSetting(Tab_Misc, Misc_Bunny_Hop))
					BunnyHop();

				if (Settings.GetBoolSetting(Tab_Misc, Misc_Teleport_Enable) && !Settings.GetBoolSetting(Tab_Misc, Misc_Anti_Untrust))
				{
					int telval = Settings.GetSetting(Tab_Misc, Misc_Teliport_Type);
					switch (telval) {
					case 1:
						Teleport();
						break;
					case 2:
						TeleportZ(Hacks.CurrentCmd->viewangles);
						break;
					case 3:
						TeleportInvert(Hacks.CurrentCmd->viewangles);
						break;
					}
				}
				if (!(Settings.GetSetting(Tab_Ragebot, Ragebot_AntiAimTargets))) {
					alive = true;
				}

				if (alive)
				{
#pragma region Prediction
					// Can Do Prediction Because We Have The Move Helper, If Not Pattern Search It And Try Again Next Packet
					if (Interfaces.g_pMoveHelper)
					{
						int TickBase = Hacks.LocalPlayer->GetTickBase(); // Get The Tick Base
						int Old_Time = Interfaces.pGlobalVars->curtime; // Get Current Time (Client Not Server)
						int Old_Frame_Time = Interfaces.pGlobalVars->frametime; // Get Frame Time (Client)

						Interfaces.pGlobalVars->curtime = TickBase * Interfaces.pGlobalVars->interval_per_tick; // Set Time To Server Time
						Interfaces.pGlobalVars->frametime = Interfaces.pGlobalVars->interval_per_tick; // Set Framerate To Tick Rate

						CMoveData Move_Data; // Make A Move Data
						memset(&Move_Data, 0, sizeof(Move_Data));
						bool Ducked = false;
						if (Hacks.CurrentCmd->buttons & IN_DUCK)
							Ducked = true;
						int duvkval = Settings.GetSetting(Tab_Ragebot, Ragebot_Duck);
						switch (duvkval) {
						case 2:
							Hacks.CurrentCmd->buttons &= ~IN_DUCK;
							break;
						}
						Interfaces.g_pMoveHelper->SetHost(Hacks.LocalPlayer); // Set Myself To Get Predicted
						Interfaces.g_pPred->SetupMove(Hacks.LocalPlayer, Hacks.CurrentCmd, Interfaces.g_pMoveHelper, &Move_Data); // Setup Prediction
						Interfaces.g_pGameMovement->ProcessMovement(Hacks.LocalPlayer, &Move_Data); // Process Prediction
						Interfaces.g_pPred->FinishMove(Hacks.LocalPlayer, Hacks.CurrentCmd, &Move_Data); // Finish Prediction
						Interfaces.g_pGameMovement->DecayPunchAngles();
						Interfaces.g_pMoveHelper->SetHost(NULL); // Remove Self From Move Helper
						if (Ducked)
							Hacks.CurrentCmd->buttons |= IN_DUCK;

						Interfaces.pGlobalVars->curtime = Old_Time;  // Reset Times To Correct Time
						Interfaces.pGlobalVars->frametime = Old_Frame_Time; // Reset Frame Time To Correct Time

						CBaseCombatWeapon* pWeapon = Hacks.LocalPlayer->GetActiveBaseCombatWeapon();
						if (pWeapon)
							pWeapon->UpdateAccuracyPenalty();
					}
					else
					{
						// if we dont have a pointer to Move Helper, Find One.
						Interfaces.g_pMoveHelper = **(IMoveHelper***)(Utils.PatternSearch("client.dll", (PBYTE)"\x8B\x0D\x00\x00\x00\x00\x8B\x45\x00\x51\x8B\xD4\x89\x02\x8B\x01", "xx????xx?xxxxxxx", NULL, NULL) + 2);
					}
#pragma endregion Player And Others Prediction


					if (Settings.GetBoolSetting(Tab_Ragebot, Ragebot_Enable))
						Ragebot.NewMove();


					int duvkval = Settings.GetSetting(Tab_Ragebot, Ragebot_Duck);
					switch (duvkval) {
					case 2:
						if (Hacks.CurrentCmd->buttons & IN_ATTACK)
							Hacks.CurrentCmd->buttons &= ~IN_DUCK;
						break;
					}
				}
				if (Settings.GetSetting(Tab_LegitBot, Legit_Activate) || Settings.GetBoolSetting(Tab_LegitBot, Trigger_Active)) {
					if (Settings.GetSetting(Tab_LegitBot, Legit_ME))
						Legitbot.Move();
					else
						dolegitshit();
				}

				//if(Settings.GetSetting(Tab_LegitBot, Old_Legit_Activate))
				//dolegitshit();

				Airstuck();

				/* AutoPistol */
				if (Settings.GetSetting(Tab_Ragebot, Ragebot_AutoShoot)) {
					if ((Hacks.CurrentCmd->buttons & IN_ATTACK) && (Hacks.LocalWeapon->NextPrimaryAttack()
						- ((float)Hacks.LocalPlayer->GetTickBase()
							* Interfaces.pGlobalVars->interval_per_tick) > 0) && Hacks.LocalWeapon->isPistoleW()) Hacks.CurrentCmd->buttons &= ~IN_ATTACK;
				}



#pragma region AntiUntrust
				if (Settings.GetSetting(Tab_Misc, Misc_Anti_Untrust))
				{
					Ragebot.FastLargeNormalise(Hacks.CurrentCmd->viewangles);
					while (Hacks.CurrentCmd->viewangles.y < -180.0f) Hacks.CurrentCmd->viewangles.y += 360.0f;
					while (Hacks.CurrentCmd->viewangles.y > 180.0f) Hacks.CurrentCmd->viewangles.y -= 360.0f;
					if (Hacks.CurrentCmd->viewangles.x > 89.0f) Hacks.CurrentCmd->viewangles.x = 89.0f;
					if (Hacks.CurrentCmd->viewangles.x < -89.0f) Hacks.CurrentCmd->viewangles.x = -89.0f;
					Hacks.CurrentCmd->viewangles.z = 0;
				}
#pragma endregion 
				Vector simplifiedang = Hacks.CurrentCmd->viewangles;
				Vector simplifiedorg = OrigAng;
				if (!Settings.GetSetting(Tab_Misc, Misc_Anti_Untrust))
				{

					Ragebot.FastLargeNormaliseMove(simplifiedang);
					while (simplifiedang.y < -180.0f) simplifiedang.y += 360.0f;
					while (simplifiedang.y > 180.0f) simplifiedang.y -= 360.0f;

					Ragebot.FastLargeNormaliseMove(simplifiedorg);
					while (simplifiedorg.y < -180.0f) simplifiedorg.y += 360.0f;
					while (simplifiedorg.y > 180.0f) simplifiedorg.y -= 360.0f;

				}
				CorrectMovement(simplifiedorg, Hacks.CurrentCmd, simplifiedang);
				Hacks.LastAngles = Hacks.CurrentCmd->viewangles;
				if (!Settings.GetSetting(Tab_Misc, Misc_Anti_Untrust) && alive) {
					//nothing
				}
				if (Settings.GetSetting(Tab_Misc, Misc_Anti_Untrust))
				{
					Ragebot.FastLargeNormalise(Hacks.CurrentCmd->viewangles);
					while (Hacks.CurrentCmd->viewangles.y < -180.0f) Hacks.CurrentCmd->viewangles.y += 360.0f;
					while (Hacks.CurrentCmd->viewangles.y > 180.0f) Hacks.CurrentCmd->viewangles.y -= 360.0f;
					if (Hacks.CurrentCmd->viewangles.x > 89.0f) Hacks.CurrentCmd->viewangles.x = 89.0f;
					if (Hacks.CurrentCmd->viewangles.x < -89.0f) Hacks.CurrentCmd->viewangles.x = -89.0f;
					Hacks.CurrentCmd->viewangles.z = 0;
				}


			}

		}
#pragma endregion

#pragma region Set Cmds
		VerifiedCmd->m_cmd = *Hacks.CurrentCmd;
		VerifiedCmd->m_crc = Hacks.CurrentCmd->GetChecksum();
#pragma endregion
	}
}
#pragma endregion Movement Related Hacks

#pragma region Paint Traverse



bool PaintTraverse_Hacks::PaintTraverse_IsGoodPlayer_ESP(CBaseEntity* Target)
{
	if (!Target)
		return false;

	if (Target == Hacks.LocalPlayer)
		return false;

	if (Target->IsDormant())
		return false;

	if (!Target->IsPlayer())
		return false;

	if (Target->GetHealth() == 0)
		return false;

	if (!Target->isAlive())
		return false;


	return true;
}
struct DHitbox
{
	DHitbox(void)
	{
		dhitbox = -1;
	}

	DHitbox(int newHitBox)
	{
		dhitbox = newHitBox;
	}

	int  dhitbox;
	Vector points[9];
};
bool GetHitbox(CBaseEntity* Player, DHitbox *box)
{
	if (!Player)
		return false;

	matrix3x4 matrix[128];
	if (!Player->SetupBones(matrix, 128, 0x00000100, GetTickCount64()))
		return false;
	const model_t* mod = Player->GetModel();
	if (!mod)
		return false;
	studiohdr_t* hdr = Interfaces.g_pModelInfo->GetStudioModel(mod);
	if (!hdr)
		return false;
	mstudiohitboxset_t* set = hdr->GetHitboxSet(0);
	if (!set)
		return false;
	mstudiobbox_t* hitbox = set->pHitbox(box->dhitbox);
	if (!hitbox)
		return false;

	// center and all the corners of the hitbox hehe
	Vector points[] = { ((hitbox->bbmin + hitbox->bbmax) * .5f),
		Vector(hitbox->bbmin.x, hitbox->bbmin.y, hitbox->bbmin.z),
		Vector(hitbox->bbmin.x, hitbox->bbmax.y, hitbox->bbmin.z),
		Vector(hitbox->bbmax.x, hitbox->bbmax.y, hitbox->bbmin.z),
		Vector(hitbox->bbmax.x, hitbox->bbmin.y, hitbox->bbmin.z),
		Vector(hitbox->bbmax.x, hitbox->bbmax.y, hitbox->bbmax.z),
		Vector(hitbox->bbmin.x, hitbox->bbmax.y, hitbox->bbmax.z),
		Vector(hitbox->bbmin.x, hitbox->bbmin.y, hitbox->bbmax.z),
		Vector(hitbox->bbmax.x, hitbox->bbmin.y, hitbox->bbmax.z) };

	for (int index = 0; index <= 8; ++index)
	{
		g_Math.VectorTransform2(points[index], matrix[hitbox->bone], box->points[index]);
	}

	return true;
}
void DFixHitbox(DHitbox* box)
{
	box->points[0].z += 10;
	for (int index = 0; index <= 8; ++index)
	{
		trace_t tr;
		Ray_t ray;
		CTraceFilter filter;
		ray.Init(box->points[index], box->points[0]);
		Interfaces.pTrace->TraceRay(ray, MASK_SHOT, &filter, &tr);

		box->points[index] = tr.endpos;
	}
}
extern Vector pointaim;
extern Vector Delta2Screen(Vector delta, int w, int h);
bool drawhitbox(CBaseEntity* Player) {

	Vector a;
	Vector b;

	if (!Player)
		return 0;

	matrix3x4 matrix[128];
	if (!Player->SetupBones(matrix, 128, 0x00000100, GetTickCount64())) return 0;
	const model_t* mod = Player->GetModel();
	if (!mod) return 0;
	studiohdr_t* hdr = Interfaces.g_pModelInfo->GetStudioModel(mod);
	if (!hdr) return 0;
	mstudiohitboxset_t* set = hdr->GetHitboxSet(0);
	if (!set) return 0;
	mstudiobbox_t* hitbox = set->pHitbox((int)CSGOHitboxID::Pelvis);
	if (!hitbox) return 0;
	Vector vMin, vMax, vCenter, sCenter;
	g_Math.VectorTransform2(hitbox->bbmin, matrix[hitbox->bone], vMin);
	g_Math.VectorTransform2(hitbox->bbmax, matrix[hitbox->bone], vMax);
	Vector angs = Vector(0, 0, 0);
	CalcAngle(vMin, vMax, angs);
	Interfaces.g_pDebugOverlay->ScreenPosition(vMin, a);
	Interfaces.g_pDebugOverlay->ScreenPosition(vMax, b);

	Interfaces.pSurface->DrawSetColor(255, 9, 0, 255);
	Interfaces.pSurface->DrawFilledRect(a.x, a.y, a.x + 4, a.y + 4);
	Interfaces.pSurface->DrawSetColor(0, 9, 255, 255);
	Interfaces.pSurface->DrawFilledRect(b.x, b.y, b.x + 4, b.y + 4);


	return true;
}

void Draw_Corner_Box_Faster(ESP_Box Box, CBaseEntity* Target)
{
	int Line_Size = (Box.y - Box.h) / 8;
	int Line_Size2 = (Box.y - Box.h) / 6;

	//top inwards
	Interfaces.pSurface->DrawLine(Box.w, Box.y, Box.w + Line_Size, Box.y);
	Interfaces.pSurface->DrawLine(Box.x, Box.y, Box.x - Line_Size, Box.y);

	//top downwards
	Interfaces.pSurface->DrawLine(Box.x, Box.y, Box.x, Box.y - Line_Size);
	Interfaces.pSurface->DrawLine(Box.w, Box.y, Box.w, Box.y - Line_Size);

	//bottom inwards
	Interfaces.pSurface->DrawLine(Box.x, Box.h, Box.x - Line_Size, Box.h);
	Interfaces.pSurface->DrawLine(Box.w, Box.h, Box.w + Line_Size, Box.h);

	//bottom upwards
	Interfaces.pSurface->DrawLine(Box.x, Box.h, Box.x, Box.h + Line_Size);
	Interfaces.pSurface->DrawLine(Box.w, Box.h, Box.w, Box.h + Line_Size);

	//outlines
	Interfaces.pSurface->DrawSetColor(0, 0, 0, 200);

	//top inwards
	Interfaces.pSurface->DrawLine(Box.w, Box.y - 1, Box.w + Line_Size, Box.y - 1);
	Interfaces.pSurface->DrawLine(Box.x, Box.y - 1, Box.x - Line_Size, Box.y - 1);
	//inlines
	Interfaces.pSurface->DrawLine(Box.w - 1, Box.y + 1, Box.w + Line_Size, Box.y + 1);
	Interfaces.pSurface->DrawLine(Box.x + 1, Box.y + 1, Box.x - Line_Size, Box.y + 1);

	// top downwards
	Interfaces.pSurface->DrawLine(Box.x - 1, Box.y - 1, Box.x - 1, Box.y - Line_Size);
	Interfaces.pSurface->DrawLine(Box.w + 1, Box.y - 1, Box.w + 1, Box.y - Line_Size);
	//inlines
	Interfaces.pSurface->DrawLine(Box.x + 1, Box.y, Box.x + 1, Box.y - Line_Size);
	Interfaces.pSurface->DrawLine(Box.w - 1, Box.y, Box.w - 1, Box.y - Line_Size);

	//bottom inwards
	Interfaces.pSurface->DrawLine(Box.x, Box.h + 1, Box.x - Line_Size, Box.h + 1);
	Interfaces.pSurface->DrawLine(Box.w, Box.h + 1, Box.w + Line_Size, Box.h + 1);
	//inlines
	Interfaces.pSurface->DrawLine(Box.x + 1, Box.h - 1, Box.x - Line_Size, Box.h - 1);
	Interfaces.pSurface->DrawLine(Box.w - 1, Box.h - 1, Box.w + Line_Size, Box.h - 1);

	//bottom upwards
	Interfaces.pSurface->DrawLine(Box.x - 1, Box.h + 1, Box.x - 1, Box.h + Line_Size);
	Interfaces.pSurface->DrawLine(Box.w + 1, Box.h + 1, Box.w + 1, Box.h + Line_Size);
	//inlines
	Interfaces.pSurface->DrawLine(Box.x + 1, Box.h, Box.x + 1, Box.h + Line_Size);
	Interfaces.pSurface->DrawLine(Box.w - 1, Box.h, Box.w - 1, Box.h + Line_Size);

}

ESP_Box PaintTraverse_Hacks::Get_Box(CBaseEntity* Entity)
{
	ESP_Box result;
	Vector vEye = Entity->GetBonePos(6);
	Vector vPelvis = GetHitboxPOS_Ent(Entity, (int)CSGOHitboxID::Pelvis);
	Vector vFoot = GetHitboxPOS_Ent(Entity, (int)CSGOHitboxID::LeftFoot);

	Vector LvEye = vEye;
	if (vPelvis.z - vFoot.z > 30)
		LvEye.z -= 77;
	else
		LvEye.z -= 57;
	vEye += Vector(0, 0, 10);
	Vector ScreenTop, ScreenBottom;
	Interfaces.g_pDebugOverlay->ScreenPosition(vEye, ScreenTop);
	Interfaces.g_pDebugOverlay->ScreenPosition(LvEye, ScreenBottom);
	int height = ScreenBottom.y - ScreenTop.y;
	int Width = height / 2;
	ScreenTop.x += Width / 2;
	ScreenBottom.x -= Width / 2;
	result.x = ScreenBottom.x;
	result.y = ScreenTop.y;
	result.w = ScreenTop.x;
	result.h = ScreenBottom.y;
	return result;
}

bool PaintTraverse_Hacks::IsVisable(CBaseEntity* Target, int boneID)
{
	CBaseEntity* copy = Target;
	trace_t Trace;
	Vector start = Hacks.LocalPlayer->GetEyePosition();
	Vector end = GetHitboxPOS_Ent(Target, boneID);
	UTIL_TraceLine(start, end, MASK_SOLID, Hacks.LocalPlayer, 0, &Trace);
	if (Trace.m_pEnt == copy) return true;
	if (Trace.fraction == 1.0f) return true;
	return false;
}

float sepssub(Vector source, Vector pos) {
	Vector dist;
	dist.x = abs(source.x - pos.x);
	dist.y = abs(source.y - pos.y);
	float xx = dist.x*dist.x + dist.y*dist.y;
	float distance = sqrt(xx);
	return distance;
}

extern float distance(Vector source, Vector pos);

RECT GetTextSize(DWORD font, const char* text) {
	size_t origsize = strlen(text) + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t wcstring[newsize];
	mbstowcs_s(&convertedChars, wcstring, origsize, text, _TRUNCATE);
	RECT rect; int x, y;
	Interfaces.pSurface->GetTextSize(font, wcstring, x, y);
	rect.left = x; rect.bottom = y;
	rect.right = x;
	return rect;
}

void PaintTraverse_Hacks::DrawBox(CBaseEntity* Target, int r, int g, int b, int a)
{//
 //drawhitbox(Target);
	int Health = Target->GetHealth();
	int Armor = Target->GetArmorValue();
	ESP_Box	BOX = Get_Box(Target);
	int Line_Size = (BOX.y - BOX.h) / 8;
	int Line_Size2 = (BOX.y + BOX.h) / 8;
	if (Settings.GetSetting(Tab_Visuals, Vis_Box) != 0 || Settings.GetSetting(Tab_Visuals, Vis_Box) != 1)
	{
		Interfaces.pSurface->DrawSetColor(r, g, b, a);
		int swi = Settings.GetSetting(Tab_Visuals, Vis_Box);
		switch (swi) {
		case 2:
			Interfaces.pSurface->DrawSetColor(r, g, b, a);
			Interfaces.pSurface->DrawOutlinedRect(BOX.x, BOX.y, BOX.w, BOX.h);
			Interfaces.pSurface->DrawSetColor(0, 0, 0, 185);
			Interfaces.pSurface->DrawOutlinedRect(BOX.x - 1, BOX.y - 1, BOX.w + 1, BOX.h + 1);
			Interfaces.pSurface->DrawOutlinedRect(BOX.x + 1, BOX.y + 1, BOX.w - 1, BOX.h - 1);
			Interfaces.pSurface->DrawSetColor(r, g, b, a);
			break;
		case 3:
			Draw_Corner_Box_Faster(BOX, Target);
			break;
		}
	}
	if (Settings.GetSetting(Tab_Visuals, Vis_Health)) {
		if (Health > 100)
			Health = 100;
		int healthG = Health * 2.55;
		int healthR = 255 - healthG;
		Interfaces.pSurface->DrawSetColor(0, 0, 0, 150);
		Interfaces.pSurface->DrawOutlinedRect(BOX.x - 5, BOX.y - 1, BOX.x - 1, BOX.h + 1);
		Interfaces.pSurface->DrawOutlinedRect(BOX.w + 1, BOX.y - 1, BOX.w + 5, BOX.h + 1);

		double Filler = BOX.y - BOX.h;
		Filler /= 100;
		Filler *= Health;
		int pos = Filler + BOX.h;

		double Filler1 = BOX.y - BOX.h;
		Filler1 /= 100;
		Filler1 *= Armor;
		int pos1 = Filler1 + BOX.h;

		if (Health > 0) {
			Interfaces.pSurface->DrawSetColor(healthR, healthG, 0, 255);
			Interfaces.pSurface->DrawOutlinedRect(BOX.x - 4, pos, BOX.x - 2, BOX.h);
		}

		if (Armor > 0) {
			Interfaces.pSurface->DrawSetColor(80, 135, 190, 255);
			Interfaces.pSurface->DrawOutlinedRect(BOX.w + 2, pos1, BOX.w + 4, BOX.h);
		}
	}

	int aTextRed = Settings.GetSetting(Tab_Other, Other_TextRed);
	int aTextGreen = Settings.GetSetting(Tab_Other, Other_TextGreen);
	int aTextBlue = Settings.GetSetting(Tab_Other, Other_TextBlue);
	int aTextAlpha = Settings.GetSetting(Tab_Other, Other_TextAlpha);
	if (Settings.GetSetting(Tab_Visuals, Vis_Name))
	{
		Interfaces.pEngine->GetPlayerInfo(Target->GetIndex(), Info);
		RECT nameSize = GetTextSize(Hacks.Font_ESP, Info->m_szPlayerName);
		Interfaces.pSurface->DrawT(((BOX.x + BOX.w) / 2) - (nameSize.right / 2), BOX.y - 16, CColor(255, 255, 255, 255), Hacks.Font_ESP, false, Info->m_szPlayerName);
	}

	if (Settings.GetBoolSetting(Tab_Visuals, Vis_Weapon))
	{
		CBaseCombatWeapon* Weapon = Target->GetActiveBaseCombatWeapon();
		RECT textSize = GetTextSize(Hacks.Font_ESP, Weapon->GetWeaponName());
		Interfaces.pSurface->DrawT(((BOX.x + BOX.w) / 2) - (textSize.right / 2), BOX.h + 2, CColor(255, 255, 255, 255), Hacks.Font_ESP, false, Weapon->GetWeaponName());
	}
	if (Settings.GetSetting(Tab_Visuals, Vis_Background)) {
		int Health = Target->GetHealth();
		char hp[256];
		sprintf(hp, "%d", Health);
		if (Settings.GetSetting(Tab_Visuals, Vis_Health)) {
			Interfaces.pSurface->DrawT(BOX.w + 13, BOX.y, CColor(255, 255, 255, 255), Hacks.Font_ESP, false, hp);
			Interfaces.pSurface->DrawT(BOX.w + 33, BOX.y, CColor(0, 200, 255, 255), Hacks.Font_ESP, false, "HP");
		}
		else {
			Interfaces.pSurface->DrawT(BOX.w + 3, BOX.y, CColor(255, 255, 255, 255), Hacks.Font_ESP, false, hp);
			Interfaces.pSurface->DrawT(BOX.w + 23, BOX.y, CColor(0, 200, 255, 255), Hacks.Font_ESP, false, "HP");
		}
	}
	if (Settings.GetSetting(Tab_Visuals, Vis_AimLines)) {
		Interfaces.pSurface->DrawSetColor(r, g, b, a);
		int snapsize = (BOX.y - BOX.h) / 4;
		int width = 0;
		int height = 0;
		Interfaces.pEngine->GetScreenSize(width, height);
		//Shanxs said do from cross hair befor eit was height - 10
		Interfaces.pSurface->DrawLine(width / 2, height - 10, BOX.x - snapsize, BOX.h);
	}
	float dist = distance(Target->GetEyePosition(), Hacks.LocalPlayer->GetEyePosition());
}
void PaintTraverse_Hacks::DrawSkeleton(CBaseEntity* pEntity, CColor col)
{
	if (Settings.GetSetting(Tab_Visuals, Vis_Skel)) {
		studiohdr_t* pStudioHdr = Interfaces.g_pModelInfo->GetStudioModel(pEntity->GetModel());

		if (!pStudioHdr)
			return;

		Vector vParent, vChild, sParent, sChild;

		for (int j = 0; j < pStudioHdr->numbones; j++)
		{
			mstudiobone_t* pBone = pStudioHdr->GetBone(j);

			if (pBone && (pBone->flags & BONE_USED_BY_HITBOX) && (pBone->parent != -1))
			{

				vChild = pEntity->GetBonePos(j);
				vParent = pEntity->GetBonePos(pBone->parent);
				Interfaces.g_pDebugOverlay->ScreenPosition(vParent, sParent);
				Interfaces.g_pDebugOverlay->ScreenPosition(vChild, sChild);
				int red = 0;
				int green = 0;
				int blue = 0;
				int alpha = 0;
				col.GetColor(red, green, blue, alpha);
				Interfaces.pSurface->DrawSetColor(red, green, blue, alpha);
				Interfaces.pSurface->DrawLine(sParent[0], sParent[1], sChild[0], sChild[1]);
			}
		}
	}
}
bool cclassweapon(int val) {
	bool ret = false;
	if (val == (int)CSGOClassID::CAK47
		|| val >= 200 && val <= 250
		|| val == (int)CSGOClassID::CSCAR17
		|| val == (int)CSGOClassID::CDEagle)
		ret = true;
	return ret;
}

void PaintTraverse_Hacks::DrawESP()
{
	if (!Hacks.LocalPlayer) return;

	CBaseEntity* Target;
	int Max_Entitys = Interfaces.pEntList->GetHighestEntityIndex();

	/* Paint Shit */

	static DWORD dwDrawOnRadar = *(DWORD*)(DWORD)Utils.PatternSearch("client.dll", (PBYTE)"\xA1\x00\x00\x00\x00\x85\xC0\x74\x06\x05", "x????xxxxx", NULL, NULL);

	for (int i = 0; i < Max_Entitys; i++)
	{
		Target = Interfaces.pEntList->GetClientEntity(i);

		if (!Target)
			continue;

		ClientClass* cClass = (ClientClass*)Target->GetClientClass();

		if (cClass->m_ClassID == (int)CSGOClassID::CCSPlayer)
		{
			if (!PaintTraverse_IsGoodPlayer_ESP(Target))
				continue;
			if (false)//ingame radar
			{

				//BYTE* pDrawOnRadar = (BYTE*)((*(DWORD*)dwDrawOnRadar) + 0xD1D + i);
				// 1 = draw on radar
				//*pDrawOnRadar = 1;
			}
			int Red;
			int Blue;
			int Green;
			int Alpha;
			bool seeable = IsVisable(Target, 0);
			if (Target->GetTeam() == Hacks.LocalPlayer->GetTeam()) {
				if (Settings.GetSetting(Tab_Visuals, Vis_Box_Team)) {
					if (Target->GetTeam() == 3) {
						if (seeable) {
							Red = Settings.GetSetting(Tab_Other, Other_Esp_CT_Visible_Red);
							Green = Settings.GetSetting(Tab_Other, Other_Esp_CT_Visible_Green);
							Blue = Settings.GetSetting(Tab_Other, Other_Esp_CT_Visible_Blue);
							Alpha = Settings.GetSetting(Tab_Other, Other_Esp_CT_Visible_Alpha);
							DrawBox(Target, Red, Green, Blue, Alpha);
							DrawSkeleton(Target, CColor(Red, Green, Blue, Alpha));
						}
						else {
							Red = Settings.GetSetting(Tab_Other, Other_Esp_CT_inVisible_Red);
							Green = Settings.GetSetting(Tab_Other, Other_Esp_CT_inVisible_Green);
							Blue = Settings.GetSetting(Tab_Other, Other_Esp_CT_inVisible_Blue);
							Alpha = Settings.GetSetting(Tab_Other, Other_Esp_CT_inVisible_Alpha);
							if (!Settings.GetSetting(Tab_Visuals, Vis_Box_Vis)) {
								DrawBox(Target, Red, Green, Blue, Alpha);
								DrawSkeleton(Target, CColor(Red, Green, Blue, Alpha));
							}
						}
					}
					else {
						if (seeable) {
							Red = Settings.GetSetting(Tab_Other, Other_Esp_T_Visible_Red);
							Green = Settings.GetSetting(Tab_Other, Other_Esp_T_Visible_Green);
							Blue = Settings.GetSetting(Tab_Other, Other_Esp_T_Visible_Blue);
							Alpha = Settings.GetSetting(Tab_Other, Other_Esp_T_Visible_Alpha);
							DrawBox(Target, Red, Green, Blue, Alpha);
							DrawSkeleton(Target, CColor(Red, Green, Blue, Alpha));
						}
						else {
							Red = Settings.GetSetting(Tab_Other, Other_Esp_T_inVisible_Red);
							Green = Settings.GetSetting(Tab_Other, Other_Esp_T_inVisible_Green);
							Blue = Settings.GetSetting(Tab_Other, Other_Esp_T_inVisible_Blue);
							Alpha = Settings.GetSetting(Tab_Other, Other_Esp_T_inVisible_Alpha);
							if (!Settings.GetSetting(Tab_Visuals, Vis_Box_Vis)) {
								DrawBox(Target, Red, Green, Blue, Alpha);
								DrawSkeleton(Target, CColor(Red, Green, Blue, Alpha));
							}
						}
					}
				}
			}
			else {
				if (Target->GetTeam() == 3) {
					if (seeable) {
						Red = Settings.GetSetting(Tab_Other, Other_Esp_CT_Visible_Red);
						Green = Settings.GetSetting(Tab_Other, Other_Esp_CT_Visible_Green);
						Blue = Settings.GetSetting(Tab_Other, Other_Esp_CT_Visible_Blue);
						Alpha = Settings.GetSetting(Tab_Other, Other_Esp_CT_Visible_Alpha);
						DrawBox(Target, Red, Green, Blue, Alpha);
						DrawSkeleton(Target, CColor(Red, Green, Blue, Alpha));
					}
					else {
						Red = Settings.GetSetting(Tab_Other, Other_Esp_CT_inVisible_Red);
						Green = Settings.GetSetting(Tab_Other, Other_Esp_CT_inVisible_Green);
						Blue = Settings.GetSetting(Tab_Other, Other_Esp_CT_inVisible_Blue);
						Alpha = Settings.GetSetting(Tab_Other, Other_Esp_CT_inVisible_Alpha);
						if (!Settings.GetSetting(Tab_Visuals, Vis_Box_Vis)) {
							DrawBox(Target, Red, Green, Blue, Alpha);
							DrawSkeleton(Target, CColor(Red, Green, Blue, Alpha));
						}
					}
				}
				else {
					if (seeable) {
						Red = Settings.GetSetting(Tab_Other, Other_Esp_T_Visible_Red);
						Green = Settings.GetSetting(Tab_Other, Other_Esp_T_Visible_Green);
						Blue = Settings.GetSetting(Tab_Other, Other_Esp_T_Visible_Blue);
						Alpha = Settings.GetSetting(Tab_Other, Other_Esp_T_Visible_Alpha);
						DrawBox(Target, Red, Green, Blue, Alpha);
						DrawSkeleton(Target, CColor(Red, Green, Blue, Alpha));
					}
					else {
						Red = Settings.GetSetting(Tab_Other, Other_Esp_T_inVisible_Red);
						Green = Settings.GetSetting(Tab_Other, Other_Esp_T_inVisible_Green);
						Blue = Settings.GetSetting(Tab_Other, Other_Esp_T_inVisible_Blue);
						Alpha = Settings.GetSetting(Tab_Other, Other_Esp_T_inVisible_Alpha);
						if (!Settings.GetSetting(Tab_Visuals, Vis_Box_Vis)) {
							DrawBox(Target, Red, Green, Blue, Alpha);
							DrawSkeleton(Target, CColor(Red, Green, Blue, Alpha));
						}
					}
				}
			}

		}
		else if (false)//cClass->m_ClassID == (int)CSGOClassID::CPlantedC4 &&
		{
			CBaseEntity* me = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
			Vector vOrig; Vector vScreen;
			CBaseEntity* ent = Interfaces.pEntList->GetClientEntity(i);
			vOrig = ent->GetAbsOrigin();
			CCSBomb* Bomb = (CCSBomb*)ent;
			CColor col = CColor(255, 255, 255, 255);
			Interfaces.g_pDebugOverlay->ScreenPosition(vOrig, vScreen);
			float flBlow = Bomb->GetC4BlowTime();
			float TimeRemaining = flBlow - (Interfaces.pGlobalVars->interval_per_tick * me->GetTickBase());
			char buffer[256];

			if (TimeRemaining < 0)
			{
				col = CColor(45, 255, 45, 255);
				TimeRemaining = 0;
			}
			cout << TimeRemaining << endl;
			sprintf_s(buffer, "Bomb: %.1f", TimeRemaining);
			Interfaces.pSurface->DrawT(vScreen.x, vScreen.y, col, Hacks.Font_ESP, false, buffer);
		}
		else if (cclassweapon(cClass->m_ClassID)) {
			Vector vOrig; Vector vScreen; Vector cor1; Vector cor2;
			CBaseEntity* ent = Interfaces.pEntList->GetClientEntity(i);
			vOrig = ent->GetAbsOrigin();
			if (vOrig.y >= -5 && vOrig.y <= 5 && vOrig.x >= -5 && vOrig.x <= 5) {
			}
			else
			{
				Vector corner1 = vOrig + Vector(40, 40, 0);
				Vector corner2 = vOrig + Vector(-40, -40, 0);
				Interfaces.pSurface->DrawSetColor(255, 255, 255, 255);
				Interfaces.g_pDebugOverlay->ScreenPosition(corner1, cor1);
				Interfaces.g_pDebugOverlay->ScreenPosition(corner2, cor2);

				//Interfaces.pSurface->DrawOutlinedRect(cor1.x, cor1.y, cor2.x, cor2.y);

				CBaseCombatWeapon* weapon = (CBaseCombatWeapon*)ent;
				CColor col = CColor(255, 255, 255, 255);
				Interfaces.g_pDebugOverlay->ScreenPosition(vOrig, vScreen);

				Interfaces.pSurface->DrawT(vScreen.x, vScreen.y, col, Hacks.Font_ESP, false, weapon->GetPName());

			}
		}
	}
	/* Glow Shit */
	CGlowObjectManager* GlowObjectManager = (CGlowObjectManager*)Interfaces.g_pGlowObjectManager;
	CGlowObjectManager::GlowObjectDefinition_t* glowEntity;
	if (Settings.GetSetting(Tab_Visuals, Vis_Glow)) {
		for (int i = 0; i < GlowObjectManager->size; i++)
		{
			glowEntity = &GlowObjectManager->m_GlowObjectDefinitions[i];
			CBaseEntity* Entity = glowEntity->getEntity();

			if (!Entity) continue;

			ClientClass* cClass = (ClientClass*)Entity->GetClientClass();

			if (cClass->m_ClassID == (int)CSGOClassID::CCSPlayer)
			{
				if (!PaintTraverse_IsGoodPlayer_ESP(Entity))
					continue;

				int Red;
				int Blue;
				int Green;
				int Alpha;
				bool seeable = IsVisable(Entity, 0);

				if (Entity->GetTeam() == Hacks.LocalPlayer->GetTeam()) {
					if (!seeable) {

						Red = Settings.GetSetting(Tab_Other, Other_Glow_inVisible_Red);
						Green = Settings.GetSetting(Tab_Other, Other_Glow_inVisible_Green);
						Blue = Settings.GetSetting(Tab_Other, Other_Glow_inVisible_Blue);
						Alpha = Settings.GetSetting(Tab_Other, Other_Glow_inVisible_Alpha);
						if (!Settings.GetSetting(Tab_Visuals, Vis_Glow_Vis) && Settings.GetBoolSetting(Tab_Visuals, Vis_Glow_Team)) {
							glowEntity->set(CColor(Red, Green, Blue, Alpha));

						}

					}
					else {
						Red = Settings.GetSetting(Tab_Other, Other_Glow_Visible_Red);
						Green = Settings.GetSetting(Tab_Other, Other_Glow_Visible_Green);
						Blue = Settings.GetSetting(Tab_Other, Other_Glow_Visible_Blue);
						Alpha = Settings.GetSetting(Tab_Other, Other_Glow_Visible_Alpha);
						if (Settings.GetBoolSetting(Tab_Visuals, Vis_Glow_Team))
							glowEntity->set(CColor(Red, Green, Blue, Alpha));

					}

				}
				else {
					if (!seeable) {

						Red = Settings.GetSetting(Tab_Other, Other_Glow_inVisible_Red);
						Green = Settings.GetSetting(Tab_Other, Other_Glow_inVisible_Green);
						Blue = Settings.GetSetting(Tab_Other, Other_Glow_inVisible_Blue);
						Alpha = Settings.GetSetting(Tab_Other, Other_Glow_inVisible_Alpha);
						if (!Settings.GetSetting(Tab_Visuals, Vis_Glow_Vis)) {
							glowEntity->set(CColor(Red, Green, Blue, Alpha));

						}
					}
					else {
						Red = Settings.GetSetting(Tab_Other, Other_Glow_Visible_Red);
						Green = Settings.GetSetting(Tab_Other, Other_Glow_Visible_Green);
						Blue = Settings.GetSetting(Tab_Other, Other_Glow_Visible_Blue);
						Alpha = Settings.GetSetting(Tab_Other, Other_Glow_Visible_Alpha);
						glowEntity->set(CColor(Red, Green, Blue, Alpha));

					}

				}

			}
		}
	}

}

void PaintTraverse_Hacks::bombESP() {
	bool scoreopen = true;
	if (scoreopen) {
		CBaseEntity * Target;
		int playernumber = 0;
		for (int i = 0; i < 99; i++)
		{
			Target = Interfaces.pEntList->GetClientEntity(i);

			if (!Target)
				continue;

			ClientClass* cClass = (ClientClass*)Target->GetClientClass();

			if (cClass->m_ClassID == (int)CSGOClassID::CCSPlayer)
			{
				playernumber++;
			}
		}

	}
}

void PaintTraverse_Hacks::DrawPaintTraverseHacks()
{
	Hacks.LocalPlayer = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
	if (!Hacks.LocalPlayer) return;
	Hacks.LocalWeapon = Hacks.LocalPlayer->GetActiveBaseCombatWeapon();

	// Draw Cheats Here
	if (Settings.GetSetting(Tab_Visuals, Vis_Active)) {
		DrawESP();
		//bombESP();
	}

}
#pragma endregion All Drawing Related Hacks

#pragma region Draw Model Execute

void Draw_Model_Exec_Hacks::InitKeyValues(KeyValues* keyValues, char* name)
{
	DWORD dwFunction = (DWORD)Utils.PatternSearch("client.dll", (PBYTE)"\x68\x00\x00\x00\x00\x8B\xC8\xE8\x00\x00\x00\x00\x89\x45\xFC\xEB\x07\xC7\x45\x00\x00\x00\x00\x00\x8B\x03\x56", "x????xxx????xxxxxxx?????xxx", NULL, NULL); dwFunction += 7; dwFunction = dwFunction + *reinterpret_cast<PDWORD_PTR>(dwFunction + 1) + 5;
	__asm
	{
		push name
		mov ecx, keyValues
		call dwFunction
	}
}

void Draw_Model_Exec_Hacks::LoadFromBuffer(KeyValues* keyValues, char const *resourceName, const char *pBuffer)
{
	DWORD dwFunction = (DWORD)Utils.PatternSearch("client.dll", (PBYTE)"\xE8\x00\x00\x00\x00\x8A\xD8\xFF\x15\x00\x00\x00\x00\x84\xDB", "x????xxxx????xx", NULL, NULL); dwFunction = dwFunction + *reinterpret_cast<PDWORD_PTR>(dwFunction + 1) + 5;
	__asm
	{
		push 0
		push 0
		push 0
		push pBuffer
		push resourceName
		mov ecx, keyValues
		call dwFunction
	}
}

IMaterial *Draw_Model_Exec_Hacks::Create_Material(bool Ignore, bool Lit, bool Wireframe)
{
	static int created = 0;
	static const char tmp[] =
	{
		"\"%s\"\
		\n{\
		\n\t\"$basetexture\" \"vgui/white_additive\"\
		\n\t\"$envmap\" \"\"\
		\n\t\"$model\" \"1\"\
		\n\t\"$flat\" \"1\"\
		\n\t\"$nocull\" \"0\"\
		\n\t\"$selfillum\" \"1\"\
		\n\t\"$halflambert\" \"1\"\
		\n\t\"$nofog\" \"0\"\
		\n\t\"$ignorez\" \"%i\"\
		\n\t\"$znearer\" \"0\"\
		\n\t\"$wireframe\" \"%i\"\
        \n}\n"
	}; // SHHH I DIDENT PASTE THIS .___.// Looks like you did

	char* baseType = (Lit == true ? "VertexLitGeneric" : "UnlitGeneric");
	char material[512];
	char name[512];
	sprintf_s(material, sizeof(material), tmp, baseType, (Ignore) ? 1 : 0, (Wireframe) ? 1 : 0);
	sprintf_s(name, sizeof(name), "#Dingo_Chams_%i.vmt", created); ++created;
	KeyValues* keyValues = (KeyValues*)malloc(sizeof(KeyValues));
	InitKeyValues(keyValues, baseType);
	LoadFromBuffer(keyValues, name, material);
	IMaterial *createdMaterial = Interfaces.pMaterialSystem->CreateMaterial(name, keyValues);
	createdMaterial->IncrementReferenceCount();
	return createdMaterial;
}

bool Draw_Model_Exec_Hacks::Do_Chams(void* thisptr, int edx, void* ctx, void* state, const ModelRenderInfo_t &pInfo, matrix3x4 *pCustomBoneToWorld)
{
	static IMaterial* Covered_Lit = Create_Material(true, true, false);
	static IMaterial* Visable_Lit = Create_Material(false, true, false);


	/* Making Materials Is Slow, So Make Sure They Are Defined As Static */
	//fix this line below i changed it
	//from this bool flat = Settings.GetSetting(Tab_Visuals, Cham_Flat);
	bool flat = Settings.GetSetting(Tab_Visuals, Cham_Active);
	Covered_Lit->SetMaterialVarFlag(MATERIAL_VAR_TRANSLUCENT, flat);
	Visable_Lit->SetMaterialVarFlag(MATERIAL_VAR_TRANSLUCENT, flat);

	if (Settings.GetSetting(Tab_Visuals, Cham_Active)) {
		CBaseEntity* Model_Entity = Interfaces.pEntList->GetClientEntity(pInfo.entity_index);
		const char* Model_Name = Interfaces.g_pModelInfo->GetModelName((model_t*)pInfo.pModel);

		if (!Model_Entity)
			return false;

		if (strstr(Model_Name, "arm") && Settings.GetSetting(Tab_Visuals, Cham_Hands))
		{
			Covered_Lit->ColorModulate(Settings.GetSetting(Tab_Other, Other_Cham_Hands_Red) / 255,
				Settings.GetSetting(Tab_Other, Other_Cham_Hands_Green) / 255,
				Settings.GetSetting(Tab_Other, Other_Cham_Hands_Blue) / 255);

			Visable_Lit->ColorModulate(Settings.GetSetting(Tab_Other, Other_Cham_Hands_Red) / 255,
				Settings.GetSetting(Tab_Other, Other_Cham_Hands_Green) / 255,
				Settings.GetSetting(Tab_Other, Other_Cham_Hands_Blue) / 255);

			Visable_Lit->AlphaModulate(Settings.GetSetting(Tab_Other, Other_Cham_Hands_Alpha) / 255);
			Covered_Lit->AlphaModulate(Settings.GetSetting(Tab_Other, Other_Cham_Hands_Alpha) / 255);

			Interfaces.g_pModelRender->ForcedMaterialOverride(Covered_Lit, OVERRIDE_NORMAL);
			Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

			Interfaces.g_pModelRender->ForcedMaterialOverride(Visable_Lit, OVERRIDE_NORMAL);
			Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

			cout << "Test" << endl;

			return true;

		}

		if (Model_Entity->IsPlayer() && Model_Entity != Hacks.LocalPlayer && strstr(Model_Name, "models/player") && true /*  */)
		{
			if (Model_Entity->GetTeam() != Hacks.LocalPlayer->GetTeam())
			{
				Covered_Lit->ColorModulate(
					Settings.GetSetting(Tab_Other, Other_Cham_Enemy_inVisible_Red) / 255,
					Settings.GetSetting(Tab_Other, Other_Cham_Enemy_inVisible_Green) / 255,
					Settings.GetSetting(Tab_Other, Other_Cham_Enemy_inVisible_Blue) / 255);
				Covered_Lit->AlphaModulate(Settings.GetSetting(Tab_Other, Other_Cham_Enemy_inVisible_Alpha) / 255);

				Visable_Lit->ColorModulate(
					Settings.GetSetting(Tab_Other, Other_Cham_Enemy_Visible_Red) / 255,
					Settings.GetSetting(Tab_Other, Other_Cham_Enemy_Visible_Green) / 255,
					Settings.GetSetting(Tab_Other, Other_Cham_Enemy_Visible_Blue) / 255);
				Visable_Lit->AlphaModulate(Settings.GetSetting(Tab_Other, Other_Cham_Enemy_Visible_Alpha) / 255);

			}
			else
			{
				Covered_Lit->ColorModulate(
					Settings.GetSetting(Tab_Other, Other_Cham_Team_inVisible_Red) / 255,
					Settings.GetSetting(Tab_Other, Other_Cham_Team_inVisible_Green) / 255,
					Settings.GetSetting(Tab_Other, Other_Cham_Team_inVisible_Blue) / 255);
				Covered_Lit->AlphaModulate(Settings.GetSetting(Tab_Other, Other_Cham_Team_inVisible_Alpha) / 255);

				Visable_Lit->ColorModulate(
					Settings.GetSetting(Tab_Other, Other_Cham_Team_Visible_Red) / 255,
					Settings.GetSetting(Tab_Other, Other_Cham_Team_Visible_Green) / 255,
					Settings.GetSetting(Tab_Other, Other_Cham_Team_Visible_Blue) / 255);
				Visable_Lit->AlphaModulate(Settings.GetSetting(Tab_Other, Other_Cham_Team_Visible_Alpha) / 255);

			}


			if (!Model_Entity->isAlive())
			{
				Covered_Lit->ColorModulate(0.75f, 0.75f, 0.75f);
				Visable_Lit->ColorModulate(1.f, 1.f, 1.f);
			}

			if (Model_Entity->HasGunGameImmunity())
			{
				Covered_Lit->AlphaModulate(0.75f);
			}
			else
			{
				Covered_Lit->AlphaModulate(1.f);
			}

			if (Settings.GetSetting(Tab_Visuals, Cham_OnlyVis)) {
				Covered_Lit->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
			}
			else {
				Covered_Lit->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);

			}
			if (Model_Entity->GetTeam() == Hacks.LocalPlayer->GetTeam()) {
				if (Settings.GetSetting(Tab_Visuals, Cham_ShowTeam)) {
					Interfaces.g_pModelRender->ForcedMaterialOverride(Covered_Lit, OVERRIDE_NORMAL);
					Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
					Interfaces.g_pModelRender->ForcedMaterialOverride(Visable_Lit, OVERRIDE_NORMAL);
					Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
				}
				else {
					Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

					Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

				}
			}
			else {
				Interfaces.g_pModelRender->ForcedMaterialOverride(Covered_Lit, OVERRIDE_NORMAL);
				Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
				Interfaces.g_pModelRender->ForcedMaterialOverride(Visable_Lit, OVERRIDE_NORMAL);
				Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

			}

			return true;
		}

		else if (strstr(Model_Name, "weapon") && Settings.GetSetting(Tab_Visuals, Cham_Weapon) /*  */)
		{

			Visable_Lit->ColorModulate(Settings.GetSetting(Tab_Other, Other_Cham_Weapon_Red) / 255,
				Settings.GetSetting(Tab_Other, Other_Cham_Weapon_Green) / 255,
				Settings.GetSetting(Tab_Other, Other_Cham_Weapon_Blue) / 255);

			Visable_Lit->AlphaModulate(Settings.GetSetting(Tab_Other, Other_Cham_Weapon_Alpha) / 255);

			Interfaces.g_pModelRender->ForcedMaterialOverride(Visable_Lit, OVERRIDE_NORMAL);
			Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

			return true;
		}

	}
	return false;

}

#pragma endregion