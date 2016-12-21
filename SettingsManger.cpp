#include "stdafx.h"
#include <wininet.h>
#pragma comment(lib, "wininet")

double SettingsArray[20][200][26];
double PlistArray[102][200];

SettingsManger Settings;
int currentplayerinplst = 101;
int currentgroup = 1;
int oldgroup = -1;
int weaponconfigTab = Group_Default;
void SettingsManger::playerlist() {
	currentplayerinplst;
}
bool SettingsManger::weaponconfigs() {
	if (Settings.GetSetting( Tab_Misc, Misc_WeaponConfigs)) {
		if (Hacks.LocalWeapon->isSniper()) {
			if (Hacks.LocalWeapon->isAWP()) {
				currentgroup = Group_AWP;
			}
			else if (Hacks.LocalWeapon->isScout()) {
				currentgroup = Group_Scout;

			}
			else if (Hacks.LocalWeapon->isDak()) {
				currentgroup = Group_Dak;

			}

		}
		else if (Hacks.LocalWeapon->isRifle()) {
			currentgroup = Group_Rifle;

		}
		else if (Hacks.LocalWeapon->isSmgW()) {
			currentgroup = Group_SMG;

		}
		else if (Hacks.LocalWeapon->isPistoleW()) {
			currentgroup = Group_Pistol;
			weaponconfigTab = Group_Pistol;

		}
		else if (Hacks.LocalWeapon->isShotgunW()) {
			currentgroup = Group_Shotgun;

		}
		else if (Hacks.LocalWeapon->isMashineW()) {
			currentgroup = Group_Heavy;

		}
		Settings.SetSetting(Tab_Misc, Misc_WeaponConfigs, 1);
		if (currentgroup != oldgroup) {
			oldgroup = currentgroup;
			weaponconfigTab = currentgroup;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		currentgroup = Group_Default;
		weaponconfigTab = Group_Default;
		return false;
	}
	if (Settings.GetSetting(Tab_Misc, Misc_WeaponConfigs) == 0) {
		weaponconfigTab = 0;
		currentgroup = Group_Default;

	}
	return false;

}
void SettingsManger::SetSetting(int Tab, int Setting, double Value)
{
	int someweaponvalue = 0;
	if (Tab == Tab_LegitBot || Tab == Tab_Ragebot) {
		if (Settings.GetSetting( Tab_Misc, Misc_WeaponConfigs)) {
			if (Settings.GetSetting( Tab_Misc, Misc_WhichWeapon) == 0 || Settings.GetSetting( Tab_Misc, Misc_WhichWeapon) == 9) {
				someweaponvalue = weaponconfigTab;

			}
			else {
				someweaponvalue = Settings.GetSetting( Tab_Misc, Misc_WhichWeapon);
			}
		}
	}
	if (Tab == Tab_Plist) {
		PlistArray[currentplayerinplst][Setting]= Value;

	}

	SettingsArray[Tab][Setting][someweaponvalue] = Value;
}

void SettingsManger::SetBoolSetting(int Tab, int Setting, double Value)
{
	int someweaponvalue = 0;
	if (Tab == Tab_LegitBot || Tab == Tab_Ragebot) {
		if (Settings.GetSetting( Tab_Misc, Misc_WeaponConfigs)) {
			if (Settings.GetSetting( Tab_Misc, Misc_WhichWeapon) == 0 || Settings.GetSetting( Tab_Misc, Misc_WhichWeapon) == 9) {
				someweaponvalue = weaponconfigTab;

			}
			else {
				someweaponvalue = Settings.GetSetting( Tab_Misc, Misc_WhichWeapon);
			}
		}
	}
	if (Tab == Tab_Plist) {

		PlistArray[currentplayerinplst][Setting] = Value;

	}

	SettingsArray[Tab][Setting][someweaponvalue] = Value;
}

double SettingsManger::GetMenuSetting(int Tab, int Setting)
{
	int someweaponvalue = 0;
	if (Tab == Tab_LegitBot || Tab == Tab_Ragebot) {
		if (Settings.GetSetting( Tab_Misc, Misc_WeaponConfigs)) {
			if (Settings.GetSetting( Tab_Misc, Misc_WhichWeapon) == 0 || Settings.GetSetting( Tab_Misc, Misc_WhichWeapon) == 9) {
			someweaponvalue = weaponconfigTab;

		}else{
				someweaponvalue = Settings.GetSetting( Tab_Misc, Misc_WhichWeapon);
			}
		}
	}
	if (Tab == Tab_Plist) {
		return PlistArray[currentplayerinplst][Setting];

	}

	return SettingsArray[Tab][Setting][someweaponvalue];
}
double SettingsManger::GetPlayer(int index, int Tab, int Setting) {
	if (Tab != Tab_Ragebot)
		return GetSetting(Tab, Setting);
	int playerid = index; // Player->Entity->GetIndex();
	if(playerid == -1)
		return GetSetting(Tab, Setting);
	if(playerid > 100)
		return GetSetting(Tab, Setting);
	if (playerid <= 0)
		return GetSetting(Tab, Setting);
	if (Setting == Ragebot_AutoPSX)
	{
		int torf = PlistArray[playerid][Ragebot_CustomPSX];
		if (torf)
			return PlistArray[playerid][Ragebot_AutoPSX];
		else
			return GetSetting(Tab, Setting);

	}
	int PlistSetting = PlistArray[playerid][Setting];
	if(PlistSetting == 0 || PlistSetting == 1)
		return GetSetting(Tab, Setting);
	else
	{
		PlistSetting -= 1;

	}
	return PlistSetting;
}

double SettingsManger::GetSetting(int Tab, int Setting)
{
	int someweaponvalue = 0;
	if (Tab == Tab_LegitBot || Tab == Tab_Ragebot)
		someweaponvalue = weaponconfigTab;

	if (Tab == Tab_Plist) {
		return PlistArray[currentplayerinplst][Setting];

	}

	
	return SettingsArray[Tab][Setting][someweaponvalue];
}


bool SettingsManger::GetBoolSetting(int Tab, int Setting)
{
	int someweaponvalue = 0;
	if ( Tab == Tab_LegitBot || Tab == Tab_Ragebot)
		someweaponvalue = weaponconfigTab;
	if (Tab == Tab_Plist) {
		//return PlistArray[currentplayerinplst][Setting];

	}

	return (SettingsArray[Tab][Setting][someweaponvalue] == 1);
}

void loadSettings(std::string settings) {
	// sets up settings char to a vector looks like this "0:3:2:2" ie tab-setting-value
	std::string tovector = settings;

	std::stringstream ss(tovector);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> settingarray(begin, end);
	//Gets how many settings to set
	int size = settingarray.size();
	for (int i = 0; i< size - 1; i++)
	{
		// Gets the setting we are dealing with
		std::string meme = settingarray[i];
		//Converst the string to char array
		for (int i = 0; i<meme.length(); i++)
		{
			if (meme[i] == ':')
				meme[i] = ' ';
		}
		vector<double> indi;
		stringstream ss(meme);
		double temp;
		while (ss >> temp)
		indi.push_back(temp);
		//0:1:2:8
		// Sets the setting
		SettingsArray[(int)indi[0]][(int)indi[1]][(int)indi[2]] = (double)indi[3];
	}
}
void savesets() {
	int number = Settings.GetSetting( Tab_Config, Config_type);
	if (CreateDirectory("C:/dingointernal/", NULL) || ERROR_ALREADY_EXISTS == GetLastError())
	{

	}
	std::string savetype = "c:/dingointernal/save";
	savetype.append(to_string(number));
	savetype.append(".txt");

	string txt;
	ifstream file(savetype);

	if (file.is_open())
		while (file.good())
			getline(file, txt);
	file.close();
//#ifdef DEBUG
	cout << txt << endl;

//#endif // DEBUG

	loadSettings(txt);
}
void upload()
{
	int number = Settings.GetSetting(Tab_Config, Config_type);

	DWORD  lVolSerialNbr = 0;
	char sHDSerial[255] = "";
	//nSize = sizeof(cUsername); 
	GetVolumeInformation("C:\\", 0, 0, &lVolSerialNbr, 0, 0, 0, 0);
	_ultoa(lVolSerialNbr, sHDSerial, 10);
	std::string c(sHDSerial);
	c.append("/");
	LPCSTR Dir = c.c_str();
	string saveadd = c;
	saveadd.append("save").append(to_string(number));
	saveadd.append(".txt");

	std::string savetype = "c:/dingointernal/save";
	savetype.append(to_string(number));
	savetype.append(".txt");
	LPCSTR from = savetype.c_str();
	LPCSTR to = saveadd.c_str();

	HINTERNET hInternet;
	HINTERNET hFtp;
	hInternet = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	hFtp = InternetConnect(hInternet, "ftp.dingosquad.net", INTERNET_DEFAULT_FTP_PORT, "settings@dingosquad.net", "DingoSettings321", INTERNET_SERVICE_FTP, 0, 0);
	if (FtpPutFile(hFtp, from, to, FTP_TRANSFER_TYPE_BINARY, 0))
	{
	}
	else
	{
		if (FtpCreateDirectory(hFtp, Dir))
		{
			if (FtpPutFile(hFtp, from, to, FTP_TRANSFER_TYPE_BINARY, 0))
			{
			}
			else {
			}
		}
		else {
		}

	}
	InternetCloseHandle(hFtp);
	InternetCloseHandle(hInternet);
	cout << 3 << endl;

}

void writefile(std::string string) {
	int number = Settings.GetSetting( Tab_Config, Config_type);

	if (CreateDirectory("C:/dingointernal/", NULL) || ERROR_ALREADY_EXISTS == GetLastError())
	{

	}
	std::string savetype = "c:/dingointernal/save";
	savetype.append(to_string(number));
	savetype.append(".txt");
	ofstream myfile;
	myfile.open(savetype);
	myfile << string;
	myfile.close();
	cout << 1 << endl;
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)upload, 0, 0, 0);
	cout << 2 << endl;


}
std::string settingstostring() {
	std::string stra;
	int val = MAXVALUEMENU - 1;

	for (int i = 0; i < val; i++) {

		int mena = 1;
		switch (i) {
		case 0:
			mena = MAXVALUERAGE;
			break;
		case 1:
			mena = MAXVALUELEGIT;
			break;

		case 2:
			mena = MAXVALUEVISUALS;
			break;

		case 3:
			mena = MAXVALUEMISC;
			break;

		case 4:
			mena = MAXVALUEOTHER;
			break;

		case 5:
			mena = MAXVALUESKIN;
			break;


		}
		for (int a = 0; a < mena; a++) {

			double settingval;
			if (i == 1 || i == 0) {
				for (int c = 0; c < 9; c++) {
					stra.append(to_string(i));
					stra.append(":");
					stra.append(to_string(a));
					stra.append(":");
					 settingval = SettingsArray[i][a][c];
					 stra.append(to_string(c));
					 stra.append(":");
					 stra.append(to_string(settingval));
					 stra.append(" ");

				}
			}
			else {
				stra.append(to_string(i));
				stra.append(":");
				stra.append(to_string(a));
				stra.append(":");
				settingval = SettingsArray[i][a][0];
				stra.append(to_string(0));
				stra.append(":");
				stra.append(to_string(settingval));
				stra.append(" ");
			}

			

		}

	}
//#ifdef DEBUG
	cout << "Saving" << endl;

	cout << stra << endl;
//#endif
	writefile(stra);

	return stra;

}

/*  

std::string settingstostring() {
	std::string stra;
	int val = MAXVALUEMENU;
	for (int i = 0; i < val ; i++) {
		int mena;
		switch (i) {
		case 0:
			mena = MAXVALUERAGE;
		case 1:
			mena = MAXVALUELEGIT;
		case 2: 
			mena = MAXVALUEVISUALS;
		case 3: 
			mena = MAXVALUEMISC;
		case 4:
			mena = MAXVALUEOTHER;

		}
		for (int a = 0; a < mena; a++) {
			stra.append(to_string(i));
			stra.append("-"); 
			stra.append(to_string(a));
			stra.append("-");
			int settingval = SettingsArray[i][a];
			stra.append(to_string(settingval));
			stra.append(" ");

		}

	}
	return stra;
}


 //LOADING 

void uploadstringg(int id, int setting, char* upload)
{
	CURL *curl;
	CURLcode res;
	std::string content;

	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "http://sikhaks.com/csgo_internal/cloudconfigs.php");
		char *idd = strcat("id=", (char *)id);
		char *set = strcat("settings=", (char *)setting);
		
		char *uploadd= strcat("upload=", upload);
		char *barr = strcat(idd, set);
		char *var = strcat(barr, uploadd);

		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, var);
		res = curl_easy_perform(curl);

		// Check for errors 
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}

std::string getvalue(int id, int setting)
{
	CURL *curl;
	CURLcode res;
	std::string content;

	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "http://sikhaks.com/csgo_internal/cloudconfigs.php");
		char *idd = strcat("id=", (char *)id);
		char *set = strcat("settings=", (char *)setting);
		char *var = strcat(idd, set);

		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, var);
		res = curl_easy_perform(curl);

		// Check for errors 
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	ostringstream out;
	out << res;

	content = out.str();

	return content;
}

void savesettings(int settings) {
	std::string toupload = settingstostring();

}

void loadsettings(int settings) {
	std::string valas = "1"; //getvalue(1, settings);
	char *tosend = &valas[0u];
	loadSettings(tosend);
}
void cloudLoadLegit(){
    
    
}

*/