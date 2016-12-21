#include "stdafx.h"

int MenuRed;
int MenuGreen;
int MenuBlue;
int MenuAlpha;
int TextRed;
int TextGreen;
int TextBlue;
int TextAlpha;
int BackgroundRed;
int BackgroundGreen;
int BackgroundBlue;
int BackgroundAlpha;
int OutlineRed;
int OutlineGreen;
int OutlineBlue;
int OutlineAlpha;

/* function definitions for fucntion buttons */
void Unhook();
void SaveSettings();
void LoadSettings();
void ResetWorld();

bool savesettings = false;
bool loadsettings = false;

void resetcolours() {
	{

		Settings.SetSetting(Tab_Other, Other_Esp_T_Visible_Red, 247);
		Settings.SetSetting(Tab_Other, Other_Esp_T_Visible_Green, 180);
		Settings.SetSetting(Tab_Other, Other_Esp_T_Visible_Blue, 20);



		Settings.SetSetting(Tab_Other, Other_Cham_Chicken_Visible_Red, 255);
		Settings.SetSetting(Tab_Other, Other_Cham_Chicken_Visible_Green, 0);
		Settings.SetSetting(Tab_Other, Other_Cham_Chicken_Visible_Blue, 0);



		Settings.SetSetting(Tab_Other, Other_Glow_Visible_Red, 0);
		Settings.SetSetting(Tab_Other, Other_Glow_Visible_Green, 255);
		Settings.SetSetting(Tab_Other, Other_Glow_Visible_Blue, 0);


		Settings.SetSetting(Tab_Other, Other_Cham_Enemy_Visible_Red, 0);
		Settings.SetSetting(Tab_Other, Other_Cham_Enemy_Visible_Green, 255);
		Settings.SetSetting(Tab_Other, Other_Cham_Enemy_Visible_Blue, 255);

		Settings.SetSetting(Tab_Other, Other_Esp_T_inVisible_Red, 240);
		Settings.SetSetting(Tab_Other, Other_Esp_T_inVisible_Green, 30);
		Settings.SetSetting(Tab_Other, Other_Esp_T_inVisible_Blue, 35);

		Settings.SetSetting(Tab_Other, Other_Cham_Chicken_inVisible_Red, 255);
		Settings.SetSetting(Tab_Other, Other_Cham_Chicken_inVisible_Green, 255);
		Settings.SetSetting(Tab_Other, Other_Cham_Chicken_inVisible_Blue, 255);

		Settings.SetSetting(Tab_Other, Other_Glow_inVisible_Red, 255);
		Settings.SetSetting(Tab_Other, Other_Glow_inVisible_Green, 0);
		Settings.SetSetting(Tab_Other, Other_Glow_inVisible_Blue, 0);

		Settings.SetSetting(Tab_Other, Other_Cham_Enemy_inVisible_Red, 255);
		Settings.SetSetting(Tab_Other, Other_Cham_Enemy_inVisible_Green, 121);
		Settings.SetSetting(Tab_Other, Other_Cham_Enemy_inVisible_Blue, 0);

		Settings.SetSetting(Tab_Other, Other_Esp_CT_Visible_Red, 32);
		Settings.SetSetting(Tab_Other, Other_Esp_CT_Visible_Green, 180);
		Settings.SetSetting(Tab_Other, Other_Esp_CT_Visible_Blue, 57);

		Settings.SetSetting(Tab_Other, Other_Cham_Team_Visible_Red, 255);
		Settings.SetSetting(Tab_Other, Other_Cham_Team_Visible_Green, 138);
		Settings.SetSetting(Tab_Other, Other_Cham_Team_Visible_Blue, 255);

		Settings.SetSetting(Tab_Other, Other_Cham_Hands_Red, 255);
		Settings.SetSetting(Tab_Other, Other_Cham_Hands_Green, 0);
		Settings.SetSetting(Tab_Other, Other_Cham_Hands_Blue, 0);

		Settings.SetSetting(Tab_Other, Other_Esp_CT_inVisible_Red, 63);
		Settings.SetSetting(Tab_Other, Other_Esp_CT_inVisible_Green, 72);
		Settings.SetSetting(Tab_Other, Other_Esp_CT_inVisible_Blue, 205);

		Settings.SetSetting(Tab_Other, Other_Cham_Team_inVisible_Red, 178);
		Settings.SetSetting(Tab_Other, Other_Cham_Team_inVisible_Green, 0);
		Settings.SetSetting(Tab_Other, Other_Cham_Team_inVisible_Blue, 55);

		Settings.SetSetting(Tab_Other, Other_Cham_Weapon_Red, 255);
		Settings.SetSetting(Tab_Other, Other_Cham_Weapon_Green, 0);
		Settings.SetSetting(Tab_Other, Other_Cham_Weapon_Blue, 0);

	}

}
int phase1 = 0;
int phase2 = 30;
int phase3 = 60;
int phase4 = 90;
void rainbow() {
	int rads = 10 * 360;
	int divid = 10;
	float value = (((phase1 % rads) / divid)*0.0174533);
	float red = abs(255 * sin(value));
	float blue = abs(255 * sin(value + 2));
	float green = abs(255 * sin(value + 4));
	{
		if (Settings.GetSetting(Tab_Other, Other_Esp_Enemy_Rainbow)) {

			Settings.SetSetting(Tab_Other, Other_Esp_T_Visible_Red, red);
			Settings.SetSetting(Tab_Other, Other_Esp_T_Visible_Green, green);
			Settings.SetSetting(Tab_Other, Other_Esp_T_Visible_Blue, blue);
		}

		if (Settings.GetSetting(Tab_Other, Other_Cham_Chicken_Rainbow)) {

			Settings.SetSetting(Tab_Other, Other_Cham_Chicken_Visible_Red, red);
			Settings.SetSetting(Tab_Other, Other_Cham_Chicken_Visible_Green, green);
			Settings.SetSetting(Tab_Other, Other_Cham_Chicken_Visible_Blue, blue);
		}

		if (Settings.GetSetting(Tab_Other, Other_Glow_Rainbow)) {

			Settings.SetSetting(Tab_Other, Other_Glow_Visible_Red, red);
			Settings.SetSetting(Tab_Other, Other_Glow_Visible_Green, green);
			Settings.SetSetting(Tab_Other, Other_Glow_Visible_Blue, blue);
		}

		if (Settings.GetSetting(Tab_Other, Other_Cham_Enemy_Rainbow)) {
			Settings.SetSetting(Tab_Other, Other_Cham_Enemy_Visible_Red, red);
			Settings.SetSetting(Tab_Other, Other_Cham_Enemy_Visible_Green, green);
			Settings.SetSetting(Tab_Other, Other_Cham_Enemy_Visible_Blue, blue);
		}
	}
	value = (((phase2 % rads) / divid)*0.0174533);
	red = abs(255 * sin(value + 2));
	blue = abs(255 * sin(value));
	green = abs(255 * sin(value + 4));
	{
		if (Settings.GetSetting(Tab_Other, Other_Esp_Enemy_Rainbow)) {

			Settings.SetSetting(Tab_Other, Other_Esp_T_inVisible_Red, red);
			Settings.SetSetting(Tab_Other, Other_Esp_T_inVisible_Green, green);
			Settings.SetSetting(Tab_Other, Other_Esp_T_inVisible_Blue, blue);
		}
		if (Settings.GetSetting(Tab_Other, Other_Cham_Chicken_Rainbow)) {

			Settings.SetSetting(Tab_Other, Other_Cham_Chicken_inVisible_Red, red);
			Settings.SetSetting(Tab_Other, Other_Cham_Chicken_inVisible_Green, green);
			Settings.SetSetting(Tab_Other, Other_Cham_Chicken_inVisible_Blue, blue);
		}

		if (Settings.GetSetting(Tab_Other, Other_Glow_Rainbow)) {

			Settings.SetSetting(Tab_Other, Other_Glow_inVisible_Red, red);
			Settings.SetSetting(Tab_Other, Other_Glow_inVisible_Green, green);
			Settings.SetSetting(Tab_Other, Other_Glow_inVisible_Blue, blue);
		}

		if (Settings.GetSetting(Tab_Other, Other_Cham_Enemy_Rainbow)) {

			Settings.SetSetting(Tab_Other, Other_Cham_Enemy_inVisible_Red, red);
			Settings.SetSetting(Tab_Other, Other_Cham_Enemy_inVisible_Green, green);
			Settings.SetSetting(Tab_Other, Other_Cham_Enemy_inVisible_Blue, blue);
		}
	}
	value = (((phase3 % rads) / divid)*0.0174533);
	red = abs(255 * sin(value));
	blue = abs(255 * sin(value + 4));
	green = abs(255 * sin(value + 2));
	{
		if (Settings.GetSetting(Tab_Other, Other_Esp_Team_Rainbow)) {

			Settings.SetSetting(Tab_Other, Other_Esp_CT_Visible_Red, red);
			Settings.SetSetting(Tab_Other, Other_Esp_CT_Visible_Green, green);
			Settings.SetSetting(Tab_Other, Other_Esp_CT_Visible_Blue, blue);
		}
		if (Settings.GetSetting(Tab_Other, Other_Cham_Team_Rainbow)) {

			Settings.SetSetting(Tab_Other, Other_Cham_Team_Visible_Red, red);
			Settings.SetSetting(Tab_Other, Other_Cham_Team_Visible_Green, green);
			Settings.SetSetting(Tab_Other, Other_Cham_Team_Visible_Blue, blue);
		}
		if (Settings.GetSetting(Tab_Other, Other_Cham_Weapon_Rainbow)) {

			Settings.SetSetting(Tab_Other, Other_Cham_Hands_Red, red);
			Settings.SetSetting(Tab_Other, Other_Cham_Hands_Green, green);
			Settings.SetSetting(Tab_Other, Other_Cham_Hands_Blue, blue);
		}
	}
	value = (((phase4 % rads) / divid)*0.0174533);
	red = abs(255 * sin(value + 2));
	blue = abs(255 * sin(value + 4));
	green = abs(255 * sin(value));
	{
		if (Settings.GetSetting(Tab_Other, Other_Esp_Team_Rainbow)) {

			Settings.SetSetting(Tab_Other, Other_Esp_CT_inVisible_Red, red);
			Settings.SetSetting(Tab_Other, Other_Esp_CT_inVisible_Green, green);
			Settings.SetSetting(Tab_Other, Other_Esp_CT_inVisible_Blue, blue);
		}
		if (Settings.GetSetting(Tab_Other, Other_Cham_Team_Rainbow)) {

			Settings.SetSetting(Tab_Other, Other_Cham_Team_inVisible_Red, red);
			Settings.SetSetting(Tab_Other, Other_Cham_Team_inVisible_Green, green);
			Settings.SetSetting(Tab_Other, Other_Cham_Team_inVisible_Blue, blue);
		}
		if (Settings.GetSetting(Tab_Other, Other_Cham_Weapon_Rainbow)) {

			Settings.SetSetting(Tab_Other, Other_Cham_Weapon_Red, red);
			Settings.SetSetting(Tab_Other, Other_Cham_Weapon_Green, green);
			Settings.SetSetting(Tab_Other, Other_Cham_Weapon_Blue, blue);
		}
	}
	phase1++;
	phase2++;
	phase3++;
	phase4++;
}
void colourUpdate()
{


	MenuRed = Settings.GetSetting(Tab_Other, Other_MenuRed);
	MenuGreen = Settings.GetSetting(Tab_Other, Other_MenuGreen);
	MenuBlue = Settings.GetSetting(Tab_Other, Other_MenuBlue);
	MenuAlpha = Settings.GetSetting(Tab_Other, Other_MenuAlpha);
	TextRed = Settings.GetSetting(Tab_Other, Other_TextRed);
	TextGreen = Settings.GetSetting(Tab_Other, Other_TextGreen);
	TextBlue = Settings.GetSetting(Tab_Other, Other_TextBlue);
	TextAlpha = Settings.GetSetting(Tab_Other, Other_TextAlpha);

	BackgroundRed = Settings.GetSetting(Tab_Other, Other_BackgroundRed);
	BackgroundGreen = Settings.GetSetting(Tab_Other, Other_BackgroundGreen);
	BackgroundBlue = Settings.GetSetting(Tab_Other, Other_BackgroundBlue);
	BackgroundAlpha = Settings.GetSetting(Tab_Other, Other_BackgroundAlpha);
	OutlineRed = Settings.GetSetting(Tab_Other, Other_OutlineRed);
	OutlineGreen = Settings.GetSetting(Tab_Other, Other_OutlineGreen);
	OutlineBlue = Settings.GetSetting(Tab_Other, Other_OutlineBlue);
	OutlineAlpha = Settings.GetSetting(Tab_Other, Other_OutlineAlpha);

}


bool Clicked_This_Frame;
bool Holding_Mouse_1;
bool Dont_Click;
bool Holding_Menu;
int Menu_Drag_X;
int Menu_Drag_Y;

int Tab_Count = 0;
int SubTab_Misc_Count = 0;
int SubTab_Misc2_Count = 0;
int SubTab_Legit_Count = 0;

bool keys[256];
bool oldKeys[256];
bool GetKeyPress(unsigned int key)
{
	if (keys[key] == true && oldKeys[key] == false)
		return true;
	else
		return false;
}

std::vector<char*> KeyStrings = { "undefined", "Left Mouse", "Right Mouse", "Break", "Middle Mouse", "Mouse 4", "Mouse 5",
"undefined", "Backspace", "TAB", "undefined", "undefined", "undefined", "ENTER", "undefined", "undefined", "SHIFT",
"CTRL", "ALT","PAUSE","CAPS LOCK", "undefined", "undefined", "undefined", "undefined", "undefined", "undefined",
"ESC", "undefined", "undefined", "undefined", "undefined", "SPACEBAR","PG UP", "PG DOWN", "END", "HOME", "Left",
"Up", "Right", "Down", "undefined", "Print", "undefined", "Print Screen", "Insert","Delete", "undefined", "0", "1",
"2", "3", "4", "5", "6", "7", "8", "9", "undefined", "undefined", "undefined", "undefined", "undefined", "undefined",
"undefined", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U",
"V", "W", "X","Y", "Z", "Left Windows", "Right Windows", "undefined", "undefined", "undefined", "NUM 0", "NUM 1",
"NUM 2", "NUM 3", "NUM 4", "NUM 5", "NUM 6","NUM 7", "NUM 8", "NUM 9", "*", "+", "_", "-", ".", "/", "F1", "F2", "F3",
"F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12","F13", "F14", "F15", "F16", "F17", "F18", "F19", "F20", "F21",
"F22", "F23", "F24", "undefined", "undefined", "undefined", "undefined", "undefined","undefined", "undefined", "undefined",
"NUM LOCK", "SCROLL LOCK", "undefined", "undefined", "undefined", "undefined", "undefined", "undefined", "undefined",
"undefined", "undefined","undefined", "undefined", "undefined", "undefined", "undefined", "LSHIFT", "RSHIFT", "LCONTROL",
"RCONTROL", "LMENU", "RMENU", "undefined","undefined", "undefined","undefined", "undefined", "undefined", "undefined",
"undefined", "undefined", "undefined", "Next Track", "Previous Track", "Stop", "Play/Pause", "undefined", "undefined",
"undefined", "undefined", "undefined", "undefined", ";", "+", ",", "-", ".", "/?", "~", "undefined", "undefined",
"undefined", "undefined","undefined", "undefined", "undefined", "undefined", "undefined", "undefined", "undefined",
"undefined", "undefined", "undefined", "undefined", "undefined", "undefined", "undefined", "undefined","undefined",
"undefined", "undefined", "undefined", "undefined", "undefined", "undefined", "[{", "\\|", "}]", "'\"", "undefined",
"undefined", "undefined", "undefined","undefined", "undefined", "undefined", "undefined", "undefined", "undefined",
"undefined", "undefined", "undefined", "undefined", "undefined", "undefined", "undefined", "undefined", "undefined",
"undefined", "undefined", "undefined", "undefined", "undefined", "undefined", "undefined", "undefined", "undefined",
"undefined", "undefined" };

void DrawMouse()
{
	static int Texturer = Interfaces.pSurface->CreateNewTextureID(true);
	unsigned char buffer[4] = { 0, 200, 255, 255 };

	Interfaces.pSurface->DrawSetTextureRGBA(Texturer, buffer, 1, 1);
	Interfaces.pSurface->DrawSetTexture(Texturer);
	Interfaces.pSurface->DrawSetColor(0, 200, 255, 255);

	POINT Mouse;
	POINT mp; GetCursorPos(&mp);
	ScreenToClient(GetForegroundWindow(), &mp);
	Mouse.x = mp.x; Mouse.y = mp.y;
	//
	Vertex_t Verts[3];
	Verts[0].x = Mouse.x;
	Verts[0].y = Mouse.y;
	Verts[1].x = Mouse.x + 16;
	Verts[1].y = Mouse.y + 10;
	Verts[2].x = Mouse.x;
	Verts[2].y = Mouse.y + 16;

	Interfaces.pSurface->DrawTexturedPolygon(3, Verts);
}

void CMenu::Set_Current_Tab(int tab)
{
	Current_tab = tab;
}
void CMenu::Set_Current_SubTab(int tab)
{
	Current_Subtab = tab;
}

int CMenu::GetCurret_SubTab()
{
	return Current_Subtab;
}
int CMenu::GetCurret_Tab()
{
	return Current_tab;
}

void CMenu::Update_Frame()
{
	if (!Holding_Mouse_1)
	{
		if (GetClicked())
		{
			Holding_Menu = true;
		}
		else
		{
			Holding_Menu = false;
		}
	}

	if (Holding_Menu)
	{
		MenuPOS NewPOS;
		POINT Mouse;
		POINT mp; GetCursorPos(&mp);
		ScreenToClient(GetForegroundWindow(), &mp);
		Mouse.x = mp.x; Mouse.y = mp.y;
		NewPOS.x = Mouse.x - Menu_Drag_X;
		NewPOS.y = Mouse.y - Menu_Drag_Y;
		this->pos = NewPOS;
	}
}
bool CMenu::GetClicked()
{

	if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000))
	{
		return false;
	}

	POINT Mouse;
	POINT mp; GetCursorPos(&mp);
	ScreenToClient(GetForegroundWindow(), &mp);
	Mouse.x = mp.x; Mouse.y = mp.y;

	if (Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 900 && Mouse.y < this->pos.y + 20)
	{
		if (!Holding_Mouse_1)
		{
			Menu_Drag_X = Mouse.x - pos.x;
			Menu_Drag_Y = Mouse.y - pos.y;
		}
		return true;
	}
	else
	{
		return false;
	}
}

CMenu Menu;
class CButton;
class CSlider;
class CIntSlider;
class CDropbox;
class CKeybutton;
class CTab;
class CMenuBox;

class CButton
{
private:
	MenuPOS pos;
	MenuPOS offset;
	int Tab;
	int Sub;

	int Setting;
	char* Name = "ERROR";
	bool Clicked()
	{
		if (!Clicked_This_Frame)
		{
			return false;
		}
		if (Holding_Mouse_1)
		{
			return false;
		}
		if (Dont_Click)
		{
			return false;
		}

		POINT Mouse;
		POINT mp; GetCursorPos(&mp);
		ScreenToClient(GetForegroundWindow(), &mp);
		Mouse.x = mp.x; Mouse.y = mp.y;

		if (Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 12 && Mouse.y < this->pos.y + 12)
		{
			return true;
		}
		return false;
	}
public:
	void Update()
	{
		this->pos.x = Menu.pos.x + this->offset.x;
		this->pos.y = Menu.pos.y + this->offset.y;

		if (Menu.GetCurret_Tab() == Tab)
		{
			if (Menu.GetCurret_SubTab() == Sub || Sub == -1) {

				if (Clicked())
				{

					Dont_Click = true;
					Settings.SetBoolSetting(Tab, Setting, !Settings.GetMenuSetting(Tab, Setting));

				}
			}
		}
	}
	void Draw()
	{
		if (Menu.GetCurret_Tab() == Tab)
		{
			if (Menu.GetCurret_SubTab() == Sub || Sub == -1) {

				Interfaces.pSurface->DrawSetColor(35, 38, 42, 255);
				Interfaces.pSurface->DrawFilledRect(this->pos.x, this->pos.y, this->pos.x + 12, this->pos.y + 12);

				if (Settings.GetMenuSetting(this->Tab, this->Setting))
				{
					Interfaces.pSurface->DrawSetColor(23, 116, 255, 255);
					Interfaces.pSurface->DrawFilledRect(this->pos.x + 2, this->pos.y + 2, this->pos.x + 10, this->pos.y + 10);
				}
				Interfaces.pSurface->DrawSetColor(25, 25, 25, 255);
				Interfaces.pSurface->DrawOutlinedRect(this->pos.x, this->pos.y, this->pos.x + 12, this->pos.y + 12);
				Interfaces.pSurface->DrawT(this->pos.x + 15, this->pos.y - 1, CColor(255, 255, 255, 255), Hacks.Font_Tahoma, false, this->Name);
			}
		}
	}
	void Init(int Tab, int Setting, bool defult, int x, int y, char* name, int sub)
	{

		this->Tab = Tab;
		this->Setting = Setting;
		this->offset.y = y;
		this->offset.x = x;
		this->Name = name;
		this->Sub = sub;

		Settings.SetBoolSetting(Tab, Setting, defult);

	}
};

class CSlider
{
private:
	int Tab = 0;
	int SubTab = 0;
	int Setting = 0;
	double Max = 100;
	double Min = 0;
	MenuPOS pos;
	MenuPOS offset;
	char* Name = "ERROR";
	//char* SValue = "0";
	bool Is_Holding;
	bool GetClicked()
	{
		if (!Clicked_This_Frame)
		{
			this->Is_Holding = false;
			return false;
		}
		if (Holding_Mouse_1)
		{
			if (!this->Is_Holding)
			{
				return false;
			}
		}
		if (Dont_Click)
			return false;

		POINT Mouse;
		POINT mp; GetCursorPos(&mp);
		ScreenToClient(GetForegroundWindow(), &mp);
		Mouse.x = mp.x; Mouse.y = mp.y;

		if (Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 100 && Mouse.y < this->pos.y + 20)
		{
			this->Is_Holding = true;
			return true;
		}
		else if (this->Is_Holding)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
public:
	void Draw()
	{
		if (Menu.GetCurret_Tab() == Tab)
		{
			if (Menu.GetCurret_SubTab() == SubTab || SubTab == -1) {
				double Ratio = Settings.GetMenuSetting(this->Tab, this->Setting) / (this->Max - this->Min);
				double Location = Ratio * 100;
				Interfaces.pSurface->DrawSetColor(23, 116, 255, 255);
				Interfaces.pSurface->DrawFilledRect(this->pos.x + 1, this->pos.y + 8, this->pos.x + Location, this->pos.y + 14);
				Interfaces.pSurface->DrawSetColor(20, 20, 20, 255);
				Interfaces.pSurface->DrawOutlinedRect(this->pos.x, this->pos.y + 7, this->pos.x + 100, this->pos.y + 15);
				Interfaces.pSurface->DrawT(this->pos.x, this->pos.y - 12, CColor(255, 255, 255, 255), Hacks.Font_Tahoma, false, "%s", this->Name, (float)Settings.GetMenuSetting(this->Tab, this->Setting));
				float Value1 = (float)Settings.GetMenuSetting(this->Tab, this->Setting);
				char vl[256];
				sprintf(vl, "%g", Value1);
				Interfaces.pSurface->DrawT(this->pos.x + Location, this->pos.y + 3.5, CColor(255, 255, 255, 255), Hacks.Font_Tahoma, false, vl);
			}
		}
	}
	void Init(int x, int y, double min, double max, double defult, char* name, int tab, int setting, int sub)
	{

		offset.x = x;
		offset.y = y;
		Tab = tab;
		Setting = setting;
		Max = max;
		Min = min;
		Name = name;
		SubTab = sub;
		Settings.SetSetting(Tab, Setting, defult);

	}
	void Update()
	{

		this->pos.x = Menu.pos.x + offset.x;
		this->pos.y = Menu.pos.y + offset.y;

		// get clicked and changing value
		if (Menu.GetCurret_Tab() == Tab)
		{
			if (Menu.GetCurret_SubTab() == SubTab || SubTab == -1) {

				if (this->GetClicked())
				{
					Dont_Click = true;
					POINT Mouse;
					POINT mp; GetCursorPos(&mp);
					ScreenToClient(GetForegroundWindow(), &mp);
					Mouse.x = mp.x; Mouse.y = mp.y;
					// get differance
					double idifference;
					idifference = Mouse.x - this->pos.x;
					// Set Value
					double value = ((idifference / 100)*(this->Max - this->Min));
					if (value < Min)
					{
						value = Min;
					}
					else if (value > Max)
					{
						value = Max;
					}

					Settings.SetSetting(Tab, Setting, value);
				}
			}
		}
	}

};
class CIntSlider
{
private:
	int Tab = 0;
	int Setting = 0;
	int Max = 100;
	int Min = 0;
	MenuPOS pos;
	MenuPOS offset;
	char* Name = "ERROR";
	bool Is_Holding;
	bool GetClicked()
	{
		if (!Clicked_This_Frame)
		{
			this->Is_Holding = false;
			return false;
		}
		if (Holding_Mouse_1)
		{
			if (!this->Is_Holding)
			{
				return false;
			}
		}
		if (Dont_Click)
			return false;

		POINT Mouse;
		POINT mp; GetCursorPos(&mp);
		ScreenToClient(GetForegroundWindow(), &mp);
		Mouse.x = mp.x; Mouse.y = mp.y;

		if (Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 100 && Mouse.y < this->pos.y + 20)
		{
			this->Is_Holding = true;
			return true;
		}
		else if (this->Is_Holding)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
public:
	void Draw()
	{
		if (Menu.GetCurret_Tab() == Tab)
		{
			double Ratio = Settings.GetMenuSetting(this->Tab, this->Setting) / (this->Max - this->Min);
			double Location = Ratio * 100;
			Interfaces.pSurface->DrawSetColor(50, 50, 50, 255);
			Interfaces.pSurface->DrawOutlinedRect(this->pos.x, this->pos.y + 5, this->pos.x + 100, this->pos.y + 15);
			Interfaces.pSurface->DrawSetColor(0, 200, 255, 255);
			Interfaces.pSurface->DrawFilledRect(this->pos.x + 2, this->pos.y + 7, this->pos.x + Location, this->pos.y + 13);
			Interfaces.pSurface->DrawSetColor(200, 200, 200, 255);
			Interfaces.pSurface->DrawFilledRect(this->pos.x + Location - 3, this->pos.y, this->pos.x + Location + 3, this->pos.y + 20);
			Interfaces.pSurface->DrawSetColor(170, 170, 170, 255);
			Interfaces.pSurface->DrawOutlinedRect(this->pos.x + Location - 3, this->pos.y, this->pos.x + Location + 3, this->pos.y + 20);

			Interfaces.pSurface->DrawT(this->pos.x, this->pos.y - 12, CColor(255, 255, 255, 255), Hacks.Font_Tahoma, false, "%s: %.1f", this->Name, (float)Settings.GetMenuSetting(this->Tab, this->Setting));
		}
	}
	void Init(int x, int y, int min, int max, int defult, char* name, int tab, int setting)
	{

		offset.x = x;
		offset.y = y;
		Tab = tab;
		Setting = setting;
		Max = max;
		Min = min;
		Name = name;

		Settings.SetSetting(Tab, Setting, defult);

	}
	void Update()
	{

		this->pos.x = Menu.pos.x + offset.x;
		this->pos.y = Menu.pos.y + offset.y;

		// get clicked and changing value
		if (Menu.GetCurret_Tab() == Tab)
		{
			if (this->GetClicked())
			{
				Dont_Click = true;
				POINT Mouse;
				POINT mp; GetCursorPos(&mp);
				ScreenToClient(GetForegroundWindow(), &mp);
				Mouse.x = mp.x; Mouse.y = mp.y;
				// get differance
				double idifference;
				idifference = Mouse.x - this->pos.x;
				// Set Value
				int value = ((idifference / 100)*(this->Max - this->Min));
				if (value < Min)
				{
					value = Min;
				}
				else if (value > Max)
				{
					value = Max;
				}

				Settings.SetSetting(Tab, Setting, value);
			}
		}
	}

};

class CDropBox
{
private:
	int Tab = 0;
	int Setting = 0;

	char* Name = "ERROR";
	char* Parts[20];
	int Amount = 0;

	bool Dropping = false;

	MenuPOS pos;
	MenuPOS offset;
	int Sub = 0;
	bool GetClicked()
	{

		if (!Clicked_This_Frame)
		{
			return false;
		}
		if (Holding_Mouse_1)
		{
			return false;
		}
		if (Dont_Click)
		{
			return false;
		}
		POINT Mouse;
		POINT mp; GetCursorPos(&mp);
		ScreenToClient(GetForegroundWindow(), &mp);
		Mouse.x = mp.x; Mouse.y = mp.y;

		if (Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 100 && Mouse.y < this->pos.y + 20)
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	int GetPartClicked()
	{
		if (!Clicked_This_Frame)
		{
			return -1;
		}
		if (Holding_Mouse_1)
		{
			return -1;
		}
		if (Dont_Click)
		{
			return -1;
		}

		POINT Mouse;
		POINT mp;
		GetCursorPos(&mp);
		ScreenToClient(GetForegroundWindow(), &mp);
		Mouse.x = mp.x;
		Mouse.y = mp.y;

		for (int i = 1; i < this->Amount; i++)
		{
			if (Mouse.x > this->pos.x && Mouse.y > this->pos.y + (20 * (i)) && Mouse.x < this->pos.x + 100 && Mouse.y < this->pos.y + (20 * (i + 1)))
			{
				return i;
			}
		}
		return -1;

	}

public:
	void Update()
	{
		pos.x = Menu.pos.x + offset.x;
		pos.y = Menu.pos.y + offset.y;

		if (Tab == Menu.GetCurret_Tab())
		{
			if (Menu.GetCurret_SubTab() == Sub || Sub == -1) {

				if (this->GetClicked())
				{
					if (this->Dropping == true)
					{
						this->Dropping = false;
					}
					else
					{
						this->Dropping = true;
					}
					Dont_Click = true;
				}
				else if (this->Dropping)
				{
					int index = this->GetPartClicked();
					if (index != -1)
					{
						Settings.SetSetting(this->Tab, this->Setting, index);
						this->Dropping = false;
						Dont_Click = true;
					}
					else if (Clicked_This_Frame && !Holding_Mouse_1)
					{
						Dropping = false;
					}
				}
			}
			else
			{
				Dropping = false;
			}

		}
		else
		{
			Dropping = false;
		}

	}
	void Draw()
	{
		if (Tab == Menu.GetCurret_Tab())
		{
			if (Menu.GetCurret_SubTab() == Sub || Sub == -1) {

				Interfaces.pSurface->DrawSetColor(39, 42, 47, 255);
				Interfaces.pSurface->DrawFilledRect(this->pos.x, this->pos.y, this->pos.x + 100, this->pos.y + 21);
				Interfaces.pSurface->DrawSetColor(25, 25, 25, 255);
				Interfaces.pSurface->DrawOutlinedRect(this->pos.x, this->pos.y, this->pos.x + 100, this->pos.y + 21);
				Interfaces.pSurface->DrawT(this->pos.x, this->pos.y - 13, CColor(255, 255, 255, 255), Hacks.Font_Tahoma, false, this->Name);

				if (this->Dropping)
				{
					for (int i = 1; i < this->Amount; i++)
					{
						Interfaces.pSurface->DrawSetColor(35, 38, 42, 255); //dark top color
						Interfaces.pSurface->DrawFilledRect(this->pos.x, this->pos.y + (20 * i), this->pos.x + 100, this->pos.y + (20 * i) + 21);
						Interfaces.pSurface->DrawSetColor(25, 25, 25, 255);
						Interfaces.pSurface->DrawOutlinedRect(this->pos.x, this->pos.y + (20 * i), this->pos.x + 100, this->pos.y + (20 * i) + 21);
						Interfaces.pSurface->DrawT(this->pos.x + 8, this->pos.y + 4 + (20 * i), CColor(255, 255, 255, 255), Hacks.Font_Tahoma, false, this->Parts[i]);
					}
				}
				else
				{
					int value = (int)Settings.GetMenuSetting(Tab, Setting);
					if (value >= this->Amount)
						value = 0;
					Interfaces.pSurface->DrawT(this->pos.x + 8, this->pos.y + 4, CColor(255, 255, 255, 255), Hacks.Font_Tahoma, false, this->Parts[value]);

					static int Texture = Interfaces.pSurface->CreateNewTextureID(true); //need to make a texture with procedural true
					unsigned char buffer[4] = { 39, 42, 47, 255 };//{ color.r(), color.g(), color.b(), color.a() };

					Interfaces.pSurface->DrawSetTextureRGBA(Texture, buffer, 1, 1); //Texture, char array of texture, width, height
					Interfaces.pSurface->DrawSetColor(35, 35, 36, 255); // keep this full color and opacity use the RGBA @top to set values.
					Interfaces.pSurface->DrawSetTexture(Texture); // bind texture

					Vertex_t Verts2[3];
					Verts2[0].x = this->pos.x + 85;
					Verts2[0].y = this->pos.y + 6;
					Verts2[1].x = this->pos.x + 95;
					Verts2[1].y = this->pos.y + 6;
					Verts2[2].x = this->pos.x + 90;
					Verts2[2].y = this->pos.y + 14;

					Interfaces.pSurface->DrawTexturedPolygon(3, Verts2);

				}
			}
		}
	}
	void Init(int x, int y, int tab, int setting, char* name, int parts, std::vector<char*> arr, int sub)
	{
		Name = name;
		Amount = parts;

		for (int i = 0; i < parts; i++)
		{
			Parts[i] = arr[i];
		}

		Tab = tab;
		Setting = setting;
		offset.x = x;
		offset.y = y;
		Sub = sub;
	}
};

class CKeyButton
{
private:
	MenuPOS pos;
	MenuPOS offset;

	int Tab;
	int Setting;
	bool Getting_New_Key;
	char* Name = "ERROR";
	int Sub = 0;
	bool GetClicked()
	{
		if (!Clicked_This_Frame)
		{
			return false;
		}
		if (Holding_Mouse_1)
		{
			return false;
		}
		if (Dont_Click)
		{
			return false;
		}

		POINT Mouse;
		POINT mp; GetCursorPos(&mp);
		ScreenToClient(GetForegroundWindow(), &mp);
		Mouse.x = mp.x; Mouse.y = mp.y;

		if (Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 80 && Mouse.y < this->pos.y + 20)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

public:
	void Draw()
	{
		if (Menu.GetCurret_Tab() == Tab)
		{
			if (Menu.GetCurret_SubTab() == Sub || Sub == -1) {

				//Interfaces.pSurface->DrawT(this->pos.x, this->pos.y - 12, CColor(255, 255, 255, 255), Hacks.Font_Tahoma, false, "%s", this->Name);
				Interfaces.pSurface->DrawSetColor(39, 42, 47, 255);
				Interfaces.pSurface->DrawFilledRect(this->pos.x, this->pos.y, this->pos.x + 80, this->pos.y + 20);
				Interfaces.pSurface->DrawSetColor(25, 25, 25, 255);
				Interfaces.pSurface->DrawOutlinedRect(this->pos.x, this->pos.y, this->pos.x + 80, this->pos.y + 20);

				if (this->Getting_New_Key)
				{
					Interfaces.pSurface->DrawT(this->pos.x + 40, this->pos.y + 3, CColor(255, 255, 255, 255), Hacks.Font_Tahoma, true, "<PRESS>");
				}
				else
				{
					if (Settings.GetMenuSetting(this->Tab, this->Setting) == -1)
						Interfaces.pSurface->DrawT(this->pos.x + 40, this->pos.y + 3, CColor(255, 255, 255, 255), Hacks.Font_Tahoma, true, "<UNSET>");
					else
					{
						char* NameOfKey = KeyStrings[(int)Settings.GetMenuSetting(this->Tab, this->Setting)];
						Interfaces.pSurface->DrawT(this->pos.x + 40, this->pos.y + 3, CColor(255, 255, 255, 255), Hacks.Font_Tahoma, true, NameOfKey);
					}
				}
			}
		}
	}
	void Update()
	{
		pos.x = Menu.pos.x + offset.x;
		pos.y = Menu.pos.y + offset.y;

		if (Menu.GetCurret_Tab() == Tab)
		{
			if (Menu.GetCurret_SubTab() == Sub || Sub == -1) {

				if (Getting_New_Key)
				{
					for (int i = 0; i < 255; i++)
					{
						if (GetKeyPress(i))
						{
							if (i == VK_BACK)
							{
								this->Getting_New_Key = false;
								Settings.SetSetting(Tab, Setting, -1);
								break;
							}

							Settings.SetSetting(Tab, Setting, i);
							this->Getting_New_Key = false;
							break;
						}
					}
				}
				else if (this->GetClicked())
				{

					this->Getting_New_Key = !this->Getting_New_Key;

				}
			}
		}

	}
	void Init(int x, int y, int tab, int setting, char* name, int sub)
	{
		offset.x = x;
		offset.y = y;
		Tab = tab;
		Setting = setting;
		Name = name;
		Sub = sub;
		Settings.SetSetting(Tab, Setting, -1);
	}

};

class CTab
{

public:
	void Update()
	{
		pos.x = Menu.pos.x + ((800 / Tab_Count) * Tab);
		pos.y = Menu.pos.y + 0;

		if (GetClicked())
		{
			Dont_Click = true;
			Menu.Set_Current_Tab(Tab);
		}
	}
	void Draw()
	{
		Interfaces.pSurface->DrawSetColor(39, 42, 47, 255);
		Interfaces.pSurface->DrawFilledRect(pos.x, pos.y, pos.x + (800 / Tab_Count), pos.y + 40);
		if (Menu.GetCurret_Tab() == Tab)
		{
			Interfaces.pSurface->DrawSetColor(35, 38, 42, 255);
			Interfaces.pSurface->DrawFilledRect(pos.x, pos.y, pos.x + (800 / Tab_Count), pos.y + 40);
			Interfaces.pSurface->DrawT(pos.x + ((800 / Tab_Count) / 2), pos.y + 10, CColor(255, 255, 255, 255), Hacks.Font_Tab, true, Name);
		}
		else
		{
			Interfaces.pSurface->DrawSetColor(39, 42, 47, 255);
			Interfaces.pSurface->DrawFilledRect(pos.x, pos.y, pos.x + (800 / Tab_Count), pos.y + 40);
			Interfaces.pSurface->DrawT(pos.x + ((800 / Tab_Count) / 2), pos.y + 10, CColor(255, 255, 255, 255), Hacks.Font_Tab, true, Name);
		}
		//lines test
		//Interfaces.pSurface->DrawLine(pos.x + 1, pos.y, pos.x + (800 / Tab_Count) + 1, pos.y);
		//Interfaces.pSurface->DrawLine(pos.x + 1, pos.y + 30, pos.x + (800 / Tab_Count) + 1, pos.y + 30);
		//Interfaces.pSurface->DrawLine(pos.x + 1, pos.y, pos.x + 1, pos.y + 30);
		Interfaces.pSurface->DrawSetColor(25, 25, 25, 255);
		//Interfaces.pSurface->DrawLine(Menu.pos.x + 1, Menu.pos.y + 30, Menu.pos.x + 801, Menu.pos.y + 60);
		//meme lines here work here
		//Interfaces.pSurface->DrawLine(Menu.pos.x + 802, Menu.pos.y + 30, Menu.pos.x + 802, Menu.pos.y + 396);
		//Interfaces.pSurface->DrawLine(Menu.pos.x + 2, Menu.pos.y + 60, Menu.pos.x + 2, Menu.pos.y + 396);
		//Interfaces.pSurface->DrawLine(Menu.pos.x + 2, Menu.pos.y + 396, Menu.pos.x + 802, Menu.pos.y + 396);
		//border lines here

		//end lines
	}
	void Init(char* name, int tab)
	{
		Name = name;
		Tab = tab;
	}
private:
	int Tab;
	MenuPOS pos;
	char* Name = "ERROR";
	bool GetClicked()
	{
		if (!Clicked_This_Frame)
		{
			return false;
		}
		if (Holding_Mouse_1)
		{
			return false;
		}

		POINT Mouse;
		POINT mp; GetCursorPos(&mp);
		ScreenToClient(GetForegroundWindow(), &mp);
		Mouse.x = mp.x; Mouse.y = mp.y;


		if (Mouse.x > pos.x && Mouse.y > pos.y && Mouse.x < pos.x + ((800 / Tab_Count)) && Mouse.y < pos.y + 30)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
class CSubTab
{

public:
	void Update()
	{
		int SubTab_Count = SubTab_Legit_Count;
		if (Menu.GetCurret_Tab() == Tab_Misc)
			SubTab_Count = SubTab_Misc_Count;
		int tab = Tab;
		if (Tab > 2)
			tab = Tab - 3;

		pos.x = Menu.pos.x + ((800 / SubTab_Count) * tab);
		pos.y = Menu.pos.y;
		if (Menu.GetCurret_Tab() == ParentTab) {

			if (GetClicked())
			{
				Dont_Click = true;
				Menu.Set_Current_SubTab(Tab);
			}
		}
	}
	void Draw()
	{
		if (Menu.GetCurret_Tab() == ParentTab) {
			Interfaces.pSurface->DrawSetColor(39, 42, 47, 255);
			int SubTab_Count = SubTab_Legit_Count;
			if (Menu.GetCurret_Tab() == Tab_Misc)
				SubTab_Count = SubTab_Misc_Count;

			Interfaces.pSurface->DrawFilledRect(pos.x, pos.y + 41, pos.x + (800 / SubTab_Count), pos.y + 71);
			if (Menu.GetCurret_SubTab() == Tab)
			{
				Interfaces.pSurface->DrawSetColor(35, 38, 42, 255);
				Interfaces.pSurface->DrawFilledRect(pos.x + 1, pos.y + 41, pos.x + (800 / SubTab_Count), pos.y + 71);
				Interfaces.pSurface->DrawT(pos.x + ((800 / SubTab_Count / 2)), pos.y + 49, CColor(255, 255, 255, 255), Hacks.Font_Tab, true, Name);

			}
			else {
				Interfaces.pSurface->DrawT(pos.x + ((800 / SubTab_Count / 2)), pos.y + 49, CColor(255, 255, 255, 255), Hacks.Font_Tab, true, Name);
			}
			Interfaces.pSurface->DrawSetColor(25, 25, 25, 255);
			Interfaces.pSurface->DrawLine(Menu.pos.x, Menu.pos.y + 72, Menu.pos.x + 800, Menu.pos.y + 72);
			//end lines
		}
	}
	void InitSub(char* name, int tab, int SubTab)
	{
		Name = name;
		Tab = SubTab;
		ParentTab = tab;
	}
private:
	int Tab;
	int ParentTab;
	MenuPOS pos;
	char* Name = "ERROR";
	bool GetClicked()
	{
		if (!Clicked_This_Frame)
		{
			return false;
		}
		if (Holding_Mouse_1)
		{
			return false;
		}

		POINT Mouse;
		POINT mp; GetCursorPos(&mp);
		ScreenToClient(GetForegroundWindow(), &mp);
		Mouse.x = mp.x; Mouse.y = mp.y;

		int SubTab_Count = SubTab_Legit_Count;
		if (Menu.GetCurret_Tab() == Tab_Misc)
			SubTab_Count = SubTab_Misc_Count;

		if (Mouse.x > pos.x && Mouse.y > pos.y + 41 && Mouse.x < pos.x + ((800 / SubTab_Count)) && Mouse.y < pos.y + 71)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

class CMenuBox
{
public:
	void Init(char* name, int x, int y, int w, int h, int tab, int sub)
	{

		Name = name;
		offset.x = x;
		offset.y = y;
		size.x = w;
		size.y = h;
		Tab = tab;
		SubTab = sub;
	}
	void Update()
	{
		pos.x = Menu.pos.x + offset.x;
		pos.y = Menu.pos.y + offset.y;

	}
	void Draw()
	{
		if (Tab == Menu.GetCurret_Tab())
		{
			if (SubTab == Menu.GetCurret_SubTab() || SubTab == -1) {
				int Width = 0, Height = 0;
				char Buffer[2048] = { '\0' };
				va_list Args;
				va_start(Args, Name);
				vsprintf_s(Buffer, Name, Args);
				va_end(Args);
				size_t Size = strlen(Buffer);
				/* set up size.xidebuffer*/
				wchar_t* wBuffer = new wchar_t[Size];
				/* char -> size.xchar */
				mbstowcs_s(0, wBuffer, Size, Buffer, Size - 1);
				/* check center */
				Interfaces.pSurface->GetTextSize(Hacks.Font_Tahoma, wBuffer, Width, Height);
				Interfaces.pSurface->DrawSetColor(20, 20, 20, 255);
				Interfaces.pSurface->DrawLine(pos.x, pos.y, pos.x, pos.y + size.y);
				Interfaces.pSurface->DrawLine(pos.x, pos.y + size.y, pos.x + size.x, pos.y + size.y);
				Interfaces.pSurface->DrawLine(pos.x + size.x, pos.y, pos.x + size.x, pos.y + size.y);
				Interfaces.pSurface->DrawLine(pos.x, pos.y, pos.x + 8, pos.y);
				Interfaces.pSurface->DrawLine(pos.x + (Width)+12, pos.y, pos.x + size.x, pos.y);
				Interfaces.pSurface->DrawSetColor(50, 50, 50, 255);
				Interfaces.pSurface->DrawLine(pos.x + 1, pos.y + 1, pos.x + 1, pos.y + size.y - 1);
				Interfaces.pSurface->DrawLine(pos.x + 1, pos.y + size.y - 1, pos.x + size.x - 1, pos.y + size.y - 1);
				Interfaces.pSurface->DrawLine(pos.x + size.x - 1, pos.y + 1, pos.x + size.x - 1, pos.y + size.y - 1);
				Interfaces.pSurface->DrawLine(pos.x + 1, pos.y + 1, pos.x + 7, pos.y + 1);
				Interfaces.pSurface->DrawLine(pos.x + (Width)+18, pos.y + 1, pos.x + size.x, pos.y + 1);
				Interfaces.pSurface->DrawT(pos.x + 10, pos.y - 7, CColor(255, 255, 255, 255), Hacks.Font_Tahoma, false, Name);

			}
		}
	}


private:
	MenuPOS pos;
	MenuPOS offset;
	MenuPOS size;
	char* Name = "ERROR";
	int Tab;
	int SubTab = 0;
};


class CFunctionButton
{
public:
	void Update()
	{
		this->pos.x = Menu.pos.x + this->offset.x;
		this->pos.y = Menu.pos.y + this->offset.y;

		if (Menu.GetCurret_Tab() == Tab)
		{
			if (this->GetClicked())
			{
				DWORD disfunc = Function;
				__asm
				{
					CALL disfunc
				}
			}
		}
	}
	void Draw()
	{
		if (Menu.GetCurret_Tab() == Tab)
		{

			Interfaces.pSurface->DrawSetColor(39, 42, 47, 255);
			Interfaces.pSurface->DrawFilledRect(this->pos.x, this->pos.y, this->pos.x + 100, this->pos.y + 20);
			Interfaces.pSurface->DrawSetColor(25, 25, 25, 255);
			Interfaces.pSurface->DrawOutlinedRect(this->pos.x, this->pos.y, this->pos.x + 100, this->pos.y + 20);
			Interfaces.pSurface->DrawT(this->pos.x + 50, this->pos.y + 3, CColor(255, 255, 255, 255), Hacks.Font_Tahoma, true, Name);

		}
	}
	void Init(int x, int y, DWORD function, char* name, int tab)
	{
		Function = function;
		Name = name;
		offset.x = x;
		offset.y = y;
		Tab = tab;
	}
	bool GetClicked()
	{
		if (!Clicked_This_Frame)
		{
			return false;
		}
		if (Holding_Mouse_1)
		{
			return false;
		}
		if (Dont_Click)
		{
			return false;
		}

		POINT Mouse;
		POINT mp; GetCursorPos(&mp);
		ScreenToClient(GetForegroundWindow(), &mp);
		Mouse.x = mp.x; Mouse.y = mp.y;

		if (Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 100 && Mouse.y < this->pos.y + 20)
		{
			return true;
		}

		return false;
	}

private:
	DWORD Function;
	char* Name = "WOAH, NO NAME BRO";
	MenuPOS pos;
	MenuPOS offset;
	int Tab = -1;
};

std::vector<CSlider> Sliders;
std::vector<CIntSlider> IntSliders;
std::vector<CButton> Buttons;
std::vector<CDropBox> Dropboxes;
std::vector<CKeyButton> KeyButtons;
std::vector<CMenuBox> MenuBoxs;
std::vector<CTab> Tabs;
std::vector<CSubTab> SubTabs;

std::vector<CFunctionButton> FuncButtons;

int Dropboxs_Amount = 0;

void AddNewButton(int Tab, int Setting, bool defult, int x, int y, char* name)
{
	CButton Filler;
	Filler.Init(Tab, Setting, defult, x, y, name, -1);
	Buttons.push_back(Filler);

}
void AddNewSubButton(int Tab, int Setting, bool defult, int x, int y, char* name, int sub)
{
	CButton Filler;
	Filler.Init(Tab, Setting, defult, x, y, name, sub);
	Buttons.push_back(Filler);

}

void AddNewSlider(int x, int y, double min, double max, double defult, char* name, int tab, int setting)
{
	CSlider Slid;
	Slid.Init(x, y, min, max, defult, name, tab, setting, -1);
	Sliders.push_back(Slid);
}
void AddNewSubSlider(int x, int y, double min, double max, double defult, char* name, int tab, int setting, int sub)
{
	CSlider Slid;
	Slid.Init(x, y, min, max, defult, name, tab, setting, sub);
	Sliders.push_back(Slid);
}

void AddNewIntSlider(int x, int y, double min, double max, double defult, char* name, int tab, int setting)
{
	CIntSlider Slid;
	Slid.Init(x, y, min, max, defult, name, tab, setting);
	IntSliders.push_back(Slid);
}
void AddNewSubDropbox(int x, int y, int tab, int setting, char* name, int parts, std::vector<char*> arr, int sub)
{
	CDropBox Dropper;
	Dropper.Init(x, y, tab, setting, name, parts, arr, sub);
	Dropboxes.push_back(Dropper);
	Dropboxs_Amount++;
}

void AddNewDropbox(int x, int y, int tab, int setting, char* name, int parts, std::vector<char*> arr)
{
	CDropBox Dropper;
	Dropper.Init(x, y, tab, setting, name, parts, arr, -1);
	Dropboxes.push_back(Dropper);//
	Dropboxs_Amount++;
}
void AddNewKeyButton(int x, int y, int tab, int setting, char* name)
{
	CKeyButton KeyButton;
	KeyButton.Init(x, y, tab, setting, name, -1);
	KeyButtons.push_back(KeyButton);
}
void AddNewSubKeyButton(int x, int y, int tab, int setting, char* name, int Sub)
{
	CKeyButton KeyButton;
	KeyButton.Init(x, y, tab, setting, name, Sub);
	KeyButtons.push_back(KeyButton);
}

void AddNewTab(char* Name, int Tab)
{
	CTab Filler;
	Filler.Init(Name, Tab);
	Tabs.push_back(Filler);
	Tab_Count++;
}
void AddNewSubTab(char* Name, int Tab, int SubTab)
{
	CSubTab Fillerr;
	Fillerr.InitSub(Name, Tab, SubTab);
	SubTabs.push_back(Fillerr);
	if (Tab == Tab_LegitBot)
		SubTab_Legit_Count++;
	else if (Tab == Tab_Misc) {
		SubTab_Misc2_Count++;
	}
	else
		SubTab_Misc_Count++;

}

void AddNewMenuBox(char* name, int x, int y, int w, int h, int tab)
{
	CMenuBox Filler;
	Filler.Init(name, x, y, w, h, tab, -1);
	MenuBoxs.push_back(Filler);
}
void AddNewSubMenuBox(char* name, int x, int y, int w, int h, int tab, int sub)
{
	CMenuBox Filler;
	Filler.Init(name, x, y, w, h, tab, sub);
	MenuBoxs.push_back(Filler);
}

void AddNewFuncButton(int x, int y, DWORD function, char* name, int tab)
{

	CFunctionButton Filler;
	Filler.Init(x, y, function, name, tab);
	FuncButtons.push_back(Filler);

}
extern player_info_t* Info;
std::vector<char*> ingameNames{ "NONE", "DEAGLE", "DUALBERETTAS", "FIVESEVEN", "GLOCK", "AK47", "AUG", "AWP", "FAMAS", "G3SG1",
"GALILAR", "M249",  "M4A4", "MAC10",  "P90", "UMP45", "XM1014", "PPBIZON", "MAG7", "NEGEV", "SAWEDOFF", "TEC9",
"P2000", "MP7", "MP9", "NOVA", "P250",  "SCAR20", "SG553", "SSG08",  "CTKnife", "TKnife", "M4A1S", "USPS",  "CZ75AUTO", "R8Revolver" };
int page[10];
int selected[10];
int realselected[10];
void drawselectbox(int amount, char* arr[100], int width, int height, int setting, int realvals[100]) {
	int startx = Menu.pos.x + width + 3;
	int starty = Menu.pos.y + height + 3;
	Interfaces.pSurface->DrawSetColor(20, 200, 255, 255);
	Interfaces.pSurface->DrawOutlinedRect(startx - 2, starty - 2, startx + 137, starty + 202);

	for (int i = 0; i < 10; i++) {
		int number = i + 10 * page[setting];
		if (number > amount) {

		}
		else {
			Interfaces.pSurface->DrawSetColor(20, 200, 255, 255);
			Interfaces.pSurface->DrawFilledRect(startx, starty + i * 20, startx + 120, starty + i * 20 + 20);
			Interfaces.pSurface->DrawSetColor(30, 30, 30, 255);
			Interfaces.pSurface->DrawFilledRect(startx + 1, starty + i * 20 + 1, startx + 119, starty + i * 20 + 19);
			if (number == selected[setting]) {
				Interfaces.pSurface->DrawT(startx + 3, starty + i * 20 + 3, CColor(20, 200, 255, 255), Hacks.Font_Tahoma, false, arr[number]);
				realselected[setting] = realvals[number];
			}
			else
				Interfaces.pSurface->DrawT(startx + 3, starty + i * 20 + 3, CColor(255, 255, 255, 255), Hacks.Font_Tahoma, false, arr[number]);

		}
	}
	double drawbarheight = (10 * 200);
	drawbarheight /= amount;
	if (drawbarheight > 200)
		drawbarheight = 200;
	Interfaces.pSurface->DrawSetColor(20, 200, 255, 255);
	Interfaces.pSurface->DrawOutlinedRect(startx + 125, starty, startx + 135, starty + 200);
	Interfaces.pSurface->DrawSetColor(200, 200, 255, 255);
	Interfaces.pSurface->DrawFilledRect(startx + 127, starty + page[setting] * drawbarheight, startx + 133, starty + drawbarheight + page[setting] * drawbarheight);
	// scroll
	if (Clicked_This_Frame) {
		if (!Holding_Mouse_1) {
			if (!Dont_Click) {
				POINT Mouse;
				POINT mp; GetCursorPos(&mp);
				ScreenToClient(GetForegroundWindow(), &mp);
				Mouse.x = mp.x; Mouse.y = mp.y;
				if (Mouse.x > startx + 125 && Mouse.y > starty && Mouse.x < startx + 135 && Mouse.y < starty + 200)
				{
					int percentage = (Mouse.y - starty);
					for (int i = 0; i < 10; i++) {
						if (drawbarheight* i < percentage && percentage < drawbarheight* (i + 1)) {
							page[setting] = i;
						}
					}
				}

			}
		}
	}
	// getting clicked
	if (Clicked_This_Frame) {
		if (!Holding_Mouse_1) {
			if (!Dont_Click) {
				POINT Mouse;
				POINT mp; GetCursorPos(&mp);
				ScreenToClient(GetForegroundWindow(), &mp);
				Mouse.x = mp.x; Mouse.y = mp.y;
				if (Mouse.x > startx && Mouse.y > starty && Mouse.x < startx + 120 && Mouse.y < starty + 200)
				{
					int percentage = (Mouse.y - starty);
					for (int i = 0; i < 10; i++) {
						if (20 * i < percentage && percentage < 20 * (i + 1)) {
							int number = i + 10 * page[setting];
							selected[setting] = number;
						}
					}
				}

			}
		}
	}


}
int skin_wpns = 0;
int skin_skins = 1;
void skinchanger() {

}
void SetupMenu()
{

	char* arr[20] = { "ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR" };

	AddNewTab("RAGE", Tab_Ragebot);
	AddNewTab("LEGIT", Tab_LegitBot);
	AddNewTab("VISUALS", Tab_Visuals);
	AddNewTab("MISC", Tab_Misc);
	AddNewTab("CONFIG", Tab_Config);
	AddNewTab("PLAYERS", Tab_Plist);
	AddNewTab("COLORS", Tab_Other);




	/* LEGITBOT */
	AddNewSubTab("AIMBOT", Tab_LegitBot, Sub_Aimbot);
	AddNewSubTab("TRIGGERBOT", Tab_LegitBot, Sub_Trigger);

	AddNewSubButton(Tab_LegitBot, Legit_Activate, false, 10, 380, "Active", Sub_Aimbot);
	AddNewSubKeyButton(140, 375, Tab_LegitBot, Legit_Aimbot_Key, "Aim Key", Sub_Aimbot);
	AddNewSubButton(Tab_LegitBot, Legit_ME, true, 270, 380, "ME Aimbot", Sub_Aimbot);

	AddNewSubMenuBox("Aimbot", 10, 80, 120, 280, Tab_LegitBot, Sub_Aimbot);
	{
		AddNewSubButton(Tab_LegitBot, Legit_Normal_Active, false, 20, 90, "Active", Sub_Aimbot);
		AddNewSubSlider(20, 130, 0, 10, 4, "FOV", Tab_LegitBot, Legit_Normal_FOV, Sub_Aimbot);
		std::vector<char*> aimbone = { "Head", "Head", "Neck", "Chest", "Stomach" };
		AddNewSubDropbox(20, 170, Tab_LegitBot, Legit_Normal_SelectionBone, "Aimbone", 5, aimbone, Sub_Aimbot);
		std::vector<char*> aimSelection = { "Priority Only", "Priority Only", "Dynamic", "Nearest", "Random" };
		AddNewSubDropbox(20, 210, Tab_LegitBot, Legit_Normal_SelectionType, "Selection", 5, aimSelection, Sub_Aimbot);
		AddNewSubSlider(20, 250, 0, 20, 4, "Smooth", Tab_LegitBot, Legit_Normal_Speed, Sub_Aimbot);
		AddNewSubSlider(20, 290, 0.1, 20, 4, "Time", Tab_LegitBot, Legit_Normal_AimTime, Sub_Aimbot);
		AddNewSubSlider(20, 330, 0, 20, 4, "Curve", Tab_LegitBot, Legit_Normal_Curve, Sub_Aimbot);

	}
	AddNewSubMenuBox("One Taps", 140, 80, 120, 280, Tab_LegitBot, Sub_Aimbot);
	{
		AddNewSubButton(Tab_LegitBot, Legit_SA_Amount, false, 150, 90, "Active", Sub_Aimbot);
		AddNewSubSlider(150, 120, 0, 10, 4, "FOV", Tab_LegitBot, Legit_SA_FOV, Sub_Aimbot);
		std::vector<char*> aimbone = { "Head", "Head", "Neck", "Chest", "Stomach" };
		AddNewSubDropbox(150, 160, Tab_LegitBot, Legit_SA_SelectionBone, "Aimbone", 5, aimbone, Sub_Aimbot);
		std::vector<char*> aimSelection = { "Priority Only", "Priority Only", "Dynamic", "Nearest", "Random" };
		AddNewSubDropbox(150, 200, Tab_LegitBot, Legit_SA_SelectionType, "Selection", 5, aimSelection, Sub_Aimbot);
		AddNewSubSlider(150, 240, 0, 20, 4, "Smooth", Tab_LegitBot, Legit_SA_Speed, Sub_Aimbot);
		AddNewSubSlider(150, 280, 0.1, 20, 4, "Time", Tab_LegitBot, Legit_SA_AimTime, Sub_Aimbot);
		AddNewSubSlider(150, 320, 0, 20, 4, "Curve", Tab_LegitBot, Legit_SA_Curve, Sub_Aimbot);

	}
	AddNewSubMenuBox("Slow Aim", 270, 80, 120, 280, Tab_LegitBot, Sub_Aimbot);
	{
		AddNewSubButton(Tab_LegitBot, Legit_SlowAim_Active, false, 280, 90, "Active", Sub_Aimbot);
		AddNewSubSlider(280, 130, 0, 10, 4, "FOV", Tab_LegitBot, Legit_SlowAim_FOV, Sub_Aimbot);
		AddNewSubSlider(280, 170, 0, 100, 25, "Amount", Tab_LegitBot, Legit_SlowAim_Amount, Sub_Aimbot);
		std::vector<char*> SlowAim = { "Normal", "Normal", "Dynamic" };
		AddNewSubDropbox(280, 210, Tab_LegitBot, Legit_SlowAim_Type, "Selection", 3, SlowAim, Sub_Aimbot);
		std::vector<char*> SlowAimSelect{ "Heady Only", "Heady Only", "All" };
		AddNewSubDropbox(280, 250, Tab_LegitBot, Legit_SlowAim_Bone, "Bones", 3, SlowAimSelect, Sub_Aimbot);
	}
	AddNewSubMenuBox("Rcs", 400, 80, 120, 280, Tab_LegitBot, Sub_Aimbot);
	{

		AddNewSubButton(Tab_LegitBot, Legit_RCS_Enable, false, 410, 90, "Active", Sub_Aimbot);
		std::vector<char*> rcstype = { "Aim", "Aim", "Standalone", "Aim+" };
		AddNewSubDropbox(410, 130, Tab_LegitBot, Legit_RCS_Type, "Type", 4, rcstype, Sub_Aimbot);
		AddNewSubSlider(410, 170, 0, 2, 2, "RCS X", Tab_LegitBot, Legit_RCS_X, Sub_Aimbot);
		AddNewSubSlider(410, 210, 0, 2, 2, "RCS Y", Tab_LegitBot, Legit_RCS_Y, Sub_Aimbot);
		AddNewSubSlider(410, 250, 0, 20, 0, "RCS Smooth", Tab_LegitBot, Legit_RCS_Smooth, Sub_Aimbot);

	}
	AddNewSubMenuBox("Global", 530, 80, 120, 280, Tab_LegitBot, Sub_Aimbot);
	{
		AddNewSubSlider(540, 100, 0, 20, 0, "Randomise", Tab_LegitBot, Legit_Random, Sub_Aimbot);
		AddNewSubSlider(540, 130, 0, 64, 10, "Target Delay", Tab_LegitBot, Legit_TargetDelay, Sub_Aimbot);
		AddNewSubSlider(540, 160, 0, 100, 0, "NoHS Percent", Tab_LegitBot, Legit_HsPer, Sub_Aimbot);
		AddNewSubButton(Tab_LegitBot, Legit_IgnoreInAir, true, 540, 190, "Ignore In Air", Sub_Aimbot);
		//char *smoothing[10] = { "Smooth", "Smooth", "Speed" };
		//AddNewSubDropbox(540, 200, Tab_LegitBot, Legit_typeofaim, "Type", 3, smoothing, Sub_Aimbot);


	}

	AddNewSubButton(Tab_LegitBot, Trigger_Active, false, 10, 380, "Active", Sub_Trigger);

	AddNewSubMenuBox("Trigger", 10, 80, 120, 240, Tab_LegitBot, Sub_Trigger);
	{
		AddNewSubButton(Tab_LegitBot, Trigger_Type, true, 20, 90, "On Key", Sub_Trigger);
		AddNewSubKeyButton(20, 130, Tab_LegitBot, Trigger_Key, "Key", Sub_Trigger);
		std::vector<char*> Trigbone = { "All", "All", "Head", "No Legs" };
		AddNewSubDropbox(20, 170, Tab_LegitBot, Trigger_Hitboxs, "Selection", 4, Trigbone, Sub_Trigger);

		AddNewSubSlider(20, 210, 0, 30, 0, "Delay", Tab_LegitBot, Trigger_Delay, Sub_Trigger);
		AddNewSubSlider(20, 250, 0, 30, 0, "After", Tab_LegitBot, Trigger_After, Sub_Trigger);
		AddNewSubButton(Tab_LegitBot, Trigger_Check_Scope, true, 20, 290, "Check Scopped", Sub_Trigger);

	}
	AddNewSubMenuBox("Magnet", 140, 80, 120, 290, Tab_LegitBot, Sub_Trigger);
	{
		AddNewSubButton(Tab_LegitBot, Trigger_Magnet_Active, false, 150, 90, "Active", Sub_Trigger);
		AddNewSubSlider(150, 130, 0, 10, 4, "FOV", Tab_LegitBot, Trigger_Magnet_FOV, Sub_Trigger);
		std::vector<char*> aimbone = { "Head", "Head", "Neck", "Chest", "Stomach" };
		AddNewSubDropbox(150, 170, Tab_LegitBot, Trigger_Magnet_SelectionBone, "Aimbone", 5, aimbone, Sub_Trigger);
		std::vector<char*> aimSelection = { "Priority Only", "Priority Only", "Dynamic", "Nearest", "Random" };
		AddNewSubDropbox(150, 210, Tab_LegitBot, Trigger_Magnet_SelectionType, "Selection", 5, aimSelection, Sub_Trigger);
		AddNewSubSlider(150, 250, 0, 20, 4, "Smooth", Tab_LegitBot, Trigger_Magnet_Speed, Sub_Trigger);
		AddNewSubSlider(150, 290, 0.1, 20, 4, "Time", Tab_LegitBot, Trigger_Magnet_AimTime, Sub_Trigger);
		AddNewSubSlider(150, 330, 0, 20, 4, "Curve", Tab_LegitBot, Trigger_Magnet_Curve, Sub_Trigger);
	}
	AddNewSubMenuBox("Trigger Lock", 270, 80, 120, 290, Tab_LegitBot, Sub_Trigger);
	{
		std::vector<char*> triglocktype = { "Off", "Off", "Key", "Always" };
		AddNewSubDropbox(280, 100, Tab_LegitBot, Trigger_Lock_Active, "Trigger Lock", 4, triglocktype, Sub_Trigger);
		AddNewSubKeyButton(280, 140, Tab_LegitBot, Trigger_Lock_Key, "Key", Sub_Trigger);

		AddNewSubSlider(280, 180, 0, 20, 2, "Smooth", Tab_LegitBot, Trigger_Lock_Smooth, Sub_Trigger);
		AddNewSubSlider(280, 220, 1, 20, 4, "Strngth", Tab_LegitBot, Trigger_Lock_Strength, Sub_Trigger);
	}

	/* Old LEGITBOT
	AddNewSubMenuBox("Aimbot", 10, 80, 120, 200, Tab_LegitBot, Sub_OldLegit);
	{
	AddNewSubButton(Tab_LegitBot, Old_Legit_Active, false, 20, 90, "Active", Sub_OldLegit);
	AddNewSubSlider(20, 130, 0, 20, 4, "FOV", Tab_LegitBot, Old_Legit_LegitFOV, Sub_OldLegit);
	char *aimbone[10] = { "Head", "Head", "Neck", "Chest", "Stomach", "Nearest", "Random" };
	AddNewSubDropbox(20, 170, Tab_LegitBot, Old_Legit_AimBone, "Aimbone", 7, aimbone, Sub_OldLegit);
	AddNewSubSlider(20, 210, 0, 100, 4, "Speed", Tab_LegitBot, Old_Legit_LegitNormalAimSpeedX, Sub_OldLegit);
	AddNewSubSlider(20, 250, 0, 100, 4, "Speed", Tab_LegitBot, Old_Legit_LegitNormalAimSpeedY, Sub_OldLegit);

	}
	AddNewSubMenuBox("Smart Aim", 140, 80, 120, 200, Tab_LegitBot, Sub_OldLegit);
	{
	AddNewSubButton(Tab_LegitBot, Old_Legit_SAActive, false, 160, 90, "Active", Sub_OldLegit);
	AddNewSubSlider(150, 130, 0, 20, 4, "SA Bullets", Tab_LegitBot, Old_Legit_Saim, Sub_OldLegit);
	char *Saimbone[10] = { "Head", "Head", "Neck", "Chest", "Stomach", "Nearest", "Random" };
	AddNewSubDropbox(150, 170, Tab_LegitBot, Old_Legit_Sabone, "SA Bone", 7, Saimbone, Sub_OldLegit);
	AddNewSubSlider(150, 210, 0, 100, 4, "Speed", Tab_LegitBot, Old_Legit_SALegitNormalAimSpeedX, Sub_OldLegit);
	AddNewSubSlider(150, 250, 0, 100, 4, "Speed", Tab_LegitBot, Old_Legit_SALegitNormalAimSpeedY, Sub_OldLegit);

	}

	AddNewSubMenuBox("Global", 270, 80, 120, 310, Tab_LegitBot, Sub_OldLegit);
	{
	AddNewSubSlider(280, 100, 0, 20, 0, "Randomise", Tab_LegitBot, Old_Legit_Random, Sub_OldLegit);
	char *typeofaim[10] = { "Speed", "Speed", "Smooth" };
	AddNewSubDropbox(280, 140, Tab_LegitBot, Old_Legit_typeofaim, "Type", 3, typeofaim, Sub_OldLegit);
	AddNewSubSlider(280, 180, 1, 10, 1, "Pause", Tab_LegitBot, Old_Legit_AimPause, Sub_OldLegit);
	AddNewSubSlider(280, 220, 0, 64, 10, "Target Delay", Tab_LegitBot, Old_Legit_lastcount, Sub_OldLegit);
	AddNewSubSlider(280, 250, 0, 10, 0, "Curve", Tab_LegitBot, Old_Legit_Curve, Sub_OldLegit);
	AddNewSubSlider(280, 280, 0, 100, 0, "NoHS Percent", Tab_LegitBot, Old_Legit_HsPer, Sub_OldLegit);
	AddNewSubButton(Tab_LegitBot, Old_Legit_IgnoreInAir, true, 280, 310, "Ignore In Air", Sub_OldLegit);


	}

	AddNewSubMenuBox("Trigger", 400, 80, 120, 200, Tab_LegitBot, Sub_OldLegit);
	{
	AddNewSubButton(Tab_LegitBot, Old_Trigger_Type, true, 410, 90, "On Key", Sub_OldLegit);
	AddNewSubKeyButton(410, 130, Tab_LegitBot, Old_Trigger_Key, "Key", Sub_OldLegit);
	AddNewSubSlider(410, 170, 0, 30, 0, "Delay", Tab_LegitBot, Old_Trigger_Delay, Sub_OldLegit);
	AddNewSubSlider(410, 210, 0, 30, 0, "After", Tab_LegitBot, Old_Trigger_After, Sub_OldLegit);
	AddNewSubButton(Tab_LegitBot, Old_Trigger_Magnet, true, 410, 250, "Mag Active", Sub_OldLegit);

	}
	AddNewSubMenuBox("Magnet Trigger", 530, 80, 120, 200, Tab_LegitBot, Sub_OldLegit);
	{
	char *Trigbone[10] = { "Head", "Head", "Neck", "Chest", "Stomach", "Nearest", "Random" };
	AddNewSubDropbox(540, 100, Tab_LegitBot, Old_Trigger_AimBone, "Bone", 7, Trigbone, Sub_OldLegit);
	AddNewSubSlider(540, 140, 0, 10, 3, "Fov", Tab_LegitBot, Old_Trigger_Fov, Sub_OldLegit);
	AddNewSubSlider(540, 180, 0, 100, 3, "Speed", Tab_LegitBot, Old_Trigger_SpeedX, Sub_OldLegit);
	AddNewSubSlider(540, 220, 0, 100, 3, "Speed", Tab_LegitBot, Old_Trigger_SpeedY, Sub_OldLegit);
	AddNewSubButton(Tab_LegitBot, Old_Trigger_Instant, false, 540, 250, "Instant", Sub_OldLegit);
	}

	AddNewSubMenuBox("RCS", 10, 290, 250, 100, Tab_LegitBot, Sub_OldLegit);
	{
	AddNewSubButton(Tab_LegitBot, Old_Legit_RCS_Enable, true, 20, 300, "Active", Sub_OldLegit);
	char *rcstype[10] = { "Aim", "Aim", "Standalone", "+Aim" };
	AddNewSubDropbox(20, 340, Tab_LegitBot, Old_Legit_RCS_Type, "Type", 4, rcstype, Sub_OldLegit);
	AddNewSubSlider(130, 310, 0, 2, 2, "RCS X", Tab_LegitBot, Old_Legit_RCS_X, Sub_OldLegit);
	AddNewSubSlider(130, 350, 0, 2, 2, "RCS Y", Tab_LegitBot, Old_Legit_RCS_Y, Sub_OldLegit);
	}
	AddNewSubButton(Tab_LegitBot, Old_Legit_Activate, false, 400, 300, "Active Old", Sub_OldLegit);
	AddNewSubButton(Tab_LegitBot, Old_Trigger_Active, false, 400, 330, "Active Old Trig", Sub_OldLegit);
	AddNewSubButton(Tab_LegitBot, Old_Legit_Active, false, 400, 360, "Active Old Aimbot", Sub_OldLegit);
	*/


	/* Ragebot */
	AddNewButton(Tab_Ragebot, Ragebot_Enable, false, 25, 55, "Enable");
	AddNewButton(Tab_Ragebot, Ragebot_SaveFps, false, 80, 55, "Save FPS");
	//AddNewButton(Tab_Ragebot, Ragebot_NewAimbot, false, 110, 50, "New Aimbot");
	AddNewMenuBox("Aim", 20, 80, 130, 300, Tab_Ragebot);
	{
		AddNewButton(Tab_Ragebot, Ragebot_Aimbot, false, 25, 90, "Enable Aimbot");
		AddNewButton(Tab_Ragebot, Ragebot_Silent_Aim, false, 25, 110, "Silent");
		AddNewButton(Tab_Ragebot, Ragebot_pSilent, false, 25, 130, "Perfect Silent");
		AddNewButton(Tab_Ragebot, Ragebot_AutoShoot, false, 25, 150, "Auto Shoot");
		AddNewButton(Tab_Ragebot, Ragebot_NoRecoil, false, 25, 170, "No Recoil");
		AddNewButton(Tab_Ragebot, Ragebot_On_Key_Press, false, 25, 190, "On Key");
		AddNewKeyButton(35, 210, Tab_Ragebot, Rabebot_On_Key_Button, "Key");
		AddNewButton(Tab_Ragebot, Ragebot_AutoDuck, false, 25, 240, "Auto Duck");
		AddNewButton(Tab_Ragebot, Ragebot_Autoscope, false, 25, 260, "Auto Scope");
		AddNewSlider(25, 290, 0, 110, 0, "Minimum Damage", Tab_Ragebot, Ragebot_MinDam);
		AddNewSlider(25, 320, 0, 39.9, 0, "Aim Step", Tab_Ragebot, Ragebot_Speed_Limit_Amount);
		AddNewSlider(25, 350, 0, 100, 0, "Hit Chance", Tab_Ragebot, Ragebot_Hitchance_Amount);
	}

	AddNewMenuBox("AntiAim", 170, 80, 130, 300, Tab_Ragebot);
	{
		AddNewButton(Tab_Ragebot, AntiAim_Enable, false, 175, 90, "Enable");
		std::vector<char*> Antiaim_X = { "", "","Emotion", "Down", "Up", "Head Bang", "Fakedown", "Down Fake" };
		AddNewDropbox(175, 120, Tab_Ragebot, AntiAim_X, "Antiaim Pitch", 8, Antiaim_X);
		std::vector<char*> Antiaim_Y = { "", "","Back", "Right", "Left", "Forward","Spin", "Dynamic Real", "Inverse Switch", "Switch fake", "Switch Real" };
		AddNewDropbox(175, 160, Tab_Ragebot, AntiAim_Y, "Antiaim Yaw", 11, Antiaim_Y);
		AddNewDropbox(175, 200, Tab_Ragebot, AntiAim_FY, "Real Yaw", 11, Antiaim_Y);

		AddNewButton(Tab_Ragebot, AntiAim_LispAnglesX, false, 175, 240, "Lisp X");
		AddNewButton(Tab_Ragebot, AntiAim_LispAnglesY, false, 175, 270, "Lisp Y");

		std::vector<char*> AAtarge = { "Off", "Off","At Target" };
		AddNewDropbox(175, 310, Tab_Ragebot, AntiAim_AtTarget, "Yaw fix", 3, AAtarge);
		std::vector<char*> Fduck = { "Off", "Off","Fake Stand" };
		AddNewDropbox(175, 350, Tab_Ragebot, Ragebot_Duck, "Fake Duck", 3, Fduck);

	}

	AddNewMenuBox("Selection", 320, 80, 130, 300, Tab_Ragebot);
	{
		std::vector<char*> ragebox = { "Head", "Head", "Neck", "Chest", "Pelvis" };
		AddNewDropbox(325, 100, Tab_Ragebot, Ragebot_Bone, "HitBox", 5, ragebox);
		std::vector<char*> MultiBox = { "Off", "Off", "Normal", "Velocity" };
		AddNewDropbox(325, 140, Tab_Ragebot, Ragebot_Multibox, "MultiBox", 4, MultiBox);
		std::vector<char*> MultiBoxSpeed = { "Normal", "Normal", "Low", "Medium", "High" };
		AddNewDropbox(325, 180, Tab_Ragebot, Ragebot_MultiboxSpeed, "AimScan Speed", 5, MultiBoxSpeed);

		AddNewSlider(325, 220, 0, 100, 50, "Point Scale", Tab_Ragebot, Ragebot_PSX);
		std::vector<char*> Auto = { "Off", "Off", "+Multipoint", "Multipoint", };
		AddNewDropbox(325, 260, Tab_Ragebot, Ragebot_AutoPSX, "MultiPoint", 4, Auto);
		std::vector<char*> Selec = { "Fov", "Fov", "Distance" };
		AddNewDropbox(325, 300, Tab_Ragebot, Ragebot_Selection, "Selection", 3, Selec);
		AddNewSlider(325, 340, 0, 20, 0, "Smart Aim", Tab_Ragebot, Ragebot_SA);

	}

	AddNewMenuBox("Corrections", 470, 80, 130, 160, Tab_Ragebot);
	{
		AddNewButton(Tab_Ragebot, Ragebot_Resolver, false, 475, 90, "Enabled");
		std::vector<char*> ResolverX = { "Off", "Off","Auto", "Force Up", "Force Down" };
		AddNewDropbox(475, 120, Tab_Ragebot, Ragebot_ResolverX, "Force X", 5, ResolverX);
		std::vector<char*> ResolverY = { "Off", "Off", "Auto", "Inverse", "Right", "Left", "Aimware" };
		AddNewDropbox(475, 160, Tab_Ragebot, Ragebot_ResolverY, "Force Y", 7, ResolverY);
		std::vector<char*> Lispfix = { "Off", "Off", "Perfect" };
		AddNewDropbox(475, 200, Tab_Ragebot, Ragebot_LispFix, "Resolver", 3, Lispfix);
	}
	AddNewMenuBox("AntiAim Disables", 470, 260, 130, 120, Tab_Ragebot);
	{
		AddNewButton(Tab_Ragebot, Ragebot_AntiAimKnife, false, 475, 270, "Knife Out");
		AddNewButton(Tab_Ragebot, Ragebot_AntiAimTargets, false, 475, 290, "No Targets");
		AddNewButton(Tab_Ragebot, Ragebot_AntiAimWarmup, false, 475, 310, "In Warmup");
		AddNewButton(Tab_Ragebot, Ragebot_AntiAimLadders, true, 475, 330, "On Ladder");

	}

	//Player list
	AddNewMenuBox("Selection", 320, 60, 120, 160, Tab_Plist);
	{
		std::vector<char*> ragebox = { "Inheirent","inheirent", "Head", "Neck", "Chest", "Pelvis" };
		AddNewDropbox(325, 80, Tab_Plist, Ragebot_Bone, "HitBox", 6, ragebox);
		std::vector<char*> MultiBox = { "Inheirent", "Inheirent", "Off", "Normal", "Velocity", };
		AddNewDropbox(325, 120, Tab_Plist, Ragebot_Multibox, "MultiBox", 5, MultiBox);
		//char *MultiBoxSpeed[10] = { "inheirent", "inheirent", "Normal", "Low", "Medium", "High" };
		//AddNewDropbox(410, 180, Tab_Plist, Ragebot_MultiboxSpeed, "AimScan Speed", 6, MultiBoxSpeed);
		AddNewButton(Tab_Plist, Ragebot_CustomPSX, false, 325, 150, "Custom PS");
		AddNewSlider(325, 185, 0, 100, 50, "Point Scale", Tab_Plist, Ragebot_PSX);
		//char *Auto[10] = { "inheirent", "inheirent", "Off", "Normal", "+Anti-Box", "Anti-Box", "Side", "HboxScan" };
		//AddNewDropbox(410, 290, Tab_Plist, Ragebot_AutoPSX, "MultiPoint", 8, Auto);
	}

	AddNewMenuBox("Fix AntiAim", 175, 60, 120, 160, Tab_Plist);
	{
		std::vector<char*> ResolverX = { "inheirent", "inheirent", "Off","Auto", "Force Up", "Force Down" };
		AddNewDropbox(180, 80, Tab_Plist, Ragebot_ResolverX, "Fix X", 6, ResolverX);
		std::vector<char*> ResolverY = { "inheirent", "inheirent", "Off", "Auto", "Inverse", "Right", "Left", "Aimware" };
		AddNewDropbox(180, 120, Tab_Plist, Ragebot_ResolverY, "Fix Y", 8, ResolverY);
		std::vector<char*> Lispfix = { "inheirent", "inheirent",  "Off","Perfect" };
		AddNewDropbox(180, 160, Tab_Plist, Ragebot_LispFix, "Resolver", 4, Lispfix);
	}



	/* MISC */
	AddNewSubTab("MISC", Tab_Misc, Sub_Misc);
	AddNewSubTab("SKINS", Tab_Misc, Sub_Skins);
	{
		AddNewSubMenuBox("Movement", 20, 80, 130, 300, Tab_Misc, Sub_Misc);
		{
			AddNewSubButton(Tab_Misc, Misc_Bunny_Hop, false, 25, 90, "Auto Jump", Sub_Misc);
			AddNewSubButton(Tab_Misc, Misc_Auto_Strafer, false, 25, 110, "Auto Strafer", Sub_Misc);
			AddNewSubButton(Tab_Misc, Misc_CircleStrafe_Mode, false, 25, 130, "Adaptive", Sub_Misc);
			AddNewSubButton(Tab_Misc, Misc_CircleStrafe_Enabled, false, 25, 150, "Circle Strafe", Sub_Misc);
			AddNewSubKeyButton(30, 170, Tab_Misc, Misc_CircleStrafe_Key, "Circle Strafe", Sub_Misc);
			AddNewSubButton(Tab_Misc, Misc_Airstuck_Enabled, false, 25, 200, "Airstuck", Sub_Misc);
			AddNewSubKeyButton(30, 220, Tab_Misc, Misc_Airstuck_Key, "Airstuck", Sub_Misc);

			std::vector<char*> fakelag = { "", "Off", "Max", "Adaptive", "In Air" };
			AddNewSubDropbox(25, 260, Tab_Misc, Misc_Fakelagtype, "Fake Lag Type", 5, fakelag, Sub_Misc);
			//AddNewSubSlider(25, 300, 0, 13, 0, "Fake Lag", Tab_Misc, Misc_Fakelag, Sub_Misc);
			AddNewSubButton(Tab_Misc, Misc_Fakelag_Shoot, true, 25, 290, "While Shooting", Sub_Misc);
		}
		AddNewSubMenuBox("Vanity", 170, 80, 130, 300, Tab_Misc, Sub_Misc);
		{
			//
			AddNewSubButton(Tab_Misc, Misc_NameStealer, false, 175, 90, "Name Spam", Sub_Misc);
			std::vector<char*> Spams1 = { "Dingosquad", "Dingosquad", "AIMJUNKIES.NET", "' '" };
			AddNewSubDropbox(175, 110, Tab_Misc, Misc_NameStealer_Index, "", 4, Spams1, Sub_Misc);
			//
			AddNewSubButton(Tab_Misc, Misc_Clan_Active, false, 175, 150, "Clan Tag", Sub_Misc);
			std::vector<char*> Spams2 = { "DingoSquad", "DingoSquad", "Hide Name", "Action", "Slide Animation", "Flash Animation" };
			AddNewSubDropbox(175, 170, Tab_Misc, Misc_Clan_Index, "", 6, Spams2, Sub_Misc);
			//
			AddNewSubButton(Tab_Misc, Misc_Spam_Active, false, 175, 210, "Chat Spam", Sub_Misc);
			std::vector<char*> Spams3 = { "DingoSquad", "DingoSquad", "Shit Talk", "Location Spam", "Team Location" };
			AddNewSubDropbox(175, 230, Tab_Misc, Misc_Spam_Index, "", 5, Spams3, Sub_Misc);
			AddNewSubSlider(175, 270, 0, 50, 20, "Speed", Tab_Misc, Misc_Spam_Speed, Sub_Misc);
		}
		//AddNewSubMenuBox("CrossHair", 570, 80, 130, 110, Tab_Misc, Sub_Misc);
		//{
		//char *Spams[10] = { "Off", "Off", "Dot", "Cross" };
		//AddNewSubDropbox(580, 100, Tab_Misc, Misc_Xhair, "CrossHair", 4, Spams, Sub_Misc);
		//AddNewSubButton(Tab_Misc, Misc_Xhair_coil, false, 580, 130, "Recoil", Sub_Misc);

		//}

		//AddNewMenuBox("Auto Pistol", 10, 270, 130, 40, Tab_Misc);
		//{
		//AddNewButton(Tab_Misc, Misc_Apistol, false, 20, 280, "Auto Pistol");

		//}

		AddNewSubMenuBox("Functions", 320, 80, 130, 140, Tab_Misc, Sub_Misc);
		{
			AddNewSubButton(Tab_Misc, Misc_Anti_Untrust, true, 325, 90, "Anti Untrust", Sub_Misc);
			AddNewSubButton(Tab_Misc, Misc_ResetPlist, false, 325, 110, "Reset Players", Sub_Misc);
			AddNewSubButton(Tab_Misc, Misc_WaterMark, true, 325, 130, "Water Mark*", Sub_Misc);
			AddNewSubButton(Tab_Misc, Misc_WeaponConfigs, false, 325, 150, "Weapon Configs", Sub_Misc);
			std::vector<char*> wgroup = { "Current", "Rifle","Pistol", "Dak", "Awp", "Scout", "Shotgun", "SMG", "Heavy", "Current" };
			AddNewSubDropbox(325, 180, Tab_Misc, Misc_WhichWeapon, "Weapon Group", 10, wgroup, Sub_Misc);
		}
		AddNewSubMenuBox("Teleport", 320, 240, 130, 140, Tab_Misc, Sub_Misc);
		{
			AddNewSubButton(Tab_Misc, Misc_Teleport_Enable, false, 325, 250, "Enable", Sub_Misc);
			std::vector<char*> tptypes = { "Byte Patch", "Byte Patch","Roll Z","Invert" };
			AddNewSubKeyButton(330, 270, Tab_Misc, Misc_Teliport, "Teleport Key", Sub_Misc);
			AddNewSubDropbox(325, 310, Tab_Misc, Misc_Teliport_Type, "Teleport Method", 4, tptypes, Sub_Misc);
		}

	}
	{
		//skins tab here
	}
	AddNewButton(Tab_Visuals, Vis_Active, false, 25, 55, "Active");

	AddNewMenuBox("ESP", 20, 80, 130, 300, Tab_Visuals);
	{
		std::vector<char*> VisBox = { "Off", "Off","Frame", "Corners" };
		AddNewDropbox(25, 100, Tab_Visuals, Vis_Box, "Type", 4, VisBox);

		AddNewButton(Tab_Visuals, Vis_Box_Vis, false, 25, 130, "Visible Only");
		AddNewButton(Tab_Visuals, Vis_Box_Team, false, 25, 150, "Show team");
		AddNewButton(Tab_Visuals, Vis_Name, false, 25, 170, "Name");
		AddNewButton(Tab_Visuals, Vis_Weapon, false, 25, 190, "Weapon");
		AddNewButton(Tab_Visuals, Vis_Ammo, false, 25, 210, "Ammo*");
		AddNewButton(Tab_Visuals, Vis_Background, false, 25, 230, "Health");
		AddNewButton(Tab_Visuals, Vis_Health, false, 25, 250, "Vitals");
		AddNewButton(Tab_Visuals, Vis_AimLines, false, 25, 270, "Aim Lines");
		AddNewButton(Tab_Visuals, Vis_Bomb, false, 25, 290, "Bomb*");
		AddNewButton(Tab_Visuals, Vis_Skel, false, 25, 310, "Skeleton Esp");
		AddNewButton(Tab_Visuals, Vis_GrenadePred, false, 25, 330, "Grenade Prediction*");

	}
	AddNewMenuBox("Cham", 170, 80, 130, 300, Tab_Visuals);
	{
		AddNewButton(Tab_Visuals, Cham_Active, false, 175, 90, "Active");
		AddNewButton(Tab_Visuals, Cham_OnlyVis, false, 175, 110, "Visible Only");
		AddNewButton(Tab_Visuals, Cham_ShowTeam, false, 175, 130, "Show team");
		AddNewButton(Tab_Visuals, Cham_Bomb, false, 175, 150, "Bomb*");
		AddNewButton(Tab_Visuals, Cham_Weapon, false, 175, 170, "Weapon*");
		std::vector<char*> WeaponType = { "Cham","Cham", "Wireframe" };
		AddNewDropbox(175, 200, Tab_Visuals, Cham_Weapon_Type, "Type", 3, WeaponType);
		AddNewButton(Tab_Visuals, Cham_Hands, false, 175, 230, "Hands*");
		std::vector<char*> HandType = { "Cham","Cham", "Wireframe", "Remove" };
		AddNewDropbox(175, 260, Tab_Visuals, Cham_Hands_Type, "Type", 4, HandType);

		//AddNewButton(Tab_Visuals, Vis_Word, false, 185, 300, "World Adjustments");
	}

	AddNewMenuBox("Misc", 320, 80, 130, 300, Tab_Visuals);
	{
		AddNewButton(Tab_Visuals, Vis_Recoil, false, 325, 90, "No-Vis Recoil");
		AddNewButton(Tab_Visuals, Vis_NoSky, false, 325, 110, "No Sky*");
		AddNewButton(Tab_Visuals, Vis_Rainbow, false, 325, 130, "Enable Rainbow");
		AddNewButton(Tab_Visuals, Vis_NoFlash, false, 325, 150, "No Flash*");
		AddNewButton(Tab_Visuals, Vis_BombDamage, false, 325, 170, "Bomb Damage*");
		AddNewButton(Tab_Visuals, Vis_BombTime, false, 325, 190, "Bomb Info*");
		AddNewButton(Tab_Visuals, Vis_CompRank, false, 325, 210, "Show Rank*");
		AddNewButton(Tab_Visuals, Vis_ThirdPerson, false, 325, 230, "Third Person*");
		AddNewSlider(325, 260, 0, 1, 1, "Wall Alpha*", Tab_Visuals, Cham_Asus);
		AddNewSlider(325, 290, 0, 180, 0, "Fov*", Tab_Visuals, Vis_FOV);
		AddNewFuncButton(325, 320, (DWORD)ResetWorld, "Fix World*", Tab_Visuals);
	}

	AddNewMenuBox("Glow", 470, 80, 130, 100, Tab_Visuals);
	{
		AddNewButton(Tab_Visuals, Vis_Glow, false, 475, 90, "Active");
		AddNewButton(Tab_Visuals, Vis_Glow_Vis, false, 475, 110, "Only Visible");
		AddNewButton(Tab_Visuals, Vis_Glow_Team, false, 475, 130, "Show team");
	}



	/* OTHER */
	AddNewSubTab("COLOURS 1", Tab_Other, Sub_Colour1);
	AddNewSubTab("COLOURS 2", Tab_Other, Sub_Colour2);

	{//Colours 1
		AddNewSubMenuBox("Menu", 5, 70, 130, 140, Tab_Other, Sub_Colour1);
		{
			AddNewSubSlider(15, 90, 0, 255, 20, "Red", Tab_Other, Other_MenuRed, Sub_Colour1);
			AddNewSubSlider(15, 120, 0, 255, 20, "Green", Tab_Other, Other_MenuGreen, Sub_Colour1);
			AddNewSubSlider(15, 150, 0, 255, 20, "Blue", Tab_Other, Other_MenuBlue, Sub_Colour1);
			AddNewSubSlider(15, 180, 0, 255, 255, "Alpha", Tab_Other, Other_MenuAlpha, Sub_Colour1);

		}
		AddNewSubMenuBox("Text", 5, 220, 130, 140, Tab_Other, Sub_Colour1);
		{
			AddNewSubSlider(15, 240, 0, 255, 255, "Red", Tab_Other, Other_TextRed, Sub_Colour1);
			AddNewSubSlider(15, 270, 0, 255, 255, "Green", Tab_Other, Other_TextGreen, Sub_Colour1);
			AddNewSubSlider(15, 300, 0, 255, 255, "Blue", Tab_Other, Other_TextBlue, Sub_Colour1);
			AddNewSubSlider(15, 330, 0, 255, 255, "Alpha", Tab_Other, Other_TextAlpha, Sub_Colour1);
		}
		AddNewSubMenuBox("Background", 140, 70, 130, 140, Tab_Other, Sub_Colour1);
		{
			AddNewSubSlider(150, 90, 0, 255, 15, "Red", Tab_Other, Other_BackgroundRed, Sub_Colour1);
			AddNewSubSlider(150, 120, 0, 255, 15, "Green", Tab_Other, Other_BackgroundGreen, Sub_Colour1);
			AddNewSubSlider(150, 150, 0, 255, 15, "Blue", Tab_Other, Other_BackgroundBlue, Sub_Colour1);
			AddNewSubSlider(150, 180, 0, 255, 255, "Alpha", Tab_Other, Other_BackgroundAlpha, Sub_Colour1);
		}
		AddNewSubMenuBox("Outline", 140, 220, 130, 140, Tab_Other, Sub_Colour1);
		{
			AddNewSubSlider(150, 240, 0, 255, 50, "Red", Tab_Other, Other_OutlineRed, Sub_Colour1);
			AddNewSubSlider(150, 270, 0, 255, 50, "Green", Tab_Other, Other_OutlineGreen, Sub_Colour1);
			AddNewSubSlider(150, 300, 0, 255, 50, "Blue", Tab_Other, Other_OutlineBlue, Sub_Colour1);
			AddNewSubSlider(150, 330, 0, 255, 255, "Alpha", Tab_Other, Other_OutlineAlpha, Sub_Colour1);
		}
		AddNewSubMenuBox("ESP T Visible", 275, 70, 130, 140, Tab_Other, Sub_Colour1);
		{
			AddNewSubSlider(285, 90, 0, 255, 247, "Red", Tab_Other, Other_Esp_T_Visible_Red, Sub_Colour1);
			AddNewSubSlider(285, 120, 0, 255, 180, "Green", Tab_Other, Other_Esp_T_Visible_Green, Sub_Colour1);
			AddNewSubSlider(285, 150, 0, 255, 20, "Blue", Tab_Other, Other_Esp_T_Visible_Blue, Sub_Colour1);
			AddNewSubSlider(285, 180, 0, 255, 255, "Alpha", Tab_Other, Other_Esp_T_Visible_Alpha, Sub_Colour1);
		}
		AddNewSubMenuBox("ESP T Invisible", 275, 220, 130, 140, Tab_Other, Sub_Colour1);
		{
			AddNewSubSlider(285, 240, 0, 255, 240, "Red", Tab_Other, Other_Esp_T_inVisible_Red, Sub_Colour1);
			AddNewSubSlider(285, 270, 0, 255, 30, "Green", Tab_Other, Other_Esp_T_inVisible_Green, Sub_Colour1);
			AddNewSubSlider(285, 300, 0, 255, 35, "Blue", Tab_Other, Other_Esp_T_inVisible_Blue, Sub_Colour1);
			AddNewSubSlider(285, 330, 0, 255, 255, "Alpha", Tab_Other, Other_Esp_T_inVisible_Alpha, Sub_Colour1);
		}
		AddNewSubButton(Tab_Other, Other_Esp_Enemy_Rainbow, false, 285, 370, "Rainbow", Sub_Colour1);

		AddNewSubMenuBox("ESP CT Visible", 410, 70, 130, 140, Tab_Other, Sub_Colour1);
		{
			AddNewSubSlider(420, 90, 0, 255, 32, "Red", Tab_Other, Other_Esp_CT_Visible_Red, Sub_Colour1);
			AddNewSubSlider(420, 120, 0, 255, 180, "Green", Tab_Other, Other_Esp_CT_Visible_Green, Sub_Colour1);
			AddNewSubSlider(420, 150, 0, 255, 57, "Blue", Tab_Other, Other_Esp_CT_Visible_Blue, Sub_Colour1);
			AddNewSubSlider(420, 180, 0, 255, 255, "Alpha", Tab_Other, Other_Esp_CT_Visible_Alpha, Sub_Colour1);
		}
		AddNewSubMenuBox("ESP CT Invisible", 410, 220, 130, 140, Tab_Other, Sub_Colour1);
		{
			AddNewSubSlider(420, 240, 0, 255, 63, "Red", Tab_Other, Other_Esp_CT_inVisible_Red, Sub_Colour1);
			AddNewSubSlider(420, 270, 0, 255, 72, "Green", Tab_Other, Other_Esp_CT_inVisible_Green, Sub_Colour1);
			AddNewSubSlider(420, 290, 0, 255, 205, "Blue", Tab_Other, Other_Esp_CT_inVisible_Blue, Sub_Colour1);
			AddNewSubSlider(420, 330, 0, 255, 255, "Alpha", Tab_Other, Other_Esp_CT_inVisible_Alpha, Sub_Colour1);
		}
		AddNewSubButton(Tab_Other, Other_Esp_Team_Rainbow, false, 420, 370, "Rainbow", Sub_Colour1);

		AddNewSubMenuBox("Glow Visible", 545, 70, 130, 140, Tab_Other, Sub_Colour1);
		{
			AddNewSubSlider(555, 90, 0, 255, 0, "Red", Tab_Other, Other_Glow_Visible_Red, Sub_Colour1);
			AddNewSubSlider(555, 120, 0, 255, 255, "Green", Tab_Other, Other_Glow_Visible_Green, Sub_Colour1);
			AddNewSubSlider(555, 160, 0, 255, 0, "Blue", Tab_Other, Other_Glow_Visible_Blue, Sub_Colour1);
			AddNewSubSlider(555, 180, 0, 255, 255, "Alpha", Tab_Other, Other_Glow_Visible_Alpha, Sub_Colour1);
		}
		AddNewSubMenuBox("Glow Invisible", 545, 220, 130, 140, Tab_Other, Sub_Colour1);
		{
			AddNewSubSlider(555, 240, 0, 255, 255, "Red", Tab_Other, Other_Glow_inVisible_Red, Sub_Colour1);
			AddNewSubSlider(555, 270, 0, 255, 0, "Green", Tab_Other, Other_Glow_inVisible_Green, Sub_Colour1);
			AddNewSubSlider(555, 300, 0, 255, 0, "Blue", Tab_Other, Other_Glow_inVisible_Blue, Sub_Colour1);
			AddNewSubSlider(555, 330, 0, 255, 255, "Alpha", Tab_Other, Other_Glow_inVisible_Alpha, Sub_Colour1);
		}
		AddNewSubButton(Tab_Other, Other_Glow_Rainbow, false, 555, 370, "Rainbow", Sub_Colour1);

	}
	{//Colours 2
		AddNewSubMenuBox("Cham Weapon", 5, 70, 130, 140, Tab_Other, Sub_Colour2);
		{
			AddNewSubSlider(15, 90, 0, 255, 255, "Red", Tab_Other, Other_Cham_Weapon_Red, Sub_Colour2);
			AddNewSubSlider(15, 120, 0, 255, 0, "Green", Tab_Other, Other_Cham_Weapon_Green, Sub_Colour2);
			AddNewSubSlider(15, 150, 0, 255, 0, "Blue", Tab_Other, Other_Cham_Weapon_Blue, Sub_Colour2);
			AddNewSubSlider(15, 180, 0, 255, 255, "Alpha", Tab_Other, Other_Cham_Weapon_Alpha, Sub_Colour2);

		}
		AddNewSubMenuBox("Cham Hands", 5, 220, 130, 140, Tab_Other, Sub_Colour2);
		{
			AddNewSubSlider(15, 240, 0, 255, 25, "Red", Tab_Other, Other_Cham_Hands_Red, Sub_Colour2);
			AddNewSubSlider(15, 270, 0, 255, 25, "Green", Tab_Other, Other_Cham_Hands_Green, Sub_Colour2);
			AddNewSubSlider(15, 300, 0, 255, 25, "Blue", Tab_Other, Other_Cham_Hands_Blue, Sub_Colour2);
			AddNewSubSlider(15, 330, 0, 255, 255, "Alpha", Tab_Other, Other_Cham_Hands_Alpha, Sub_Colour2);
		}
		AddNewSubButton(Tab_Other, Other_Cham_Weapon_Rainbow, false, 15, 370, "Rainbow", Sub_Colour2);

		AddNewSubMenuBox("Cham Chicken Visible", 140, 70, 130, 140, Tab_Other, Sub_Colour2);
		{
			AddNewSubSlider(150, 90, 0, 255, 0, "Red", Tab_Other, Other_Cham_Chicken_Visible_Red, Sub_Colour2);
			AddNewSubSlider(150, 120, 0, 255, 0, "Green", Tab_Other, Other_Cham_Chicken_Visible_Green, Sub_Colour2);
			AddNewSubSlider(150, 150, 0, 255, 255, "Blue", Tab_Other, Other_Cham_Chicken_Visible_Blue, Sub_Colour2);
			AddNewSubSlider(150, 180, 0, 255, 255, "Alpha", Tab_Other, Other_Cham_Chicken_Visible_Alpha, Sub_Colour2);
		}
		AddNewSubMenuBox("Cham Chicken inVisible", 140, 220, 130, 140, Tab_Other, Sub_Colour2);
		{
			AddNewSubSlider(150, 240, 0, 255, 200, "Red", Tab_Other, Other_Cham_Chicken_inVisible_Red, Sub_Colour2);
			AddNewSubSlider(150, 270, 0, 255, 200, "Green", Tab_Other, Other_Cham_Chicken_inVisible_Green, Sub_Colour2);
			AddNewSubSlider(150, 300, 0, 255, 200, "Blue", Tab_Other, Other_Cham_Chicken_inVisible_Blue, Sub_Colour2);
			AddNewSubSlider(150, 330, 0, 255, 255, "Alpha", Tab_Other, Other_Cham_Chicken_inVisible_Alpha, Sub_Colour2);
		}
		AddNewSubButton(Tab_Other, Other_Cham_Chicken_Rainbow, false, 150, 370, "Rainbow", Sub_Colour2);

		AddNewSubMenuBox("Cham Enemy Visible", 275, 70, 130, 140, Tab_Other, Sub_Colour2);
		{
			AddNewSubSlider(285, 90, 0, 255, 0, "Red", Tab_Other, Other_Cham_Enemy_Visible_Red, Sub_Colour2);
			AddNewSubSlider(285, 120, 0, 255, 255, "Green", Tab_Other, Other_Cham_Enemy_Visible_Green, Sub_Colour2);
			AddNewSubSlider(285, 150, 0, 255, 255, "Blue", Tab_Other, Other_Cham_Enemy_Visible_Blue, Sub_Colour2);
			AddNewSubSlider(285, 180, 0, 255, 255, "Alpha", Tab_Other, Other_Cham_Enemy_Visible_Alpha, Sub_Colour2);
		}
		AddNewSubMenuBox("Cham Enemy Invisible", 275, 220, 130, 140, Tab_Other, Sub_Colour2);
		{
			AddNewSubSlider(285, 240, 0, 255, 255, "Red", Tab_Other, Other_Cham_Enemy_inVisible_Red, Sub_Colour2);
			AddNewSubSlider(285, 270, 0, 255, 255, "Green", Tab_Other, Other_Cham_Enemy_inVisible_Green, Sub_Colour2);
			AddNewSubSlider(285, 300, 0, 255, 0, "Blue", Tab_Other, Other_Cham_Enemy_inVisible_Blue, Sub_Colour2);
			AddNewSubSlider(285, 330, 0, 255, 255, "Alpha", Tab_Other, Other_Cham_Enemy_inVisible_Alpha, Sub_Colour2);
		}
		AddNewSubButton(Tab_Other, Other_Cham_Enemy_Rainbow, false, 285, 370, "Rainbow", Sub_Colour2);

		AddNewSubMenuBox("Cham Team Visible", 410, 70, 130, 140, Tab_Other, Sub_Colour2);
		{
			AddNewSubSlider(420, 90, 0, 255, 255, "Red", Tab_Other, Other_Cham_Team_Visible_Red, Sub_Colour2);
			AddNewSubSlider(420, 120, 0, 255, 138, "Green", Tab_Other, Other_Cham_Team_Visible_Green, Sub_Colour2);
			AddNewSubSlider(420, 150, 0, 255, 255, "Blue", Tab_Other, Other_Cham_Team_Visible_Blue, Sub_Colour2);
			AddNewSubSlider(420, 180, 0, 255, 255, "Alpha", Tab_Other, Other_Cham_Team_Visible_Alpha, Sub_Colour2);
		}
		AddNewSubMenuBox("Cham Team Invisible", 410, 220, 130, 140, Tab_Other, Sub_Colour2);
		{
			AddNewSubSlider(420, 240, 0, 255, 178, "Red", Tab_Other, Other_Cham_Team_inVisible_Red, Sub_Colour2);
			AddNewSubSlider(420, 270, 0, 255, 0, "Green", Tab_Other, Other_Cham_Team_inVisible_Green, Sub_Colour2);
			AddNewSubSlider(420, 290, 0, 255, 55, "Blue", Tab_Other, Other_Cham_Team_inVisible_Blue, Sub_Colour2);
			AddNewSubSlider(420, 330, 0, 255, 255, "Alpha", Tab_Other, Other_Cham_Team_inVisible_Alpha, Sub_Colour2);
		}
		AddNewSubButton(Tab_Other, Other_Cham_Team_Rainbow, false, 420, 370, "Rainbow", Sub_Colour2);

	}
	AddNewMenuBox("Configs", 10, 80, 130, 180, Tab_Config);
	{
		std::vector<char*> configtype = { "Default", "Legit","HvH", "Rage", "Casual", "Custom1", "Custom2" };
		AddNewDropbox(20, 100, Tab_Config, Config_type, "Config", 7, configtype);
		AddNewFuncButton(20, 140, (DWORD)SaveSettings, "Save", Tab_Config);
		AddNewFuncButton(20, 180, (DWORD)LoadSettings, "Load", Tab_Config);
		AddNewFuncButton(20, 220, (DWORD)Unhook, "Uninject", Tab_Config);
	}
}

void DrawMenu()
{
	if (Menu.Opened) {
		colourUpdate();

	}
	if (Settings.GetSetting(Tab_Visuals, Vis_Rainbow)) {
		rainbow();

	}

	static bool firsttime = true;
	Dont_Click = false;

	/* UPDATE KEYS */
	std::copy(keys, keys + 255, oldKeys);
	for (int x = 0; x < 255; x++)
	{
		keys[x] = (GetAsyncKeyState(x));
	}

	if (GetKeyPress(VK_INSERT))
	{
		Menu.Opened = !Menu.Opened;
		std::string msg = "cl_mouseenable " + std::to_string(!Menu.Opened);
		Interfaces.pEngine->ClientCmd_Unrestricted(msg.c_str(), 0);
	}

	if (firsttime /* SNIP!!, THIS WILL CAUSE ERRORS FFS! */)
	{
		/* Init Menu Here */
		SetupMenu();
		firsttime = false;
	}


	if (Menu.Opened)
	{
		if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000))
		{
			Holding_Mouse_1 = false;
		}
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			Clicked_This_Frame = true;
		}
		else
		{
			Clicked_This_Frame = false;
		}

		Menu.Update_Frame();

		//background and outline and shit
		Interfaces.pSurface->DrawSetColor(39, 42, 47, 255);
		Interfaces.pSurface->DrawFilledRect(Menu.pos.x, Menu.pos.y, Menu.pos.x + 800, Menu.pos.y + 400);
		Interfaces.pSurface->DrawSetColor(25, 25, 25, 255);
		Interfaces.pSurface->DrawOutlinedRect(Menu.pos.x - 1, Menu.pos.y - 1, Menu.pos.x + 801, Menu.pos.y + 401);
		Interfaces.pSurface->DrawLine(Menu.pos.x, Menu.pos.y + 40, Menu.pos.x + 800, Menu.pos.y + 40);

		for (CTab& Tab : Tabs)
			Tab.Update();
		for (CSubTab& SubTab : SubTabs)
			SubTab.Update();

		for (CMenuBox& MenuBox : MenuBoxs)
			MenuBox.Update();

		for (CDropBox& Dropbox : Dropboxes)
			Dropbox.Update();

		for (CSlider& slider : Sliders)
			slider.Update();

		for (CIntSlider& slider : IntSliders)
			slider.Update();

		for (CButton& Button : Buttons)
			Button.Update();

		for (CKeyButton& KeyButton : KeyButtons)
			KeyButton.Update();

		for (CFunctionButton& FuncButton : FuncButtons)
			FuncButton.Update();





		for (CTab& Tab : Tabs)
			Tab.Draw();

		for (CSubTab& SubTab : SubTabs)
			SubTab.Draw();

		for (CMenuBox& MenuBox : MenuBoxs)
			MenuBox.Draw();

		for (CFunctionButton& FuncButton : FuncButtons)
			FuncButton.Draw();

		for (CKeyButton& KeyButton : KeyButtons)
			KeyButton.Draw();

		for (CSlider& slider : Sliders)
			slider.Draw();

		for (CIntSlider& slider : IntSliders)
			slider.Draw();

		for (CButton& Button : Buttons)
			Button.Draw();


		std::reverse(Dropboxes.begin(), Dropboxes.end());

		for (CDropBox& Dropbox : Dropboxes)
			Dropbox.Draw();

		std::reverse(Dropboxes.begin(), Dropboxes.end());

		if (Menu.GetCurret_Tab() == Tab_Plist)
			Playerlist.Menu_Playerlist_Drawing(Menu.pos.x + 10, Menu.pos.y + 50);

		skinchanger();

		DrawMouse();

		if (Clicked_This_Frame)
		{
			Holding_Mouse_1 = true;
		}
	}


}


