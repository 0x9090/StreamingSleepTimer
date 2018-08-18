#define WIN32_LEAN_AND_MEAN
#include <Windows.h>;
#include <tchar.h>;
#include <chrono>;
#include <thread>;
#include <iostream>;
#include <stdio.h>;
#include "Monitors.h";

using std::cout;
using std::cin;
using std::endl;
using std::chrono::minutes;
using std::this_thread::sleep_for;

unsigned int sleep_minutes = 30;

void PowerOffMonitor() {
	Monitors monitors;
	monitors.SetPower(Monitors::Power::Off);
}

void CloseBrowsers() {
	ULONG processID;
	HANDLE processHandle;
	HWND browser = FindWindow(_T("Chrome_WidgetWin_1"), NULL);
	GetWindowThreadProcessId(browser, &processID);
	processHandle = OpenProcess(PROCESS_TERMINATE, FALSE, processID);
	TerminateProcess(processHandle, 4);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char* commandLine, int commandShow) {
	AllocConsole();
	freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	freopen_s((FILE**)stderr, "CONOUT$", "r", stderr);
	cout << "Minutes To Sleep: ";
	cin >> sleep_minutes;
	FreeConsole();
	sleep_for(minutes(sleep_minutes));
	PowerOffMonitor();
	CloseBrowsers();
}