#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <iostream>
using namespace std;
#include <vector>
#include <cmath>
#include <string>
#include <Windows.h>
#include <SDL.h> // thu vi?n chung c?a sdl
#include <SDL_image.h> // hình ?nh
#include <SDL_mixer.h> // âm thanh
#include <SDL_ttf.h> // chữ cái


static SDL_Window* g_window = NULL; // static giúp lưu giữ giá trị của biến dù cho chương trình dã chạy ra ngoài
									// khối lệnh chứa nó.
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;


//định nghĩa các thông số cơ bản cho môi trường của game:

//1. màn hình screen
const int SCREEN_WIDTH = 1280; // chi?u r?ng
const int SCREEN_HEIGHT = 640; // chi?u cao
const int SCREEN_BPP = 32;     // pixel_độ phân giải

const int COLOR_KEY_R = 167; // định nghĩa màu sắc
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;
const int COLOR_KEY_A = 0;

const int RENDER_DRAW_COLOR = 0xff; // 0xff = 255


//************************************************//
// PHẦN ĐỊNH NGHĨA VỀ MAP

// Định nghĩa kích thước một mắt lưới
#define TILE_SIZE_ 64
#define BLANK_TILE 0

// Định nghĩa kích thước của map
#define MAP_MAX_X 400	//chiều ngang = số cột
#define MAP_MAX_Y 10	//chiều cao = số hàng
//-> có 4000 ô


// LỚP LƯU CÁC TRẠNG THÁI VỀ CHỈ SỐ, Ô THỨ BAO NHIÊU , TỌA ĐỘ CỦA Ô
 struct Map
{
	int start_x;	// vị trí của ô. Ví dụ như ô thứ 10 sẽ là : 10 * TILE_SIZE_(kích thước mắt lưới)
	int start_y;

	// Ô THỨ BAO NHIÊU 
	int max_x_;		// thực ra max_x_ = phần nguyên của static/TILE_SIZE_
					// ví dụ 641/64 vẫn là ô thứ 10
	int max_y_;


	// một mảng hai chiều lưu toàn bộ trạng thái của ô đó
	int tile[MAP_MAX_Y][MAP_MAX_X];		// hàng-cột; 0 1 2 0 
										//			 0 0 1 1
	
	// biến lưu tên file
	std::string file_name_;

	Map()
	{
		start_x = 0;
		start_y = 0;
		max_x_ = 0;
		max_y_ = 0;
	}

};

 //*****************************************************************
 typedef struct Input
 {
	 int left_;
	 int right_;
	 int up_;
	 int down_;
	 int jump_;

 };

//thời gian
 const int FRAME_PER_SECOND = 60;	//FPS: SỐ FRAME TRÊN MỘT GIÂY

 // đồ hỗ trợ
#define DIAMOND 9
#define NUM_DIE 3
#define TIME_GAME 150

 namespace SDL_COMMONFUNCTION
 {
	 bool CheckReAct(const SDL_Rect& object1, const SDL_Rect& object2);
	 int ShowMenu(SDL_Surface* des, TTF_Font* font);
 }

#endif