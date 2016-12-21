#pragma once
#include "stdafx.h"
#include "CGameEvent.h"

void __fastcall Hooked_Createmove(CInput* thisptr, void* _EAX, int sequence_number, float input_sample_frametime, bool active);
void __stdcall Hooked_PaintTraverse(unsigned int vguiPanel, bool forceRepaint, bool allowForce);
void  __stdcall Hooked_Frame_Stage_Notify(ClientFrameStage_t curStage);
void __stdcall Hooked_OverrideView(CViewSetup* pSetup);
LRESULT __stdcall Hooked_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void __fastcall Hooked_DrawModelExecute(void* thisptr, int edx, void* ctx, void* state, const ModelRenderInfo_t &pInfo, matrix3x4 *pCustomBoneToWorld);
void __fastcall Hooked_D3D();
void __fastcall Hooked_D3DReset();

bool __fastcall Hooked_FireEventClientSide(void*, void*, IGameEvent* pEvent);

//void __stdcall Hooked_OverrideMouseInput(float *x, float* y);


extern VMTManager VMTClientMode;

class CHackManager
{

private:
	/* Typedefs */
	typedef void(__thiscall *iPaintTraverse)(void*, unsigned int, bool, bool);
	typedef void(__stdcall *iCreateMoveFn)(CInput*, void*, int, float, bool);
	typedef void(__stdcall *iFrameStageNotifyFn)(ClientFrameStage_t);
	typedef void(__stdcall *iOverRideViewFn)(CViewSetup*);
	typedef void(__stdcall *iD3D)();
	typedef void(__thiscall* IDrawModelExecute)(void*, void*, void*, const ModelRenderInfo_t&, matrix3x4*);
	//typedef void(__stdcall* iOverrideMouseInput)(float *x, float *y);
	typedef bool(__thiscall *FireEventClientSide)(void*, IGameEvent*);


public:
	/* Original Functions */
	DWORD oCreateMove;
	iPaintTraverse oPaintTraverse;
	iFrameStageNotifyFn oFrameStageNotify;
	IDrawModelExecute oDrawModelExecute;
	iD3D oD3D;
	FireEventClientSide oFireEventClientSide;

	//iOverRideViewFn oOverrideView;
	//	iFireEventClientSide oFireEventClientSide;
	//iOverrideMouseInput oOverrideMouseInput;
	HWND g_hWindow;
	WNDPROC g_pOldWindowProc;


	/* Holding Varialbles */
	CInput::CUserCmd* CurrentCmd;
	CBaseEntity* LocalPlayer;
	CBaseCombatWeapon* LocalWeapon;
	Vector LastAngles;
	bool SendPacket = true;

	/* Some Fonts .___. , why is it here, cuz im lazy as fuck... */
	DWORD Font_Tahoma;
	DWORD Font_Title;
	DWORD Font_Tab;
	DWORD Font_ESP;
	/* Hooking */
	void Hook()
	{
		/* Hey WHATS THIS FONT SHIT DOIGN HERE!? */
		Font_Tahoma = Interfaces.pSurface->Create_Font();
		Font_Title = Interfaces.pSurface->Create_Font();
		Font_Tab = Interfaces.pSurface->Create_Font();
		Font_ESP = Interfaces.pSurface->Create_Font();
		Interfaces.pSurface->SetFontGlyphSet(Font_Tahoma, "Tahoma", 13, 400, 0, 0, FONTFLAG_ANTIALIAS);
		Interfaces.pSurface->SetFontGlyphSet(Font_Tab, "Tahoma", 16, 600, 0, 0, FONTFLAG_ANTIALIAS);
		Interfaces.pSurface->SetFontGlyphSet(Font_Title, "Tahoma", 13, 600, 0, 0, FONTFLAG_ANTIALIAS);
		Interfaces.pSurface->SetFontGlyphSet(Font_ESP, "Tahoma", 12, 700, 0, 0, FONTFLAG_DROPSHADOW);

		// Hooks
		if (Interfaces.pClient)
		{
			VMTClient.Initialise((DWORD*)Interfaces.pClient);
			oCreateMove = VMTClient.HookMethod((DWORD)&Hooked_Createmove, 21);

			//#ifdef DEBUG

			cout << ired << "Create Move Hooked (21)." << iyellow << " oCreateMove = 0x" << oCreateMove << white << endl;
			//#endif		
			oFrameStageNotify = (iFrameStageNotifyFn)VMTClient.HookMethod((DWORD)&Hooked_Frame_Stage_Notify, 36);
			//#ifdef DEBUG

			cout << ired << "Frame Stage Notfiy Hooked (36)." << iyellow << " oFrameStageNotify = 0x" << oFrameStageNotify << white << endl;
			//#endif		

		}
		//if (Interfaces.pSurface)
		//{
		//	VMTPanel.Initialise((DWORD*)Interfaces.pPanel);
		//	oFireEventClientSide = (iFireEventClientSide)VMTPanel.HookMethod((DWORD)&Hooked_PaintTraverse, 41);
		//	//#ifdef DEBUG

		//	cout << ired << "Paint Traverse Hooked (41)." << iyellow << " oPaintTraverse = 0x" << oPaintTraverse << white << endl;
		//#endif		
		//}


		if (Interfaces.pSurface)
		{
			VMTPanel.Initialise((DWORD*)Interfaces.pPanel);
			oPaintTraverse = (iPaintTraverse)VMTPanel.HookMethod((DWORD)&Hooked_PaintTraverse, 41);
			cout << ired << "Paint Traverse Hooked (41)." << iyellow << " oPaintTraverse = 0x" << oPaintTraverse << white << endl;
		}
		static DWORD dwDevice = (Utils.PatternSearch("shaderapidx9.dll", (PBYTE)"\xA1\x00\x00\x00\x00\x50\x8B\x08\xFF\x51\x0C", "x????xxxxxx", NULL, NULL) + 1);
		if (dwDevice) {

			//	VMTD3DDevice9.Initialise((DWORD*)dwDevice);
			//	oD3D = (iD3D)VMTD3DDevice9.HookMethod((DWORD)&Hooked_D3D, 16);
			//	oD3D = (iD3D)VMTD3DDevice9.HookMethod((DWORD)&Hooked_D3DReset, 42);

		}
		if (Interfaces.g_pModelRender)
		{
			VMTModelRender.Initialise((DWORD*)Interfaces.g_pModelRender);
			oDrawModelExecute = (IDrawModelExecute)VMTModelRender.HookMethod((DWORD)&Hooked_DrawModelExecute, 21);
			//#ifdef DEBUG
			cout << ired << "Draw Model Execute Hooked (21)." << iyellow << " oDrawModelExecute = 0x" << oDrawModelExecute << white << endl;
			//#endif		
		}

		//	if (Interfaces.pClientMode)
		//{
		//	VMTClientMode.Initialise((DWORD*)Interfaces.pClientMode);
		//	oOverrideView = (iOverRideViewFn)VMTClientMode.HookMethod((DWORD)&Hooked_OverrideView, 18);
#ifdef DEBUG
		//cout << ired << "Override View Hooked (18)." << iyellow << " oOverrideView = 0x" << oOverrideView << white << endl;
		//oOverrideMouseInput = (iOverrideMouseInput)VMTClientMode.HookMethod((DWORD)&Hooked_OverrideMouseInput, 23);
		//cout << ired << "Override Mouse Input Hooked (23)." << iyellow << " oOverrideMouseInput = 0x" << oOverrideMouseInput << white << endl;
#endif		
		//}

		VMTGameEvent.Initialise((DWORD*)Interfaces.g_GameEventMgr);
		oFireEventClientSide = (FireEventClientSide)VMTGameEvent.HookMethod((DWORD)&Hooked_FireEventClientSide, 9);
		cout << ired << "FEC (9)." << iyellow << " oFEC = 0x" << oFireEventClientSide << white << endl;

		while (!(g_hWindow = FindWindowA("Valve001", NULL))) Sleep(100);
		if (g_hWindow) g_pOldWindowProc = (WNDPROC)SetWindowLongPtr(g_hWindow, GWL_WNDPROC, (LONG_PTR)Hooked_WndProc);

	}

	void UnHook()
	{
		Interfaces.pEngine->ClientCmd_Unrestricted("crosshair 1", 0);

		VMTClient.RestoreOriginal();
		VMTPanel.RestoreOriginal();
		VMTModelRender.RestoreOriginal();
		VMTClientMode.RestoreOriginal();
		VMTGameEvent.RestoreOriginal();
		SetWindowLongPtr(g_hWindow, GWL_WNDPROC, (LONG_PTR)g_pOldWindowProc);
	}

};