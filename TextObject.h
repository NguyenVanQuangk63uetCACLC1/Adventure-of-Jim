#pragma once

#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_

#include "CommonFunction_CHUNG_.h"

class TextObject
{
public:
	TextObject();
	~TextObject();

	bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen);


	enum ColorType
	{
		RED_TEXT = 0,
		WHITE_TEXT = 1,
		BLACK_TEXT = 2,
	};
	
	void Free();
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	void setcolor(int type);
	void RenderText(SDL_Renderer* screen,
					int x_p, int y_p,
					SDL_Rect* clip /*= NULL */,
					double angle /* = 0.0 */,
					SDL_Point* center /* = NULL */,
					SDL_RendererFlip flip /* = SDL_FLIP_NONE */);
	int GetWidth()
	{
		return width_;
	}
	int GetHeigh()
	{
		return heigh_;
	}
	void SetText(const std::string& text)
	{
		str_val_ = text;
	}
	std::string GetText()
	{
		return str_val_;
	}
private:
	std::string str_val_;
	SDL_Color text_color;
	SDL_Texture* texture_;
	int	width_;
	int heigh_;
};



#endif