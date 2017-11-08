#include "SDL_wsg.h"

wsg::App::App(std::string _bg,int _w,int _h)
	:Container(*this,0,0,_w,_h),screen(NULL),bg(NULL),cursor(NULL),font(NULL),color(0),RUN(true)
{
	init();
	bg = load_image(_bg);
	if(bg!=NULL) hasbg = true;
	else hasbg = false;
}

wsg::App::App(Uint32 _color,int _w,int _h)
	:Container(*this,0,0,_w,_h),screen(NULL),bg(NULL),cursor(NULL),font(NULL),color(_color),RUN(true),hasbg(false)
{
	init();
}


void wsg::App::init()
{
	screen = SDL_SetVideoMode(w,h,32,SDL_SWSURFACE);
	canvas = create_image(w,h);
	cursor = load_image("cursor.png");
	font = TTF_OpenFont("monaco.ttf",16);
}

void wsg::App::paint(SDL_Surface *screen)
{
	if(!is_empty(&clip))
	{
		SDL_FillRect(canvas,&clip,color);
		if(hasbg) apply_surface(clip.x,clip.y,bg,canvas,&clip);
		for(ConstChildIter iter = childs.begin();iter!=childs.end();++iter)
		{
			Ctrl *child = *iter;
			if(collision(&clip,child->x,child->y,child->w,child->h)) child->paint(canvas);
		}
		empty_rect(&clip);
	}
	apply_surface(0,0,canvas,screen);
	apply_surface(cx,cy,cursor,screen);
	SDL_Flip(screen);
}

void wsg::App::event(SDL_Event &_event)
{
	for(ConstChildIter iter = childs.begin();iter!=childs.end();++iter)
	{
	    Ctrl *child = *iter;
	    if(in_rect(cx,cy,child->x,child->y,child->w,child->h)||child->state&ACTIVE) child->event(_event);
	}
	switch(_event.type)
	{
	case SDL_MOUSEMOTION:
		cx = _event.motion.x;
		cy = _event.motion.y;
		paint(screen);
		break;
	case SDL_KEYUP:
		{

		}
		break;
	case SDL_QUIT:
		RUN = false;
		break;
	default:break;
	}
}

TTF_Font *wsg::App::get_font()
{
	return font;
}

void wsg::App::repaint(int _x,int _y,int _w,int _h)
{
	clip.x = _x;
	clip.y = _y;
	clip.w = _w;
	clip.h = _h;
	paint(screen);
}

void wsg::App::run()
{
	paint(screen);
	while(RUN)
	{
		while(SDL_PollEvent(&_event))
		{
			event(_event);
		}
		SDL_Delay(10);
	}
}

void wsg::App::exit()
{
	SDL_FreeSurface(bg);
	SDL_FreeSurface(cursor);
	TTF_CloseFont(font);
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}

wsg::App::~App()
{
	exit();
}