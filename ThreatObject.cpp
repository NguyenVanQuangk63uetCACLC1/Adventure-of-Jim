#include "stdafx.h"
#include "ThreatObject.h"

ThreatObject::ThreatObject()
{
	width_frame_ = 0;
	heigh_frame_ = 0;
	x_val_ = 0;
	y_val_ = 0;
	x_pos_ = 0;
	y_pos_ = 0;
	on_ground_ = false;
	come_back_time_ = 0;
	frame_ = 0;
	 
	animation_a_ = 0;
	animation_b_ = 0;
	input_type_.left_ = 0;	//đối tượng mặc định bằng 0, nếu là đối tượng tĩnh thì thay đổi sau
	type_move_ = STATIC_THREAT; 
}

ThreatObject::~ThreatObject()
{

}

bool ThreatObject::LoadImg(string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret == true)
	{
		width_frame_ = rect_.w / THREAT_FRAME_NUMBER;
		heigh_frame_ = rect_.h;
	}
	return ret;
}

void ThreatObject::Set_clip()
{
	if (width_frame_ > 0 && heigh_frame_ > 0)
	{
		frame_clip_[0].x = 0;
		frame_clip_[0].y = 0;
		frame_clip_[0].w = width_frame_;
		frame_clip_[0].h = heigh_frame_;

		frame_clip_[1].x = width_frame_;
		frame_clip_[1].y = 0;
		frame_clip_[1].w = width_frame_;
		frame_clip_[1].h = heigh_frame_;

		frame_clip_[2].x = 2 * width_frame_;
		frame_clip_[2].y = 0;
		frame_clip_[2].w = width_frame_;
		frame_clip_[2].h = heigh_frame_;

		frame_clip_[3].x = 3 * width_frame_;
		frame_clip_[3].y = 0;
		frame_clip_[3].w = width_frame_;
		frame_clip_[3].h = heigh_frame_;

		frame_clip_[4].x = 4 * width_frame_;
		frame_clip_[4].y = 0;
		frame_clip_[4].w = width_frame_;
		frame_clip_[4].h = heigh_frame_;


		frame_clip_[5].x = 5 * width_frame_;
		frame_clip_[5].y = 0;
		frame_clip_[5].w = width_frame_;
		frame_clip_[5].h = heigh_frame_;

		frame_clip_[6].x = 6 * width_frame_;
		frame_clip_[6].y = 0;
		frame_clip_[6].w = width_frame_;
		frame_clip_[6].h = heigh_frame_;

		frame_clip_[7].x = 7 * width_frame_;
		frame_clip_[7].y = 0;
		frame_clip_[7].w = width_frame_;
		frame_clip_[7].h = heigh_frame_;
	}
}

void ThreatObject::Show(SDL_Renderer* des)
{
	if (come_back_time_ == 0)
	{
		rect_.x = x_pos_ - map_x_;
		rect_.y = y_pos_ - map_y_;
		frame_++;	//không cần bấm nút
		if (frame_ >= 8)
		{
			frame_ = 0;
		}
		SDL_Rect* current_Clip = &frame_clip_[frame_];
		SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_,heigh_frame_ };
		SDL_RenderCopy(des, p_object_,current_Clip, &renderQuad);

	}
}

void ThreatObject::DOplayer(Map& gMap)
{
	if (come_back_time_ == 0)
	{
		x_val_ = 0;
		y_val_ += THREAT_GRAVITY_SPEED;
		if (y_val_ >= THREAT_MAX_FALL_SPEED)
		{
			y_val_ = THREAT_MAX_FALL_SPEED;
		}

		if (input_type_.left_ == 1)
		{
			x_val_ -= THREAT_SPEED;	//TỐC ĐỘ QUÁI
		}
		else if (input_type_.right_ == 1)
		{
			x_val_ += THREAT_SPEED;
		}

		CheckToMap(gMap);

	}
	else if (come_back_time_ > 0)
	{										
		come_back_time_--;
		if (come_back_time_ == 0)
		{
			InitThreat();
		}
	}
}
void ThreatObject::InitThreat()
{
	x_val_ = 0;
	y_val_ = 0;
	if (x_pos_ > 64 * 4)	//4 ô tilemap
	{
		x_pos_ -= 64 * 4;
		animation_a_ -= 64 * 4;
		animation_b_ -= 64 * 4;
	}
	else
	{
		x_pos_ = 0;
	}
	y_pos_ = 0;
	come_back_time_ = 0;
	input_type_.left_ = 1;
}

void ThreatObject::ReMoveBullet(const int& idx)
{
	int size = bullet_list_.size();	//ktra xem băng có đạn k
	if (size > 0 && idx < size)
	{
		BulletObject* p_bullet = bullet_list_.at(idx);
		bullet_list_.erase(bullet_list_.begin() + idx);
		if (p_bullet)
		{
			delete p_bullet;
			p_bullet = NULL;
		}
	}
}

void ThreatObject::CheckToMap(Map& gMap)
{
	/*
	có nhiều trường hợp:
	rơi chạm map
	chạm chướng ngại vật
	chạm vực
	*/

	int x1 = 0;	//giới hạn kiểm tra từ A đến B theo chiều x
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	// check chiều ngang: nhân vật đang nằm từ ô thứ bao nhiêu đến ô thứ bao nhiêu trên bản đồ
	int heigh_min = heigh_frame_ < TILE_SIZE_ ? heigh_frame_ : TILE_SIZE_;	//so sánh chiều cao của nhân vật với tilesize và heigh_min sẽ gán bằng cái nhỏ hơn

	x1 = (x_pos_ + x_val_) / TILE_SIZE_;	//Ô THỨ BAO NHIÊU
	x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE_;	// 0.5 là sai số

	y1 = (y_pos_ + y_val_) / TILE_SIZE_;
	y2 = (y_pos_ + heigh_frame_ - 1) / TILE_SIZE_;

	if (x1 >= 0 && x2 <= MAP_MAX_X && y1 >= 0 && y2 <= MAP_MAX_Y)	//NHÂN VẬT NẰM TRONG PHẦN BẢN ĐỒ
	{

		if (x_val_ > 0)	// di chuyển sang phải
		{
			//XỬ LÍ Ô HỖ TRỢ
			int val1 = gMap.tile[y1][x2];
			int val2 = gMap.tile[y2][x2];
			
			if ((val1 != BLANK_TILE && val1 != DIAMOND) || (val2 != BLANK_TILE && val2 != DIAMOND))	//ô khác ô trống ( ô trống kí hiệu là 0 )
			{
				x_pos_ = x2 * TILE_SIZE_;
				x_pos_ -= width_frame_ + 1;
				x_val_ = 0;
			}
		}
		else if (x_val_ < 0)	//di chuyển sang trái
		{
			int val1 = gMap.tile[y1][x1];
			int val2 = gMap.tile[y2][x1];

			if ((val1 != BLANK_TILE && val1 != DIAMOND) || (val2 != BLANK_TILE && val2 != DIAMOND))
			{
				x_pos_ = (x1 + 1) * TILE_SIZE_;
				x_val_ = 0;
			}

		}
	}

	//check theo chiều dọc
	int width_min = width_frame_ < TILE_SIZE_ ? width_frame_ : TILE_SIZE_;
	x1 = x_pos_ / TILE_SIZE_;
	x2 = (x_pos_ + width_frame_) / TILE_SIZE_;

	y1 = (y_pos_ + y_val_) / TILE_SIZE_;
	y2 = (y_pos_ + y_val_ + heigh_frame_ - 1) / TILE_SIZE_;

	if (x1 >= 0 && x2 <= MAP_MAX_X && y1 >= 0 && y2 <= MAP_MAX_Y)
	{
		if (y_val_ >= 0)
		{
			int val1 = gMap.tile[y2][x1];
			int val2 = gMap.tile[y2][x2];
		
			if ((val1 != BLANK_TILE && val1 != DIAMOND) || (val2 != BLANK_TILE && val2 != DIAMOND))
			{
				y_pos_ = y2 * TILE_SIZE_;
				y_pos_ -= heigh_frame_ + 1;
				y_val_ = 0;

				on_ground_ = true;	//lúc này đang trên mặt đất
			}

		}
		else if (y_val_ < 0)
		{
			int val1 = gMap.tile[y1][x1];
			int val2 = gMap.tile[y1][x2];
		
			if ((val1 != BLANK_TILE && val1 != DIAMOND) || (val2 != BLANK_TILE && val2 != DIAMOND))
			{
				y_pos_ = (y1 + 1) * TILE_SIZE_;
				y_val_ = 0;
			}

		}
	}
	//nếu các trường hợp trên không xảy ra thì đi bình thường
	x_pos_ += x_val_;
	y_pos_ += y_val_;
	if (x_pos_ < 0)
	{
		x_pos_ = 0;		//ko cho lùi nx
	}
	else if (x_pos_ + width_frame_ > gMap.max_x_)
	{
		x_pos_ = gMap.max_x_ - width_frame_ - 1;


	}
	if (y_pos_ > gMap.max_y_)	// thời gian delay
	{
		come_back_time_ = 60;
	}
}

void ThreatObject::ImpMoveType(SDL_Renderer* screen)
{
	if (type_move_ == STATIC_THREAT)
	{
		; //
	}
	else
	{
		if (on_ground_ == true)
		{
			if (x_pos_ > animation_b_)
			{
				input_type_.left_ = 1;	//đi quá thì đổi chiều
				input_type_.right_ = 0;
				LoadImg("file_hinh_anh_img//Threat_red_bird_left.png", screen); 

			}
			else if (x_pos_ < animation_a_)
			{
				input_type_.left_ = 0;
				input_type_.right_ = 1;
				LoadImg("file_hinh_anh_img//Threat_red_bird_right.png", screen);
			}
		}
		else
		{
			if (input_type_.left_ == 1)
			{
				LoadImg("file_hinh_anh_img//threat_left.png", screen);
			}
		}
	}
}

void ThreatObject::InitBullet(BulletObject* p_bullet, SDL_Renderer* screen)
{
	if (p_bullet != NULL)
	{
		//bool ret = p_bullet.loadImg("file_hinh_anh_img//bullet01.png", screen);
		p_bullet->Set_bullet_type(BulletObject::CIRCLE_BULLET);
		bool ret = p_bullet->LoadImgBullet(screen);
		if (ret)
		{
			p_bullet->Set_is_move(true);
			p_bullet->Set_bullet_direction(BulletObject::DIR_LEFT_);
			p_bullet->SetRect(rect_.x + 5, rect_.y + 10);
			p_bullet->Set_x_val_(15);
			bullet_list_.push_back(p_bullet);
		}
		
	}
}

void ThreatObject::MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit)
{
	for (int i = 0; i < bullet_list_.size(); i++)
	{
		BulletObject* p_bullet = bullet_list_.at(i);
		if (p_bullet != NULL)
		{
			if (p_bullet->Get_is_move())
			{
				int distant_allow_bullet = rect_.x + width_frame_ - p_bullet->GetRect().x;
				if (distant_allow_bullet < 300 && distant_allow_bullet > 0)
				{
					p_bullet->HandleMove(x_limit, y_limit);
					p_bullet->Render(screen);
				}
				else
				{
					p_bullet->Set_is_move(false);	//cho đạn biến mất
				}

			}
			else
			{
				p_bullet->Set_is_move(true);
				p_bullet->SetRect(rect_.x + 5, rect_.y + 10);
			}
		}
	}
}

SDL_Rect ThreatObject::GetRectFrame()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = width_frame_;
	rect.h = heigh_frame_;
	return rect;
}