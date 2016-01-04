#pragma once
#include "stdafx.h"
#include <thread>
#include <chrono>

typedef DWORD THandle;

class CThreads
{
private:
	void threadInterval();
	int time = 0;
	bool active = false;
	char type = 0;
	std::thread temp;
	void (* function)();
	std::chrono::milliseconds timeOut;
public:
	THandle SetTimeOut(int time, void(*function)());
	THandle SetInterval(int time, void(*function)());

	void changeTime(int time, THandle hand);
	void kill(THandle hand);

	CThreads();
	~CThreads();
};

