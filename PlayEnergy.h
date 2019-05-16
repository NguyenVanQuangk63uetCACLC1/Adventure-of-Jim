#pragma once
#ifndef PLAY_ENERGY_H_
#define PLAY_ENERGY_H_

#include "CommonFunction_CHUNG_.h"
#include "BaseObject.h"

class PlayEnergy :public BaseObject		//chỉ số sinh mệnh
{
public:
	PlayEnergy();
	~PlayEnergy();

	void SetNumber(const int& num)
	{
		number_ = num;
	}
	void AddPos(const int& xPos);
	void Show(SDL_Renderer* screen);
	void Init(SDL_Renderer* screen);
	void InitCrease();
	void Decrease();

private:
	int number_;
	std::vector<int> pos_list_;

};

class PlayDiamond :public BaseObject
{
public:
	PlayDiamond();
	~PlayDiamond();

	void Init(SDL_Renderer* screen);
	void Show(SDL_Renderer* screen);
	void SetPOS(const int& x, const int& y)
	{
		x_pos = x;
		y_pos = y;
	}
private:
	int x_pos;
	int y_pos;
};

#endif