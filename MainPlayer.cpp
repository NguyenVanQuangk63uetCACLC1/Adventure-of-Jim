	#include "stdafx.h"
#include "MainPlayer.h"

MainPlayer::MainPlayer()
{
	frame_ = 0;	//->	chỉ số của frame
	x_pos_ = 0;	//->	vị trí của nhân vật
	y_pos_ = 0;
	width_frame_ = 0;	// ->chiều dài và chiều rộng của 1 nhân vật
	heigh_frame_ = 0;
	status_ = WALK_BEGIN_;	// ->	trạng thái của nhân vật ( trái hay phải )
	x_val_ = 0;		// ->	di chuyển mọt đoạn bao nhiêu
	y_val_ = 0;
	input_type_.left_ = 0;
	input_type_.right_ = 0;
	input_type_.jump_ = 0;
	input_type_.down_ = 0;
	input_type_.up_ = 0;

	on_ground_ = false;

	map_x_ = 0;	//mép trái bản đồ
	map_y_ = 0; 
	diamond_count = 0;
}

MainPlayer::~MainPlayer()
{

}


bool MainPlayer::LoadImg(std::string path, SDL_Renderer* screen)
{
	//do ở trong BaseObject đã có hàm rồi nên ta sẽ kế thừa nó và chỉ thêm một số tính năng khác vào
	// trong hàm LoadImg ở BaseObject ta thêm từ khóa virtual

	bool ret = BaseObject::LoadImg(path, screen);
	if (ret == true) //load thành công
	{
		//kích thước thật của một frame
		width_frame_ = rect_.w / NUM_PLAYER_FRAME;	//do có 8 frame
		heigh_frame_ = rect_.h;

	}
	return ret;	//?????????
}

//hàm tách từng frame 
/*
  Y
  ^
  |
  | *************
  | | 1| 2| 3| 4|
  | *************
  O----------------> X
*/
void MainPlayer::set_clips()
{

	if (width_frame_ > 0 && heigh_frame_ > 0)	//chiều cao và chiều ngang của nhân vật
	{
		frame_clip_[0].x = 0;
		frame_clip_[0].y = 0;
		frame_clip_[0].w = width_frame_;
		frame_clip_[0].h = heigh_frame_;

		frame_clip_[1].x = width_frame_;
		frame_clip_[1].y = 0;
		frame_clip_[1].w = width_frame_;
		frame_clip_[1].h = heigh_frame_;

		frame_clip_[2].x = 2*width_frame_;
		frame_clip_[2].y = 0;
		frame_clip_[2].w = width_frame_;
		frame_clip_[2].h = heigh_frame_;

		frame_clip_[3].x = 3*width_frame_;
		frame_clip_[3].y = 0;
		frame_clip_[3].w = width_frame_;
		frame_clip_[3].h = heigh_frame_;

		frame_clip_[4].x = 4*width_frame_;
		frame_clip_[4].y = 0;
		frame_clip_[4].w = width_frame_;
		frame_clip_[4].h = heigh_frame_;

		
		frame_clip_[5].x = 5*width_frame_;
		frame_clip_[5].y = 0;
		frame_clip_[5].w = width_frame_;
		frame_clip_[5].h = heigh_frame_;

		/*frame_clip_[6].x = 6*width_frame_;
		frame_clip_[6].y = 0;
		frame_clip_[6].w = width_frame_;
		frame_clip_[6].h = heigh_frame_;

		frame_clip_[7].x = 7*width_frame_;
		frame_clip_[7].y = 0;
		frame_clip_[7].w = width_frame_;
		frame_clip_[7].h = heigh_frame_;
		*/
	}
}

void MainPlayer::Show(SDL_Renderer* des)

{
	UpdateImage(des);	//->cập nhật trạng thái cho nhân vật
	
	if (input_type_.left_ == 1 || input_type_.right_ == 1)		//nếu liên tục bấm thì tăng frame
	{
		frame_++;
	}
	else
	{
		frame_ = 0;
	}

	if (frame_ >= NUM_PLAYER_FRAME)		//nếu frame lớn hơn bằng 8 thì chạy lại từ đầu
	{
		frame_ = 0;
	}
	if (come_back_time_ == 0)
	{
		rect_.x = x_pos_ - map_x_;		//trừ đi vì khi chạy nhân vật thì màn hình bị cuốn chiếu theo, cho nên x_pos_ tính từ mốc ban đầu đến điểm hiện tại
		rect_.y = y_pos_ - map_y_;		//trong khi đó màn hình đang hiển thị từ vị trí map_x trở đi nên phải trừ đi lượng map_x là lượng đã bị cuốn đi

		SDL_Rect* currentclip = &frame_clip_[frame_];

		SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, heigh_frame_ };		//tạo ra kích thước chuẩn nhất

		SDL_RenderCopy(des, p_object_, currentclip, &renderQuad);		//đạt p_object lên des(destop)
	}
	
}

void MainPlayer::HandleInputAction(SDL_Event event, SDL_Renderer* screen)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			status_ = WALK_RIGHT_;
			input_type_.right_ = 1;
			input_type_.left_ = 0;
			UpdateImage(screen);

		}
		break;
		case SDLK_LEFT:
			{
				status_ = WALK_LEFT_;
				input_type_.left_ = 1;
				input_type_.right_ = 0;
				UpdateImage(screen);
				break;
			}
		}

	}
	else if( event.type == SDL_KEYUP )
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			input_type_.right_ = 0;
		}
		break;
		case SDLK_LEFT:
		{
			input_type_.left_ = 0;
		}
		break;
		}
	}

	//xử lí nhảy cho nhân vật trong hàm handleinputaction
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_RIGHT)	//NÚT PHẢI
		{
			input_type_.jump_ = 1;
		}
		else if (event.button.button == SDL_BUTTON_LEFT)
		{
			BulletObject* p_bullet = new BulletObject();	//hàm constructor -> set lại từ đầu
			p_bullet->Set_bullet_type(BulletObject::CIRCLE_BULLET);
			p_bullet->LoadImgBullet(screen);

			if (status_ == WALK_LEFT_)
			{
				p_bullet->Set_bullet_direction(BulletObject::DIR_LEFT_);
				p_bullet->SetRect(this->rect_.x , rect_.y + heigh_frame_ * 0.20);
			}
			else
			{
				p_bullet->Set_bullet_direction(BulletObject::DIR_RIGHT_);
				p_bullet->SetRect(this->rect_.x + width_frame_ - 15, rect_.y + heigh_frame_ * 0.2);
			}

			p_bullet->Set_x_val_(20);
			p_bullet->Set_is_move(true);
			p_bullet_list_.push_back(p_bullet);
			
		}
	}
}

void MainPlayer::HandleBullet(SDL_Renderer* des)
{
	for (int i = 0; i < p_bullet_list_.size(); i++)
	{
		BulletObject* p_bullet = p_bullet_list_.at(i);
		if (p_bullet != NULL)
		{
			if (p_bullet->Get_is_move() == true)
			{
				p_bullet->HandleMove(SCREEN_WIDTH*1/2+64*3, SCREEN_HEIGHT*1/2+10 );//TẦM XA CỦA ĐẠN
				p_bullet->Render(des);	//SHOW LÊN DESKTOP	
			}
		}
		else
		{
			p_bullet_list_.erase(p_bullet_list_.begin() + i);
			if (p_bullet != NULL)
			{
				delete p_bullet;
				p_bullet = NULL;
			}
		}
	}
}



void MainPlayer::ReMoveBullet(const int& idx)
{
	int size = p_bullet_list_.size();	//ktra xem băng có đạn k
	if (size > 0 &&  idx < size)
	{
		BulletObject* p_bullet = p_bullet_list_.at(idx);
		p_bullet_list_.erase(p_bullet_list_.begin() + idx);
		if (p_bullet)
		{
			delete p_bullet;
			p_bullet = NULL;
		}
	}
}

//XỬ LÍ VA CHẠM
void MainPlayer::DoPlayer(Map& map_data)
{
	//trong thời gian come_back_time thì ko xử lí phần dưới
	if (come_back_time_ == 0)
	{
		x_val_ = 0;
		y_val_ += GRAVITY_SPEED;

		if (y_val_ > MAX_FALL_SPEED)
		{
			y_val_ = MAX_FALL_SPEED;
		}

		if (input_type_.left_ == 1)	//khi bấm trái
		{
			x_val_ -= PLAYER_SPEED;	//khi bấm trái thì x_val phải trừ đi một đoạn bằng tốc độ di chuyển

		}
		else if (input_type_.right_ == 1)	//khi bấm phải
		{
			x_val_ += PLAYER_SPEED;
		}

		//xử lí nhảy
		if (input_type_.jump_ == 1)
		{
			if (on_ground_ == true)	//chỉ khi nào ở trên mặt đất mới cho phép nhảy
			{
				y_val_ = -PLAYER_JUMP_VAL;	//nhảy ngay lên	
			}
			input_type_.jump_ = 0;
			on_ground_ = false;

		}
		//hết xử lí nhảy
		
		// hai hàm check map
		CheckPlayerandMap(map_data);	
		CenterEntityOnMap(map_data);
	}

	if (come_back_time_ > 0)
	{
		come_back_time_ --;
		if (come_back_time_ == 0)	//RESET LẠI TRẠNG THÁI
		{
			on_ground_ = false;		
			if (x_pos_ > 250)
			{
				x_pos_ -= 64*3;	// 4 ô tile_map
			}
			else
			{
				x_pos_ = 0;
			}
			y_pos_ = 0;
			x_val_ = 0;
			y_val_ = 0;
	

		}
	}
	
}





void MainPlayer::CenterEntityOnMap(Map& map_data)
{
	map_data.start_x = x_pos_ - (SCREEN_WIDTH / 2);	//TÍNH TOÁN LÀM SAO KHI NHÂN VẬT DI CHUYỂN ĐC NỬA BẢN ĐÒ THÌ BẢN ĐỒ ĐC CUỐN THEO
	if (map_data.start_x < 0)	//khi đi lùi
	{
		map_data.start_x = 0;
	}
	else if (map_data.start_x + SCREEN_WIDTH >= map_data.max_x_)	//lớn hơn chiều dài tối đa của bản đồ
	{
		map_data.start_x = map_data.max_x_ - SCREEN_WIDTH; //??
	}

	map_data.start_y = y_pos_ - (SCREEN_HEIGHT / 2);
	if (map_data.start_y < 0)
	{
		map_data.start_y = 0;
	}
	else if (map_data.start_y + SCREEN_HEIGHT > map_data.max_y_)
	{
		map_data.start_y = map_data.max_y_ - SCREEN_HEIGHT;
	}
}

void MainPlayer::CheckPlayerandMap(Map& map_data)
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
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];
			if (val1 == DIAMOND || val2 == DIAMOND)
			{
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;
				Increase_diamond();
			}
			else
			{
				if (val1 != BLANK_TILE || val2 != BLANK_TILE)	//ô khác ô trống ( ô trống kí hiệu là 0 )
				{
					x_pos_ = x2 * TILE_SIZE_;
					x_pos_ -= width_frame_ + 1;
					x_val_ = 0;

				}
				
			}
		}
		else if (x_val_ < 0)	//di chuyển sang trái
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1] ;
			if (val1 == DIAMOND || val2 == DIAMOND)
			{
				map_data.tile[y1][x1] = 0;
				map_data.tile[y2 ][x1] = 0;
				Increase_diamond();
			}
			else
			{
				if (val1 != BLANK_TILE || val2 != BLANK_TILE)
				{
					x_pos_ = (x1 + 1) * TILE_SIZE_;
					x_val_ = 0;
				}
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
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];
			if (val1 == DIAMOND || val2 == DIAMOND)
			{
				map_data.tile[y2][x1] = 0;
				map_data.tile[y2][x2] = 0;
				Increase_diamond();
			}
			else
			{
				if ( val1 != BLANK_TILE || val2 != BLANK_TILE)
				{
					y_pos_ = y2 * TILE_SIZE_;
					y_pos_ -= heigh_frame_ + 1;
					y_val_ = 0;

					on_ground_ = true;	//lúc này đang trên mặt đất
					if (status_ == WALK_BEGIN_)
					{
						status_ = WALK_RIGHT_;
					}

				}

			}
			
		}
		else if (y_val_ < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];
			if (val1 == DIAMOND || val2 == DIAMOND)
			{
				map_data.tile[y1][x1] = 0;
				map_data.tile[y1][x2] = 0;
				Increase_diamond();
			}
			else
			{
				if (val1 != BLANK_TILE || val2 != BLANK_TILE)
				{
					y_pos_ = (y1 + 1) * TILE_SIZE_;
					y_val_ = 0;
				}
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
	else if (x_pos_ + width_frame_ > map_data.max_x_)
	{
		x_pos_ = map_data.max_x_ - width_frame_ - 1;


	}
	if (y_pos_ > map_data.max_y_)	// thời gian delay
	{
		come_back_time_ = 60;
	}
}

void MainPlayer::Increase_diamond()
{
	diamond_count+=10;
}

void MainPlayer::UpdateImage(SDL_Renderer* des)
{
	if (on_ground_ == true)
	{
		if (status_ == WALK_LEFT_)
		{
			LoadImg("file_hinh_anh_img//player2_left.png", des);
		}
		else if( status_ == WALK_RIGHT_)
		{
			LoadImg("file_hinh_anh_img//player2_right.png", des);
		}
	}
	else
	{
		if ( status_ == WALK_LEFT_)
		{
			LoadImg("file_hinh_anh_img//player2_jum_left.png", des);
		}
		else if ( status_ == WALK_RIGHT_)
		{
			LoadImg("file_hinh_anh_img//player2_jum_right.png", des);
		}
		
	}
}

SDL_Rect MainPlayer::GetRectFrame()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = width_frame_;
	rect.h = heigh_frame_;
	
	return rect;
}
