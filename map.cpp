#include "stdafx.h"
#include "map.h"

void GameMap::LoadMap(std::string name)	// đọc toàn bộ file trong sơ đồ map
										// NAME là tên của file
{
	//sử dung con trỏ fp để đọc
	FILE* fp = NULL;
	fopen_s(&fp, name.c_str(), "rb");	//truyền vào con trỏ fp; tên file; chế độ "rb" là chế độ đọc
	if(fp == NULL)	//kiểm tra việc đọc
	{
		return;
	}

	game_map_.max_x_ = 0;	//	CỘT 0
	game_map_.max_y_ = 0;	//  HÀNG 0

	for( int i=0 ; i< 10 ; i++ )  // 10: số hàng của map
	{
		for( int j=0 ; j < 320 ; j++) // 38:  số cột
		{
			fscanf_s(fp, "%d", &game_map_.tile[i][j]);	//&game_map_.tile[i][j] là các số 0,1,2,3
														// FSCANF_S là hàm đọc dữ liệu -> từ file :v hàm này trong C
			//ys laf nos lấy dữ liệu từ gamemaptile rồi truyền vào con trỏ à ??
			//con trỏ nào :v
			// nó lấy dữ liệu từ fp truyền vào gamemap_tile
			//fp nó đang lưu hết dữ liệu của cái file đúng k.
			//uh
			// thế làm sao nó biết gán giá trị nào vào đâu
			//đọc file mà. đọc từđầu đén cuối file
			///đm VKey

			int val = game_map_.tile[i][j];
			if( val > 0 )		//GIÁ TRỊ 1,2,3,4...KHÁC 0 THÌ KO PHẢI FILL
			{
				if( j > game_map_.max_x_ )	// j là chỉ số cột giống như game_map.max_x = Ô THỨ BAO NHIÊU
				{
					game_map_.max_x_ = j; 
				}
				if( i> game_map_.max_y_ )
				{
					game_map_.max_y_ = i;
				}
			}

		}
	}
	game_map_.max_x_= (game_map_.max_x_+1)* TILE_SIZE_;
	game_map_.max_y_= (game_map_.max_y_+1)* TILE_SIZE_;

	game_map_.start_x = 0;
	game_map_.start_y = 0;
	
	game_map_.file_name_ = name;
	fclose(fp);
}

// HÀM LOAD IMAGE CHO CÁC TẤM ẢNH TƯƠNG ỨNG
void GameMap::LoadTiles(SDL_Renderer* screen)
{
	char file_img[30];
	FILE* fp = NULL;
	for(int i=0 ; i < MAX_TILE ; i++)
	{
		sprintf_s(file_img, "map/%d.png", i);	// LỆNH CHUYỂN ĐỔI KÍ TỰ I THÀNH %D RỒI CHO VÀO FILE_IMG
												//nếu i=0 -> map/0.png và chuyển vào file img 
		fopen_s(&fp, file_img, "rb" );	//mở file
		if(fp == NULL )
		{
			continue;
		}
		fclose(fp);

		tile_mat[i].LoadImg(file_img, screen);	//load sẵn các tấm ảnh		???????
		//hàm loadimg hoạt động ntn ?
		/*
		tile_mat ke thua basoObject nen la 1 doi tuong hinh anh rieng biet
		nen no load cung nhu baseObject load thoi

		Class GameMap co thuoc tinh là tile_mat[]
			nghĩa là nó load sẵn các tilemat
			và khi nào cần thì chỉ việc render ra thôi

			sao nó lại truyền vào fileimg vs screen?
		file_img là tên file
		screen là SDL_Renderer đẻ load ảnh

		vậy nó hoạt động ntn ? tưc là hàm sẽ làm ntn để load ảnh ấy

		vcl :v

		
		*/
			 
	}
}

// nhiệm vụ fill cấc hình ảnh vào các ô
void GameMap::DrawMap(SDL_Renderer* screen)
{
	int x1 =0;
	int x2 =0;
	int y1 =0;
	int y2 =0;

	// KHAI BÁO BIẾN LÀ CHỈ SỐ CỦA Ô.
	int map_x =0;
	int map_y =0;


	//****************************************
	map_x = game_map_.start_x / TILE_SIZE_;
	x1 = (game_map_.start_x % TILE_SIZE_)*-1;
	x2 = x1 + SCREEN_WIDTH + (x1 ==0 ? 0 : TILE_SIZE_);	// nếu x1 =0 thì + 0; nếu x1 !=0 thì + TILE_SIZE
	
	map_y = game_map_.start_y / TILE_SIZE_;
	y1 = (game_map_.start_y % TILE_SIZE_)*-1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE_);
	
	// bắt đầu fill
	for( int i = y1; i < y2 ; i+=TILE_SIZE_ )
	{
		map_x = game_map_.start_x / TILE_SIZE_;
		for( int j = x1; j < x2; j+=TILE_SIZE_ )
		{
			int val = game_map_.tile[map_y][map_x];
			if( val > 0 )
			{
				tile_mat[val].SetRect(j,i);	//set rect (j,i)
				tile_mat[val].Render(screen);

			}
			map_x ++;
		}
		map_y ++;
	}
}

void GameMap::checkLoadMap()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			std::cout << game_map_.tile[i][j] << ' ';
		}
		std::cout << endl;
	}
}