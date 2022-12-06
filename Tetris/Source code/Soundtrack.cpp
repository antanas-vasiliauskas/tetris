#include "Soundtrack.h"

#include <iostream>
void Soundtrack::_PlaySound(int Netinkamasis)
{
	int Random = Netinkamasis;
	for (int i = 0; i < 3 && Random == Netinkamasis; i++);
		Random = (rand() + clock()) % 3;
	if (Random == Netinkamasis)
	{
		Random++;
		if (Random > 2) Random = 0;
	}
	mciSendString("close mp3", NULL, 0, NULL);
	if (Random == 0)
	{
		mciSendString("open \"Soundtrack/Toccata and Fugue in D Minor.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
		mciSendString("play mp3", NULL, 0, NULL);
		length = 525000;
		startTime = clock();
	}
	else if(Random == 1)
	{
		mciSendString("open \"Soundtrack/Hall of the Mountain King.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
		mciSendString("play mp3", NULL, 0, NULL);
		length = 155000;
		startTime = clock();
	}
	else
	{	
		mciSendString("open \"Soundtrack/Korobeiniki.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
		mciSendString("play mp3", NULL, 0, NULL);
		length = 60000;
		startTime = clock();
	}
	currentTrack = Random;
}

void Soundtrack::_StopSound()
{
	mciSendString("close mp3", NULL, 0, NULL);
}

void Soundtrack::_ChangeSound()
{
	currentTrack++;
	if (currentTrack > 2) currentTrack = 0;

	mciSendString("close mp3", NULL, 0, NULL);
	if (currentTrack == 0)
	{
		mciSendString("open \"Soundtrack/Toccata and Fugue in D Minor.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
		mciSendString("play mp3", NULL, 0, NULL);
		length = 525000;
		startTime = clock();
	}
	else if (currentTrack == 1)
	{
		mciSendString("open \"Soundtrack/Hall of the Mountain King.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
		mciSendString("play mp3", NULL, 0, NULL);
		length = 155000;
		startTime = clock();
	}
	else
	{
		mciSendString("open \"Soundtrack/Korobeiniki.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
		mciSendString("play mp3", NULL, 0, NULL);
		length = 60000;
		startTime = clock();
	}
}

void Soundtrack::_CheckSound()
{
	if (clock() - startTime > length)
		_PlaySound(currentTrack);
}

void Soundtrack::_ChangeVolume(int volumeproc)
{
	int volume = 65535 * volumeproc / 100;
	volume = volume << 16 | volume;
	waveOutSetVolume(NULL, volume);
}
