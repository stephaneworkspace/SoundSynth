#include <iostream>
#include <string>
using namespace std;

#include "olcNoiseMaker.h"

/*double calc = 0.5 * sin(440.0 * 2 * 3.14159 * dTime);
string calcString = std::to_string(calc);
wstring wcalcString;
StringToWString(wcalcString, calcString);
wcout << wcalcString << endl;
int StringToWString(std::wstring& ws, const std::string& s)
{
	std::wstring wsTmp(s.begin(), s.end());

	ws = wsTmp;

	return 0;
}*/

double dFrequencyOutput = 0.0;

double MakeNoise(double dTime)
{
	// sin wave
	//return 0.5 * sin(440.0 * 2 * 3.14159 * dTime);
	// Square wave
	double dOutput = 1 * sin(dFrequencyOutput * 2 * 3.14159 * dTime);
	if (dOutput > 0.0)
		return 0.2;
	else
		return -0.2;
}

int main()
{
	wcout << "Synth - Part 1" << endl;

	// Get all sound hardware
	vector<wstring> devices = olcNoiseMaker<short>::Enumerate();

	// Display all device
	for (auto d : devices) wcout << "Found output device:" << d << endl;

	// Create sound machine
	olcNoiseMaker<short> sound(devices[0], 44100, 1, 8, 512);

	// Link noise function with sound machine
	sound.SetUserFunction(MakeNoise);

	while (1) 
	{
		// Add a keyboard
		if (GetAsyncKeyState('A') & 0x8000)
		{
			dFrequencyOutput = 440.0;
		}
		else
		{
			dFrequencyOutput = 0.0;
		}
	}

	return 0;
}