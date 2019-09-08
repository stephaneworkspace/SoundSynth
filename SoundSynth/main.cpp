#include <iostream>
#include <string>

#include <chrono>
#include <thread>
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
	//return 0.5 * sin(dFrequencyOutput * 2 * 3.14159 * dTime);
	// Square wave
	double dOutput = 1 * sin(dFrequencyOutput * 2 * 3.14159 * dTime);
	if (dOutput > 0.0)
		return 0.2;
	else
		return -0.2;
	// Chord sin
	//double dOutput = 1.0 * (sin(dFrequencyOutput * 2 * 3.14159 * dTime) + sin((dFrequencyOutput + 20) * 2.0 * 3.14159 * dTime));
	//return dOutput * 0.4;
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

	//double dOctaveBaseFrequency = 440; // C 110.0; // A2
	double dOctaveBaseFrequency = 432; // A2
	double d12ThRootOF2 = pow(2.0, 1.0 / 12); // puissance

	while (1) 
	{



		/*
		// Add a keyboard like a piano
		bool bKeyPRessed = false;
		for (int k = 0; k < 15; k++)
		{
			if (GetAsyncKeyState((unsigned char)("YSXCFVGBNJMK\xbcL\xbe"[k])) & 0x8000)
			{
				dFrequencyOutput = dOctaveBaseFrequency * pow(d12ThRootOF2, k);
				bKeyPRessed = true;
			}
		}
		if (!bKeyPRessed)
			dFrequencyOutput = 0.0;
			*/

		// 12

		for (int i = 1; i <= 72; i++)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(30));
			dFrequencyOutput = dOctaveBaseFrequency * pow(d12ThRootOF2, i);
		}

		/*
		// Add a keyboard
		if (GetAsyncKeyState('A') & 0x8000)
		{
			//dFrequencyOutput = 440.0;
			//for (int i = 1; i <= 12; i++)
			dFrequencyOutput = dOctaveBaseFrequency * pow(d12ThRootOF2, 0);
		}
		else
		{
			dFrequencyOutput = 0.0;
		}
		*/
	}

	return 0;
}