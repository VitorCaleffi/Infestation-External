#include "Threads.h"

void CThreads::threadInterval()
{
	while (1)
	{
		if (this->type == 1 || !this->active)
			return;

		std::this_thread::sleep_for(timeOut);

		this->function();
	}
}

THandle CThreads::SetTimeOut(int time, void (*function)())
{
	this->type = 1;
	this->active = true;
	this->time = time;
	this->function = function;

	timeOut = std::chrono::milliseconds(time);

	temp = std::thread(&CThreads::threadInterval, this);
	temp.detach();

	return 1;
}

THandle CThreads::SetInterval(int time, void(*function)())
{
	this->type = 2;
	this->active = true;
	this->time = time;
	this->function = function;

	timeOut = std::chrono::milliseconds(time);

	temp = std::thread(&CThreads::threadInterval, this);
	temp.detach();

	return 1;
}

void CThreads::changeTime(int time, THandle hand)
{

}

void CThreads::kill(THandle hand)
{
	this->active = false;
}

CThreads::CThreads()
{
}

CThreads::~CThreads()
{
}