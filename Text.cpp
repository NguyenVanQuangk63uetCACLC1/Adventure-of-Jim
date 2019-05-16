#include "stdafx.h"
#include "TextObject.h"

TextObject::TextObject()
{
	text_color.r = 255;
	text_color.g = 255;
	text_color.b = 255;
	texture_ = NULL;
}

TextObject::~TextObject()
{

}

bool TextObject::LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen)
{
	SDL_Surface* textsurface = TTF_RenderText_Solid(font, str_val_.c_str(), text_color);
	{
		if (textsurface)
		{
			texture_ = SDL_CreateTextureFromSurface(screen, textsurface);
			width_ = textsurface->w;
			heigh_ = textsurface->h;
			SDL_FreeSurface(textsurface);
		}
		return texture_ != NULL;
	}
}

void TextObject::Free()
{
	if (texture_ != NULL)
	{
		SDL_DestroyTexture(texture_);
		texture_ = NULL;
	}
}

void TextObject::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	text_color.r = red;
	text_color.g = green;
	text_color.b = blue;
}
void TextObject::setcolor(int type)
{
	if (type == RED_TEXT)
	{
		SDL_Color color = { 255,0,0 };
		text_color = color;
	}
	else if (type == WHITE_TEXT)
	{

		SDL_Color color = { 255,255,255 };
		text_color = color;
	}
	else if (type == BLACK_TEXT)
	{

		SDL_Color color = { 0,0,0 };
		text_color = color;
	}
}

void TextObject::RenderText(SDL_Renderer* screen,
							int x_p, int y_p,
							SDL_Rect* clip /*= NULL */,
							double angle /* = 0.0 */,
							SDL_Point* center /* = NULL */,
							SDL_RendererFlip flip /* = SDL_FLIP_NONE */)
{
	SDL_Rect renderquad = { x_p,y_p,width_,heigh_ };
	if (clip != NULL)
	{
		renderquad.w = clip->w;
		renderquad.h = clip->h;
	}

	SDL_RenderCopyEx(screen, texture_, clip, &renderquad, angle,center, flip);

}