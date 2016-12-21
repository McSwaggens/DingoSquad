#include "stdafx.h"
CLegitbot Legitbot;
extern int bullets;
bool shootingX = false;
float CLegitbot::FovToPlayer(Vector ViewOffSet, Vector View, CBaseEntity* pEntity, int HitBox)
{
	CONST FLOAT MaxDegrees = 180.0f;
	Vector Angles = View;
	Vector Origin = ViewOffSet;
	Vector Delta(0, 0, 0);
	Vector Forward(0, 0, 0);
	g_Math.angleVectors(Angles, Forward);
	Vector AimPos = GetHitboxPOS_Ent(pEntity, HitBox);
	VectorSubtract(AimPos, Origin, Delta);
	g_Math.Normalize(Delta, Delta);
	FLOAT DotProduct = Forward.Dot(Delta);
	float FOV(acos(DotProduct) * (MaxDegrees / PI));
	if (FOV < 0) FOV - (FOV * 2);
	return FOV;
}
double CLegitbot::randomval(double value) {
	double random = value*(Settings.GetSetting(Tab_LegitBot, Legit_Random)/20);
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

void CLegitbot::Normalise(Vector &angle)
{

	if (!std::isfinite(angle.x)) { angle.x = 0; }
	if (!std::isfinite(angle.y)) { angle.y = 0; }

	while (angle.y <= -1800000) angle.y += 3600000;
	while (angle.y > 1800000) angle.y -= 3600000;
	while (angle.x <= -1800000) angle.x += 3600000;
	while (angle.x > 1800000) angle.x -= 3600000;

	while (angle.y <= -18000) angle.y += 36000;
	while (angle.y > 18000) angle.y -= 36000;
	while (angle.x <= -18000) angle.x += 36000;
	while (angle.x > 18000) angle.x -= 36000;

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
Vector CLegitbot::GetHitboxPOS(CBaseEntity* Player, int HitboxID)
{
	if (!Player)
		return Vector(0, 0, 0);

	matrix3x4 matrix[128];
	if (!Player->SetupBones(matrix, 128, 0x00000100, GetTickCount64())) return Vector(0, 0, 0);
	const model_t* mod = Player->GetModel();
	if (!mod) return Vector(0, 0, 0);
	studiohdr_t* hdr = Interfaces.g_pModelInfo->GetStudioModel(mod);
	if (!hdr) return Vector(0, 0, 0);
	mstudiohitboxset_t* set = hdr->GetHitboxSet(0);
	if (!set) return Vector(0, 0, 0);
	mstudiobbox_t* hitbox = set->pHitbox(HitboxID);
	if (!hitbox) return Vector(0, 0, 0);
	Vector vMin, vMax, vCenter, sCenter;
	g_Math.VectorTransform2(hitbox->bbmin, matrix[hitbox->bone], vMin);
	g_Math.VectorTransform2(hitbox->bbmax, matrix[hitbox->bone], vMax);
	vCenter = (vMin + vMax) *0.5f;
	return vCenter;
}
bool CLegitbot::IsPosVisable(Vector Target, CBaseEntity* Player)
{
	trace_t Trace;
	Vector start = Hacks.LocalPlayer->GetEyePosition();
	Vector end = Target;
	UTIL_TraceLine(start, end, MASK_SOLID, Hacks.LocalPlayer, 0, &Trace);
	if (Trace.m_pEnt == Player) return true;
	if (Trace.fraction == 1.0f) return true;
	return false;
}

bool CLegitbot::isVisable(CBaseEntity* Target, int HitBox)
{
	CBaseEntity* copy = Target;
	trace_t Trace;
	Vector start = Hacks.LocalPlayer->GetEyePosition();
	Vector end = GetHitboxPOS(Target, HitBox);
	UTIL_TraceLine(start, end, MASK_SOLID, Hacks.LocalPlayer, 0, &Trace);
	if (Trace.m_pEnt == copy) return true;
	if (Trace.fraction == 1.0f) return true;
	return false;
}
bool CLegitbot::checkhitbox() {
	trace_t tr;
	Vector Angle = Hacks.CurrentCmd->viewangles;
	Vector Punchangs = Hacks.LocalPlayer->GetPunchAngle() * 2;
	Angle += Punchangs;
	Vector Addition = Vector(0, 0, 0);
	Addition.x = 10000;
	if (90 < Angle.y || Angle.y< -90)
	{
		Addition.x = -10000;
		if (90 == Angle.y || Angle.y == -90) {
			Angle.y -= 0.00001;
		}
		Addition.y = tan(DEG2RAD(Angle.y))*Addition.x;
		Addition.z = tan(DEG2RAD(-Angle.x))*sqrt(Addition.x*Addition.x + Addition.y * Addition.y);


	}
	else {
		Addition.y = tan(DEG2RAD(Angle.y))*Addition.x;
		Addition.z = tan(DEG2RAD(-Angle.x))*sqrt(Addition.x*Addition.x + Addition.y * Addition.y);
	}

	Vector src = Hacks.LocalPlayer->GetEyePosition();
	Vector dst = src + Addition;
	UTIL_TraceLine(src, dst, 0x4600400B, Hacks.LocalPlayer, 0, &tr);

	if (!tr.m_pEnt)return false;

	if (Hacks.LocalWeapon->IsNotWeapon()) return false;

	if (Hacks.LocalWeapon->IsKnife() && tr.fraction > 0.03)
		return false;
	if ((int)Hacks.LocalWeapon->IsZeus() && tr.fraction > 0.04)
		return false;
	if (tr.m_pEnt)
	{
		CBaseEntity* tokill = tr.m_pEnt;
		if (tokill->GetTeam() == Hacks.LocalPlayer->GetTeam())return false;

		int aimgroup = Settings.GetSetting(Tab_LegitBot, Trigger_Hitboxs);
		switch (aimgroup) {
			case 0:
				if (tr.hitgroup != 0)
					return true;
				break;
			case 1:
				if (tr.hitgroup != 0)
					return true;
				break;

			case 2:
				if (tr.hitgroup == 1)
					return true;
				break;

			case 3:
				if (tr.hitgroup < 6 && tr.hitgroup!=0)
					return true;
				break;


		}
		return false;

	}

	return false;
}

double CLegitbot::AngletoScreenX(double angle, double previous) {
	// 4:3 90, 16:9 106, 16:10 100
	// 4:3 90, 16:9 106, 16:10 100

	int width = 0;
	int height = 0;
	Interfaces.pEngine->GetScreenSize(width, height);	
	int A = 74 * (PI / 180);
	double theta = (angle - previous)*(PI / 180);
	double X = (height* tan(theta)) / (2 * tan(37 * (PI / 180)));
	return X;
}
double CLegitbot::AngletoScreenY(double angle, double previous) 
{
	// 4:3 90, 16:9 106, 16:10 100
	int width = 0;
	int height = 0;
	Interfaces.pEngine->GetScreenSize(width, height);
	int B = 100;
	if (width / height == 4 / 3) 
	{
		B = 90;
	}
	else if (width / height == 16 / 9) 
	{
		B = 106;
	}
	else
	{
		B = 100;
	}
	double	A = (B / 2) * (PI / 180);
	double theta = (angle - previous)*(PI / 180);
	double Y = (height* tan(theta)) / (2 * tan(A));
	return Y;
}

int CLegitbot::getHitBox(int Hitbox, int Selection, Vector ViewOffSet, Vector View, CBaseEntity* pEntity, bool firstt) {
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
		if(!isVisable(pEntity, returnval)) {
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
					float temp = FovToPlayer(ViewOffSet, View, pEntity, hitboxes[i]);
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
int sign = 1;
Vector CLegitbot::CalculateBezierPoint(double t, Vector start, Vector end, float curvefac, bool first)
{
	double beforecur = curvefac;
	double ux = (1 - t);
	double uy = (1 - t);
	curvefac = randomval(curvefac) * 5;
	Vector p1 = start;
	Vector p2 = end;
	//p1.y += ((end.y - start.y) / 4)* curvefac;
	//p2.y += (curvefac);
	if (beforecur == 0)
		p2.y = end.y;
	
	double uux = ux * ux;
	double uuy = uy * uy;

	double ttx = t * t;
	double tty = t * t;

	double uuux = ux * ux * ux;
	double tttx = t * t * t;
	double uuuy = uy * uy * uy;
	double ttty = t * t * t;

	Vector p;

	//Y
	p.y = uuuy * start.y; //first term
	p.y += 3 * uuy * t * p1.y; //second term
	p.y += 3 * uy * tty * p2.y; //third term
	p.y += ttty * end.y; //fourth term

	p.x = uuux * start.x; //first term
	p.x += 3 * uux * t * p1.x; //second term
	p.x += 3 * ux * ttx * p2.x; //third term
	p.x += tttx * end.x; //fourth term

						 //p.z = 0;
	return p;
}

Vector CLegitbot::AimAng(Vector point) {
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
Vector PaintStart;
Vector PaintOut;
bool PaintFirst;
Vector ImageCalculateBezierPoint()
{
	bool first = PaintFirst;
	Vector start = PaintStart;
	Vector end = PaintOut;
	float curvefac = (Settings.GetSetting(Tab_LegitBot, Legit_Normal_Curve)*5);
	Vector p1 = start;
	Vector p2 = end;
	//p1.y += ((end.y - start.y) / 4)* curvefac;

	p2.y += (curvefac);

	for (int i = 0; i < 51; i++) {
		double t = i;
		t /= 50;

		double ux = (1 - t);
		double uy = (1 - t);

		double uux = ux * ux;
		double uuy = uy * uy;

		double ttx = t * t;
		double tty = t * t;

		double uuux = ux * ux * ux;
		double tttx = t * t * t;
		double uuuy = uy * uy * uy;
		double ttty = t * t * t;

		Vector p;

		//Y
		p.y = uuuy * start.y; //first term
		p.y += 3 * uuy * t * p1.y; //second term
		p.y += 3 * uy * tty * p2.y; //third term
		p.y += ttty * end.y; //fourth term

		p.x = uuux * start.x; //first term
		p.x += 3 * uux * t * p1.x; //second term
		p.x += 3 * ux * ttx * p2.x; //third term
		p.x += tttx * end.x; //fourth term

							 //p.z = 0;

		Interfaces.pSurface->DrawSetColor(0, 255, 0, 255);
		Interfaces.pSurface->DrawLine(p.x, p.y, p.x + 5, p.y + 5);

	}
	Interfaces.pSurface->DrawSetColor(255, 0, 0, 255);
	Interfaces.pSurface->DrawLine(20, 20, 100 + 1, 100);

	return Vector(0, 0, 0);

}
Vector Delta2Screen(Vector delta, int w, int h)
{
	/*
	* notes:
	* - the yaw 'fov' for a 4:3 res is 45 degrees
	* - the pitch 'fov' for a 4:3 res is 37 degrees
	*
	* logic:
	* - div the width & height by the fov to get an 'angles per pixel' ratio
	* - multiply the angles by that to grab the screen position
	*
	* this allows an accurate and non-shaky mouse aimbot
	*/
	Vector result =  Vector(0,0,0);
	Vector apx = Vector(0, 0, 0);
	Vector fov = Vector(0, 0, 0);

	//assign fovs
	fov.x = 37; //pitch
	// 4:3 90, 16:9 106, 16:10 100
	int width = 0;
	int height = 0;
	Interfaces.pEngine->GetScreenSize(width, height);
	int B = 45;
	if (width / height == 4 / 3)
	{
		B = 45;
	}
	else if (width / height == 16 / 9)
	{
		B = 53;
	}
	else if(width / height == 16 / 10)
	{
		B = 50;
	}
	fov.y = B;
				//grab the ratio
	apx.x = h / fov.x; //window height / pitch fov
	apx.y = w / fov.y; //window height / pitch fov

					   //now convert! (in an x/y format, relative to the center of the screen)
	result.x = -((delta.y / apx.y) * w / 4);
	result.y = (delta.x / apx.x) * h / 4;

	return result;
}
Vector CLegitbot::RcsStandalone(bool aimbot) {
	static bool first = true;
	float sens = Interfaces.g_ICVars->FindVar("sensitivity")->GetFloat();
	float multiply = (2 / sens) * 2;
	if (Hacks.LocalPlayer->m_bIsScoped())
		multiply *= 2;
	Vector punchangs = Hacks.LocalPlayer->GetPunchAngle();
	punchangs.x *= randomval(Settings.GetSetting(Tab_LegitBot, Legit_RCS_X)) * multiply;
	punchangs.y *= randomval(Settings.GetSetting(Tab_LegitBot, Legit_RCS_Y)) * multiply;
	if (punchangs.y != 0 || punchangs.x != 0) {

		static Vector lastpunangs = punchangs;
		if (first)
			lastpunangs = punchangs;
		Vector views = Hacks.CurrentCmd->viewangles;
		Vector angs = views + lastpunangs;
		angs -= punchangs;
		Normalise(angs);
		Vector delta = Vector(0, 0, 0);
		if ((angs.y < -110 && Hacks.CurrentCmd->viewangles.y > 110) || (angs.y > 110 && Hacks.CurrentCmd->viewangles.y < -110)) {
			double negativedifY = 180 - abs(angs.y);
			double posdiffenceY = 180 - abs(Hacks.CurrentCmd->viewangles.y);
			delta.y = negativedifY + posdiffenceY;
			delta.x = angs.x - Hacks.CurrentCmd->viewangles.x;
		}
		else
		{
			delta.x = angs.x - Hacks.CurrentCmd->viewangles.x;
			delta.y = angs.y - Hacks.CurrentCmd->viewangles.y;
		}
		int width = 0;
		int height = 0;
		Interfaces.pEngine->GetScreenSize(width, height);
		Vector middle;
		middle.x = width;
		middle.y = width;

		Vector screen = Delta2Screen(delta, width, height);
		Vector nextpoint = screen + middle;
		Vector smoothedpoint = CalculateSmoothPoint(middle, nextpoint, randomval(20 - Settings.GetSetting(Tab_LegitBot, Legit_RCS_Smooth)), 100);
		Vector movement = nextpoint - smoothedpoint;

		if(!aimbot)
			mouse_event(MOUSEEVENTF_MOVE, (int)movement.x, (int)movement.y, 0, 0);
		screen.z = 0;
		lastpunangs = punchangs;
		first = false;
	}
	else {
		first = true;

	}

	return Vector(0, 0, 0);

}
Vector CLegitbot::CalculateSmoothPoint(Vector start, Vector end, double smooth, double BestFov) {
	Vector sendback = Vector(0, 0, 0);
	double differenceX = end.x - start.x;
	double differenceY = end.y - start.y;
	if (smooth < 0)
		smooth = 0;

	double m = randomval(smooth);
	double n = 20 - m;
	double x = (n*differenceX) / 20;
	double y = (n*differenceY) / 20;

	sendback.x = x;
	sendback.y = y;
	int random = rand() % 11;
	if (random == 1) {

		if (sendback.x != 0 && sendback.x < 1 && sendback.x > -1) {
			if (sendback.x < 0) {
				sendback.x = -1;
			}
			else {
				sendback.x = 1;
			}

		}
		if (sendback.y != 0 && sendback.y < 1 && sendback.y > -1) {
			if (sendback.y < 0) {
				sendback.y = -1;
			}
			else {
				sendback.y = 1;
			}

		}
	}
	sendback.x += start.x;
	sendback.y += start.y;

	return sendback;
}
/*
Vector CLegitbot::Rcs(bool first) {

	Vector punchangs = Hacks.LocalPlayer->GetPunchAngle();
	float sens = Interfaces.g_ICVars->FindVar("sensitivity")->GetFloat();
	float multiply = (2 / sens) * 2;

	punchangs.x *= Settings.GetSetting(Tab_LegitBot, Legit_RCS_X)/ multiply;
	punchangs.y *= Settings.GetSetting(Tab_LegitBot, Legit_RCS_Y)/ multiply;
	Vector views = Hacks.CurrentCmd->viewangles;
	Vector angs = views;
	angs -= punchangs;
	Normalise(angs);
	Vector delta = Vector(0, 0, 0);
	delta.x = angs.x - views.x;
	delta.y = angs.y - views.y;
	int width = 0;
	int height = 0;
	Interfaces.pEngine->GetScreenSize(width, height);
	Vector screen = Delta2Screen(delta, width, height);
	screen.z = 0;
	return screen;
}
*/
Vector apnt = Vector( 0 , 0 , 0 );
bool CLegitbot::Aimbot(double Smooth, int PrimaryHitbox, int HitboxSelection, bool First, double Fov, double Curve, double Time) {
	if (!Hacks.LocalPlayer) return false;
	if (!Hacks.LocalWeapon) return false;
	if (!Hacks.CurrentCmd) return false;
	//
	ConVar* sens = Interfaces.g_ICVars->FindVar("sensitivity");
	CBaseEntity* me = Hacks.LocalPlayer;
	CBaseCombatWeapon* Gun = me->GetActiveBaseCombatWeapon();
	int a = Interfaces.pEntList->GetHighestEntityIndex();
	CBaseEntity* Target = me;
	CBaseEntity* Player;
	double BestFov = 360;
	int TargetHitbox = -1;
	// Get Target and Hitbox
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
			continue; 

		int	BestHitbox = -1;
		BestHitbox = getHitBox(PrimaryHitbox, HitboxSelection, Hacks.LocalPlayer->GetEyePosition(), Hacks.CurrentCmd->viewangles, Player, First);

		Vector b4 = Hacks.CurrentCmd->viewangles;
		Vector punchAngles = me->GetPunchAngle() * 2.0f;
		if (punchAngles.x != 0.0f || punchAngles.y != 0)
		{
			b4 += punchAngles;
		}

		float FOV = FovToPlayer(me->GetEyePosition(), b4, Player, BestHitbox);
		if (FOV <= BestFov && FOV <= Fov && isVisable(Player, BestHitbox))
		{
			BestFov = FOV;
			Target = Player;
			TargetHitbox = BestHitbox;
		}

	}
	if (Target == me || TargetHitbox == -1)
	{
		return false;
	}
	if (!Target)
		return false;
	static CBaseEntity *lastTarget = Hacks.LocalPlayer;
	static int countdown = 0;
	if (lastTarget != Target) {
		tick = 0;
		countdown = randomval(Settings.GetSetting(Tab_LegitBot, Legit_TargetDelay));
		lastTarget = Target;
	}
	if (First) {
		countdown = 0;
		lastTarget = Target;
		tick = 0;

	}
	if (countdown > 0) {
		countdown--;
		return false;
	}
	if (!(Target->GetFlags() & FL_ONGROUND) && Settings.GetSetting(Tab_LegitBot, Legit_IgnoreInAir))
		return false;

	Vector point = GetHitboxPOS(Target, TargetHitbox);
	Vector out;
	int width = 0;
	int height = 0;
	Interfaces.pEngine->GetScreenSize(width, height);
	float curve = Curve;
	float ScreenCenterX = (width / 2);
	float ScreenCenterY = (height / 2);
	Interfaces.g_pDebugOverlay->ScreenPosition(point, out);
	Vector middleofscreen;
	middleofscreen.x = ScreenCenterX;
	middleofscreen.y = ScreenCenterY;
	if (Settings.GetSetting(Tab_LegitBot, Legit_RCS_Enable)) {
		Vector angs = Hacks.CurrentCmd->viewangles;
		angs -= Hacks.LocalPlayer->GetPunchAngle();
		Normalise(angs);
		Vector delta = Vector(0, 0, 0);
		if ((angs.y < -110 && Hacks.CurrentCmd->viewangles.y > 110) || (angs.y > 110 && Hacks.CurrentCmd->viewangles.y < -110)) {
			double negativedifY = 180 - abs(angs.y);
			double posdiffenceY = 180 - abs(Hacks.CurrentCmd->viewangles.y);
			delta.y = negativedifY + posdiffenceY;
			delta.x = angs.x - Hacks.CurrentCmd->viewangles.x;
		}
		else
		{
			delta.x = angs.x - Hacks.CurrentCmd->viewangles.x;
			delta.y = angs.y - Hacks.CurrentCmd->viewangles.y;
		}
		Vector screen = Delta2Screen(delta, width, height);
		out.x += screen.x;
		out.y += screen.y;
		apnt = out;
	}
	double t = tick;
	if (Time != 0.1) {
		double tempt = t / (Time * 10);
		t = tempt;
	}
	else
		t = 1;
	Vector outt;
	Vector changer = Vector(0, 0, 0);
	outt = out;
	if (t > 1)
		t = 1;

	if (t < 1) {
		outt = CalculateBezierPoint(t, middleofscreen, out, curve, First);
	}
	
	outt = CalculateSmoothPoint(middleofscreen, outt, Smooth, BestFov);
	//if (Settings.GetSetting(Tab_LegitBot, Legit_RCS_Enable))
		//changer = Rcs(First);
	//outt += changer;



	float x = outt.x;
	float y = outt.y;

	float TargetX = 0;
	float TargetY = 0;
	if (x != 0)
	{
			TargetX = x - ScreenCenterX;
	}
	if (y != 0)
	{
			TargetY = y - ScreenCenterY;
	}
	float multiply = 2 / sens->GetFloat() * 2;
	posX = TargetX * multiply;
	posY = TargetY*multiply;
	shootingX = true;
	tick++;
	return true;
}


bool aimbot = false;
void CLegitbot::Legitbot() {
	static bool First = true;
	if (First) {
		bullets = 0;
	}
	int AimKey = Settings.GetSetting(Tab_LegitBot, Legit_Aimbot_Key);
	if (GetAsyncKeyState(AimKey)) {
		if(true){
			static int delaycout = 0;
			if (First)
				delaycout = 2;
			if(delaycout > 0){
				delaycout--;
				Hacks.CurrentCmd->buttons &= ~IN_ATTACK;

			}

		}

		double Smooth = randomval(Settings.GetSetting(Tab_LegitBot, Legit_Normal_Speed));
		double Curve = randomval(Settings.GetSetting(Tab_LegitBot, Legit_Normal_Curve));
		double Time = randomval(Settings.GetSetting(Tab_LegitBot, Legit_Normal_AimTime));
		int PrimaryHitbox = Settings.GetSetting(Tab_LegitBot, Legit_Normal_SelectionBone);
		int HitboxSelection = Settings.GetSetting(Tab_LegitBot, Legit_Normal_SelectionType);
		Vector punch = Hacks.LocalPlayer->GetPunchAngle();
		if (Settings.GetSetting(Tab_LegitBot, Legit_SA_Amount)) {
			if (abs(punch.x) < 0.1 && abs(punch.y) < 0.1) {
				Smooth = randomval(Settings.GetSetting(Tab_LegitBot, Legit_SA_Speed));
				Curve = randomval(Settings.GetSetting(Tab_LegitBot, Legit_SA_Curve));
				Time = randomval(Settings.GetSetting(Tab_LegitBot, Legit_SA_AimTime));
				PrimaryHitbox = Settings.GetSetting(Tab_LegitBot, Legit_SA_SelectionBone);
				HitboxSelection = Settings.GetSetting(Tab_LegitBot, Legit_SA_SelectionType);
			}
		}

		double Fov = Settings.GetSetting(Tab_LegitBot, Legit_Normal_FOV);
		aimbot = Aimbot(Smooth, PrimaryHitbox, HitboxSelection, First, Fov, Curve, Time);

		First = false;
		mouse_event(MOUSEEVENTF_MOVE, (uint)(posX), (uint)(posY), NULL, NULL);

	}
	else {

		First = true;
		tick = 1;
		bullets = 0;

	}
}
bool CLegitbot::TriggerHold() {
	if (!Hacks.LocalWeapon)return false;
	int TriggerKey = Settings.GetSetting(Tab_LegitBot, Trigger_Lock_Key);
	static int strength = 0;
	static int lasthitbox = 0;
	if ((Settings.GetSetting(Tab_LegitBot, Trigger_Lock_Active) == 2 && !GetAsyncKeyState(TriggerKey)))return false;

	if (Hacks.LocalWeapon->isSniper() && Hacks.LocalPlayer->m_bIsScoped() || !Hacks.LocalWeapon->isSniper()){
		bool trace = false;
		trace_t tr;

		tr.hitbox = 0;
		Vector Angle = Hacks.CurrentCmd->viewangles;
		Vector Punchangs = Hacks.LocalPlayer->GetPunchAngle() * 2;
		Angle += Punchangs;
		Vector Addition = Vector(0, 0, 0);
		Addition.x = 10000;
		if (90 < Angle.y || Angle.y< -90)
		{
			Addition.x = -10000;
			if (90 == Angle.y || Angle.y == -90) {
				Angle.y -= 0.00001;
			}
			Addition.y = tan(DEG2RAD(Angle.y))*Addition.x;
			Addition.z = tan(DEG2RAD(-Angle.x))*sqrt(Addition.x*Addition.x + Addition.y * Addition.y);


		}
		else {
			Addition.y = tan(DEG2RAD(Angle.y))*Addition.x;
			Addition.z = tan(DEG2RAD(-Angle.x))*sqrt(Addition.x*Addition.x + Addition.y * Addition.y);
		}

		Vector src = Hacks.LocalPlayer->GetEyePosition();
		Vector dst = src + Addition;
		UTIL_TraceLine(src, dst, 0x4600400B, Hacks.LocalPlayer, 0, &tr);

		if (!tr.m_pEnt)return false;

		if (Hacks.LocalWeapon->IsNotWeapon()) return false;

		if (Hacks.LocalWeapon->IsKnife() && tr.fraction > 0.03)
			return false;
		if ((int)Hacks.LocalWeapon->IsZeus() && tr.fraction > 0.04)
			return false;
		if (tr.m_pEnt)
		{
			CBaseEntity* tokill = tr.m_pEnt;
			if (tokill->GetTeam() == Hacks.LocalPlayer->GetTeam())return false;

			if (tr.hitgroup != 0) {
				trace = true;
			}
			//if (trace)
			//	cout << tr.hitbox << endl;
			if (trace) {
				strength = Settings.GetSetting(Tab_LegitBot, Trigger_Lock_Strength);
				lasthitbox = tr.hitbox;
			}



		}
		if (strength > 0) {
			double smooth = Settings.GetSetting(Tab_LegitBot, Trigger_Lock_Smooth);
			Aimbot(smooth, 0, 2, true, 2, 0.1, 0.1);
			mouse_event(0x0001, (uint)(posX), (uint)(posY), NULL, NULL);
			strength--;
		}
	}

	return true;

}
bool CLegitbot::HitboxTriggerbot() {
	if (!Hacks.LocalWeapon)return false;
	
	bool shouldshoot = checkhitbox();
	if (Hacks.LocalWeapon->isSniper() && Settings.GetSetting(Tab_LegitBot, Trigger_Check_Scope))
	{
		if (!Hacks.LocalPlayer->m_bIsScoped())
			shouldshoot = false;
	}
	return shouldshoot;
}
bool CLegitbot::MagnetTrigger() {
	static bool First = true;
	int TriggerKey = Settings.GetSetting(Tab_LegitBot, Trigger_Key);

	if (Settings.GetSetting(Tab_LegitBot, Trigger_Type) && GetAsyncKeyState(TriggerKey) || Settings.GetSetting(Tab_LegitBot, Trigger_Type) == 0) {
		double Smooth = randomval(Settings.GetSetting(Tab_LegitBot, Trigger_Magnet_Speed));
		double Curve = randomval(Settings.GetSetting(Tab_LegitBot, Trigger_Magnet_Curve));
		int PrimaryHitbox = Settings.GetSetting(Tab_LegitBot, Trigger_Magnet_SelectionBone);
		int HitboxSelection = Settings.GetSetting(Tab_LegitBot, Trigger_Magnet_SelectionType);
		double Fov = randomval(Settings.GetSetting(Tab_LegitBot, Trigger_Magnet_FOV));
		double Time = randomval(Settings.GetSetting(Tab_LegitBot, Trigger_Magnet_AimTime));

		bool abot = Aimbot(Smooth, PrimaryHitbox, HitboxSelection, First, Fov, Curve, Time);
		if (!abot)
			return false;

		First = false;
		return true;

	}
	else {
		First = true;
		tick = 1;
		bullets = 0;
		return false;
	}
}

void CLegitbot::Triggerbot() {
	bool attack = false;
	static bool first = true;
	static bool Attacking = false;
	static int delay = 0;
	static int after = 0;
	static bool shoot = false;
	static bool spraying = false;
	bool hittrig = HitboxTriggerbot();
	int TriggerKey = Settings.GetSetting(Tab_LegitBot, Trigger_Key);
	if (Settings.GetSetting(Tab_LegitBot, Trigger_Type) && GetAsyncKeyState(TriggerKey) || Settings.GetSetting(Tab_LegitBot, Trigger_Type) == 0) {
		if (Settings.GetSetting(Tab_LegitBot, Trigger_Magnet_Active))
		{
			attack = MagnetTrigger();
			if (!attack && hittrig)
				attack = true;
		}
		else
		{
			attack = hittrig;
		}
	}
	bool delayed = false;
	if (attack) {
		if (first) {
			Attacking = true;
			delayed = true;
			first = false;
		}
	}
	if (Attacking) {
		if (delay >= randomval(Settings.GetSetting(Tab_LegitBot, Trigger_Delay))) {
			shoot = true;
			if (!attack)
			{
				Attacking = false;
				delay = 0;
				first = true;
			}

		}
		else 
		{
			delay++;
			shoot = false;
		}
	}
	else
	{
		first = true;
		shoot = false;

	}
	if (shoot) {
		if(Settings.GetSetting(Tab_LegitBot, Trigger_Magnet_Active))
			mouse_event(0x0001, (uint)(posX), (uint)(posY), NULL, NULL);
		if(hittrig)
			Hacks.CurrentCmd->buttons |= IN_ATTACK;
		
		spraying = true;	
	}
	if (spraying && !shoot) {
		if (after <= randomval(Settings.GetSetting(Tab_LegitBot, Trigger_After))) {
			if (Settings.GetSetting(Tab_LegitBot, Trigger_Magnet_Active))
				mouse_event(0x0001, (uint)(posX), (uint)(posY), NULL, NULL);
				Hacks.CurrentCmd->buttons |= IN_ATTACK;
			after++;
		}
		else 
		{
			after = 0;
			spraying = false;
		}

	}
}
void CLegitbot::SlowAim() {
	ConVar* sens = Interfaces.g_ICVars->FindVar("sensitivity");
	static float Orginalsens = sens->GetFloat();
	CBaseEntity* Target = Hacks.LocalPlayer;
	CBaseEntity* Player;
	double BestFov = 360;
	double Fov = randomval(Settings.GetSetting(Tab_LegitBot, Legit_SlowAim_FOV));
	for (int i = 0; i < 99; i++)
	{
		Player = Interfaces.pEntList->GetClientEntity(i);
		if (!Player)
			continue;

		if (Player->IsDormant()
			|| (Player->GetHealth() == 0)
			|| !Player->isAlive()
			|| (Player == Hacks.LocalPlayer)
			|| (Player->GetTeam() == Hacks.LocalPlayer->GetTeam())
			|| Player->HasGunGameImmunity())
			continue;


		Vector b4 = Hacks.CurrentCmd->viewangles;
		Vector punchAngles = Hacks.LocalPlayer->GetPunchAngle() * 2.0f;
		if (punchAngles.x != 0.0f || punchAngles.y != 0)
		{
			b4 += punchAngles;
		}
		int bonetoaim = 0;
		if (Settings.GetSetting(Tab_LegitBot, Legit_SlowAim_Bone) == 2) {
			float bestfov = 360;
			for (int i = 0; i < 5; i++) {
				float FOV = FovToPlayer(Hacks.LocalPlayer->GetEyePosition(), b4, Player, bonetoaim);
				if (FOV < bestfov && isVisable(Player, i)) {
					bonetoaim = i;
					bestfov = Fov;
				}
			}

		}
		else {
			bonetoaim = 0;

		}

		float FOV = FovToPlayer(Hacks.LocalPlayer->GetEyePosition(), b4, Player, bonetoaim);
		//cout << bonetoaim << endl;
		if (FOV <= BestFov && FOV <= Fov && isVisable(Player, bonetoaim))
		{
			BestFov = FOV;
			Target = Player;
		}

	}
	//
	if (Target == Hacks.LocalPlayer) {
		sens->SetValue(Orginalsens);

		return;
	}

	if (!Target) {
		sens->SetValue(Orginalsens);
		return;
	}

	float slowaim = Orginalsens * (Settings.GetSetting(Tab_LegitBot, Legit_SlowAim_Amount)/100);
	float slowaime = slowaim;

	if (Settings.GetSetting(Tab_LegitBot, Legit_SlowAim_Type) == 2)
	{
		slowaim = BestFov / Fov * (Orginalsens - slowaime) + slowaime;
	}
	sens->SetValue(slowaim);

}
void CLegitbot::Move() {
	posX = 0;
	posY = 0;
	shootingX = true;
	Normalise(Hacks.CurrentCmd->viewangles);
	if (!Menu.Opened) {
		if (Settings.GetSetting(Tab_LegitBot, Legit_Activate)) {
			if (Settings.GetSetting(Tab_LegitBot, Legit_SlowAim_Active))
				SlowAim();
			if (Settings.GetSetting(Tab_LegitBot, Legit_Normal_Active))
				Legitbot();
				
		}
		if(Settings.GetSetting(Tab_LegitBot, Trigger_Lock_Active) == 2|| Settings.GetSetting(Tab_LegitBot, Trigger_Lock_Active) == 3)
			TriggerHold();
		if (Settings.GetSetting(Tab_LegitBot, Trigger_Active))
			Triggerbot();
		static int firedelay = 0;
		static bool first = true;
		if (Settings.GetSetting(Tab_LegitBot, Legit_RCS_Type) == 2)
			RcsStandalone(aimbot);

		if (Settings.GetSetting(Tab_LegitBot, Legit_FireDelay) != 0) {
			if (Hacks.CurrentCmd->buttons & IN_ATTACK) {
				if (first) {
					firedelay = Settings.GetSetting(Tab_LegitBot, Legit_FireDelay);
					first = false;
				}
				else
					firedelay--;
				if (firedelay > 0)
				{
					Hacks.CurrentCmd->buttons &= ~IN_ATTACK;
				}
					

			}
			else {
				first = true;
			}

		}

		Normalise(Hacks.CurrentCmd->viewangles);
	}
}