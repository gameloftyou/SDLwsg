#include "SDL_wsg.h"

wsg::Ctrl::Ctrl(Container &_parent,int _x,int _y,int _w,int _h)
	:parent(_parent),canvas(NULL),state(~(ENTER|ACTIVE|DOWN)),x(_x),y(_y),w(_w),h(_h),redraw(true)
{
	canvas = create_image(w,h);
	clip.x = 0;
	clip.y = 0;
	clip.w = w;
	clip.h = h;
}

bool wsg::Ctrl::Init()
{
	if(SDL_Init(SDL_INIT_EVERYTHING)==-1) return false;
	if(TTF_Init()==-1) return false;
	if(Mix_Init(MIX_INIT_MP3)==0) return false;
	return true;
}

wsg::Ctrl::~Ctrl()
{
	SDL_FreeSurface(canvas);
}