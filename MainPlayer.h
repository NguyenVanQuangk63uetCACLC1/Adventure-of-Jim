#pragma once
#ifndef MAIN_PLAYER_H_
#define MAIN_PLAYER_H_

#include <vector>
#include "CommonFunction_CHUNG_.h"
#include "BaseObject.h"
#include "BulletObject.h"

#define GRAVITY_SPEED 0.8		//tốc độ rơi
#define MAX_FALL_SPEED 30
#define PLAYER_SPEED  10
#define PLAYER_JUMP_VAL 16
#define NUM_PLAYER_FRAME 6

// tạo class mainplayer kế thừa từ baseobject
class MainPlayer : public BaseObject
{
public:
	MainPlayer();
	~MainPlayer();

	enum Walktype		//enum???
	{
		WALK_BEGIN_ = 0, WALK_LEFT_ = 2, WALK_RIGHT_ = 1
	};


	bool LoadImg(std::string path, SDL_Renderer* screen);	//mặc dù trong baseobject đã có nhưng hàm này load nhiều frame khác nhau

	//hàm show các frame <tăng frame>
	void Show(SDL_Renderer* des);

	//hàm xử lí sự kiện khi ấn trái phải
	void HandleInputAction(SDL_Event event, SDL_Renderer* screen);

	//hàm xử lí hiệu ứng animation clip
	void set_clips();

	//************** xử lí va cham;
	void DoPlayer(Map& map_data);	//hàm tính lượng để nhân vật di chuyển
									//cần chuyền vào bản đồ đẻ check va chạm

	void CheckPlayerandMap(Map& map_data);	//hàm chính kiểm tra va chạm giữa nhân vật với bản đồ

	//làm background chạy theo nhân vật
	void SetMapXY(const int map_x, const int map_y)
	{
	map_x_ = map_x;
	map_y_ = map_y;
	}

	void CenterEntityOnMap(Map& map_data);		//hàm tính toán thông số của bản đồ, đc gọi cùng vị trí với hàm checkplayerandmap
												//trong quá trình check va chạm và di chuyển cx sẽ tính toán luôn thông số của map nên gọi trong hàm doplayer

	void UpdateImage(SDL_Renderer* des);



	//đạn
	void Set_bullet_list(std::vector<BulletObject*> bullet_list_)
	{
		p_bullet_list_ = bullet_list_;
	}
	std::vector<BulletObject*> Get_bullet_list()
	{
		return p_bullet_list_;
	}
	void HandleBullet(SDL_Renderer* des);

	void ReMoveBullet(const int& idx);
	//hết đạn


	void Increase_diamond();
	int Get_diamond()
	{
		return diamond_count;
	}

	SDL_Rect GetRectFrame();

	//chỉ số sinh mạng
	void Set_come_back_time(const int& comebacktime)
	{
		come_back_time_ = comebacktime;
	}

	int get_frame_width()
	{
		return width_frame_;
	}

private:
	//đồ hỗ trợ
	int diamond_count;



	//đạn
	std::vector<BulletObject*> p_bullet_list_;	//đạn
	//hết đạn
	float x_val_;	//mỗi lần ấn di chuyển một đoạn bằng bao nhiêu -> trái phải
	float y_val_;

	float x_pos_;	//biến lưu vị trí hiện tại của nhân vât
	float y_pos_;

	int width_frame_;	//kích thước của frame
	int heigh_frame_;

	//biến lưu các frame sẽ ở trong hàm set_clips()
	SDL_Rect frame_clip_[8];

	//biến lưu trạng thái di chuyển lên xuống trái phải
	Input input_type_;

	//biến lưu chỉ số của frame ( đang ở frame bao nhiêu )
	int frame_;

	//biến lưu status của nhân vật ( đang di chuyển sang trái hay sang phải )
	int status_;
	//**************
	bool on_ground_;

	//làm background chạy theo nhân vật
	int map_x_;		//khi di chuyển thì mép của bản đồ sẽ ở vị trí mới map_x; map_y 
	int map_y_;

	//xử lí rơi xuống vực thẳm
	int come_back_time_ = 0;

};


#endif // !MAIN_PLAYER_H_
