#include "SDL_wsg.h"

wsg::Button::Button(Container &_parent,std::string _text,int _x,int _y,int _w,int _h)
	:Container(_parent,_x,_y,_w,_h),text(_text)
{

}

wsg::Button::~Button()
{

}