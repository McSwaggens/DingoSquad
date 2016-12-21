#include "stdafx.h"

#include "Ragebot.h"
#include "PLegitbot.h"
#include "Resolver.h"

#include "Legitbot.h"
#include "Menu.h"
struct ESP_Box
{
	int x = 0, y = 0, h = 0, w = 0;
};

Vector GetHitboxPOS_Ent(CBaseEntity* Player, int HitboxID);

class Createmove_Hacks
{
	/* All CREATEMOVE HACKS IN THIS CLASS */
private:
	void BunnyHop();
	void AutoStrafer();
	void CorrectMovement(Vector vOldAngles, CInput::CUserCmd* pCmd, Vector Viewangs);
	bool CircleStrafer(Vector &angles);
public:
	bool UnLagNextTick = false;
	void MovePacket(CInput* thisptr, void* _EAX, int sequence_number, float input_sample_frametime, bool active);
};
extern Createmove_Hacks CM_Hacks;



class PaintTraverse_Hacks
{
private:
	void DrawESP();
	void DrawSkeleton(CBaseEntity* pEntity, CColor col);
	void DrawBox(CBaseEntity* Target, int r, int g, int b, int a);
	bool IsVisable(CBaseEntity* Target, int boneID);
	bool WorldToScreen(Vector &vOrigin, Vector &vScreen);
	ESP_Box Get_Box(CBaseEntity* Entity);
	ESP_Box Get_PBox(CBaseEntity* Entity);
	void bombESP();
	bool PaintTraverse_IsGoodPlayer_ESP(CBaseEntity* Target);
	void recoilXhair();
	void AsusWalls();

public:
	void DrawPaintTraverseHacks();
};
extern PaintTraverse_Hacks PT_Hacks;


class Draw_Model_Exec_Hacks
{
private:
	void InitKeyValues(KeyValues* keyValues, char* name);
	void LoadFromBuffer(KeyValues* keyValues, char const *resourceName, const char *pBuffer);
	IMaterial *Create_Material(bool Ignore, bool Lit, bool Wireframe);
	void AsusWalls(void* thisptr, int edx, void* ctx, void* state, const ModelRenderInfo_t &pInfo, matrix3x4 *pCustomBoneToWorld, IMaterial* Visable_Lit, IMaterial* Covered_Lit);
public:
	bool Do_Chams(void* thisptr, int edx, void* ctx, void* state, const ModelRenderInfo_t &pInfo, matrix3x4 *pCustomBoneToWorld);

};
extern Draw_Model_Exec_Hacks DMEHacks;