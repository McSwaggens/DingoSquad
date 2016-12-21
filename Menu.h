#pragma once

void DrawMenu();


struct MenuPOS
{
	LONG x = 0, y = 0;
};

class CMenu
{
public:
	MenuPOS pos;
	void Set_Current_Tab(int tab);
	int GetCurret_Tab();
	void Set_Current_SubTab(int tab);
	int GetCurret_SubTab();

	void Update_Frame();
	bool Opened = false;
private:
	int Current_tab = 0;
	int Current_Subtab = 0;

	bool GetClicked();
};
extern CMenu Menu;


bool GetKeyPress(unsigned int key);

class CButton_Independant
{
public:
	MenuPOS pos;
	MenuPOS offset;
	bool Enabled;
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

		if (Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 20 && Mouse.y < this->pos.y + 20)
		{
			return true;
		}
		return false;
	}
public:
	void Update(int x, int y)
	{
		this->pos.x = x;
		this->pos.y = y;

		if (Clicked())
		{
			Dont_Click = true;
			Enabled = !Enabled;
		}
	}
	void Draw()
	{
		Interfaces.pSurface->DrawSetColor(15, 15, 15, 255);
		Interfaces.pSurface->DrawFilledRect(this->pos.x, this->pos.y, this->pos.x + 20, this->pos.y + 20);

		if (this->Enabled)
		{
			Interfaces.pSurface->DrawSetColor(0, 200, 255, 255);
			Interfaces.pSurface->DrawFilledRect(this->pos.x + 4, this->pos.y + 4, this->pos.x + 16, this->pos.y + 16);
		}

		Interfaces.pSurface->DrawSetColor(OutlineRed, OutlineGreen, OutlineBlue, OutlineAlpha);
		Interfaces.pSurface->DrawOutlinedRect(this->pos.x, this->pos.y, this->pos.x + 20, this->pos.y + 20);
		Interfaces.pSurface->DrawT(this->pos.x + 30, this->pos.y + 6, CColor(TextRed, TextGreen, TextBlue, TextAlpha), 39, false, this->Name);
	}
	void Init(bool defult, char* name)
	{
		this->Name = name;
		Enabled = defult;
	}
};

class CSlider_Independant
{
public:
	double Max = 100;
	double Min = 0;
	double Value = 50;
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

		double Ratio = Value / (this->Max - this->Min);
		double Location = Ratio * 100;
		Interfaces.pSurface->DrawSetColor(80, 80, 80, 255);
		Interfaces.pSurface->DrawOutlinedRect(this->pos.x, this->pos.y + 5, this->pos.x + 100, this->pos.y + 15);
		Interfaces.pSurface->DrawSetColor(MenuRed, MenuGreen, MenuBlue, MenuAlpha);
		Interfaces.pSurface->DrawFilledRect(this->pos.x + 2, this->pos.y + 7, this->pos.x + Location, this->pos.y + 13);
		Interfaces.pSurface->DrawSetColor(200, 200, 200, 255);
		Interfaces.pSurface->DrawFilledRect(this->pos.x + Location - 3, this->pos.y, this->pos.x + Location + 3, this->pos.y + 20);
		Interfaces.pSurface->DrawSetColor(170, 170, 170, 255);
		Interfaces.pSurface->DrawOutlinedRect(this->pos.x + Location - 3, this->pos.y, this->pos.x + Location + 3, this->pos.y + 20);

		Interfaces.pSurface->DrawT(this->pos.x, this->pos.y - 12, CColor(TextRed, TextGreen, TextBlue, TextAlpha), 39, false, "%s: %.1f", this->Name, (float)Value);

	}
	void Init(double min, double max, double defult, char* name)
	{
		Max = max;
		Min = min;
		Name = name;
		Value = defult;

	}
	void Update(int x, int y)
	{
		this->pos.x = x;
		this->pos.y = y;

		if (this->GetClicked())
		{
			Dont_Click = true;
			POINT Mouse;
			POINT mp; GetCursorPos(&mp);
			ScreenToClient(GetForegroundWindow(), &mp);
			Mouse.x = mp.x; Mouse.y = mp.y;
			double idifference;
			idifference = Mouse.x - this->pos.x;
			double value = ((idifference / 100)*(this->Max - this->Min));
			if (value < Min)
			{
				value = Min;
			}
			else if (value > Max)
			{
				value = Max;
			}

			Value = value;
		}

	}

};

class CDropBox_Independant
{
public:

	char* Name = "ERROR";
	char* Parts[20];
	int Amount = 0;
	bool Dropping = false;

	MenuPOS pos;
	MenuPOS offset;

	int Index = 0;

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

	void Update(int x, int y)
	{
		pos.x = x;
		pos.y = y;

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
				Index = index;
				this->Dropping = false;
				Dont_Click = true;
			}
			else if (Clicked_This_Frame && !Holding_Mouse_1)
			{
				Dropping = false;
			}
		}
	}
	void Draw()
	{
		Interfaces.pSurface->DrawSetColor(BackgroundRed, BackgroundGreen, BackgroundBlue, BackgroundAlpha);
		Interfaces.pSurface->DrawFilledRect(this->pos.x, this->pos.y, this->pos.x + 100, this->pos.y + 21);
		Interfaces.pSurface->DrawSetColor(MenuRed, MenuGreen, MenuBlue, MenuAlpha);;
		Interfaces.pSurface->DrawOutlinedRect(this->pos.x, this->pos.y, this->pos.x + 100, this->pos.y + 21);
		Interfaces.pSurface->DrawT(this->pos.x, this->pos.y - 12, CColor(TextRed, TextGreen, TextBlue, TextAlpha), 39, false, this->Name);

		if (this->Dropping)
		{
			for (int i = 1; i < this->Amount; i++)
			{
				Interfaces.pSurface->DrawSetColor(BackgroundRed, BackgroundGreen, BackgroundBlue, BackgroundAlpha);
				Interfaces.pSurface->DrawFilledRect(this->pos.x, this->pos.y + (20 * i), this->pos.x + 100, this->pos.y + (20 * i) + 21);
				Interfaces.pSurface->DrawSetColor(MenuRed, MenuGreen, MenuBlue, MenuAlpha);
				Interfaces.pSurface->DrawOutlinedRect(this->pos.x, this->pos.y + (20 * i), this->pos.x + 100, this->pos.y + (20 * i) + 21);
				Interfaces.pSurface->DrawT(this->pos.x + 50, this->pos.y + 5 + (20 * i), CColor(TextRed, TextGreen, TextBlue, TextAlpha), 39, true, this->Parts[i]);
			}
		}
		else
		{
			Interfaces.pSurface->DrawT(this->pos.x + 50, this->pos.y + 5, CColor(TextRed, TextGreen, TextBlue, TextAlpha), 39, true, this->Parts[Index]);

			static int Texture = Interfaces.pSurface->CreateNewTextureID(true); //need to make a texture with procedural true
			unsigned char buffer[4] = { BackgroundRed, BackgroundGreen, BackgroundBlue, BackgroundAlpha };//{ color.r(), color.g(), color.b(), color.a() };

			Interfaces.pSurface->DrawSetTextureRGBA(Texture, buffer, 1, 1); //Texture, char array of texture, width, height
			Interfaces.pSurface->DrawSetColor(MenuRed, MenuGreen, MenuBlue, MenuAlpha); // keep this full color and opacity use the RGBA @top to set values.
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
	void Init(char* name, int parts, char* arr[20])
	{
		Name = name;
		Amount = parts;

		for (int i = 0; i < parts; i++)
		{
			Parts[i] = arr[i];
		}
	}
};
