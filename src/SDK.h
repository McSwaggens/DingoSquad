#pragma once
#include "stdafx.h"


typedef unsigned char uint8;
typedef unsigned char BYTE;
typedef unsigned char byte;

class KeyValues
{
public:
	char _pad[0x20];//csgo, for css its a diff size
};

inline void**& getvtable(void* inst, size_t offset = 0)
{

	return *reinterpret_cast<void***>((size_t)inst + offset);
}
inline const void** getvtable(const void* inst, size_t offset = 0)
{
	if (!inst && !offset)
		return NULL;
	return *reinterpret_cast<const void***>((size_t)inst + offset);
}
template< typename Fn >
inline Fn getvfunc(const void* inst, size_t index, size_t offset = 0)
{
	if (!inst && offset == 0)
		return NULL;

	return reinterpret_cast<Fn>(getvtable(inst, offset)[index]);
}

typedef float matrix3x4[3][4];
typedef float matrix4x4[4][4];
typedef void* (__cdecl* CreateInterface_t)(const char*, int*);
typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);

typedef __int16					int16;
typedef unsigned __int16		uint16;
typedef __int32					int32;
typedef unsigned __int32		uint32;
typedef __int64					int64;
typedef unsigned __int64		uint64;
typedef float					vec_t;

class VMatrix;
class IClientModeShared
{
public:
};

//USERCMD OFFSETS
#define USERCMDOFFSET 0xEC
#define VERIFIEDCMDOFFSET 0xF0
#define MULTIPLAYER_BACKUP 150
#define CURRENTCOMMANDOFFSET 0x16E8
#define CURRENTPLAYERCOMMANDOFFSET 0x1640
#define PREIDCTIONSEEDOFFSET 0x30
#define PREDICTIONPLAYEROFFSET 0x54
#define GLOBALSOFFSET 0x53
#define WEAPONDATA_MAXRANGEOFFSET 0x77C
#define WEAPONDATA_DAMAGEOFFSET 0x778
#define WEAPONDATA_RANGEMODIFIEROFFSET 0x780
#define WEAPONDATA_PENETRATIONPOWEROFFSET 0x774
#define INPUTOFFSET 0x5F
#define GETSPREADOFFSET 0x740
#define GETCONEOFFSET 0x744
#define UPDATEACCURACYPENALTYOFFSET 0x748
#define WEAPONIDOFFSET 0x6D8
#define WEAPONDATAOFFSET 0x708
#define GETNAMEOFFSET 0x5CC
#define APPSYSTEMFACTORYOFFSET 0x3D
#define CLIENTFACTORYOFFSET 0x75
#define GLOWINDEXOFFSET 0x1DB8

//LIFESTATE
#define	LIFE_ALIVE				0 
#define	LIFE_DYING				1 
#define	LIFE_DEAD				2 
#define LIFE_RESPAWNABLE		3
#define LIFE_DISCARDBODY		4

//Player flags
#define	FL_ONGROUND				(1<<0)	// At rest / on the ground
#define FL_DUCKING				(1<<1)	// Player flag -- Player is fully crouched
#define	FL_WATERJUMP			(1<<3)	// player jumping out of water
#define FL_ONTRAIN				(1<<4) // Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
#define FL_INRAIN				(1<<5)	// Indicates the entity is standing in rain
#define FL_FROZEN				(1<<6) // Player is frozen for 3rd person camera
#define FL_ATCONTROLS			(1<<7) // Player can't move, but keeps key inputs for controlling another entity
#define	FL_CLIENT				(1<<8)	// Is a player
#define FL_FAKECLIENT			(1<<9)	// Fake client, simulated server side; don't send network messages to them
#define	FL_INWATER				(1<<10)	// In water

/* MOVE TYPES */
enum MoveType_t
{
	MOVETYPE_NONE = 0,
	MOVETYPE_ISOMETRIC,
	MOVETYPE_WALK,
	MOVETYPE_STEP,
	MOVETYPE_FLY,
	MOVETYPE_FLYGRAVITY,
	MOVETYPE_VPHYSICS,
	MOVETYPE_PUSH,
	MOVETYPE_NOCLIP,
	MOVETYPE_LADDER,
	MOVETYPE_OBSERVER,
	MOVETYPE_CUSTOM,
	MOVETYPE_LAST = MOVETYPE_CUSTOM,
	MOVETYPE_MAX_BITS = 4
};

enum class ObserverMode_t : int
{
	OBS_MODE_NONE = 0,
	OBS_MODE_DEATHCAM = 1,
	OBS_MODE_FREEZECAM = 2,
	OBS_MODE_FIXED = 3,
	OBS_MODE_IN_EYE = 4,
	OBS_MODE_CHASE = 5,
	OBS_MODE_ROAMING = 6
};


//USERCMD BUTTONS
#define IN_ATTACK		(1 << 0)
#define IN_JUMP			(1 << 1)
#define IN_DUCK			(1 << 2)
#define IN_FORWARD		(1 << 3)
#define IN_BACK			(1 << 4)
#define IN_USE			(1 << 5)
#define IN_CANCEL		(1 << 6)
#define IN_LEFT			(1 << 7)
#define IN_RIGHT		(1 << 8)
#define IN_MOVELEFT		(1 << 9)
#define IN_MOVERIGHT	(1 << 10)
#define IN_ATTACK2		(1 << 11)
#define IN_RUN			(1 << 12)
#define IN_RELOAD		(1 << 13)
#define IN_ALT1			(1 << 14)
#define IN_ALT2			(1 << 15)
#define IN_SCORE		(1 << 16)   // Used by client.dll for when scoreboard is held down
#define IN_SPEED		(1 << 17)	// Player is holding the speed key
#define IN_WALK			(1 << 18)	// Player holding walk key
#define IN_ZOOM			(1 << 19)	// Zoom key for HUD zoom
#define IN_WEAPON1		(1 << 20)	// weapon defines these bits
#define IN_WEAPON2		(1 << 21)	// weapon defines these bits
#define IN_BULLRUSH		(1 << 22)
#define IN_GRENADE1		(1 << 23)	// grenade 1
#define IN_GRENADE2		(1 << 24)	// grenade 2

#include "SDK_Others.h"

class ISurface;
class IPanel;
class HLCLient;
class CEntityList;
class CEngineClient;
class CInput;
class CGlowObjectManager;
class IVModelInfo;
class IVModelRender;
class CPrediction;
class CGameMovement;
class IMoveHelper;
class CGlobalVars;
class IEngineTrace;
class IPhysicsSurfaceProps;
class CDebugOverlay;
class IMaterialSystem;
class IGameEventManager2;
class IVRenderView;
class ICVar;
class IClientModeShared;


class CInterfaces
{
private:
	DWORD WaitOnModuleHandle(std::string moduleName)
	{
		DWORD ModuleHandle = NULL;
		while (!ModuleHandle)
		{
			ModuleHandle = (DWORD)GetModuleHandle(moduleName.c_str());
			if (!ModuleHandle)
				Sleep(50);
		}
		return ModuleHandle;
	}
	void* GetPointer(const char* Module, const char* InterfaceName)
	{
		void* Interface = NULL;
		char PossibleInterfaceName[1024];

		CreateInterfaceFn CreateInterface = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA(Module), "CreateInterface");
		for (int i = 1; i < 100; i++)
		{
			Interface = (void*)CreateInterface(PossibleInterfaceName, NULL);
			if (Interface != NULL)
			{
				//#ifdef DEBUG
				cout << PossibleInterfaceName << " Found: 0x " << igreen << Interface << endl;
				//#endif		

				break;
			}

			Interface = (void*)CreateInterface(PossibleInterfaceName, NULL);
			if (Interface != NULL)
			{
				//#ifdef DEBUG
				cout << PossibleInterfaceName << " Found: 0x " << igreen << Interface << endl;
				//#endif		
				break;
			}
		}

		return Interface;
	}
	void* GetInterfacePtr(const char* interfaceName, const char* ptrName, CreateInterface_t pInterface)
	{

		char szDebugString[2048];

		std::string sinterface = "";
		std::string interfaceVersion = "0";

		for (int i = 0; i <= 99; i++)
		{
			sinterface = interfaceName;
			sinterface += interfaceVersion;
			sinterface += std::to_string(i);

			void* funcPtr = pInterface(sinterface.c_str(), NULL);

			if ((DWORD)funcPtr != 0x0)
			{

				sprintf_s(szDebugString, "%s: 0x%x (%s%s%i)", ptrName, (DWORD)funcPtr, interfaceName, interfaceVersion.c_str(), i);
				//#ifdef DEBUG
				cout << iblue << ptrName << igreen << ": 0x" << funcPtr << "(" << iyellow << interfaceName << interfaceVersion << i << igreen << ")" << white << endl;
				//#endif		
				return funcPtr;
			}
			if (i >= 99 && interfaceVersion == "0")
			{
				interfaceVersion = "00";
				i = 0;
			}
			else if (i >= 99 && interfaceVersion == "00")
			{

				sprintf_s(szDebugString, "%s: 0x%x (error)", ptrName, (DWORD)funcPtr);
				cout << ired << ptrName << ": 0x" << funcPtr << " (ERROR)" << white << endl;
			}
		}
		return 0;
	}
public:
	inline void* CaptureInterface(const char* chHandle, const char* chInterfaceName)
	{
		volatile auto handlegotten = (GetModuleHandleA(chHandle) != nullptr);
		while (!GetModuleHandleA(chHandle)) Sleep(100);
		void* fnFinal = nullptr;
		auto PossibleInterfaceName = new char[strlen(chInterfaceName) + 4];
		auto TestInterface = reinterpret_cast<CreateInterface_t>(GetProcAddress(GetModuleHandleA(chHandle), "CreateInterface"));
		delete PossibleInterfaceName;
		return fnFinal;
	}
	void InitialiseSDK()
	{
		/*cout << white << "The VAC module is scanning" << white << "......" << white << endl;
		Sleep(2000);
		cout << white << "The VAC module is scanning...." << green << "  Done!" << white << endl;
		cout << white << "The VAC module Signature is " << ired << "  lukcncOOSvHkrueGgGA7WDcbAJxj32VNZiNiYv7MYmP3hjfRwL" << white << endl;
		cout << white << "A code mutation is performed...." << white << "" << white << endl;
		Sleep(3000);
		cout << white << "A code mutation is performed:\n" << green << "rndseed = 100500\nmacro randomize{\nrandseed = randseed * 1103515245 + 12345\nrandseed = (randseed / 65536) mod 0x100000000\nrndnum = randseed and 0xFFFFFFFF\n}" << white << endl;
		Sleep(2000);
		cout << white << "A code mutation is performed:\n" << green << "randomize\nint_val = rndnum mod 0xFF" << white << endl;
		Sleep(2000);
		cout << white << "A code mutation is performed\n" << green << "cd78 | int 0x78\ncda6 | int 0xa6\ncdb4 | int 0xb4n\ncd36 | int 0x36n\ncdec | int 0xec\ncd6a | int 0x6a\ncd68 | int 0x68" << white << endl;
		Sleep(2000);
		cout << white << "A code mutation is performed" << green << "  Done!" << white << endl;
		Sleep(100);
		cout << white << "0XACE randomization of api calls" << green << "  Done!" << white << endl;
		
		Sleep(100);
		cout << white << "New Build was created:..." << green << "  Done!" << white << endl;*/
		

		DWORD dwInitAddress = Utils.PFindPattern("engine.dll", "A1 ? ? ? ? 33 D2 6A ? 6A ? 33 C9 89 B0 08 4E ? ? A1");
		cout << igreen << "dwInitAddress: " << ired << "0x" << dwInitAddress << white << endl;

		DWORD p = Utils.PFindPattern("client.dll", "8B 0D ? ? ? ? FF 75 08 8B 01 FF 50 64");

		if (p)
		{
			pClientMode = **(DWORD***)(p + 2);
			pClientMode = pClientMode;
		}
		cout << iblue << "pClientMode" << igreen << ": 0x" << pClientMode << white << endl;

		CreateInterfaceFn fnEngineFactory = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("engine.dll"), "CreateInterface");
		CreateInterfaceFn AppSystemFactory = (CreateInterfaceFn)GetProcAddress((HMODULE)GetModuleHandle("vguimatsurface.dll"), "CreateInterface");//**(PDWORD*)//(dwInitAddress + 0x3D);
		CreateInterfaceFn MaterialSystemFactory = (CreateInterfaceFn)GetProcAddress((HMODULE)GetModuleHandle("materialsystem.dll"), "CreateInterface");
		CreateInterfaceFn ClientFactory = (CreateInterfaceFn)GetProcAddress((HMODULE)GetModuleHandle("client.dll"), "CreateInterface");
		CreateInterfaceFn StdFactory = (CreateInterfaceFn)GetProcAddress((HMODULE)GetModuleHandle("vstdlib.dll"), "CreateInterface");
        CreateInterfaceFn VGUISurfaceFactory= (CreateInterfaceFn)GetProcAddress((HMODULE)GetModuleHandle("vgui2.dll"), "CreateInterface");
		//CreateInterfaceFn VGUI2Factory = (CreateInterfaceFn)GetProcAddress((HMODULE)GetModuleHandle("vgui2.dll"), "CreateInterface");
		CreateInterfaceFn PhysFactory = (CreateInterfaceFn)GetProcAddress((HMODULE)GetModuleHandle("vphysics.dll"), "CreateInterface");
		
		

		typedef CGlowObjectManager*(__thiscall* GetGlowObjectManager_t)(void);
		static GetGlowObjectManager_t GetGlowObjectManager = (GetGlowObjectManager_t)Utils.PFindPattern("client.dll", "A1 ? ? ? ? A8 01 75 4B");
		g_pGlowObjectManager = GetGlowObjectManager();
		cout << iblue << "g_pGlowObjectManager:" << igreen<<  ": 0x" << g_pGlowObjectManager << white  << endl;

		pSurface = (ISurface*)GetInterfacePtr("VGUI_Surface", "g_pSurface", AppSystemFactory);
		pPanel = (IPanel*)GetInterfacePtr("VGUI_Panel", "g_pPanel", VGUISurfaceFactory);
	    //pClient = (HLCLient*)GetPointer("client.dll", "VClient018");
		pClient = (HLCLient*)GetInterfacePtr("VClient", "g_pClient", ClientFactory);
        pEngine = (CEngineClient*)GetInterfacePtr("VEngineClient", "g_pEngine", fnEngineFactory);
		pEntList = (CEntityList*)GetInterfacePtr("VClientEntityList", "g_pEntList", ClientFactory);
		g_pDebugOverlay = (CDebugOverlay*)GetInterfacePtr("VDebugOverlay", "g_pDebugOverlay", fnEngineFactory);
		pTrace = (IEngineTrace*)GetInterfacePtr("EngineTraceClient", "g_pEngineTraceClient", fnEngineFactory);
		g_pModelInfo = (IVModelInfo*)GetInterfacePtr("VModelInfoClient", "g_pModelInfo", fnEngineFactory);
		g_pModelRender = (IVModelRender*)GetInterfacePtr("VEngineModel", "g_ModelRender", fnEngineFactory);
		g_pPred = (CPrediction*)GetInterfacePtr("VClientPrediction", "g_pPred", ClientFactory);
		g_pGameMovement = (CGameMovement*)GetInterfacePtr("GameMovement", "g_pGameMovement", ClientFactory);
		pPhysProps = (IPhysicsSurfaceProps*)GetInterfacePtr("VPhysicsSurfaceProps", "g_pPhysprops", PhysFactory);
		pMaterialSystem = (IMaterialSystem*)GetInterfacePtr("VMaterialSystem", "pMaterialSystem", MaterialSystemFactory);
		g_pRenderView = (IVRenderView*)GetInterfacePtr("VEngineRenderView", "g_pRenderView", fnEngineFactory);
		pGlobalVars = *(CGlobalVars**)(((*(PDWORD*)pClient)[0]) + 0x1B);
		pGlobalVars = (CGlobalVars*)*(PDWORD)pGlobalVars;
		cout << iblue << "pGlobalVars " << igreen << ": 0x" << pGlobalVars << white << endl;
		pInput = *(CInput**)((*(DWORD**)pClient)[15] + 0x1);//[15] + 0x1)
		g_ICVars = (ICVar*)GetInterfacePtr("VEngineCvar", "g_pCVars", StdFactory);
		//g_GameEventMgr = (IGameEventManager2*)GetInterfacePtr("GAMEEVENTSMANAGER", "g_pGameEventsMgr", fnEngineFactory);
		g_GameEventMgr = (IGameEventManager2*)fnEngineFactory("GAMEEVENTSMANAGER002", NULL);
		
	//	cout << iblue << "g_pRenderView:" << igreen << ": 0x" << g_pRenderView << white << endl;
		


	}
private:
	bool InitialisedSuccessfuly = false;
public:
	ISurface* pSurface;
	//DWORD* pClientMode;
	DWORD* pClientMode;
	IPanel* pPanel;
	HLCLient* pClient;
	CEntityList* pEntList;
	CEngineClient* pEngine;
	CInput* pInput;
	CGlowObjectManager* g_pGlowObjectManager;
	IVModelInfo* g_pModelInfo;
	IVModelRender* g_pModelRender;
	CPrediction* g_pPred;
	CGameMovement* g_pGameMovement;
	IMoveHelper* g_pMoveHelper;
	CGlobalVars* pGlobalVars;
	IEngineTrace* pTrace;
	IGameEventManager2* pGameEventManager;
	IPhysicsSurfaceProps* pPhysProps;
	CDebugOverlay* g_pDebugOverlay;
	IMaterialSystem* pMaterialSystem;
	IVRenderView* g_pRenderView;
	ICVar* g_ICVars;
	IGameEventManager2* g_GameEventMgr;
};
extern CInterfaces Interfaces;

#include "Math.h"

#include "checksum_crc.h"
#include "dt_recv2.h"
#include "NetVars.h"


#include "ISurface.h"
#include "CClient.h"
#include "EngineClient.h"
#include "Entitys.h"
#include "EntList.h"
#include "DebugOverlay.h"
#include "CTrace.h"
#include "IVRenderView.h"
#include "CModelInfo.h"
#include "CInput.h"
#include "ICVars.h"
#include "CGlobleVars.h"
#include "CGameMovement.h"
#include "CPred.h"
#include "CGlow.h"

void UTIL_TracePos(Ray_t &ray, unsigned int mask, const IHandleEntity *ignore, int collisionGroup, trace_t *ptr);
void UTIL_TraceLine(Vector& vecAbsStart, Vector& vecAbsEnd, unsigned int mask, const IHandleEntity *ignore, int collisionGroup, trace_t *ptr);
void UTIL_ClipTraceToPlayers(Vector& vecAbsStart, Vector& vecAbsEnd, unsigned int mask, ITraceFilter* filter, trace_t* tr);
bool TraceToExit(Vector& end, trace_t& tr, Vector start, Vector vEnd, trace_t* trace);

/* FIRE BULLET DATA */
struct FireBulletData
{
	FireBulletData(const Vector &eye_pos)
		: src(eye_pos)
	{
	}
	Vector          src;
	trace_t         enter_trace;
	Vector          direction;
	CTraceFilter    filter;
	float           trace_length;
	float           trace_length_remaining;
	float           current_damage;
	int             penetrate_count;
};

/* HITGROUP DEFINITIONS */
#define		HITGROUP_GENERIC    0
#define		HITGROUP_HEAD       1
#define		HITGROUP_CHEST      2
#define		HITGROUP_STOMACH    3
#define		HITGROUP_LEFTARM    4    
#define		HITGROUP_RIGHTARM   5
#define		HITGROUP_LEFTLEG    6
#define		HITGROUP_RIGHTLEG   7
#define		HITGROUP_GEAR       10

typedef bool(*ShouldHitFunc_t)(IHandleEntity *pHandleEntity, int contentsMask);

enum class CSGOClassID
{
	CAK47 = 1,
	CBaseAnimating = 2,
	CBaseAnimatingOverlay = 3,
	CBaseAttributableItem = 4,
	CBaseButton = 5,
	CBaseCombatCharacter = 6,
	CBaseCombatWeapon = 7,
	CBaseCSGrenade = 8,
	CBaseCSGrenadeProjectile = 9,
	CBaseDoor = 10,
	CBaseEntity = 11,
	CBaseFlex = 12,
	CBaseGrenade = 13,
	CBaseParticleEntity = 14,
	CBasePlayer = 15,
	CBasePropDoor = 16,
	CBaseTeamObjectiveResource = 17,
	CBaseTempEntity = 18,
	CBaseToggle = 19,
	CBaseTrigger = 20,
	CBaseViewModel = 21,
	CBaseVPhysicsTrigger = 22,
	CBaseWeaponWorldModel = 23,
	CBeam = 24,
	CBeamSpotlight = 25,
	CBoneFollower = 26,
	CBreakableProp = 27,
	CBreakableSurface = 28,
	CC4 = 29,
	CCascadeLight = 30,
	CChicken = 31,
	CColorCorrection = 32,
	CColorCorrectionVolume = 33,
	CCSGameRulesProxy = 34,
	CCSPlayer = 35,
	CCSPlayerResource = 36,
	CCSRagdoll = 37,
	CCSTeam = 38,
	CDEagle = 39,
	CDecoyGrenade = 40,
	CDecoyProjectile = 41,
	CDynamicLight = 42,
	CDynamicProp = 43,
	CEconEntity = 44,
	CEconWearable = 45,
	CEmbers = 46,
	CEntityDissolve = 47,
	CEntityFlame = 48,
	CEntityFreezing = 49,
	CEntityParticleTrail = 50,
	CEnvAmbientLight = 51,
	CEnvDetailController = 52,
	CEnvDOFController = 53,
	CEnvParticleScript = 54,
	CEnvProjectedTexture = 55,
	CEnvQuadraticBeam = 56,
	CEnvScreenEffect = 57,
	CEnvScreenOverlay = 58,
	CEnvTonemapController = 59,
	CEnvWind = 60,
	CFEPlayerDecal = 61,
	CFireCrackerBlast = 62,
	CFireSmoke = 63,
	CFireTrail = 64,
	CFish = 65,
	CFlashbang = 66,
	CFogController = 67,
	CFootstepControl = 68,
	CFunc_Dust = 69,
	CFunc_LOD = 70,
	CFuncAreaPortalWindow = 71,
	CFuncBrush = 72,
	CFuncConveyor = 73,
	CFuncLadder = 74,
	CFuncMonitor = 75,
	CFuncMoveLinear = 76,
	CFuncOccluder = 77,
	CFuncReflectiveGlass = 78,
	CFuncRotating = 79,
	CFuncSmokeVolume = 80,
	CFuncTrackTrain = 81,
	CGameRulesProxy = 82,
	CHandleTest = 83,
	CHEGrenade = 84,
	CHostage = 85,
	CHostageCarriableProp = 86,
	CIncendiaryGrenade = 87,
	CInferno = 88,
	CInfoLadderDismount = 89,
	CInfoOverlayAccessor = 90,
	CItem_Healthshot = 91,
	CItemDogtags = 92,
	CKnife = 93,
	CKnifeGG = 94,
	CLightGlow = 95,
	CMaterialModifyControl = 96,
	CMolotovGrenade = 97,
	CMolotovProjectile = 98,
	CMovieDisplay = 99,
	CParticleFire = 100,
	CParticlePerformanceMonitor = 101,
	CParticleSystem = 102,
	CPhysBox = 103,
	CPhysBoxMultiplayer = 104,
	CPhysicsProp = 105,
	CPhysicsPropMultiplayer = 106,
	CPhysMagnet = 107,
	CPlantedC4 = 108,
	CPlasma = 109,
	CPlayerResource = 110,
	CPointCamera = 111,
	CPointCommentaryNode = 112,
	CPointWorldText = 113,
	CPoseController = 114,
	CPostProcessController = 115,
	CPrecipitation = 116,
	CPrecipitationBlocker = 117,
	CPredictedViewModel = 118,
	CProp_Hallucination = 119,
	CPropDoorRotating = 120,
	CPropJeep = 121,
	CPropVehicleDriveable = 122,
	CRagdollManager = 123,
	CRagdollProp = 124,
	CRagdollPropAttached = 125,
	CRopeKeyframe = 126,
	CSCAR17 = 127,
	CSceneEntity = 128,
	CSensorGrenade = 129,
	CSensorGrenadeProjectile = 130,
	CShadowControl = 131,
	CSlideshowDisplay = 132,
	CSmokeGrenade = 133,
	CSmokeGrenadeProjectile = 134,
	CSmokeStack = 135,
	CSpatialEntity = 136,
	CSpotlightEnd = 137,
	CSprite = 138,
	CSpriteOriented = 139,
	CSpriteTrail = 140,
	CStatueProp = 141,
	CSteamJet = 142,
	CSun = 143,
	CSunlightShadowControl = 144,
	CTeam = 145,
	CTeamplayRoundBasedRulesProxy = 146,
	CTEArmorRicochet = 147,
	CTEBaseBeam = 148,
	CTEBeamEntPoint = 149,
	CTEBeamEnts = 150,
	CTEBeamFollow = 151,
	CTEBeamLaser = 152,
	CTEBeamPoints = 153,
	CTEBeamRing = 154,
	CTEBeamRingPoint = 155,
	CTEBeamSpline = 156,
	CTEBloodSprite = 157,
	CTEBloodStream = 158,
	CTEBreakModel = 159,
	CTEBSPDecal = 160,
	CTEBubbles = 161,
	CTEBubbleTrail = 162,
	CTEClientProjectile = 163,
	CTEDecal = 164,
	CTEDust = 165,
	CTEDynamicLight = 166,
	CTEEffectDispatch = 167,
	CTEEnergySplash = 168,
	CTEExplosion = 169,
	CTEFireBullets = 170,
	CTEFizz = 171,
	CTEFootprintDecal = 172,
	CTEFoundryHelpers = 173,
	CTEGaussExplosion = 174,
	CTEGlowSprite = 175,
	CTEImpact = 176,
	CTEKillPlayerAttachments = 177,
	CTELargeFunnel = 178,
	CTEMetalSparks = 179,
	CTEMuzzleFlash = 180,
	CTEParticleSystem = 181,
	CTEPhysicsProp = 182,
	CTEPlantBomb = 183,
	CTEPlayerAnimEvent = 184,
	CTEPlayerDecal = 185,
	CTEProjectedDecal = 186,
	CTERadioIcon = 187,
	CTEShatterSurface = 188,
	CTEShowLine = 189,
	CTesla = 190,
	CTESmoke = 191,
	CTESparks = 192,
	CTESprite = 193,
	CTESpriteSpray = 194,
	CTest_ProxyToggle_Networkable = 194,
	CTestTraceline = 196,
	CTEWorldDecal = 197,
	CTriggerPlayerMovement = 198,
	CTriggerSoundOperator = 199,
	CVGuiScreen = 200,
	CVoteController = 201,
	CWaterBullet = 202,
	CWaterLODControl = 203,
	CWeaponAug = 204,
	CWeaponAWP = 205,
	CWeaponBaseItem = 206,
	CWeaponBizon = 207,
	CWeaponCSBase = 208,
	CWeaponCSBaseGun = 209,
	CWeaponCycler = 210,
	CWeaponElite = 211,
	CWeaponFamas = 212,
	CWeaponFiveSeven = 213,
	CWeaponG3SG1 = 214,
	CWeaponGalil = 215,
	CWeaponGalilAR = 216,
	CWeaponGlock = 217,
	CWeaponHKP2000 = 218,
	CWeaponM249 = 219,
	CWeaponM3 = 220,
	CWeaponM4A1 = 221,
	CWeaponMAC10 = 222,
	CWeaponMag7 = 223,
	CWeaponMP5Navy = 224,
	CWeaponMP7 = 225,
	CWeaponMP9 = 226,
	CWeaponNegev = 227,
	CWeaponNOVA = 228,
	CWeaponP228 = 229,
	CWeaponP250 = 230,
	CWeaponP90 = 231,
	CWeaponSawedoff = 232,
	CWeaponSCAR20 = 233,
	CWeaponScout = 234,
	CWeaponSG550 = 235,
	CWeaponSG552 = 236,
	CWeaponSG556 = 237,
	CWeaponSSG08 = 238,
	CWeaponTaser = 239,
	CWeaponTec9 = 240,
	CWeaponTMP = 241,
	CWeaponUMP45 = 242,
	CWeaponUSP = 243,
	CWeaponXM1014 = 244,
	CWorld = 245,
	DustTrail = 246,
	MovieExplosion = 247,
	ParticleSmokeGrenade = 248,
	RocketTrail = 249,
	SmokeTrail = 250,
	SporeExplosion = 251,
	SporeTrail = 252

	
};