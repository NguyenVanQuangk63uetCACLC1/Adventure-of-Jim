#pragma once
#ifndef THREAT_OBJECT_H_
#define THREAT_OBJECT_H_

#include "CommonFunction_CHUNG_.h"
#include "BaseObject.h"
#include "BulletObject.h"

#define THREAT_FRAME_NUMBER 8
#define THREAT_GRAVITY_SPEED 1
#define THREAT_MAX_FALL_SPEED 20
#define THREAT_SPEED 5 //TỐC ĐỘ QUÁI

class ThreatObject:public BaseObject
{
public:
	ThreatObject();
	~ThreatObject();

	enum TypeMove
	{

		STATIC_THREAT = 0,
	    MOVE_IN_SPACE_THREAT = 1,

	};

	void Set_x_val(const float& xVal)
	{
		x_val_ = xVal;
	}
	void Set_y_val(const float& yVal)
	{
		y_val_ = yVal;
	}
	//....................................
	void Set_x_pos(const float& xPos)
	{
		x_pos_ = xPos;
	}
	void Set_y_pos(const float& yPos)
	{
		y_pos_ = yPos;
	}
	float Get_x_pos()
	{
		return x_pos_;
	}
	float Get_y_pos()
	{
		return y_pos_;
	}
	//...............................
	int Get_width_frame()
	{
		return width_frame_;
	}
	int Get_heigh_frame()
	{
		return heigh_frame_;
	}
	//............................
	void DOplayer(Map& gMap);

	void CheckToMap(Map& gMap);

	void SetMapXY(const int& mp_x, const int& mp_y)
	{
		map_x_ = mp_x;
		map_y_ = mp_y;
	}

	void Set_clip();
	bool LoadImg(string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);

	void Set_type_move(const int& typeMove)
	{
		type_move_ = typeMove;
	}
	void Set_animation_POS(const int& pos_a, const int& pos_b)
	{
		animation_a_ = pos_a;
		animation_b_ = pos_b;
	}
	void Set_input_left(const int ipLeft)
	{
		input_type_.left_ = ipLeft;
	} 
	void ImpMoveType(SDL_Renderer* screen);

	void InitThreat();

	std::vector<BulletObject*> Get_bullet_list()
	{
		return bullet_list_;
	}
	void Set_bullet_list(const std::vector<BulletObject*>& bl_list)
	{
		bullet_list_ = bl_list;
	}

	void InitBullet(BulletObject* p_bullet, SDL_Renderer* screen);
	void MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit);
	void ReMoveBullet(const int& idx);
	SDL_Rect ThreatObject::GetRectFrame();

private:
	int frame_;
	int width_frame_;
	int heigh_frame_;

	SDL_Rect frame_clip_[THREAT_FRAME_NUMBER];

	bool on_ground_;
	int come_back_time_;
	float x_pos_, y_pos_;
	float x_val_, y_val_;
	int map_x_, map_y_; //hai mép bản đồ
	
	int type_move_; 
	int animation_a_;
	int animation_b_;
	Input input_type_;

	std::vector<BulletObject*> bullet_list_;
	
};



#endif