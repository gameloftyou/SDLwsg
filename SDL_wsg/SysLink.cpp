#include "SDL_wsg.h"

wsg::SysLink::SysLink(Container &_parent,std::string _text,int _x,int _y,int _w,int _h,CallBack _callback)
	:Ctrl(_parent,_x,_y,_w,_h),text(_text),callback(_callback)
{
	parent.addChild(this);
}

void wsg::SysLink::paint(SDL_Surface *screen)
{
	if(redraw)
	{
		if(state&ENTER)
		{
			TTF_Font *font = parent.get_font();
			SDL_Color color = { 49, 154, 255 };
			SDL_Surface *temp = TTF_RenderText_Solid(font,text.c_str(),color);
			SDL_Rect clip = { x, y, w, h };
			apply_surface(0,0,screen,canvas,&clip);
			apply_surface(0,0,temp,canvas);
			if(temp!=NULL) Draw_Line(canvas,0,MIN(temp->h-1,h-1),MIN(temp->w-1,w-1),MIN(temp->h-1,h-1),0x319AFF);
			SDL_FreeSurface(temp);
		}
		else
		{
			TTF_Font *font = parent.get_font();
			SDL_Color color = { 0, 101, 206 };
			SDL_Surface *temp = TTF_RenderText_Solid(font,text.c_str(),color);
			SDL_Rect clip = { x, y, w, h };
			apply_surface(0,0,screen,canvas,&clip);
			apply_surface(0,0,temp,canvas);
			SDL_FreeSurface(temp);
		}
		redraw = false;
	}
	apply_surface(x,y,canvas,screen);
}

void wsg::SysLink::event(SDL_Event &_event)
{
	switch(_event.type)
	{
	case SDL_MOUSEMOTION:
		DWEOS
		break;
	case SDL_KEYUP:
		if(state&ENTER)
		{
			callback();
		}
		break;
	default:break;
	}
}

wsg::SysLink::~SysLink()
{

}