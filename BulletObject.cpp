#include "stdafx.h"
#include "BulletObject.h"

BulletObject::BulletObject()
{
	x_val_ = 0;
	y_val_ = 0;
	is_move_ = false;
	bullet_type_ = CIRCLE_BULLET;


}

BulletObject::~BulletObject()
{

}

bool BulletObject::LoadImgBullet(SDL_Renderer* des)
{
	bool ret = false;
	if (bullet_type_ == LASER_BULLET)
	{
		ret = LoadImg("file_hinh_anh_img//laser_bullet.png", des);
	}
	else
	{
		ret = LoadImg("file_hinh_anh_img//bullet2.png", des);
	}
	return ret;
}
void BulletObject::HandleMove(const int& x_lim_ , const int& y_lim_)
{
	if (bullet_direction_ == DIR_RIGHT_)
	{
		rect_.x += x_val_;
		if (rect_.x > x_lim_)
		{
			is_move_ = false;
		}
	}
	else if( bullet_direction_ == DIR_LEFT_)
	{
		rect_.x -= x_val_;
		if (rect_.x < 0)
		{
			is_move_ = false;
		}

	}
}