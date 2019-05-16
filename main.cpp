// DU_AN_GAME.cpp : Defines the entry point for the console application.


#include "stdafx.h"
#include "CommonFunction_CHUNG_.h"
#include "BaseObject.h"
#include "map.h"
#include "MainPlayer.h"
#include "Time.h"
#include "ThreatObject.h"
#include "ExplosionObject.h"
#include "TextObject.h"
#include "PlayEnergy.h"




//											BACK_GROUND
//**********************************************************************************************
BaseObject g_background;
TTF_Font* font_time = NULL;
//**********************************************************************************************





//						Hàm khởi tạo các thông số cho môi trường làm việc của SDL
//*********************************************************************************************
bool InitData()
{
	bool success = true;
	int ret = SDL_Init( SDL_INIT_VIDEO ); // trả về <0 nếu có lỗi
	// nếu không thành công
	if( ret<0 )
		return false;

	// nếu thành công thì thiết lập hàm tỉ lệ về chất lượng
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY , "1" ); // dịch: gợi ý chất lượng quy mô

	// tạo cửa sổ window cho game
	g_window = SDL_CreateWindow( "ADVENTURE_OF_JIM.version 1.0", // tiêu đề
								  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, // tạo hai cửa sổ chưa xác định
								  SCREEN_WIDTH, SCREEN_HEIGHT,
								  SDL_WINDOW_SHOWN );

	if( g_window == NULL )
	{
		success = false;
	}
	else
	{
		g_screen = SDL_CreateRenderer( g_window, -1, SDL_RENDERER_ACCELERATED );
		if( g_screen == NULL ) //nếu không thành công
		{
			success = false; 
		}
		else
		{
			SDL_SetRenderDrawColor( g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR );

			int imgFlags = IMG_INIT_PNG; // cắm cờ cho ảnh
			if( !IMG_Init(imgFlags) && !imgFlags )
			{
				success = false;
			}
		}
		//					KHỞI TẠO TEXT~TTF
		//********************************************************
		if (TTF_Init() == -1)
		{
			success = false;
		}
		font_time = TTF_OpenFont("font//font1.ttf", 15);
		if (font_time == NULL)
		{
			success = false;
		}
		//********************************************************
	}

	return success;
}
//****************************************************************************************************




//										LOAD_BACK_GROUND
//***************************************************************************************************
bool LoadBackground()
{
	// tạo một biến đại diện cho background, biến sẽ lưu tấm ảnh và load lên màn hình
	// biến đó là g_background kế thừa từ class BaseObject

	bool ret = g_background.LoadImg("file_hinh_anh_img//backgroundgame2.png", g_screen);
	if( ret == false )
	{
		return false;
	}
	return true;
}
//***************************************************************************************************




//							 CLOSE : giải phóng các đối tượng
//*************************************************************************************************
void close()
{
	g_background.Free();
	SDL_DestroyRenderer( g_screen );
	g_screen = NULL;
	SDL_DestroyWindow( g_window );
	g_window = NULL;
	IMG_Quit();
	SDL_Quit();
}
//*************************************************************************************************




//											THREAT
//************************************************************************************************
std::vector<ThreatObject*>  Make_threat_lists()
{
	std::vector<ThreatObject*> list_threat;


	//đối tượng ĐỘNG
	//******************************************************************
	ThreatObject* action_threat = new ThreatObject[30];
	for (int i = 0; i < 30; i++)
	{
		ThreatObject* p_threat = (action_threat + i);
		if (p_threat != NULL)
		{
			p_threat->LoadImg("file_hinh_anh_img//Threat_red_bird_right.png", g_screen);
			p_threat->Set_clip();
			p_threat->Set_type_move(ThreatObject::MOVE_IN_SPACE_THREAT);
			p_threat->Set_x_pos(500 + i * 800);		//Set vị trí
			p_threat->Set_y_pos(200);
			int pos1 = p_threat->Get_x_pos() - 70;
			int pos2 = p_threat->Get_x_pos() + 70;
			p_threat->Set_animation_POS(pos1, pos2);	
			p_threat->Set_input_left(1);	
			list_threat.push_back(p_threat);
		}
	}
	//******************************************************************


	//đối tượng TĨNH
	//******************************************************************
	ThreatObject* threat_obj = new ThreatObject[50]; 
	for (int i = 0; i < 50; i++)
	{
		ThreatObject* p_threat = (threat_obj + i);
		if (p_threat != NULL)
		{
			p_threat->LoadImg("file_hinh_anh_img//bomb_orange.png", g_screen);
			p_threat->Set_clip();
			p_threat->Set_x_pos(i*400+900);		//Set vị trí
			p_threat->Set_y_pos(250);
			p_threat->Set_type_move(ThreatObject::STATIC_THREAT);
			p_threat->Set_input_left(0);

			BulletObject* p_bullet = new BulletObject();
			p_threat->InitBullet(p_bullet, g_screen);

			list_threat.push_back(p_threat);

		}
	}

	ThreatObject* threat_obj2 = new ThreatObject[70];
	for (int i = 0; i < 70; i++)
	{
		ThreatObject* p_threat = (threat_obj2 + i);
		if (p_threat != NULL)
		{
			p_threat->LoadImg("file_hinh_anh_img//threat_pig_real.png", g_screen);
			p_threat->Set_clip();
			p_threat->Set_x_pos(i * 300 + 700);		//Set vị trí
			p_threat->Set_y_pos(250);
			p_threat->Set_type_move(ThreatObject::STATIC_THREAT);
			p_threat->Set_input_left(0);

			BulletObject * p_bullet = new BulletObject();
			p_threat->InitBullet(p_bullet, g_screen);

			list_threat.push_back(p_threat);

		}
	}
	
	//*******************************************************************

	return list_threat;
}
//												MAIN
//*****************************************************************************************************
int main(int argc, char* argv[])
{
	Time fps_timer;

	//**********************************************************
	// đầu tiên gọi hàm InitData
	if( InitData() == false )
	{
		return -1;
	}
	// gọi hàm LoadBackground
	if( LoadBackground() == false)
	{
		return -1;
	}
	//**********************************************************



	//								KHAI BÁO CÁC BIẾN
	//****************************************************************************************

	GameMap game_map;
	game_map.LoadMap("map/map_real.txt");	// tên file bản đồ
	game_map.LoadTiles(g_screen);	//???SAO LẠI LÀ G_SCREEN
	game_map.checkLoadMap();


	MainPlayer p_player;
	p_player.LoadImg("file_hinh_anh_img//player2_right.png", g_screen);
	p_player.set_clips();


	PlayEnergy play_energy;
	play_energy.Init(g_screen);

	PlayDiamond play_diamond;
	play_diamond.Init(g_screen);
	play_diamond.SetPOS(SCREEN_WIDTH*4/5 + 100, 10);


	std::vector<ThreatObject*> list_threat = Make_threat_lists();

	//*****************************************************************************************




	//								HIỆU ỨNG VỤ NỔ
	//*************************************************************************
	ExplosionObject exp_threat;
	bool tRet = exp_threat.LoadImg("file_hinh_anh_img//exp01.png", g_screen);
	if (!tRet)
	{
		return -1;
	}
	exp_threat.set_clip();

	ExplosionObject exp_main;
	bool qRet = exp_main.LoadImg("file_hinh_anh_img//exp01.png", g_screen);
	if (!qRet)
	{
		return -1;
	}
	exp_main.set_clip();
	//**************************************************************************



	//								CHỈ SỐ SINH MẠNG
	//**************************************************************************
	int num_die = 0;
	//**************************************************************************


	//						THỜI GIAN VÀ ĐIỂM SỐ <THUỘC TEXT>
	//**************************************************************************
	TextObject time_game;
	time_game.setcolor(TextObject::RED_TEXT);

	TextObject mark_game;
	mark_game.setcolor(TextObject::RED_TEXT);
	UINT mark_val = 0;


	TextObject money_game;
	money_game.setcolor(TextObject::RED_TEXT);

	//**************************************************************************




	// tạo một vòng lặp for chạy vô tận để chương trình load được tấm ảnh <PHẦN CHÍNH>
	//****************************************************************************************************

	bool is_quit = false; // chưa hề quit
	while ( !is_quit )
	{
		fps_timer.start();
		while( SDL_PollEvent( &g_event) != 0 ) // event chỉ là biến bình thường chứ k phải biến con trỏ < đc định nghĩa là biến thường trong commonfunction >
		{
			if( g_event.type == SDL_QUIT )
			{
				is_quit = true;
			}
			p_player.HandleInputAction(g_event, g_screen);		//sao lại đặt tại chỗ này trong vòng while ?????????
		}



		//					SET MÀU CHO MÀN HÌNH
		//********************************************************
		SDL_SetRenderDrawColor( g_screen, 
								RENDER_DRAW_COLOR,
								RENDER_DRAW_COLOR,
								RENDER_DRAW_COLOR,
								RENDER_DRAW_COLOR );




		//						XÓA MÀN HÌNH
		//********************************************************
  		SDL_RenderClear(g_screen);
		//********************************************************



		//						VẼ BACK_GROUND    ->DrawMap()
		//********************************************************
		g_background.Render(g_screen, NULL );  // biến background load ảnh ở trên sẽ truyền vào trong g_screen
		game_map.DrawMap(g_screen);
		//********************************************************



		//							VẼ MAP
		//**************************************************************
		Map map_data = game_map.getMap();	//tạo ra biến map_data và hàm getMap return ra biến game_map_

		p_player.SetMapXY(map_data.start_x, map_data.start_y);	//làm background di chuyển chỉ dòng này
		p_player.DoPlayer(map_data);
		p_player.Show(g_screen);
		p_player.HandleBullet(g_screen);

		game_map.SetMap(map_data);	//làm background chạy
		game_map.DrawMap(g_screen);

		//**************************************************************



		//**************************************************************
		play_energy.Show(g_screen);
		play_diamond.Show(g_screen);
		//**************************************************************



		//threat
		for (int i = 0; i < list_threat.size(); i++)
		{
			ThreatObject* p_threat = list_threat.at(i);
			if (p_threat != NULL)
			{
				p_threat->SetMapXY(map_data.start_x, map_data.start_y);

				p_threat->ImpMoveType(g_screen);
				p_threat->DOplayer(map_data);
				p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
				p_threat->Show(g_screen);

					
				//kiểm tra va chạm player và quái

				SDL_Rect rect_player = p_player.GetRectFrame();

				bool bCol1 = false;
				std::vector<BulletObject*> tBullet_list = p_threat->Get_bullet_list();
				for (int jj = 0; jj < tBullet_list.size(); ++jj)
				{

					BulletObject* pt_bullet = tBullet_list.at(jj);

					if (pt_bullet)	//
					{
						bCol1 = SDL_COMMONFUNCTION::CheckReAct(pt_bullet->GetRect(), rect_player);	//KIỂM TRA GIỮA HIỂM HỌA VÀ NHÂN VẬT
						if (bCol1 == true)
						{
							p_threat->ReMoveBullet(jj); 
							break;
						}
					}
				}
				//kiểm tra giữa player và threat

				SDL_Rect rect_threat = p_threat->GetRectFrame();
				bool bCol2 = SDL_COMMONFUNCTION::CheckReAct(rect_player, rect_threat);
				if ( bCol2 )		//SAI CHỖ bCol1 này này....
				{
					int frame_exp_width = exp_main.get_frame_width();
					int frame_exp_heigh = exp_main.get_frame_heigh();
					for (int ex = 0; ex < NUM_FRAME_EXP; ex++)
					{
						int x_pos = p_player.GetRect().x + p_player.get_frame_width()*0.5 - frame_exp_width * 0.5;
						int y_pos = p_player.GetRect().y + p_player.get_frame_width()*0.5 - frame_exp_heigh * 0.5;

						exp_threat.set_frame(ex);
						exp_threat.SetRect(x_pos, y_pos);
						exp_threat.Show(g_screen);
						SDL_RenderPresent(g_screen);
					}

					//									MẠNG SỐNG
					//*******************************************************************************
					num_die++;
					if (num_die <= NUM_DIE)	//số mạng
					{
							p_player.SetRect(0, 0);
							p_player.Set_come_back_time(60);
							SDL_Delay(800);
							play_energy.Decrease();
							play_energy.Render(g_screen);
							continue;
					}
					else
					{
						if (MessageBox(NULL, L"GAME_OVER", L"Infomation", MB_OK | MB_ICONSTOP) == IDOK)
						{
							p_threat->Free();
							close();
							SDL_Quit();
							return 0;
						}
					}
					//************************************************************************************
				}
																										
			}
		}
		//hết threat

		//										XỬ LÍ VA CHẠM
		//********************************************************************************************
		int frame_exp_width = exp_threat.get_frame_width();
		int frame_exp_heigh = exp_threat.get_frame_heigh();


		std::vector<BulletObject*> bullet_arr = p_player.Get_bullet_list();
		for (int r = 0; r < bullet_arr.size(); r++)
		{
			BulletObject* p_bullet = bullet_arr.at(r);	//danh sách đạn
			if (p_bullet != NULL)
			{
				for (int t = 0; t < list_threat.size(); t++)	//danh sách threat
				{
					ThreatObject* obj_threat = list_threat.at(t);
					if (obj_threat != NULL)
					{
						SDL_Rect tRect;
						tRect.x = obj_threat->GetRect().x;
						tRect.y = obj_threat->GetRect().y;
						tRect.h = obj_threat->GetRect().h;
						tRect.w = obj_threat->Get_width_frame();
						tRect.w = obj_threat->Get_heigh_frame();

						SDL_Rect bRect = p_bullet->GetRect();
						bool bCol = SDL_COMMONFUNCTION::CheckReAct(bRect, tRect);	//check va chạm giữa đạn và quái
						if (bCol)	//khi xayr ra va chamj, bawts ddaauf chayj vongf for nhuwng trong time raast nhor
						{
							mark_val+=15;
							for (int ex = 0; ex < NUM_FRAME_EXP; ex++)
							{
								int x_pos = p_bullet->GetRect().x - frame_exp_width * 0.5;
								int y_pos = p_bullet->GetRect().y - frame_exp_heigh * 0.5;

								exp_threat.set_frame(ex);
								exp_threat.SetRect(x_pos, y_pos);
								exp_threat.Show(g_screen);
							}
							p_player.ReMoveBullet(r);	//xóa viên đạn thứ r
							obj_threat->Free();
							list_threat.erase(list_threat.begin() + t);	//xóa mối hiểm họa thứ t
						}
					}
				}
			}
		}
		//******************************************************************************************




		//show game_time
		//*******************************************************************************************
		std::string str_time = "Time_Game:";
		Uint32 time_val = SDL_GetTicks() / 1000;
		Uint32 val_time = TIME_GAME-time_val;
		if (val_time <= 0)
		{
			if (MessageBox(NULL, L"GAME_OVER", L"Infomation", MB_OK | MB_ICONSTOP) == IDOK)
			{
				
				is_quit = true;
				break;
			}
		}
		else
		{
			std::string str_val = std::to_string(val_time);
			str_time += str_val;
			time_game.SetText(str_time);
			time_game.LoadFromRenderText(font_time, g_screen);
			time_game.RenderText(g_screen, 2*SCREEN_HEIGHT / 3 + 100, 15,NULL, 0, NULL, SDL_FLIP_NONE );
		}
		//***************************************************************************************




		//TEXT
		//*************************************************************************************
		std::string val_str_mark = std::to_string(mark_val);
		std::string strMark("Mark: ");
		strMark += val_str_mark;
		mark_game.SetText(strMark);
		mark_game.LoadFromRenderText(font_time, g_screen);
		mark_game.RenderText(g_screen, 2 * SCREEN_HEIGHT / 3 + 130, 60, NULL, 0, NULL, SDL_FLIP_NONE);
		int money_count = p_player.Get_diamond();
		std::string money_str = std::to_string(money_count);
		money_game.SetText(money_str);
		money_game.LoadFromRenderText(font_time, g_screen);
		money_game.RenderText(g_screen, SCREEN_WIDTH *4/5 + 150 , 15, NULL, 0, NULL, SDL_FLIP_NONE);
		//**********************************************************************************************






		// update lại màn hình
		SDL_RenderPresent(g_screen);


		
		//XỬ LÍ THỜI GIAN
		//*******************************************************************************************
		int real_time = fps_timer.get_tick();
		int time_one_frame_ = 1000 / FRAME_PER_SECOND;	// 1s/25 hình
		if (real_time < time_one_frame_)
		{
			int delay_time = time_one_frame_ - real_time;
			if( delay_time >= 0)
			{
				SDL_Delay(delay_time);
			}
			

		}
		//******************************************************************************************
	}




	// giải phóng tất cả các đối tượng bằng hàm close đã viết
	//**********************************************************************************************
	for (int i = 0; i < list_threat.size(); i++)
	{
		ThreatObject* p_threat = list_threat.at(i);
		if (p_threat != NULL)
		{
			p_threat->Free();
			p_threat = NULL;
		}
	}
	list_threat.clear();
	close();
   //***********************************************************************************************
    return 0;
	
}
 
