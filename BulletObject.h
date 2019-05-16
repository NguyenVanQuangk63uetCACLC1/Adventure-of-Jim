#pragma once
#ifndef	BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include "CommonFunction_CHUNG_.h"
#include "BaseObject.h"

class BulletObject : public BaseObject
{
public:
	BulletObject();
	~BulletObject();
	enum Bulletdirection
	{
		DIR_LEFT_ = 21, DIR_RIGHT_ = 20,

	};

	enum BulletType
	{
		CIRCLE_BULLET = 50,
		LASER_BULLET = 51,
	};

	void Set_x_val_(const int& xVal)
	{
		x_val_ = xVal;
	}
	void Set_y_val_(const int& yVal)
	{
		y_val_ = yVal;
	}
	int Get_x_val()
	{
		return x_val_;
	}
	int Get_y_val()
	{
		return y_val_;
	}
	void Set_is_move(const bool& isMove)
	{
		is_move_ = isMove;
	}
	bool Get_is_move()
	{
		return is_move_;
	}
	void Set_bullet_direction(const int& bullet_dir)
	{
		bullet_direction_ = bullet_dir;
	}
	int Get_bullet_direction()
	{
		return bullet_direction_;
	}

	//hàm xử lí di chuyển cho đạn
	void HandleMove(const int& x_lim_, const int& y_lim_);

	void Set_bullet_type(const int& bulletType)
	{
		bullet_type_ = bulletType;
	}
	int Get_bullet_type()
	{
		return bullet_type_;
	}

	//HÀM LOAD HÌNH ẢNH ĐẠN
	bool LoadImgBullet(SDL_Renderer* des);

private:
	int x_val_;
	int y_val_;
	bool is_move_;	//có di chuyển k -> dùng để xoá đạn
	int bullet_direction_;
	int bullet_type_;

};



#endif
