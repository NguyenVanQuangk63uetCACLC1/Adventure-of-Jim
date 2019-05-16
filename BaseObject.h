// BaseObject là l?p chuyên qu?n lí hình ?nh
// Các ??i t??ng khác liên quan ??n hình ?nh nh? player, bullet,... s? k? th?a l?p BaseObject

#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "CommonFunction_CHUNG_.h"

// định nghĩa class BaseObject
class BaseObject
{
public:
	BaseObject();  // định nghĩa constructor
	~BaseObject(); // định nghĩa destructor

	//hàm nhận vào kích thước tấm ảnh rect
	void SetRect( const int& x, const int& y)
	{
		rect_.x = x;   // hmm...
		rect_.y = y;
	}

	// hàm lấy ra kích thước tấm ảnh rect
	SDL_Rect GetRect()
	{
		 return rect_;
	}
	
	// hàm lấy ra hình ảnh
	SDL_Texture* GetObject()
	{
		 return p_object_;
	}

	// hàm load ảnh lên trên đối tượng p_object để p_object phiên vào hàm GetObject -> màn hình
	virtual bool LoadImg( std::string path /*đường dẫn tấm ảnh*/, SDL_Renderer* screen );	
	void Render( SDL_Renderer* des, const SDL_Rect* clip = NULL );
	void Free();

protected:

	SDL_Texture* p_object_;  // biến chuyên lưu trữ hình ảnh.
	SDL_Rect rect_;			 // biến chuyên lưu trữ kích thước của tấm ảnh.
};

#endif