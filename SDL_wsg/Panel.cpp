#include "SDL_wsg.h"

wsg::Panel::Panel(Container &_parent,std::string _bg,int _x,int _y,int _w,int _h)
	:Container(_parent,_x,_y,_w,_h),bg(NULL),color(0)
{
	bg = load_image(_bg);
	if(bg!=NULL) hasbg = true;
	else hasbg = false;
	parent.addChild(this);
}

wsg::Panel::Panel(Container &_parent,Uint32 _color,int _x,int _y,int _w,int _h)
	:Container(_parent,_x,_y,_w,_h),bg(NULL),color(_color),hasbg(false)
{
	parent.addChild(this);
}

void wsg::Panel::paint(SDL_Surface *screen)
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
	apply_surface(x,y,canvas,screen);
}

void wsg::Panel::event(SDL_Event &_event)
{
	if(state&ACTIVE)
	{
		this->_event = _event;
		if(_event.type==SDL_MOUSEMOTION)
		{
			this->_event.motion.x -= x;
			this->_event.motion.y -= y;
		}
		for(ConstChildIter iter = childs.begin();iter!=childs.end();++iter)
		{
			Ctrl *child = *iter;
			if(in_rect(cx,cy,child->x,child->y,child->w,child->h)||child->state&ACTIVE) child->event(this->_event);
		}
	}
	switch(_event.type)
	{
	case SDL_MOUSEMOTION:
		if(in_rect(_event.motion.x,_event.motion.y,x,y,w,h))
		{												
			if(!(state&ENTER))							
			{											
				state |= ENTER;											
			}											
		}												
		else												
		{												
			state &= ~ENTER;						
		}
		cx = _event.motion.x-x;
		cy = _event.motion.y-y;
		break;
	case SDL_KEYUP:
		if(state&ENTER)
		{
			state |= ACTIVE;//向父窗口请求激活
		}
		break;
	default:break;
	}
}

wsg::Panel::~Panel()
{

}