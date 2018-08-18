// Monitors class taken from, http://www.vilipetek.com/2014/06/18/turn-off-monitor-power-in-windows-using-ddcci-c/

#include "Monitors.h"
#include <lowlevelmonitorconfigurationapi.h>

// load the relevant libary
#pragma comment(lib, "Dxva2.lib")

Monitors::Monitors()
{
	// get the list of monitors
	EnumDisplayMonitors(NULL, NULL, Monitors::MonitorEnumProc,
		reinterpret_cast<LPARAM>(&m_oMonitors));
}

Monitors::~Monitors()
{
	// release the monitor handles
	for (auto hMonitor : m_oMonitors)
	{
		DestroyPhysicalMonitor(hMonitor);
	}
}

// A static callback used for retrieving the list of monitors
// Called by the EnumDisplayMonitors() method used in Monitors class constructor
BOOL CALLBACK Monitors::MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor,
	LPRECT lprcMonitor, LPARAM dwData)
{
	std::set<HANDLE>* pMonitors = reinterpret_cast<std::set<HANDLE>*>(dwData);
	DWORD nMonitorCount;

	if (GetNumberOfPhysicalMonitorsFromHMONITOR(hMonitor, &nMonitorCount))
	{
		PHYSICAL_MONITOR* pMons = new PHYSICAL_MONITOR[nMonitorCount];

		if (GetPhysicalMonitorsFromHMONITOR(hMonitor, nMonitorCount, pMons))
		{
			for (DWORD i = 0; i < nMonitorCount; i++)
			{
				pMonitors->insert(pMons[i].hPhysicalMonitor);
			}
		}
		delete[] pMons;
	}

	return TRUE;
}

// Set power mode of the monitor using DDC/CI
// param:
//		nPower	Power::<On, Standby, Suspend, Off, HardOff>
void Monitors::SetPower(Power nPower)
{
	const BYTE PowerMode = 0xD6;

	for (auto hMonitor : m_oMonitors)
	{
		SetVCPFeature(hMonitor, PowerMode, nPower);
	}
}
