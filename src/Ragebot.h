#pragma once
#include "stdafx.h"
extern bool FireSimulatedBullet(FireBulletData &data, CBaseEntity *Local, CBaseCombatWeapon* weapon);


class CRageBot
{
public:
	void Move();
	void NewMove();

	void FastLargeNormalise(Vector &angle);
	void FastLargeNormaliseMove(Vector &angle);
	float PelvisAng(CPlayer * Target);
	void AutoWall_ScanPos(Vector Target, int bone_ID, float& Damage);

private:

	void Do_pSilent(Vector AimbotAng, Vector Antiaimang);
	Vector DoAimSpeedLimit(Vector Last, Vector angle, bool &shoot);
	bool pointshitable(CPlayer* Player);
	/* Aimbot */
	void DoAimbot();
	bool DoNewAimbot();
	bool IsVisableExact(CPlayer* Target, int boneID);
	int HitScan(CPlayer* Target, Vector &point);
	Vector pointScanEdge(CPlayer* Player, int hitbox, float &damage);
	Vector pointScanEdge2(CPlayer* Player, int hitbox, float &damage);

	Vector MultiBoxScan(CPlayer* Target, float& Damage);
	bool smartaim();

	/* Anti Aim */
	void DoAntiAim();

	/* Others */
	bool Ragebot_IsGoodPlayer(CPlayer * Target);

	bool IsVisable(CPlayer* Target, int boneID);
	bool IsPosVisable(Vector Target);
	void AutoWall_Scan(CPlayer* Target, int bone_ID, float& Damage);

	void AutoWall_ScanPs(CPlayer* Target, int bone_ID, Vector ps, float& Damage);

	Vector GetHitboxPOSScan(CPlayer* Player, int HitboxID, Vector ps);
	Vector GetHitboxPOSBOXER(CPlayer* Player, int HitboxID);
	Vector GetBestPoint(CPlayer* Player, int HitboxID);

	Vector Aimbot_Angle;
	Vector Antiaim_Angle;
	Vector LastAngle;
	CPlayer* Target;
	int Target_Bone;	
	int Target_Bone_PerEnt;
	float Expected_Damage;
	float Expected_Damage_PerEnt;
	bool Any_Targets;
};
extern CRageBot Ragebot;