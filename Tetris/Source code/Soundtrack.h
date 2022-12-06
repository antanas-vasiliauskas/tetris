#pragma once
#include <Windows.h>
#pragma comment(lib, "Winmm.lib")

#include <chrono>

class Soundtrack
{
private: 
	int length;
	int currentTrack;
	int startTime;
public:
	void _PlaySound(int Netinkamasis);
	void _StopSound();
	void _ChangeSound();
	void _CheckSound();
	void _ChangeVolume(int volumeproc);
};

