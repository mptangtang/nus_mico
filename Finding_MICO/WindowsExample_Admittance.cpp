
#include <Windows.h>
#include "CommunicationLayerWindows.h"
#include "CommandLayer.h"
#include <conio.h>
#include "KinovaTypes.h"
#include <iostream>
#include <time.h>
#include <fstream>


using namespace std;

//A handle to the API.
HINSTANCE commandLayer_handle;

//Function pointers to the functions we need
int(*MyInitAPI)();
int(*MyCloseAPI)();
int(*MyStartForceControl)();
int(*MyGetDevices)(KinovaDevice devices[MAX_KINOVA_DEVICE], int &result);
int(*MySetActiveDevice)(KinovaDevice device);
int(*MyGetGlobalTrajectoryInfo)(TrajectoryFIFO &Response);
int(*MyRunGravityZEstimationSequence)(ROBOT_TYPE type, double OptimalzParam[OPTIMAL_Z_PARAM_SIZE]);

int main(int argc, char* argv[])
{
	int programResult = 0;
	int result;
	
	//We load the API.
	commandLayer_handle = LoadLibrary(L"CommandLayerWindows.dll");

	//We load the functions from the library (Under Windows, use GetProcAddress)
	MyInitAPI = (int(*)()) GetProcAddress(commandLayer_handle, "InitAPI");
	MyCloseAPI = (int(*)()) GetProcAddress(commandLayer_handle, "CloseAPI");
	MyStartForceControl = (int(*)()) GetProcAddress(commandLayer_handle, "StartForceControl");
	MyGetDevices = (int(*)(KinovaDevice devices[MAX_KINOVA_DEVICE], int &result)) GetProcAddress(commandLayer_handle, "GetDevices");
	MySetActiveDevice = (int(*)(KinovaDevice devices)) GetProcAddress(commandLayer_handle, "SetActiveDevice");
	MyGetGlobalTrajectoryInfo = (int(*)(TrajectoryFIFO&)) GetProcAddress(commandLayer_handle, "GetGlobalTrajectoryInfo");
	MyRunGravityZEstimationSequence = (int(*)(ROBOT_TYPE type, double OptimalzParam[OPTIMAL_Z_PARAM_SIZE])) GetProcAddress(commandLayer_handle, "RunGravityZEstimationSequence");

	//If the was loaded correctly
	if ((MyInitAPI == NULL) || (MyCloseAPI == NULL)
		|| (MySetActiveDevice == NULL) || (MyGetDevices == NULL))
	{
		cout << "* * *  E R R O R   D U R I N G   I N I T I A L I Z A T I O N  * * *" << endl;
		programResult = 0;
	}
	else
	{
		cout << "I N I T I A L I Z A T I O N   C O M P L E T E D" << endl << endl;

		result = (*MyInitAPI)();

		cout << "Initialization's result :" << result << endl;

		KinovaDevice list[MAX_KINOVA_DEVICE];

		TrajectoryFIFO info;
		
		int devicesCount = MyGetDevices(list, result);

		for (int i = 0; i < devicesCount; i++)
		{
		cout << "Found a robot on the USB bus (" << list[i].SerialNumber << ")" << endl;

		//Setting the current device as the active device.
		MySetActiveDevice(list[i]);

		MyStartForceControl();

		cout << endl << "The robot's admittance control is now active, you can move it freely with your hand." <<
		" To deactivate it call the function StopForceControl()." << endl;
		}
		

		cout << endl << "C L O S I N G   A P I" << endl;
		result = (*MyCloseAPI)();
		programResult = 1;

	}

	FreeLibrary(commandLayer_handle);

	return programResult;
}
