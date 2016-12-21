#include "stdafx.h"
#include <math.h>       /* atan */

//Yes this is messy, Yes there is alot of useless code, yes i should clean it up but it was all used at a point and I tested stuff with it. Pls leave and dont judge.
Vector GetHitboxPOS_Ent(CBaseEntity* Enemy, int HitboxID);

float FovToPlayer_Ent(Vector ViewOffSet, Vector View, CBaseEntity* pEntity, int aHitBox);
CBaseEntity* evil;
bool bitches2aimAt;
int lowestfov;
extern float DistanceToRay(const Vector &pos, const Vector &rayStart, const Vector &rayEnd, float *along = NULL, Vector *pointOnRay = NULL);
double randomval(double value) {
	double random = value*(Settings.GetSetting(Tab_LegitBot, Legit_Random) / 20);
	if (random != 0) {
		double min = (value - random);
		double difference = abs(value) - abs(min);
		int randomiser = difference * 100000;
		float valuee = rand() % randomiser;
		difference += (valuee / 100000);
		return difference;
	}
	else
		return value;
}
CBaseCombatWeapon* LasttWeap;
int psilentcount = 6;
void Do_pSilent(Vector AimbotAng, Vector Antiaimang)
{
	static bool UnLagNextTick = false;

	float flServerTime = (float)Hacks.LocalPlayer->GetTickBase() * Interfaces.pGlobalVars->interval_per_tick;
	float flNextPrimaryAttack = Hacks.LocalWeapon->NextPrimaryAttack();

	bool BulletTime = true;

	if (flNextPrimaryAttack > flServerTime)
		BulletTime = false;

	if (BulletTime && !UnLagNextTick)
	{
		if (psilentcount == 6) {
			Hacks.CurrentCmd->viewangles = AimbotAng;
			Hacks.CurrentCmd->buttons |= IN_ATTACK;
		}
		else {

			Hacks.CurrentCmd->viewangles = Antiaimang;
			Hacks.CurrentCmd->buttons &= ~IN_ATTACK;

		}

		Hacks.SendPacket = false;
		psilentcount--;
		if(psilentcount == 0)
			UnLagNextTick = true;
	}
	else
	{
		if (UnLagNextTick)
		{
			psilentcount = 6;
			UnLagNextTick = false;
			Hacks.SendPacket = true;
		}
		Hacks.CurrentCmd->viewangles = Antiaimang;
	}

	LasttWeap = Hacks.LocalWeapon;
}
void ppsilentmeme() {
	Vector look = Hacks.CurrentCmd->viewangles;
	Vector Target = look;
	Target.y += 1;
	Do_pSilent(Target, look);
}
void screentomouseevent(double y, double x) {
	//65535 1800
	double valuey = y;
	double valuex = x;
	DWORD dx = valuex;
	DWORD dy = valuey;
	if (dx == 0 && valuex != 0) {
		if (valuex > 0.0)
			dx = 10;
		else
			dx = -10;
		//
	}
	
	if (dy == 0 && valuey != 0) {

		if (valuey > 0.0)
			dy = 10;
		else
			dy = -10;



	}

	mouse_event(MOUSEEVENTF_MOVE, valuex, valuey, 0, 0);

}
double AngletoScreenX(double angle, double previous) {
	//D = W tanB / 2Tan(A / 2)
	//X
	int width = 0;
	int height = 0;
	Interfaces.pEngine->GetScreenSize(width, height);	int A = 74 *(PI / 180);
	double theta = (angle - previous)*(PI / 180);
	double X =(height* tan(theta)) / (2 * tan(37 * (PI / 180)));
	//X /= 1000;
	//Y
	// 4:3 90, 16:9 106, 16:10 100
	/*
	int B = 100;
	double Y = (W* tan(angle.y*(PI / 180))) / (2 * tan(B / 2));
	Vector screen;
	screen.y = Y;
	screen.x = X;
	return screen;
	*/
	return X;
}
double AngletoScreenY(double angle, double previous) {
	//D = W tanB / 2Tan(A / 2)
	//X
	int width = 0;
	int height = 0;
	Interfaces.pEngine->GetScreenSize(width, height);	
	int B = 100;
	if (width / height == 4 / 3) {
		B = 90;
	}
	else if (width / height == 16 / 9) {
		B = 106;
	}
	else
	{
	  B = 100;

	}

	double	A = (B / 2) * (PI / 180);
	double theta = (angle - previous)*(PI / 180);
	double Y = (height* tan(theta)) / (2 * tan(A));
	//X /= 1000;
	//Y
	// 4:3 90, 16:9 106, 16:10 100
	/*
	int B = 100;
	double Y = (W* tan(angle.y*(PI / 180))) / (2 * tan(B / 2));
	Vector screen;
	screen.y = Y;
	screen.x = X;
	return screen;
	*/
	return Y;
}

Vector topointt(Vector point) {
	// Get the full angles
	Vector angles;

	if (point.Length() == 0) return angles;
	CBaseEntity* me = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

	Vector src = me->GetEyePosition();

	CalcAngle(src, point, angles);

	if (angles[0] != angles[0] || angles[1] != angles[1])
	{
		return angles;
	}

	return angles;
}

HLCLient HLC;

bool WorldToScreen(Vector &vOrigin, Vector &vScreen)
{
	vScreen.z = 0;
		Interfaces.g_pDebugOverlay->ScreenPosition(vOrigin, vScreen);

	return true;
}
bool isVisable(CBaseEntity* Target, int HitBox)
{
	CBaseEntity* copy = Target;
	trace_t Trace;
	Vector start = Hacks.LocalPlayer->GetEyePosition();
	Vector end = GetHitboxPOS_Ent(Target, HitBox);
	UTIL_TraceLine(start, end, MASK_SOLID, Hacks.LocalPlayer, 0, &Trace);
	if (Trace.m_pEnt == copy) return true;
	if (Trace.fraction == 1.0f) return true;
	return false;
}

Vector Getspeed(double Smooth, double Time, Vector AddAngs) {
	Vector sped;
	double base = (20 - randomval(Time))/100;

	double m = randomval(Smooth);
	double n = 20 - m;
	sped.x = (n*AddAngs.x) / 40;
	sped.y = (n*AddAngs.y) / 40;
		if (sped.x < 0)
			sped.x *= -1;
		if (sped.y < 0)
			sped.y *= -1;
		if (Time < 19) {
			sped.x += base;
			sped.y += base;
		}

	
	return sped;
}




bool AimAtPoint(CBaseEntity* pLocal, Vector point, CInput::CUserCmd* cmd)
{
	// Get the full angles
	if (point.Length() == 0) return false;   
	 
	Vector angles;      
	Vector src = pLocal->GetEyePosition();      
	          
	CalcAngle(src, point, angles);        
	          
	if (angles[0] != angles[0] || angles[1] != angles[1])
	{
		return false;    
	}
	cmd->viewangles = angles;    
	    
	return false; 
}//
bool isSeeable(CBaseEntity* Target, int aHitBox)
{
	CBaseEntity* copy = Target;
	trace_t Trace;
	Vector start = Hacks.LocalPlayer->GetEyePosition();
	Vector end = GetHitboxPOS_Ent(Target, aHitBox);
	UTIL_TraceLine(start, end, MASK_SOLID, Hacks.LocalPlayer, 0, &Trace);
	if (Trace.m_pEnt == copy) return true;
	if (Trace.fraction == 1.0f) return true;
	return false;
}
int returnval = 0;
bool nohstrue = false;
int getHitBox(int Hitbox, int Selection, Vector ViewOffSet, Vector View, CBaseEntity* pEntity, bool firstt) {
	static bool nohstrue = false;
	int returnval = -1;
	static int hitboxs;

	int hitboxes[] = { (int)CSGOHitboxID::Head,(int)CSGOHitboxID::Neck, (int)CSGOHitboxID::Chest, (int)CSGOHitboxID::UpperChest, (int)CSGOHitboxID::LowerChest, (int)CSGOHitboxID::Stomach, (int)CSGOHitboxID::Pelvis, (int)CSGOHitboxID::Pelvis, (int)CSGOHitboxID::Pelvis, (int)CSGOHitboxID::Pelvis };
	if (Settings.GetSetting(Tab_LegitBot, Legit_HsPer) != 0) {
		if (firstt) {
			if (rand() % 99 < randomval(Settings.GetSetting(Tab_LegitBot, Legit_HsPer))) {
				nohstrue = true;
			}
			else {
				nohstrue = false;
			}
		}
	}
	else {

		nohstrue = false;
	}


	float perm = 360;
	if (Selection == 0 || Selection == 1) {
		switch (Hitbox) {
		case 0:
			returnval = (int)CSGOHitboxID::Head;
			break;
		case 1:
			returnval = (int)CSGOHitboxID::Head;
			break;

		case 2: //neck
			returnval = (int)CSGOHitboxID::Neck;
			break;


		case 3:// chest
			returnval = (int)CSGOHitboxID::Chest;
			break;

		case 4: // stomach
			returnval = (int)CSGOHitboxID::Stomach;
			break;
		}
	}
	else if (Selection == 2) {//Dynamic
		switch (Hitbox) {
		case 0:
			returnval = (int)CSGOHitboxID::Head;
			break;
		case 1:
			returnval = (int)CSGOHitboxID::Head;
			break;

		case 2: //neck
			returnval = (int)CSGOHitboxID::Neck;
			break;


		case 3:// chest
			returnval = (int)CSGOHitboxID::Chest;
			break;

		case 4: // stomach
			returnval = (int)CSGOHitboxID::Stomach;
			break;
		}
		if (!isVisable(pEntity, returnval)) {
			for (int i = 0; i < 6; i++) {
				int temp = hitboxes[i];
				if (isVisable(pEntity, temp)) {
					returnval = temp;
					break;
				}
			}

		}
	}
	else if (Selection == 3) {//Nearest
		if (firstt) {
			for (int i = 0; i < 7; i++) {
				float temp = FovToPlayer_Ent(ViewOffSet, View, pEntity, hitboxes[i]);
				if (temp < perm) {
					perm = temp;
					returnval = hitboxes[i];
					hitboxs = returnval;
				}
			}

		}
		else {
			returnval = hitboxs;
		}

	}
	else if (Selection == 4) {//Random

		if (firstt) {

			for (int i = 0; i < 6; i++) {
				int temp = hitboxes[rand() % 6];
				if (isVisable(pEntity, temp)) {
					returnval = hitboxes[temp];
					hitboxs = returnval;

					break;
				}
			}
		}
		else {
			returnval = hitboxs;

		}
	}


	if (returnval == 0 && nohstrue)
		returnval = (int)CSGOHitboxID::LowerChest;

	return returnval;
}
void NormaliseViewAngle(Vector &angle)
{
	if ((Settings.GetSetting(Tab_Misc, Misc_Teleport_Enable)) && !(Settings.GetSetting(Tab_Misc, Misc_Anti_Untrust)))
		return;
	while (angle.y <= -180) angle.y += 360;
	while (angle.y > 180) angle.y -= 360;
	while (angle.x <= -180) angle.x += 360;
	while (angle.x > 180) angle.x -= 360;

	if (angle.x > 89.0) angle.x = 89;
	if (angle.x < -89.0) angle.x = -89;
	if (angle.y < -180) angle.y = -179.999;
	if (angle.y > 180) angle.y = 179.999;

	angle.z = 0;
}

bool shouldshot(Vector ViewOffSet, Vector View, CBaseEntity* pEntity, int aHitBox, float fov){
    if(Hacks.LocalWeapon->ammo() != 0 && isSeeable(pEntity, aHitBox)){
        if(FovToPlayer_Ent(ViewOffSet, View, pEntity, aHitBox) <= fov){
            return true;
        }else{
            return false;

        }
    }
    else{
         return false;
    }
}
int getclosest() {
	return 0;
}
void rcs(int wherefrom) {
	if (Settings.GetSetting(Tab_LegitBot, Legit_RCS_Enable)) {
		CBaseEntity* me = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
		auto punchAngles = me->GetPunchAngle();
		float forX = (float)Settings.GetSetting(Tab_LegitBot, Legit_RCS_X);
		float forY = (float)Settings.GetSetting(Tab_LegitBot, Legit_RCS_Y);
		int typee = Settings.GetSetting(Tab_LegitBot, Legit_RCS_Type);

		if (wherefrom == 1 && typee == 3) {
			forX = 2.0f;
			forY = 2.0f;
		}
		static Vector Last_Puch_Angle = Hacks.CurrentCmd->viewangles;
		if (punchAngles.x != 0.0f || punchAngles.y != 0) {
			if(wherefrom == 2)
				Hacks.CurrentCmd->viewangles += Last_Puch_Angle;

			if (punchAngles.x != 0.0f)
				Hacks.CurrentCmd->viewangles.x -= punchAngles.x * forX;
			if (punchAngles.y != 0.0f)
				Hacks.CurrentCmd->viewangles.y -= punchAngles.y* forY;

			Last_Puch_Angle.x = punchAngles.x * forX;
			Last_Puch_Angle.y = punchAngles.y * forY;

		}
		//int width = 1280;//GetSystemMetrics(SM_CXSCREEN);
				//int height = 768;//GetSystemMetrics(SM_CYSCREEN);
				//Vector moving = AngletoScreen(viewangs);



		NormaliseViewAngle(Hacks.CurrentCmd->viewangles);

	}

}
void mouseeventLegit() {

}


int curveabot = 0;
int bones[9] = { 6, 5, 4, 2, 0, 36, 8, 70, 64 };
int nonhsbones[9] = { 36, 4, 80, 75, 3, 0, 8, 75, 80 };
int randomabone = 1;
bool close = false;
bool aimstepshotx = false;
bool aimstepshoty = false;
int countt = 0;
int counttt = 0;
bool rageaimsucces = false;
bool inaim = false;
bool setcurvestart = false;
int aimbotbonee = 1;
int dela77;
int conta = -1;
int triggerbotdelay = 0;
bool inaimbot = false;
//auto vecCurrentViewAngles = g_ClientState.GetViewAngles();
//auto vecViewAngleDelta = vecViewAngles - vecCurrentViewAngles;
//vecViewAngleDelta += Vector3_t(vecViewAngleDelta.y/flYScale, vecViewAngleDelta.x/flXScale, 0.0f); // i don't have a 2D vector class for angles cause i'm a lazy fuck.
//vecViewAngleDelta /= flSmooth;
//vecViewAngles = vecCurrentViewAngles+vecViewAngleDelta;

bool SmokeCheck(CBaseEntity* player, int boneID)
{
	if (boneID < 0)
	{
		return false; 
	}
	CBaseEntity* me = Hacks.LocalPlayer;
	CBaseEntity* copy = player; 
	trace_t Trace;
	Vector start = me->GetEyePosition(); 
	Vector end = GetHitboxPOS_Ent(player, boneID);




	if (Trace.m_pEnt == copy)
	{
		return true;
	}
	if (Trace.fraction == 1.0f)
	{
		return true;
	}
	return false;
}


float fl_Random(float min, float max)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float range = max - min;
	return (random*range) + min;
}

// TRIGGERBOT 
void Triggerbot()
{
	// Some Random Definitions 
	CBaseEntity* me = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
	CBaseCombatWeapon* Gun = me->GetActiveBaseCombatWeapon();
	bool shoot = false;

	// Keys
	int TriggerKey = Settings.GetSetting( Tab_LegitBot, Trigger_Key);
	bool UsingKey = Settings.GetBoolSetting(Tab_LegitBot, Trigger_Type);

	//Values 
	int DelayTicks = Settings.GetSetting( Tab_LegitBot, Trigger_Delay);


	//Vector Definitions 
	Vector MyEyes = me->GetEyePosition();
	Vector Target = Vector(0, 0, 0);
	Vector Angle = Hacks.CurrentCmd->viewangles;


	// Reverse RCS 
	if (!Hacks.LocalWeapon->isSniper()) {
		Vector PunchAngles = me->GetPunchAngle() * 2.0f;
		if (PunchAngles.x != 0.0f || PunchAngles.y != 0.0f)
		{
			Angle += PunchAngles;
		}
	}
	//Find Crosshair POS 
	g_Math.angleVectors(Angle, Target);
	g_Math.Normalize(Target, Target); //MAKE ITS LENGH 1 

	float Lengh = Gun->GetCSWpnData()->GetRange();

	if (Gun->IsKnife())
	{
		Lengh = 70;
	}
	else if (Gun->GetClientClass()->m_ClassID == 231 )
	{
		Lengh = 165;
	}


	Target *= Lengh;
	Target += MyEyes;


	// Define Some Junk 
	trace_t Trace;

	//Shoot A Lazer Ray Meme 
	UTIL_TraceLine(MyEyes, Target, 0x46004003, me, 0, &Trace);

	CBaseEntity* TargetPlayer = Trace.m_pEnt;

	if (TargetPlayer)
	{
		if (TargetPlayer->GetClientClass()->m_ClassID == 35)
		{
			if (TargetPlayer->IsPlayer() && !TargetPlayer->HasGunGameImmunity() && TargetPlayer->GetTeam() != me->GetTeam())
			{

				shoot = true;

			}
		}
	}

	//Handle Shooting, Delays, Etc 
	static int Counter = DelayTicks;
	if (shoot)
	{
		if (GetAsyncKeyState(TriggerKey) || !UsingKey)
		{
			if (DelayTicks != 0)
			{
				if (Counter <= 0)
				{
					Hacks.CurrentCmd->buttons |= IN_ATTACK;
					Counter = DelayTicks;
				}
				else
				{
					Counter--;
				}
			}
			else
			Hacks.CurrentCmd->buttons |= IN_ATTACK;
		}
		else
		{
			Counter = DelayTicks;
		}
	}
}

// Magnet Triggerbot 


bool overshoottrig = false;
int maglasttargetcount;
CBaseEntity* maglastTarget;
void MagnetTrig()
{
	overshoottrig = false;
	CBaseEntity* me2 = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
	CBaseEntity* Target2 = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
	int TargetBestBone2;
	dela77 = Settings.GetSetting( Tab_LegitBot, Trigger_Delay);
	bool canshoot = false;

	if (triggerbotdelay >= dela77) {
		canshoot = true;
	}
	else {
		triggerbotdelay++;
	}

	int	TriggerKey = Settings.GetSetting( Tab_LegitBot, Trigger_Key);
	if (GetAsyncKeyState(TriggerKey) && canshoot || !Settings.GetBoolSetting(Tab_LegitBot, Trigger_Type) && canshoot) {
		inaimbot = true;
		Vector b4 = Hacks.CurrentCmd->viewangles;
		bool aimsucess = false;
		bool onetapticks = false;
		bool awalling = false;
		bool first = false;
		if (countt == 0)
			first = true;
		countt++;
		int BestFov = 180;
		float Fov = Settings.GetSetting( Tab_LegitBot, Trigger_Magnet_FOV);
		int TargetBestBone = -1;
		static int OldBone = -1;
		CBaseEntity* me = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
		CBaseCombatWeapon* Gun = me->GetActiveBaseCombatWeapon();
		if (!me || !Gun)
			return;

		if ((!Gun->IsMiscWeapon() || !Gun->IsKnife()) && me->isAlive())
		{

			int a = Interfaces.pEntList->GetHighestEntityIndex();
			CBaseEntity* Target = me;
			CBaseEntity* Player;

			bool whichRvis[128];
			for (int i = 0; i < a; i++)
			{
				Player = Interfaces.pEntList->GetClientEntity(i);

				if (!Player)
					continue;

				if (Player->IsDormant()
					|| (Player->GetHealth() == 0)
					|| !Player->isAlive()
					|| (Player == me)
					|| (Player->GetTeam() == me->GetTeam())
					|| Player->HasGunGameImmunity())
					continue; // IS PLAYER A PLAYER /

							  // Loop Though Main Bones /

				int	LeBestBone = -1;


				float IDbone;
				IDbone = bones[5];
				int iv = 5;
				int bonefrommenu = Settings.GetSetting( Tab_LegitBot, Trigger_Magnet_SelectionBone);
				int Selectionfrommenu = Settings.GetSetting(Tab_LegitBot, Trigger_Magnet_SelectionType);

				LeBestBone = getHitBox(bonefrommenu, Selectionfrommenu, me->GetEyePosition(), Hacks.CurrentCmd->viewangles, Player, first);

				//LeBestBone = 6;
				// IDbone;



				//LeBestBone = 6;
				aimsucess = false;

				if (isSeeable(Player, LeBestBone) && FovToPlayer_Ent(me->GetEyePosition(), Hacks.CurrentCmd->viewangles, Player, LeBestBone) <= Fov)
				{
					aimsucess = true;
					whichRvis[i] = true;
				}
				Vector b4 = Hacks.CurrentCmd->viewangles;
				Vector punchAngles = me->GetPunchAngle() * 2.0f;
				if (punchAngles.x != 0.0f || punchAngles.y != 0)
				{
					b4 += punchAngles;
				}

				float FOV = FovToPlayer_Ent(me->GetEyePosition(), b4, Player, LeBestBone);
				if (FOV <= BestFov && FOV <= Fov && isSeeable(Player, LeBestBone))
				{

					BestFov = FOV;
					Target = Player;
					TargetBestBone = LeBestBone;
					OldBone = LeBestBone;
				}

			}
			if (maglastTarget != Target && maglasttargetcount != 0) {
				maglasttargetcount--;
				return;
			}
			else {
				maglasttargetcount = Settings.GetSetting( Tab_LegitBot, Legit_TargetDelay);
				maglastTarget = Target;
			}

			if (Target == me || TargetBestBone == -1)
			{
				return;
				maglasttargetcount = 0;
			}

			Vector punchAngles = me->GetPunchAngle() * 2.0f;
			if (punchAngles.x != 0.0f || punchAngles.y != 0)
			{
				Hacks.CurrentCmd->viewangles += punchAngles;
			}
			//	if (aimsucess ) {
			Vector CurrentAngle = Vector(0, 0, 0);
			Interfaces.pEngine->GetViewAngles(CurrentAngle);
			AimAtPoint(me, GetHitboxPOS_Ent(Target, TargetBestBone), Hacks.CurrentCmd);
			Vector targett = topointt(GetHitboxPOS_Ent(Target, TargetBestBone));
			//RCS HERE
			rcs(1);
			NormaliseViewAngle(Hacks.CurrentCmd->viewangles);
			Vector AddAngs = Hacks.CurrentCmd->viewangles - CurrentAngle;
			NormaliseViewAngle(AddAngs);
			Vector instantAng = AddAngs;
			float angsX = AddAngs.x *100.0f;
			float angsY = AddAngs.y *100.0f;
			curveabot++;
			float speedmenuX;
			float speedmenuY;

			double smooth = (double)Settings.GetSetting( Tab_LegitBot, Trigger_Magnet_Speed);
			double time = (double)Settings.GetSetting(Tab_LegitBot, Trigger_Magnet_AimTime);

			
			Vector values = Getspeed(smooth, time, AddAngs);
			speedmenuX = values.x;
			speedmenuY = values.y;

			//		speedmenuX = angsX / ((float)Settings.GetSetting( Tab_LegitBot, Old_Legit_LegitNormalAimSpeedX));

			float speedX = (speedmenuX );
			float speedY = (speedmenuY );
			//speedX = 0.01f;
			//speedY = 0.01f;
			Vector vecToTarg = targett - Hacks.CurrentCmd->viewangles;
			//speed = 0.5f;
			///*
			if (AddAngs.Length2D() > speedY || AddAngs.Length2D() > speedX)
			{
				g_Math.Normalize(AddAngs, AddAngs);
				if (AddAngs.Length2D() > speedY) {
					AddAngs.y *= speedY;

				}
				if (AddAngs.Length2D() > speedX) {
					AddAngs.x *= speedX;

				}
				if (smooth == 0) {
					AddAngs = instantAng;
				}
				//AddAngs += vecToTarg;
				Hacks.CurrentCmd->viewangles = CurrentAngle + AddAngs;

			}


			//MAY NEED NORMALISING

			NormaliseViewAngle(Hacks.CurrentCmd->viewangles);
			overshoottrig = true;
			//	}
			//else {
			//hacks.CurrentCmd->viewangles = b4;
			//				}
		}

	}
else {
	maglasttargetcount = 0;

}
}
int overshootingcount = Settings.GetSetting( Tab_LegitBot, Trigger_After);
void overshoting() {
	if (overshoottrig) {
		Hacks.CurrentCmd->buttons |= IN_ATTACK;
		overshootingcount = Settings.GetSetting( Tab_LegitBot, Trigger_After);
	}
	else {
		if (overshootingcount > 0) {
		Hacks.CurrentCmd->buttons |= IN_ATTACK;
		overshootingcount--;
		}
	}
}
//Legitbot 

CBaseEntity* lastTarget;
int lasttargetcount = Settings.GetSetting( Tab_LegitBot, Legit_TargetDelay);

void Legitbott()
{//
	int AimKey = Settings.GetSetting(Tab_LegitBot, Legit_Aimbot_Key);
	if (GetAsyncKeyState(AimKey)) {
		inaimbot = true;
		Vector b4 = Hacks.CurrentCmd->viewangles;
		bool aimsucess = false;
		bool onetapticks = false;
		bool awalling = false;
		bool first = false;
		if (countt == 0)
			first = true;
		countt++;
		int BestFov = 180;
		float Fov = Settings.GetSetting(Tab_LegitBot, Legit_Normal_FOV);
		int TargetBestBone = -1;
		static int OldBone = -1;
		CBaseEntity* me = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
		CBaseCombatWeapon* Gun = me->GetActiveBaseCombatWeapon();
		if (!me || !Gun)
			return;

		if ((!Gun->IsMiscWeapon() || !Gun->IsKnife()) && me->isAlive())
		{

			int a = Interfaces.pEntList->GetHighestEntityIndex();
			CBaseEntity* Target = me;
			CBaseEntity* Player;

			bool whichRvis[128];
			for (int i = 0; i < a; i++)
			{
				Player = Interfaces.pEntList->GetClientEntity(i);

				if (!Player)
					continue;

				if (Player->IsDormant()
					|| (Player->GetHealth() == 0)
					|| !Player->isAlive()
					|| (Player == me)
					|| (Player->GetTeam() == me->GetTeam())
					|| Player->HasGunGameImmunity())
					continue; // IS PLAYER A PLAYER /

							  // Loop Though Main Bones /

				int	LeBestBone = -1;


				float IDbone;
				IDbone = bones[5];
				int iv = 5;
				int bonefrommenu = Settings.GetSetting( Tab_LegitBot, Legit_Normal_SelectionBone);
				int typefrommenu = Settings.GetSetting(Tab_LegitBot, Legit_Normal_SelectionType);

				if (Settings.GetSetting(Tab_LegitBot, Legit_SA_Amount)) {
					Vector punch = Hacks.LocalPlayer->GetPunchAngle();

					if (abs(punch.x) < 0.1 && abs(punch.y) < 0.1) {
						bonefrommenu = Settings.GetSetting(Tab_LegitBot, Legit_SA_SelectionBone);
						typefrommenu = Settings.GetSetting(Tab_LegitBot, Legit_SA_SelectionType);

					}
				}

				LeBestBone = getHitBox(bonefrommenu, typefrommenu, me->GetEyePosition(), Hacks.CurrentCmd->viewangles, Player, first);
				
				//LeBestBone = 6;
				// IDbone;



				//LeBestBone = 6;
				aimsucess = false;

				if (isSeeable(Player, LeBestBone) && FovToPlayer_Ent(me->GetEyePosition(), Hacks.CurrentCmd->viewangles, Player, LeBestBone) <= Fov)
				{
					aimsucess = true;
					whichRvis[i] = true;
				}
				Vector b4 = Hacks.CurrentCmd->viewangles;
				Vector punchAngles = me->GetPunchAngle() * 2.0f;
				if (punchAngles.x != 0.0f || punchAngles.y != 0)
				{
					b4 += punchAngles;
				}

				float FOV = FovToPlayer_Ent(me->GetEyePosition(), b4, Player, LeBestBone);
					if (FOV <= BestFov && FOV <= Fov && isSeeable(Player, LeBestBone))
					{

						BestFov = FOV;
						Target = Player;
						TargetBestBone = LeBestBone;
						OldBone = LeBestBone;
					}
				
			}
			if (lastTarget != Target && lasttargetcount != 0) {
				lasttargetcount--;
				return;
			}
			else {
				lasttargetcount = Settings.GetSetting( Tab_LegitBot, Legit_TargetDelay);
				lastTarget = Target;
			}

			if (Target == me || TargetBestBone == -1)
			{
				lasttargetcount = 0;
				return;
			}
			if (!(Target->GetFlags() & FL_ONGROUND) && Settings.GetSetting(Tab_LegitBot, Legit_IgnoreInAir))
				return;

			double time = (double)Settings.GetSetting(Tab_LegitBot, Legit_Normal_AimTime);
			float smooth = (float)randomval(Settings.GetSetting(Tab_LegitBot, Legit_Normal_Speed));
			if (Settings.GetSetting(Tab_LegitBot, Legit_SA_Amount)) {
				Vector punch = Hacks.LocalPlayer->GetPunchAngle();
				if (abs(punch.x) < 0.1 && abs(punch.y) < 0.1) {
					time = (double)Settings.GetSetting(Tab_LegitBot, Legit_SA_AimTime);
					smooth = (float)randomval(Settings.GetSetting(Tab_LegitBot, Legit_SA_Speed));
				}
			}

			Vector punchAngles = me->GetPunchAngle() * 2.0f;
			if (punchAngles.x != 0.0f || punchAngles.y != 0)
			{
				Hacks.CurrentCmd->viewangles += punchAngles;
			}
			Vector CurrentAngle = Vector(0, 0, 0);
			Interfaces.pEngine->GetViewAngles(CurrentAngle);
			AimAtPoint(me, GetHitboxPOS_Ent(Target, TargetBestBone), Hacks.CurrentCmd);
			Vector targett = topointt(GetHitboxPOS_Ent(Target, TargetBestBone));
			rcs(1);
			NormaliseViewAngle(Hacks.CurrentCmd->viewangles);
			Vector AddAngs = Hacks.CurrentCmd->viewangles - CurrentAngle;
			NormaliseViewAngle(AddAngs);
			float angsX = AddAngs.x *100.0f;
			float angsY = AddAngs.y *100.0f;
			curveabot++;
			float speedmenuX;
			float speedmenuY;
			


			Vector values = Getspeed(smooth, time, AddAngs);
			speedmenuX = values.x;
			speedmenuY = values.y;

			float speedX = (speedmenuX );
			float speedY = (speedmenuY );
			Vector vecToTarg = targett - Hacks.CurrentCmd->viewangles ;
			if (AddAngs.Length2D() > speedY || AddAngs.Length2D() > speedX)
			{
				g_Math.Normalize(AddAngs, AddAngs);
				if (AddAngs.Length2D() > speedY) {
					AddAngs.y *= speedY;

				}
				if (AddAngs.Length2D() > speedX) {
					AddAngs.x *= speedX;

				}
				Hacks.CurrentCmd->viewangles = CurrentAngle + AddAngs;

			}		

			NormaliseViewAngle(Hacks.CurrentCmd->viewangles);
		}
	}
	else {
		curveabot = 0;
		countt = 0;
		inaimbot = false;
		lasttargetcount = 0;
	}
}


extern std::string settingstostring();

void dolegitshit() {
	NormaliseViewAngle(Hacks.CurrentCmd->viewangles);
	if (!Menu.Opened) {
		Vector beforeangs = Hacks.CurrentCmd->viewangles;

		if (Settings.GetSetting(Tab_LegitBot, Legit_Activate)) {
	
			Legitbott();
		}

		if (Settings.GetSetting(Tab_LegitBot, Legit_RCS_Type) == 2 || Settings.GetSetting(Tab_LegitBot, Legit_RCS_Type) == 3)
			rcs(2);
		if (Settings.GetSetting(Tab_LegitBot, Trigger_Active))
		{
			if (Settings.GetSetting(Tab_LegitBot, Trigger_Magnet))
				MagnetTrig();
			else
				Triggerbot();

			overshoting();
		}

		NormaliseViewAngle(Hacks.CurrentCmd->viewangles);
		Vector currentangs = Hacks.CurrentCmd->viewangles;
			Hacks.CurrentCmd->viewangles = currentangs;
			NormaliseViewAngle(Hacks.CurrentCmd->viewangles);
			Interfaces.pEngine->SetViewAngles(Hacks.CurrentCmd->viewangles);

	}
}