#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "CommonFunction_CHUNG_.h"
#include "BaseObject.h"

// tạo ra một đối tượng về vấn đề hình ảnh kế thừa BaseObject
// do map chỉ quản lí về vấn đề vị trí và kích thước trạng thái của đối tượng
// chứ chưa có đối tượng hình ảnh

//****LỚP LƯU HÌNH ẢNH****
class TileMat :public BaseObject	// ý nghĩa: TileMat là class kế thừa của BaseObject
									// do đây chỉ là đối tượng tĩnh nên k có phần Private
									// kế thừa chỉ mang tính chất tạo ra một đối tượng riêng biệt thôi
{
public:
	TileMat() {;}		// hàm constructor 
	~TileMat() {;}		// hàm destructor

};


//xây dựng lên một lớp quản lí việc xây dựng map
// chức năng: đẩy toàn bộ hình ảnh TileMat vào các vị trí ô vuông của struct Map


// ****LỚP CHÈN HÌNH ẢNH VÀO Map*******
#define MAX_TILE 20 // số lượng địa hình tối đa
class GameMap
{
public:
	GameMap() {;}
	~GameMap() {;}

	// tạo ra một hàm đọc toàn bộ thông tin ở trong file sơ đồ map
	void LoadMap(std::string name);		//ĐỌC MAP



	// hàm load toàn bộ hình ảnh 
	void LoadTiles(SDL_Renderer* screen);	//LOAD ẢNH



	// hàm xây dựng map ( fill tất cả hình ảnh vào các vị trí )
	void DrawMap(SDL_Renderer* screen );		//TRUYỀN ẢNH VÀO MAP

	Map getMap()
	{ return game_map_;};
	
	//làm background chạy theo nhân vật
	void SetMap(Map& map_data)
	{
		game_map_ = map_data;
	};

	void checkLoadMap();
private:
	// do có hai mô hình đối tượng là hình ảnh và vị trí nên sẽ có hai biến
	Map game_map_;	// biến chứa toàn bộ thông tin về trạng thái và vị trí của bản đồ
	TileMat tile_mat [MAX_TILE];	// biến chứa hình ảnh của các dạng địa hình.			
};

#endif 