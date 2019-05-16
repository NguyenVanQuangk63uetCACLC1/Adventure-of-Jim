#include "stdafx.h"
#include "BaseObject.h"


// Định nghia hàm constructor 
BaseObject::BaseObject()
{
	// định nghĩa các biến
	p_object_ = NULL;	
	rect_.x = 0;	//->	kích thước của frame
	rect_.y = 0;
	rect_.w = 0;  //rộng
	rect_.h = 0;  //cao
}

 // định nghĩa hàm destructor
BaseObject::~BaseObject()
{
	Free();
}

 // d?nh nghia hàm LoadImg
/*

Surface là bề mặt; được xử lí bởi Cpu, lưuu trử trên RAM
Renderer là kết cấu hình ảnh, đc xử lí bởi GPU

gpu chuyên dùng để vẽ -> nên dùng gpu để vẽ ảnh,lưuuw trử tren VRAM
tiết kiệm tài nguyên cpu cho việc khác






*/
 bool BaseObject::LoadImg( std::string path /*đường dẫn tấm ảnh*/, SDL_Renderer* screen )
{ 
	Free();
	SDL_Texture* new_texture = NULL; //biến kết quả cuối cùng 

	//quá trình ĐỌC tấm ảnh bằng hàm : "IMG_Load"
	SDL_Surface* load_surface = IMG_Load( path.c_str());	//-> đọc tấm ảnh từ đường dẫn  path; 
															// ta sẽ chuyển surface thành texture để load lên màn hình
	if( load_surface != NULL )
	{
		// xóa phông cho tấm ảnh
		SDL_SetColorKey( load_surface, SDL_TRUE, SDL_MapRGBA( load_surface -> format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B, COLOR_KEY_A) );
		//format là lấy định dạng của surface thôi
		//chuyển Surface thành Texture
		new_texture = SDL_CreateTextureFromSurface( screen, load_surface );
		if(new_texture != NULL)
		{
			 rect_.w = load_surface -> w;	//chỗ này nx???
			 rect_.h = load_surface -> h;

			 //lấy kích thước của ảnh qua surface w = width / h = height
			 //sau đó lưu vào rect_ nhưng mà ta đã khai báo w vs h đâu
			 // w với h là thuộc tính của surface, - khi load thì nó tự nhân giá trị

		}

		//bây giờ new_texture lưu giữ mọi thông tin của tấm ảnh

		SDL_FreeSurface(load_surface);	// giải phóng load_surface vì k cần nx
	}

	p_object_ = new_texture;

	return p_object_ != NULL;

	//-> đối tượng BaseObject sau khi gọi LoadImg có được thông tin về texture của tấm ảnh và đồng thời có được kích thước rect của tấm ảnh
}

 // định nghĩa hàm Render
void BaseObject::Render( SDL_Renderer* des, const SDL_Rect* clip ) // des là đích, tức là chúng ta muốn load tấm ảnh lên nền nào, lên đối tượng nào
{
	SDL_Rect renderquad = { rect_.x, rect_.y, rect_.w, rect_.h };	//bao gồm vị trí và kích thước tấm ảnh
	SDL_RenderCopy( des, p_object_,clip, &renderquad);		//-> đẩy toàn bộ thông số của p_object_ lên des; với kích thước và vị trí nằm trong renderquad

}

void BaseObject::Free()
{
	if(p_object_ != NULL )
	{
		SDL_DestroyTexture(p_object_);
		p_object_ = NULL;
		rect_.w = 0;
		rect_.h = 0;
	}
}
