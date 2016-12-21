#include "hwutils.h"
#include "stdafx.h"
#include <wininet.h>
#include <cstring>
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <urlmon.h>
#include <ctype.h>

extern bool Unhook_Cheat;

#pragma comment(lib,"wininet.lib")
#pragma comment(lib, "urlmon.lib")

std::string ReadHWFile() {
	std::ifstream ifs("C:\\h.txt");
	std::string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));
	return content;
}
string serial() {
	DWORD  lVolSerialNbr = 0;
	char sHDSerial[255] = "";
	//nSize = sizeof(cUsername); 
	GetVolumeInformation("C:\\", 0, 0, &lVolSerialNbr, 0, 0, 0, 0); 
	_ultoa(lVolSerialNbr, sHDSerial, 10); 
	std::string c(sHDSerial); 
	return c;
}

int encrypt(float Xv, int Bv) {
	int x = Xv;
	int B = 3; Bv % 21;
	//int y = (((((((x) ^ 2)*2.7 - 44) + B*(x / 32.3) * 81 + cos(x) - sin(x ^ 3 + B)*B*x) / (421)) - x)*(2.3)*sin(x) + 2 * cos(x)*cos(x) - (B*x) / 3 + cos(x) * 13)*10;
	int y = (x * 3);
	return abs(y);
}
bool jakeschecks() {
	IStream* pStream = NULL;
	string var1 = ReadHWFile();
	string var2 = serial();
	int Xv = rand() % 40000;
	int Bv = (atoi(var2.c_str()));
	int encrypts = encrypt(Xv, Bv);

	string var3 = "1";
	string website = "http://dingosquad.net/antic.php?var1=";
	website.append(var1).append("&var2=").append(var2).append("&var3=").append(var3).append("&var4=").append(to_string(Xv));
	LPCSTR lpcstr = website.c_str();
	//cout << website << endl;
	if (SUCCEEDED(URLOpenBlockingStream(0, lpcstr, &pStream, 0, 0))) {
		pStream->Release();
		HINTERNET connect = InternetOpen("MyBrowser", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);

		HINTERNET OpenAddress = InternetOpenUrl(connect, lpcstr, NULL, 0, INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_KEEP_CONNECTION, 0);

		if (!OpenAddress) {
			InternetCloseHandle(connect);
			return true;
		}
		char DataReceived[100];
		DWORD NumberOfBytesRead = 0;
		while (InternetReadFile(OpenAddress, DataReceived, 100, &NumberOfBytesRead) && NumberOfBytesRead) {}

		InternetCloseHandle(OpenAddress);
		InternetCloseHandle(connect);
		//cout << "DR " << DataReceived << endl;
		stringstream value;
		for (int i = 0; i < 20; i++) {
			if (DataReceived[i] == '0' || DataReceived[i] == '1' || DataReceived[i] == '2' || DataReceived[i] == '3' || DataReceived[i] == '4' || DataReceived[i] == '5' || DataReceived[i] == '6' || DataReceived[i] == '7' || DataReceived[i] == '8' || DataReceived[i] == '9')
				value << DataReceived[i];
		}
		string encc(value.str());
		int encryptedint;
		value >> encryptedint;
		//cout << encryptedint << endl;
		int decrypted = encryptedint;
		//cout << "De: " << (decrypted) << " Ekey: " << encrypts << endl;
		if (strstr(DataReceived, "7767")) {
			return true;
		}
		else {
			Unhook_Cheat = true;
			return false;

		}
	

	}
	else {
		return true;

	}
	return true;
}

bool DoesHWIDMatch() {
	HINTERNET connect = InternetOpen("MyBrowser", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);

	if (!connect)
		return false;

	std::string URL = "http://lolihook.xyz/panel/loader/ishwidbanned.php?hwid=" + ReadHWFile();
	LPCSTR Final = URL.c_str();

	HINTERNET OpenAddress = InternetOpenUrl(connect, Final, NULL, 0, INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_KEEP_CONNECTION, 0);

	if (!OpenAddress) {
		InternetCloseHandle(connect);
		return false;
	}

	char DataReceived[4096];
	DWORD NumberOfBytesRead = 0;
	while (InternetReadFile(OpenAddress, DataReceived, 4096, &NumberOfBytesRead) && NumberOfBytesRead) {}

	InternetCloseHandle(OpenAddress);
	InternetCloseHandle(connect);

	if (strstr(DataReceived, "booyah") || strstr(DataReceived, "Yes")) {
		return false;
	}

	return true;
}