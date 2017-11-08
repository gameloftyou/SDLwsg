#include "SDL_wsg.h"

wsg::Container::Container(Container &_parent,int _x,int _y,int _w,int _h)
	:Ctrl(_parent,_x,_y,_w,_h),cx(0),cy(0)
{

}

TTF_Font *wsg::Container::get_font()
{
	return parent.get_font();
}

void wsg::Container::repaint(int _x,int _y,int _w,int _h)
{
	clip.x = _x;
	clip.y = _y;
	clip.w = _w;
	clip.h = _h;
	parent.repaint(x+_x,y+_y,_w,_h);
}

void wsg::Container::addChild(Ctrl *child)
{
	childs.push_back(child);
}

wsg::Container::~Container()
{

}