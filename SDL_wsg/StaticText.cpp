#include "SDL_wsg.h"

wsg::StaticText::StaticText(Container &_parent,std::string _text,int _x,int _y,int _w,int _h)
	:Ctrl(_parent,_x,_y,_w,_h),text(_text)
{
	parent.addChild(this);
}

void wsg::StaticText::paint(SDL_Surface *screen)
{
	if(redraw)
	{
		TTF_Font *font = parent.get_font();
		SDL_Color color = { 0, 0, 0 };
		SDL_Surface *temp = TTF_RenderText_Solid(font,text.c_str(),color);
		SDL_Rect clip = { x, y, w, h };
		apply_surface(0,0,screen,canvas,&clip);
		apply_surface(0,0,temp,canvas);
		SDL_FreeSurface(temp);
		redraw = false;
	}
	apply_surface(x,y,canvas,screen);
}

void wsg::StaticText::event(SDL_Event &_event)
{

}

wsg::StaticText::~StaticText()
{

}