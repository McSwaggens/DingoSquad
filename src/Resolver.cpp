#include "stdafx.h"
#include "Resolver.h"

extern int bullets;
CResolver Resolver;
void CResolver::AAID(Vector* &Angle, CPlayer* Player) {
	Vector orginalview = Vector(0, 0, 0); orginalview.x = Angle->x; orginalview.y = Angle->y;
	int origin = 0;
	Vector angle = Vector(0, 0, 0);
	CalcAngle(Player->Entity->GetEyePosition(), Hacks.LocalPlayer->GetEyePosition(), angle);
	int pelvisview = Player->Entity->pelvisangs();
	int totarget = angle.y;
	if (pelvisview < 0)
		pelvisview = abs(pelvisview) + 180;
	if (orginalview.y == 0) {
		Player->aa = "Lisp";
		if(pelvisview >= pelvisview + 180 - 10 && pelvisview <= pelvisview + 180 - 10) Player->aa = "Lisp Inverse";
		else if (pelvisview >= totarget + 180 -10 && pelvisview <= totarget + 180 + 10) Player->aa = "Lisp Backwrads";
		else if (pelvisview >= totarget - 10 && pelvisview <= totarget + 10) Player->aa = "Lisp Forwards";
		else if (pelvisview >= totarget + 90 - 10 && pelvisview <= totarget + 90 + 10) Player->aa = "Lisp Right";
		else if (pelvisview >= totarget - 90 - 10 && pelvisview <= totarget - 90 + 10) Player->aa = "Lisp Left";

	}
	else if (pelvisview - orginalview.y > 10 || pelvisview - orginalview.y < -10) {
		Player->aa = "No fakes";
		if (orginalview.y == origin + 180) Player->aa = "Inverse";
		if (orginalview.y == totarget + 180) Player->aa = "Backwrads";
		if (orginalview.y == totarget) Player->aa = "Forwards";
		if (orginalview.y == totarget + 90) Player->aa = "Right";
		if (orginalview.y == totarget - 90) Player->aa = "Left";
	}
	else {
		Player->aa = "Fake";
		if (pelvisview >= pelvisview + 180 - 10 && pelvisview <= pelvisview + 180 - 10) Player->aa = "Real Inverse";
		else if (pelvisview >= totarget + 180 - 10 && pelvisview <= totarget + 180 + 10) Player->aa = "Real Backwrads";
		else if (pelvisview >= totarget - 10 && pelvisview <= totarget + 10) Player->aa = "Real Forwards";
		else if (pelvisview >= totarget + 90 - 10 && pelvisview <= totarget + 90 + 10) Player->aa = "Real Right";
		else if (pelvisview >= totarget - 90 - 10 && pelvisview <= totarget - 90 + 10) Player->aa = "Real Left";

	}
}
/*void CResolver::AutoResolver(Vector* &Angle, CPlayer* Player) {
	static int jitter = 1;
	static DWORD g_InterpolationList = Utils.PatternSearch("client.dll", (PBYTE)"\x0F\xB7\x05\x00\x00\x00\x00\x3D\x00\x00\x00\x00\x74\x3F", "xxx????x????xx", 0, 0);
	if (g_InterpolationList)
	{
		DWORD* togoto0 = reinterpret_cast<DWORD*>(static_cast<DWORD>(g_InterpolationList) + 18);//array size/ list gotta clear it
		togoto0 = 0;
		DWORD* someothershit = reinterpret_cast<DWORD*>(static_cast<DWORD>(g_InterpolationList) + 12); //invalidate the head interpolation
		someothershit = (DWORD*)0xFFFF;
	}// Credits kelse, Flosen and Jake this works but the array size might be wrong and the head might also me wrong, also could be jumping byte wrong /(")

	Vector orginalview = Vector(0, 0, 0); orginalview.x = Angle->x; orginalview.y = Angle->y;
	float pelvisview = Player->Entity->pelvisangs();
	
	if (Player->Entity->GetFlags() & FL_ONGROUND && Hacks.LocalPlayer->GetVecVelocity().Length2D() != 0|| Player->lastpelvisang != pelvisview) {
		Player->difference = pelvisview - orginalview.y;
		Player->lastpelvisang = (int)pelvisview;

	}
	if(jitter % 2 == 0)
		Angle->y += Player->difference;
	jitter++;
}
*/
void CResolver::Lispfix(Vector* &Angle, CPlayer* Player) {
	int index = Player->Index;
	int lispfix = Settings.GetPlayer(index, Tab_Ragebot, Ragebot_LispFix);
	switch (lispfix) {
	case 2:
	{		
		if (!Player->Entity) {

		}
		else {
			Angle->y = Player->Entity->pelvisangs();
		}
	}
	break;

	//case 3:
	//{
		//AutoResolver(Angle, Player);
	//}
	//break;
	}
}
void CResolver::XResolver(Vector* &Angle, CPlayer* Player) {
	int index = Player->Index;
	int switchvalX = Settings.GetPlayer(index, Tab_Ragebot, Ragebot_ResolverX);
	switch (switchvalX) {
	case 2:	{
		int num = bullets % 3;
		switch (num) {
		case 0:	Angle->x = -90; break;
		case 1:	Angle->x = 0.f; break;
		case 2:	Angle->x = 90.f; break;
		}
	}
	break;
	case 3:	{
		Angle->x = -89;
	}
	break;
	case 4:	{
		Angle->x = 89;
	}
	break;
	}
}

void CResolver::YResolver(Vector* &Angle, CPlayer* Player)
{
	float yvalue;
	int bigy = Player->Resolved_Angle.y * 10000;
	int index = Player->Index;
	int switchvaly = Settings.GetPlayer(index, Tab_Ragebot, Ragebot_ResolverY);
	static bool jitter = true;

	switch (switchvaly) {
	case 2:
	{
		/*int value = (bullets) % 13;
		switch (value) {
		case 0: Angle->y += 0.0f; break;
		case 1: Angle->y += 25; break;
		case 2: Angle->y += 0; break;
		case 3: Angle->y -= 25; break;
		case 4: Angle->y += 0; break;
		case 5: Angle->y += 80; break;
		case 6: Angle->y += 0; break;
		case 7: Angle->y -= 80; break;
		case 8: Angle->y += 0; break;
		case 9: Angle->y += 40; break;
		case 10: Angle->y += 0; break;
		case 11: Angle->y -= 40; break;
		case 12: Angle->y += 0; break;

		}
		break;
		*/
		static int spin = 0;
		spin += 25;
		Angle->y = spin;
	}
	break;
	case 3:
	{
		if(jitter)
		Angle->y += 180;
		else
		Angle->y = Player->reset.y + 180;

	}
	break;
	case 4:
	{
		if (jitter)
			Angle->y += 90;
		else
			Angle->y = Player->reset.y + 90;
	}
	break;
	case 5:
	{
		if (jitter)
			Angle->y -= 90;
		else
			Angle->y = Player->reset.y - 90;
	}
	break;
	case 6: //Fuck you aimware
	{
		int value = (bullets) % 11;
		switch (value) {
		case 0:Angle->y = Player->reset.y; break;
		case 1:Angle->y += 0; break;
		case 2:Angle->y = Player->reset.y + 180; break;
		case 3:Angle->y += 15; break;
		case 4:Angle->y = Player->reset.y + 90; break;
		case 5:Angle->y -= 15; break;
		case 6:Angle->y = Player->reset.y + 270; break;
		case 7:Angle->y += 0; break;
		case 8:Angle->y = Player->reset.y + 180; break;
		case 9:Angle->y -= 45; break;
		case 10:Angle->y += 45; break;
		}
		break;

	}break;
	}
	jitter = !jitter;
}
void CResolver::Reset() {
	for (int i = 0; i < 99; i++) {
		CPlayer* Player = Playerlist.Get_Player_By_Index(i);
		if (!Player->Entity)continue;
		if (Player->Entity->GetTeam() == Hacks.LocalPlayer->GetTeam())continue;

		//if (!Player->updated) continue;
		Player->delta.x = Player->reset.x - Player->Resolved_Angles.x;
		Player->delta.y = Player->reset.y - Player->Resolved_Angles.y;
		Player->delta.z = Player->reset.z - Player->Resolved_Angles.z;
		//cout << Player->delta.y << endl;
	}

}
void CResolver::TargetsResolver() {
	for (int i = 0; i < 99; i++)
	{
		CPlayer* Player = Playerlist.Get_Player_By_Index(i);
		if (!Player->Entity)continue;
		if (!Player) continue;
		if (Player->Entity->GetTeam() == Hacks.LocalPlayer->GetTeam())continue;
		Player->updated = false;

		Vector* Angle = Player->Entity->GetEyeAnglesPointer();
		Vector viewy = Player->Entity->GetEyeAngles();
		if (*Angle != Player->Resolved_Angles)
			Player->delta = Vector(0, 0, 0);
		Angle->x += Player->delta.x;
		Angle->y += Player->delta.y;
		Angle->z += Player->delta.z;
		Player->reset = *Angle;
		//No longer lisp fix just resolver in general
		AAID(Angle, Player);
		Lispfix(Angle, Player);
		int index = Player->Index;
		int lispfix = Settings.GetPlayer(index, Tab_Ragebot, Ragebot_LispFix);
		Player->updated = true;
		XResolver(Angle, Player);
		YResolver(Angle, Player);

		Player->Resolved_Angles = *Angle;

	}

}

void CResolver::Resolver(ClientFrameStage_t curStage)
{
	if (!Hacks.LocalPlayer || !Hacks.LocalWeapon) {

	}
	else {
		if (Hacks.LocalPlayer->isAlive()) {
			if (curStage == ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
			{
				TargetsResolver();
			}
			if (curStage == ClientFrameStage_t::FRAME_RENDER_END) {
				Reset();
			}
		}
	}
}


