#define WIN32_LEAN_AND_MEAN
#include <Windows.h>;
#include <tchar.h>;
#include <chrono>;
#include <thread>;
#include "Monitors.h";


static unsigned int sleep_minutes = 5;


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
	std::this_thread::sleep_for(std::chrono::minutes(sleep_minutes));
	PowerOffMonitor();
	CloseBrowsers();
}