#include "stdafx.h"
#include "Skins.h"

CHackManager Hacks;

VMTManager VMTPanel;
VMTManager VMTClient;
VMTManager VMTModelRender;
VMTManager VMTClientMode;
VMTManager VMTD3DDevice9;
VMTManager VMTGameEvent;

CPlayerList Playerlist;

bool warmup = false;

bool __fastcall Hooked_FireEventClientSide(void *ecx, void* edx, IGameEvent* pEvent) {
	if (!pEvent)
		return Hacks.oFireEventClientSide(ecx, pEvent);

	const char* szEventName = pEvent->GetName();

	if (!strcmp(szEventName, "round_freeze_end"))
		warmup = false;

	if (!strcmp(szEventName, "round_prestart"))
		warmup = true;

	if (!strcmp(szEventName, "player_death"))
		ApplyCustomKillIcon(pEvent);

	if (!strcmp(szEventName, "game_newmap")) {
		if (g_ViewModelCFG.size() >= 1)
			g_ViewModelCFG.clear();
		SetViewModelCFG();
	}

	return Hacks.oFireEventClientSide(ecx, pEvent);
}

void __stdcall Hooked_PaintTraverse(unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{
	Hacks.oPaintTraverse(Interfaces.pPanel, vguiPanel, forceRepaint, allowForce);

	if (strcmp("FocusOverlayPanel", Interfaces.pPanel->GetName(vguiPanel)))
	{
		return;
	}


	/* DRAWING HERE */
	PT_Hacks.DrawPaintTraverseHacks();

	DrawMenu();

	//Interfaces.pSurface->DrawT2(100, 100, CColor(0, 255, 255, 255), Hacks.Font_Tahoma, "Tohomahhh!1!");


}

bool infakelag = false;
bool fl = false;
int flTimer = -1;
bool lastfltick = -1;
int factor = 0;

void doFakeLag() {
	int fakeLagType = (int)Settings.GetSetting(Tab_Misc, Misc_Fakelagtype);
	if (fakeLagType > 0 && Settings.GetBoolSetting(Tab_Ragebot, Ragebot_Aimbot)) {
		fl = true;
		auto Velocity = Hacks.LocalPlayer->GetVecVelocity().Length() * Interfaces.pGlobalVars->interval_per_tick;
		auto tmpLagTicks = 0;
		switch (fakeLagType) {
		case 1:
			Hacks.SendPacket = true;
			infakelag = false;
			break;
		case 2:
			if (flTimer > 13) {
				Hacks.SendPacket = true;
				infakelag = false;
				flTimer = -1;
			}
			else {
				if (flTimer == 13)
					lastfltick = true;
				Hacks.SendPacket = false;
				infakelag = true;
			}
			flTimer++;
			break;
		case 3: // I think this one is adaptive.
			do {
				factor = tmpLagTicks;
				if ((tmpLagTicks * Velocity) > 68.f)
					break;
				tmpLagTicks += 1;
				if (((tmpLagTicks + 1) * Velocity) > 68.f)
					break;
				tmpLagTicks += 2;
			} while (tmpLagTicks <= 12);
			if (flTimer > factor) {
				Hacks.SendPacket = true;
				infakelag = false;
				flTimer = -1;
			}  else {
				if (flTimer == factor)
					lastfltick = true;
				Hacks.SendPacket = false;
				infakelag = true;
			}
			flTimer++;
			break;
		case 4:
			if (flTimer > 13 || Hacks.LocalPlayer->GetFlags() & FL_ONGROUND) {
				Hacks.SendPacket = true;
				infakelag = false;
				flTimer = -1;
			} else {
				if (flTimer == 13)
					lastfltick = true;
				Hacks.SendPacket = false;
				infakelag = true;
			}
			flTimer++;
			break;
		case 5:
			break;
		}
	}
}

bool bSendPacket = true;
void __declspec(naked) __fastcall Hooked_Createmove(CInput* thisptr, void* _EAX, int sequence_number, float input_sample_frametime, bool active)
{

	__asm
	{
		MOV bSendPacket, BL
		PUSH EBP
			MOV EBP, ESP
			SUB ESP, 8
			PUSHAD
			PUSH active
			PUSH input_sample_frametime
			PUSH sequence_number
			CALL Hacks.oCreateMove
	}
	Hacks.LocalPlayer = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
	if (Hacks.LocalPlayer)
	{
		Hacks.SendPacket = bSendPacket;

		doFakeLag();

		CM_Hacks.MovePacket(thisptr, _EAX, sequence_number, input_sample_frametime, active);

		bSendPacket = Hacks.SendPacket;
	}
	__asm
	{
		POPAD
		MOV BL, bSendPacket
			MOV ESP, EBP
			POP EBP
			RETN 0x0C
	}
}

int bullets = 1;

bool bullettime() {
	if (!Hacks.LocalWeapon)return false;
	float flServerTime = (float)Hacks.LocalPlayer->GetTickBase() * Interfaces.pGlobalVars->interval_per_tick;
	float flNextPrimaryAttack = Hacks.LocalWeapon->NextPrimaryAttack();

	bool BulletTime = true;

	if (flNextPrimaryAttack > flServerTime)
		BulletTime = false;

	return BulletTime;

}
void bilcount() {
	//bool bulletfired = true;
	static bool bulletcounter = 0;
	if (true) {
		bool bulletfired = bullettime();
		static bool firsttick = true;
		if (!bulletfired) {
			if (firsttick) {
				bullets++;
				firsttick = false;

			}
			bulletcounter++;
			if (bulletcounter > 20) {
				bulletcounter = 0;
				firsttick = true;
			}
		}
		else {
			firsttick = true;
			bulletcounter = 0;
		}
	}
}
bool switchf = false;
bool shouldresolve() {
	if (switchf) {
		switchf = false;
		return true;
	}
	else {
		switchf = true;
		return true;
	}
}


/*
Aimware Anti aims

Pitch:
Down = 90

Emotion = 88.9948

Fake down =  -90

Angel Down = 0

Angel up = 0
These values are realitivy to where they are facing except those where I say static



Yaw:
Backwards = 180
Fake backwards
1 = 180
2 = 0
Jitter
1 = 160
2 = 0
3 = -160
Jitter Sync
1 = 160
2 = 0
3 = 160
Sideways = 90
Fake sideways
1 = 90
2 = -90
Fake Forward
1 = 0
2 = 180
SlowSpinn / fast spin
CBF
Angel backwards = 180
Angel inverse
STATIC = 0
Angel Spin
= + 80
Angel Fake spin
1 = STATIC = 180
2 = +80 (per thing so really + 160)
Faken Angel
STATIC  = 180
*/
double skinz[200][6];
extern int realselected[10];
void setskins(std::string settings) {
	// sets up settings char to a vector looks like this "0:3:2:2" ie tab-setting-value
	std::string tovector = settings;

	std::stringstream ss(tovector);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> settingarray(begin, end);
	//Gets how many settings to set
	int size = settingarray.size();
	for (int i = 0; i< size - 1; i++)
	{
		// Gets the setting we are dealing with
		std::string meme = settingarray[i];
		//Converst the string to char array
		for (int i = 0; i<meme.length(); i++)
		{
			if (meme[i] == ':')
				meme[i] = ' ';
		}
		vector<double> indi;
		stringstream ss(meme);
		double temp;
		while (ss >> temp)
			indi.push_back(temp);
		//0:1:2:8
		// Sets the setting
		skinz[(int)indi[0]][(int)indi[1]] = (double)indi[2];
	}

}
void loadskin() {
	int number = Settings.GetSetting(Tab_Config, Config_type);
	if (CreateDirectory("C:/dingointernal/", NULL) || ERROR_ALREADY_EXISTS == GetLastError())
	{

	}
	std::string savetype = "c:/dingointernal/skin.txt";

	string txt;
	ifstream file(savetype);

	if (file.is_open())
		while (file.good())
			getline(file, txt);
	file.close();
	setskins(txt);
}

void writeskinfile(std::string string) {
	int number = Settings.GetSetting(Tab_Config, Config_type);

	if (CreateDirectory("C:/dingointernal/", NULL) || ERROR_ALREADY_EXISTS == GetLastError())
	{

	}
	std::string savetype = "c:/dingointernal/skin.txt";
	ofstream myfile;
	myfile.open(savetype);
	myfile << string;
	myfile.close();
}
std::string skinstosave() {
	std::string stra;

	for (int i = 0; i < 200; i++) {

		for (int a = 0; a < 6; a++) {
			stra.append(to_string(i));
			stra.append(":");
			stra.append(to_string(a));
			stra.append(":");
			stra.append(to_string(skinz[i][a]));
			stra.append(" ");
		}
	}
	writeskinfile(stra);

	return stra;

}

void setskin(int id) {
	id = realselected[0];//Settings.GetSetting(Tab_Other, Other_SkinChanger_ID);
	skinz[id][0] = realselected[1];//344;//Settings.GetSetting(Tab_Other, Other_SkinChanger_FallBack);
	skinz[id][1] = Settings.GetSetting(Tab_Other, Other_SkinChanger_Quality);
	skinz[id][2] = Settings.GetSetting(Tab_Other, Other_SkinChanger_Seed);
	skinz[id][3] = Settings.GetSetting(Tab_Other, Other_SkinChanger_StatTrak);
	skinz[id][4] = Settings.GetSetting(Tab_Other, Other_SkinChanger_Wear);

}

void __stdcall Hooked_OverrideView(CViewSetup* pSetup)
{
	if (Settings.GetBoolSetting(Tab_Visuals, Vis_Active))
	{
		if (Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected() && Settings.GetSetting(Tab_Visuals, Vis_FOV) != 0)
		{
			if (!Hacks.LocalPlayer->m_bIsScoped()) {
				pSetup->fov = Settings.GetSetting(Tab_Visuals, Vis_FOV);
			}
		}
	}
}
extern void CalcAngle(Vector src, Vector dst, Vector &angles);
Vector GetHitboxPOS(CPlayer* Player, int HitboxID);


void  __stdcall Hooked_Frame_Stage_Notify(ClientFrameStage_t curStage)
{
	while (curStage == FRAME_NET_UPDATE_POSTDATAUPDATE_START) {
		CBaseEntity* pLocal = Hacks.LocalPlayer;
		if (!pLocal || !pLocal->isAlive())
			break;

		UINT *hWeapons = (UINT*)((DWORD)pLocal + 0x2DE8); // DT_BasePlayer -> m_hMyWeapons
		if (!hWeapons)
			break;

		player_info_t pLocalInfo;
		Interfaces.pEngine->GetPlayerInfo(Interfaces.pEngine->GetLocalPlayer(), &pLocalInfo);

		for (int i = 0; hWeapons[i]; i++) {
			CBaseAttributableItem* pWeapon = (CBaseAttributableItem*)Interfaces.pEntList->GetClientEntityFromHandle((HANDLE)hWeapons[i]);
			if (!pWeapon)
				continue;

			int nWeaponIndex = *pWeapon->GetItemDefinitionIndex();
			ApplyCustomModel(pLocal, pWeapon, nWeaponIndex);

			if (pLocalInfo.m_nXuidLow != *pWeapon->GetOriginalOwnerXuidLow())
				continue;

			if (pLocalInfo.m_nXuidHigh != *pWeapon->GetOriginalOwnerXuidHigh())
				continue;

			ApplyCustomSkin(pWeapon, nWeaponIndex);

			*pWeapon->GetAccountID() = pLocalInfo.m_nXuidLow;
		}

		break;
	}

	CBaseEntity* pLocal = Hacks.LocalPlayer;
	Vector aimPunch;
	Vector viewPunch;

	if (Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected())
	{
		Playerlist.Update();

		static int aimPunchOffset = GET_NETVAR("DT_BasePlayer", "localdata", "m_Local", "m_aimPunchAngle");
		static int viewPunchOffset = GET_NETVAR("DT_BasePlayer", "localdata", "m_Local", "m_viewPunchAngle");
		Vector *pPunchAngle = nullptr, *pViewPunchAngle = nullptr, vPunchAngle, vViewPunchAngle;

		if (Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected()) {
			if (pLocal) {

				if (curStage == FRAME_RENDER_START) {

					if (*(bool*)((DWORD)Interfaces.pInput + 0xA5))
						*(Vector*)((DWORD)pLocal + 0x31C8) = Hacks.LastAngles;

					if (Settings.GetBoolSetting(Tab_Visuals, Vis_Recoil) && Settings.GetBoolSetting(Tab_Visuals, Vis_Active)) {
						pPunchAngle = Hacks.LocalPlayer->GetPunchAnglePtr();
						pViewPunchAngle = Hacks.LocalPlayer->GetViewPunchAnglePtr();

						if (pPunchAngle && pViewPunchAngle) {
							vPunchAngle = *pPunchAngle;
							pPunchAngle->Init();
							vViewPunchAngle = *pViewPunchAngle;
							pViewPunchAngle->Init();
						}


					}
				}
			}
		}

		Hacks.oFrameStageNotify(curStage);


		if (pPunchAngle && pViewPunchAngle) {
			*pPunchAngle = vPunchAngle;
			//*pViewPunchAngle = vViewPunchAngle;
		}

		if (Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected()) {
			if (pLocal) {
				if (curStage == FRAME_RENDER_START) {
					//*(Vector*)((DWORD)pLocal + aimPunchOffset)  = aimPunch;
					//*(Vector*)((DWORD)pLocal + viewPunchOffset) = viewPunch;
				}
			}
		}

		if (Settings.GetBoolSetting(Tab_Ragebot, Ragebot_Resolver))
		{
			Resolver.Resolver(curStage);
		}

		if (curStage == ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
		{
			if (Settings.GetSetting(Tab_Other, Other_SkinChanger_Set)) {
				skinstosave();
				Interfaces.pEngine->ClientCmd_Unrestricted("record x;stop", NULL);
				Settings.SetSetting(Tab_Other, Other_SkinChanger_Set, 0);
			}
			if (Settings.GetSetting(Tab_Other, Other_SkinChanger_Update)) {
				loadskin();
				Interfaces.pEngine->ClientCmd_Unrestricted("record x;stop", NULL);
				Settings.SetSetting(Tab_Other, Other_SkinChanger_Update, 0);

			}
			// Update Playerlist

			if (true) {
				if (!Hacks.LocalPlayer)
					return;
				if (!Hacks.LocalWeapon)
					return;
				bilcount();
			}

			//
			// Do Resolver

		}
	}
}

void __stdcall Hooked_OverrideMouseInput(float *x, float* y)
{
	if (false) { // ur soo mean, u removed my meme
				 //	Hacks.oOverrideMouseInput(x, y);


		*(float*)x += 70;// for some reason its gotta be written with 
						 // *(float*) behind, i thought it was just *x = 0; but noh, its *(float*)x (im retarded)


	}
}

void __fastcall Hooked_DrawModelExecute(void* thisptr, int edx, void* ctx, void* state, const ModelRenderInfo_t &pInfo, matrix3x4 *pCustomBoneToWorld)
{

	if (!DMEHacks.Do_Chams(thisptr, edx, ctx, state, pInfo, pCustomBoneToWorld))
		Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

	Interfaces.g_pModelRender->ForcedMaterialOverride(NULL, OverrideType_t::OVERRIDE_NORMAL);
}

void __fastcall Hooked_D3D()
{

}
void __fastcall Hooked_D3DReset()
{

}


LRESULT __stdcall Hooked_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//if (Menu.Opened)
	//	return true; // IF MENU ISNT OPEN, BLOCK IMPUT :)

	return CallWindowProc(Hacks.g_pOldWindowProc, hWnd, uMsg, wParam, lParam);
}