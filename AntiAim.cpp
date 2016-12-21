#include "stdafx.h"
#include "AntiAim.h"

/*
AntiAim::AntiAim()
{
	Vector views = Hacks.CurrentCmd->viewangles;

	int lispPitch = 0;
	if (lisPitchon) {
		lispPitch = 11322360;
	}
	int lispYaw = 0;
	if (lisYawpon) {
		lispYaw = 11322360;
	}
	bool shouldfakepitch = false;
	int fakePitchang = 0; //get value from menu
	if (fakePitchang != 0) {
		shouldfakepitch = true;
		bool switcher = false;

		if (switcher) {
			Hacks.SendPacket = false;
		}
		else {
			Hacks.SendPacket = true;

		}

		switcher = !switcher;



	}
	//Pitch

	switch (1)
	{


	case 1://emotion
		if (Hacks.SendPacket || !shouldfakepitch) {
			views.x = 63.74 + lispPitch;
		}
		else {
			views.x = fakePitchang + lispPitch;
		}

	case 2: //down
		if (Hacks.SendPacket || !shouldfakepitch) {
			views.x = 89 + lispPitch;
		}
		else {
			views.x = fakePitchang + lispPitch;
		}

	case 3: //up
		if (Hacks.SendPacket || !shouldfakepitch) {
		views.x = -89 + lispPitch;
		}
		else {
			views.x = fakePitchang + lispPitch;
		}

	case 4: //Fake up
		if (Hacks.SendPacket || !shouldfakepitch) {
			views.x = -180 + lispPitch;
		}
		else {
			views.x = fakePitchang + lispPitch;
		}

	case 5: //Fake down
		if (Hacks.SendPacket || !shouldfakepitch) {
			views.x = 180 + lispPitch;
		}
		else {
			views.x = fakePitchang + lispPitch;
		}


	}
	//Yaw
	switch (1)
	{

	case 1: 
		//Backwards 
		views.y += 180 + lispYaw;

	case 2:
		//forward
		views.y = lispYaw;
	case 3:
		//Sideways
		views.y -= 90;
	case 4:
		//Slow spin
		int spinval = rand() % 20;
		views.y -= spinval + lispYaw;
	case 5:
		//Fast spin
		int spinval = rand() % 80;
		views.y += spinval + 100 + lispYaw;
	case 6:
		//Fake Fast spin
		int spinval = rand() % 80;
		if (Hacks.SendPacket) {
			views.y += spinval + 100 + lispYaw;
		}
		else {
			views.y += 180 + lispYaw;
		}
	case 7:
		//Fake sideways
		if (Hacks.SendPacket) {
			views.y = 90 + lispYaw;
		}
		else {
			views.y = -90 + lispYaw;
		}


	}
	if (attargers) {
		//paste in aimbot code
		Vector totarget;
		views.y += totarget.y;
	}

}
*/

AntiAim::~AntiAim()
{
}
