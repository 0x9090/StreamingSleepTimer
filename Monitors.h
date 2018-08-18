#pragma once
#include <Windows.h>
#include <set>

class Monitors
{
public:
	enum Power { On = 0x01, Standby = 0x02, Suspend = 0x03, Off = 0x04, HardOff = 0x05 };

	Monitors();
	virtual ~Monitors();

	void SetPower(Power nPower);

private:
	static BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor,
		LPRECT lprcMonitor, LPARAM dwData);

private:
	std::set<HANDLE> m_oMonitors;
};
