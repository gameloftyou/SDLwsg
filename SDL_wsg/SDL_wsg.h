/*=======================================
 * name: SDL_wsg
 * coder: gameloftyou
 * version: 1.00
 *=======================================*/


#ifndef __SDL_WSG_H__
#define __SDL_WSG_H__


#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_draw.h>
#include <SDL/SDL_thread.h>
#include <SDL/SDL_mixer.h>
#include <vector>
#include <string>
#include <functional>


namespace wsg
{


#define		MIN(A,B)		(A>B?B:A)
#define		MAX(A,B)		(A>B?A:B)
#define		DWEOS								\
if(in_rect(_event.motion.x,_event.motion.y,x,y,w,h))\
{												\
	if(!(state&ENTER))							\
	{											\
		state |= ENTER;							\
		redraw = true;							\
		parent.repaint(x,y,w,h);					\
	}											\
}												\
else												\
{												\
	state &= ~ENTER;								\
	redraw = true;								\
	parent.repaint(x,y,w,h);						\
}


inline SDL_Surface *create_image(int w,int h)
{
	SDL_Surface *createdImage = NULL;
	SDL_Surface *optimizedImage = NULL;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	createdImage = SDL_CreateRGBSurface(SDL_SWSURFACE,w,h,32,0xff000000,0x00ff0000,0x0000ff00,0x000000ff);
#else
	createdImage = SDL_CreateRGBSurface(SDL_SWSURFACE,w,h,32,0x000000ff,0x0000ff00,0x00ff0000,0xff000000);
#endif
	if(createdImage!=NULL)
	{
		optimizedImage = SDL_DisplayFormat(createdImage);
		SDL_FreeSurface(createdImage);
	}
	return optimizedImage;
}

inline SDL_Surface *load_image(std::string filename)
{
	SDL_Surface *loadedImage = NULL;
	SDL_Surface *optimizedImage = NULL;

	loadedImage = IMG_Load(filename.c_str());
	if(loadedImage!=NULL)
	{
		optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	return optimizedImage;
}

inline void apply_surface(int x,int y,SDL_Surface *source,SDL_Surface *destination,SDL_Rect *clip=NULL)
{
	SDL_Rect offset;
	offset.x = static_cast<Sint16>(x);
	offset.y = static_cast<Sint16>(y);
	SDL_BlitSurface(source,clip,destination,&offset);
}

inline void set_rect(SDL_Rect *rect,int x,int y,int w,int h)
{
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
}

inline void empty_rect(SDL_Rect *rect)
{
	set_rect(rect,0,0,0,0);
}

inline bool is_empty(SDL_Rect *rect)
{
	if(rect->w==0&&rect->h==0&&rect->x==0&&rect->y==0) return true;
	return false;
}

inline bool collision(SDL_Rect *rect1,SDL_Rect *rect2)
{
	int x = rect2->x,y = rect2->y;
	int left = rect1->x-rect2->w,right = rect1->x+rect1->w;
	int up = rect1->y-rect2->h,down = rect1->y+rect1->h;

	if(x>left&&x<right&&y>up&&y<down) return true;
	return false;
}

inline bool collision(SDL_Rect *rect1,int _x,int _y,int _w,int _h)
{
	int left = rect1->x-_w,right = rect1->x+rect1->w;
	int up = rect1->y-_h,down = rect1->y+rect1->h;

	if(_x>left&&_x<right&&_y>up&&_y<down) return true;
	return false;
}

inline bool in_rect(int x,int y,int _x,int _y,int _w,int _h)
{
    if(x>=_x&&x<_x+_w&&y>=_y&&y<_y+_h) return true;
    return false;
}

inline void do_nothing() {}


typedef unsigned short State;
typedef std::function<void()> CallBack;
const State ACTIVE = 0x0001;
const State ENTER = 0x0010;
const State DOWN = 0x0100;


class Container;

class Ctrl {

public:
					Ctrl(Container &_parent,int _x,int _y,int _w,int _h);
	virtual	void	paint(SDL_Surface *screen) = 0;
	virtual	void	event(SDL_Event &_event) = 0;
	static	bool	Init();
					~Ctrl();
	
	Container	&parent;
	SDL_Surface	*canvas;
	SDL_Rect	clip;
	State		state;
	int			x,y,w,h;
	bool		redraw;

};

typedef std::vector<Ctrl *>::const_iterator ConstChildIter;


class Container : public Ctrl {

public:
				        Container(Container &_parent,int _x,int _y,int _w,int _h);
			void        addChild(Ctrl *child);
	virtual	TTF_Font    *get_font();
	virtual	void		repaint(int _x,int _y,int _w,int _h);
					    ~Container();

	std::vector<Ctrl *>	childs;
	SDL_Event			_event;
	int					cx,cy;

};


class StaticText : public Ctrl {

public:
			    StaticText(Container &_parent,std::string _text,int _x,int _y,int _w,int _h);
	void		paint(SDL_Surface *screen);
			    ~StaticText();

private:
	void		event(SDL_Event &_event);
	std::string	text;

};


class SysLink : public Ctrl {

public:
			    SysLink(Container &_parent,std::string _text,int _x,int _y,int _w,int _h,CallBack _callback=do_nothing);
	void		paint(SDL_Surface *screen);
	void		event(SDL_Event &_event);
			    ~SysLink();
private:
	std::string text;
	CallBack	callback;

};


class Panel : public Container {

public:
					Panel(Container &_parent,std::string _bg,int _x,int _y,int _w,int _h);
					Panel(Container &_parent,Uint32 _color,int _x,int _y,int _w,int _h);
	virtual	void	paint(SDL_Surface *screen);
	virtual	void	event(SDL_Event &_event);
					~Panel();
	SDL_Surface		*bg;
	Uint32			color;
	bool			hasbg;

};


class Button : public Container {
	
public:
	Button(Container &_parent,std::string _text,int _x,int _y,int _w,int _h);
	~Button();
	std::string text;

};


class PushButton : public Button {

public:
			    PushButton(Container &_parent,std::string _text,int _x,int _y,int _w,int _h,CallBack _callback=do_nothing);
	void		paint(SDL_Surface *screen);
	void		event(SDL_Event &_event);
			    ~PushButton();
private:
	CallBack	callback;

};


class Runnable {

public:
	virtual void run() = 0;

};


class Thread {

public:
			    Thread(Runnable *_runnable);
			    Thread(CallBack _callback);
	void		start();
	void		stop();
			    ~Thread();

private:
	Runnable	*runnable;
	CallBack	callback;
	bool		hascb;
	static int run(void *runnable);
	static int cb(void *callback);

};

class App : public Container {

public:
			    App(std::string _bg,int _w,int _h);
			    App(Uint32 _color,int _w,int _h);
	void		paint(SDL_Surface *screen);
	void		event(SDL_Event &_event);
	TTF_Font	*get_font();
	void		repaint(int _x,int _y,int _w,int _h);
	void		run();
	void		exit();
			    ~App();

private:
	void		init();
	SDL_Surface	*screen,*bg,*cursor;
	TTF_Font	*font;
	Uint32		color;
	bool		RUN;
	bool		hasbg;

};


}

#endif //__SDL_WSG_H__