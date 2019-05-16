#include "stdafx.h"
#include "PlayEnergy.h"

PlayEnergy::PlayEnergy()
{
	number_ = 0;
}

PlayEnergy::~PlayEnergy()
{

}

void PlayEnergy::Init(SDL_Renderer* screen)
{
	LoadImg("file_hinh_anh_img//player2_pw.png", screen);
	number_ = NUM_DIE;
	if (pos_list_.size() > 0)
	{
		pos_list_.clear();

	}
	AddPos(20);
	AddPos(60);
	AddPos(100);
}

void PlayEnergy::AddPos(const int& xPos)
{
	pos_list_.push_back(xPos);
}

void PlayEnergy::Show(SDL_Renderer* screen)
{
	for (int i = 0; i < pos_list_.size(); i++)
	{
		rect_.x = pos_list_.at(i);
		rect_.y = 0;
		Render(screen);
	}
}

void PlayEnergy::Decrease()	//giảm mạng
{
	number_--;
	pos_list_.pop_back();
}

void PlayEnergy::InitCrease()
{
	number_++;
	int last_pos = pos_list_.back();	//lấy vị trí cuối cùng
	last_pos += 40;	//mỗi ô mạng cách nhau 40
	pos_list_.push_back(last_pos);
}

PlayDiamond::PlayDiamond()
{
	x_pos = 0;
	y_pos = 0;
}

PlayDiamond::~PlayDiamond()
{

}

void PlayDiamond::Init(SDL_Renderer* screen)
{
	bool ret = LoadImg("file_hinh_anh_img//diamond.png", screen);
}

void PlayDiamond::Show(SDL_Renderer* screen)
{
	rect_.x = x_pos;
	rect_.y = y_pos;
	Render(screen);
}
