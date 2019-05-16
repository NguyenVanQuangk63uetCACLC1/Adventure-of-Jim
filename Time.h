#pragma once
#ifndef TIME_H_
#define TIME_H_

class Time
{
public:
	Time();
	~Time();
	void start();
	void stop();
	void pause();
	void stopPause();
	int get_tick();
	bool is_started();
	bool is_pause();

private:
	int start_tick_;
	int pause_tick_;
	bool is_paused_;
	bool is_started_;

};

#endif // TIME_H_
