#include "SDL_wsg.h"

using wsg::Ctrl;
using wsg::App;
using wsg::StaticText;
using wsg::SysLink;
using wsg::PushButton;
using wsg::Panel;
using wsg::Runnable;
using wsg::Thread;


struct MyPanel : public Panel,Runnable {

	bool RUN;

	MyPanel(Container &_parent,Uint32 _color,int _x,int _y,int _w,int _h)
		:Panel(_parent,_color,_x,_y,_w,_h),RUN(false){}
	
	void run()
	{
		while(1)
		{
			parent.repaint(x,y,w,h);
			SDL_Delay(1000);
		}
	}

	void start()
	{
		if(RUN) return;
		Thread(this).start();
		RUN = true;
	}

	void paint(SDL_Surface *screen)
	{
		color ^= 0xFF;
		SDL_FillRect(canvas,NULL,color);
		wsg::apply_surface(x,y,canvas,screen);
	}

};


int main(int argc,char *argv[])
{
	Ctrl::Init();
	App app("bg.png",480,800);
	StaticText text(app,"StaticText",20,20,100,20);
	SysLink link(app,"SysLink",20,50,70,20);
	PushButton pushbutton(app,"PushButton",20,80,120,30);
	Panel panel(app,0xF0F0F0,10,120,140,180);
	MyPanel mypanel(panel,0xFF0000,20,20,100,100);
	PushButton pushbutton1(panel,"start",10,130,120,30,std::bind(&MyPanel::start,&mypanel));
	app.run();
	return 0;
}