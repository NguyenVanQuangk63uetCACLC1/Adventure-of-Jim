#pragma once

#ifndef EXPLOSION_OBJECT_H_
#define EXPLOSION_OBJECT_H_

#include "CommonFunction_CHUNG_.h"
#include "BaseObject.h"
#include "BulletObject.h"

#define NUM_FRAME_EXP 8

class ExplosionObject : public BaseObject
{
public:
	ExplosionObject();
	~ExplosionObject();

public:
	void set_clip();
	void set_frame(const int& fr)
	{
		frame_ = fr;
	}
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* screen);
	int get_frame_width()
	{
		return frame_width_;
	}
	int get_frame_heigh()
	{
		return frame_heigh_;
	}
private:
	int frame_width_;
	int frame_heigh_;
	unsigned int frame_;
	SDL_Rect frame_clip_[8];


};


#endif