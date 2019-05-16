#include "stdafx.h"
#include "Time.h"
#include "CommonFunction_CHUNG_.h"

Time::Time()
{
	start_tick_ = 0;
	pause_tick_ = 0;
	is_paused_ = false;
	is_started_ = false;
}

Time::~Time()
{

}

void Time::start()
{
	is_started_ = true;
	is_paused_ = false;
	start_tick_ = SDL_GetTicks();	//hàm lấy thời gian
	
}

void Time::stop()
{
	is_paused_ = false;
	is_started_ = false;
}

void Time::pause()
{

	if (is_started_ == true && is_paused_ == false)
	{
		is_paused_ = true;
		pause_tick_ = SDL_GetTicks() - start_tick_ ;	//HÀM LẤY THỜI GIAN HIỆN TẠI
	}
}

void Time::stopPause()
{
	if (is_paused_ == true)
	{
		start_tick_ = SDL_GetTicks() - pause_tick_;
		pause_tick_ = 0;
	}
}

int Time::get_tick()
{
	if (is_started_ == true)
	{
		if (is_paused_ == true)
		{
			return pause_tick_;
		}
	}
	else
	{
		return SDL_GetTicks() - start_tick_;	//ví dụ 7-5=2
	}
	return 0;
}

bool Time::is_started()
{
	return is_started_;
}

bool Time::is_pause()
{
	return is_paused_;
}
