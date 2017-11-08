#include "SDL_wsg.h"
#include "cst.hpp"

wsg::PushButton::PushButton(Container &_parent,std::string _text,int _x,int _y,int _w,int _h,CallBack _callback)
	:Button(_parent,_text,_x,_y,_w,_h),callback(_callback)
{
	parent.addChild(this);
}

void wsg::PushButton::paint(SDL_Surface *screen)
{
	if(redraw)
	{
		if(state&ENTER)
		{
			if(state&DOWN)
			{
				TTF_Font *font = parent.get_font();
				SDL_Color color = { 0, 0, 0 };
				SDL_Surface *temp = TTF_RenderText_Solid(font,text.c_str(),color);
				SDL_Rect clip = { x, y, w, h };
				apply_surface(0,0,screen,canvas,&clip);
				Draw_Pixel(canvas,1,0,0x395971);
				Draw_Pixel(canvas,2,0,0x2E6086);
				Draw_Line(canvas,3,0,w-4,0,0x2C628B);
				Draw_Pixel(canvas,w-3,0,0x2E6086);
				Draw_Pixel(canvas,w-2,0,0x395971);

				Draw_Pixel(canvas,0,1,0x335671);
				Draw_Pixel(canvas,1,1,0x3A688A);
				Draw_Pixel(canvas,2,1,0x869DAB);
				Draw_Line(canvas,3,1,w-4,1,0x9EB0BA);
				Draw_Pixel(canvas,w-3,1,0x95ABB8);
				Draw_Pixel(canvas,w-2,1,0x3A688A);
				Draw_Pixel(canvas,w-1,1,0x335671);

				Draw_Pixel(canvas,0,2,0x2C5F86);
				Draw_Pixel(canvas,1,2,0x869DAB);
				Draw_Pixel(canvas,w-2,2,0x95ABB8);
				Draw_Pixel(canvas,w-1,2,0x2C5F86);
				if(h==6)
				{
					Draw_Line(canvas,2,2,w-3,2,0xE5F4FC);
					Draw_Line(canvas,2,3,w-2,3,0x6DB6DD);
				}
				else if(h==7)
				{
					Draw_Line(canvas,2,2,w-3,2,0xE5F4FC);
					Draw_Line(canvas,2,3,w-3,3,0x98D1EF);
					Draw_Line(canvas,2,4,w-3,4,0x6DB6DD);
				}
				else
				{
					double st = 190/240.0,sb = 176/240.0,lt = 226/240.0,lb = 208/240.0;
					int n = (h-4)/2;
					HSL hsl = { 134/240.0*360.0, st, lt };
					RGB rgb;
					for(int i=0;i<n;++i)
					{
						hsl.s = st+(sb-st)*i/(n-1);
						hsl.l = lt+(lb-lt)*i/(n-1);
						rgb = HSLtoRGB(hsl);
						Draw_Line(canvas,2,2+i,w-3,2+i,rgb.r<<16|rgb.g<<8|rgb.b);
					}
					st = 175/240.0,sb = 148/240.0,lt = 184/240.0,lb = 152/240.0;
					n = h-4-n;
					for(int i=0;i<n;++i)
					{
						hsl.s = st+(sb-st)*i/(n-1);
						hsl.l = lt+(lb-lt)*i/(n-1);
						rgb = HSLtoRGB(hsl);
						Draw_Line(canvas,2,h/2+i,w-3,h/2+i,rgb.r<<16|rgb.g<<8|rgb.b);
					}
				}
				Draw_Pixel(canvas,2,2,0xBACBD5);
				Draw_Pixel(canvas,w-3,2,0xBACBD5);

				Draw_Line(canvas,0,3,0,h-4,0x2C628B);
				Draw_Line(canvas,1,3,1,h-4,0xAAC1CE);
				Draw_Line(canvas,w-2,3,w-2,h-4,0xAAC1CE);
				Draw_Line(canvas,w-1,3,w-1,h-4,0x2C628B);

				Draw_Pixel(canvas,0,h-3,0x2D6188);
				Draw_Pixel(canvas,1,h-3,0x5592B5);
				Draw_Pixel(canvas,2,h-3,0x6DB5DC);
				Draw_Pixel(canvas,w-3,h-3,0x6DB5DC);
				Draw_Pixel(canvas,w-2,h-3,0x5592B5);
				Draw_Pixel(canvas,w-1,h-3,0x2D6188);

				Draw_Pixel(canvas,0,h-2,0x476E8C);
				Draw_Pixel(canvas,1,h-2,0x2F648A);
				Draw_Pixel(canvas,2,h-2,0x63ACD3);
				Draw_Line(canvas,3,h-2,w-4,h-2,0x68B3DB);
				Draw_Pixel(canvas,w-3,h-2,0x63ACD3);
				Draw_Pixel(canvas,w-2,h-2,0x2F648A);
				Draw_Pixel(canvas,w-1,h-2,0x476E8C);

				Draw_Pixel(canvas,1,h-1,0x4B7593);
				Draw_Pixel(canvas,2,h-1,0x2E648C);
				Draw_Line(canvas,3,h-1,w-4,h-1,0x2C628B);
				Draw_Pixel(canvas,w-3,h-1,0x2E648C);
				Draw_Pixel(canvas,w-2,h-1,0x4B7593);
				if(temp!=NULL) apply_surface((w-temp->w)/2,(h-temp->h)/2,temp,canvas);
				SDL_FreeSurface(temp);
			}
			else
			{
				TTF_Font *font = parent.get_font();
				SDL_Color color = { 0, 0, 0 };
				SDL_Surface *temp = TTF_RenderText_Solid(font,text.c_str(),color);
				SDL_Rect clip = { x, y, w, h };
				apply_surface(0,0,screen,canvas,&clip);
				Draw_Pixel(canvas,1,0,0x6693B5);
				Draw_Pixel(canvas,2,0,0x4283B3);
				Draw_Line(canvas,3,0,w-4,0,0x3C7FB1);
				Draw_Pixel(canvas,w-3,0,0x4283B3);
				Draw_Pixel(canvas,w-2,0,0x6693B5);

				Draw_Pixel(canvas,0,1,0x588AAF);
				Draw_Pixel(canvas,1,1,0x699DC3);
				Draw_Pixel(canvas,2,1,0xDFEBF3);
				Draw_Line(canvas,3,1,w-4,1,0xFAFDFE);
				Draw_Pixel(canvas,w-3,1,0xDFEBF3);
				Draw_Pixel(canvas,w-2,1,0x699DC3);
				Draw_Pixel(canvas,w-1,1,0x588AAF);

				Draw_Pixel(canvas,0,2,0x3E80B2);
				Draw_Pixel(canvas,1,2,0xE1EDF4);
				Draw_Pixel(canvas,w-2,2,0xE1EDF4);
				Draw_Pixel(canvas,w-1,2,0x3E80B2);
				if(h==6)
				{
					Draw_Line(canvas,2,2,w-3,2,0xEAF6FD);
					Draw_Line(canvas,2,3,w-2,3,0xA7D9F5);
				}
				else if(h==7)
				{
					Draw_Line(canvas,2,2,w-3,2,0xEAF6FD);
					Draw_Line(canvas,2,3,w-3,3,0xBEE6FD);
					Draw_Line(canvas,2,4,w-3,4,0xA7D9F5);
				}
				else
				{
					double st = 198/240.0,sb = 205/240.0,lt = 228/240.0,lb = 221/240.0;
					int n = (h-4)/2;
					HSL hsl = { 135/240.0*360.0, st, lt };
					RGB rgb;
					for(int i=0;i<n;++i)
					{
						hsl.s = st+(sb-st)*i/(n-1);
						hsl.l = lt+(lb-lt)*i/(n-1);
						rgb = HSLtoRGB(hsl);
						Draw_Line(canvas,2,2+i,w-3,2+i,rgb.r<<16|rgb.g<<8|rgb.b);
					}
					st = 226/240.0,sb = 191/240.0,lt = 208/240.0,lb = 195/240.0;
					n = h-4-n;
					for(int i=0;i<n;++i)
					{
						hsl.s = st+(sb-st)*i/(n-1);
						hsl.l = lt+(lb-lt)*i/(n-1);
						rgb = HSLtoRGB(hsl);
						Draw_Line(canvas,2,h/2+i,w-3,h/2+i,rgb.r<<16|rgb.g<<8|rgb.b);
					}
				}
				Draw_Pixel(canvas,2,2,0xF7FBFE);
				Draw_Pixel(canvas,w-3,2,0xF7FBFE);

				Draw_Line(canvas,0,3,0,h-4,0x3C7FB1);
				Draw_Line(canvas,1,3,1,h-4,0xF8FCFE);
				Draw_Line(canvas,w-2,3,w-2,h-4,0xF8FCFE);
				Draw_Line(canvas,w-1,3,w-1,h-4,0x3C7FB1);
				
				Draw_Pixel(canvas,0,h-3,0x3E81B2);
				Draw_Pixel(canvas,1,h-3,0xD3E6F2);
				Draw_Pixel(canvas,2,h-3,0xDCF0FB);
				Draw_Pixel(canvas,w-3,h-3,0xDCF0FB);
				Draw_Pixel(canvas,w-2,h-3,0xD3E6F2);
				Draw_Pixel(canvas,w-1,h-3,0x3E81B2);

				Draw_Pixel(canvas,0,h-2,0x5A8BB0);
				Draw_Pixel(canvas,1,h-2,0x649BC3);
				Draw_Pixel(canvas,2,h-2,0xD4E7F3);
				Draw_Line(canvas,3,h-2,w-4,h-2,0xE8F5FC);
				Draw_Pixel(canvas,w-3,h-2,0xD4E7F3);
				Draw_Pixel(canvas,w-2,h-2,0x649BC3);
				Draw_Pixel(canvas,w-1,h-2,0x5A8BB0);

				Draw_Pixel(canvas,1,h-1,0x578AAF);
				Draw_Pixel(canvas,2,h-1,0x3E80B2);
				Draw_Line(canvas,3,h-1,w-4,h-1,0x3C7FB1);
				Draw_Pixel(canvas,w-3,h-1,0x3E80B2);
				Draw_Pixel(canvas,w-2,h-1,0x578AAF);
				if(temp!=NULL) apply_surface((w-temp->w)/2,(h-temp->h)/2,temp,canvas);
				SDL_FreeSurface(temp);
			}
		}
		else
		{
			TTF_Font *font = parent.get_font();
			SDL_Color color = { 0, 0, 0 };
			SDL_Surface *temp = TTF_RenderText_Solid(font,text.c_str(),color);
			SDL_Rect clip = { x, y, w, h };
			apply_surface(0,0,screen,canvas,&clip);
			Draw_Pixel(canvas,1,0,0x909090);
			Draw_Pixel(canvas,2,0,0x777777);
			Draw_Line(canvas,3,0,w-4,0,0x707070);
			Draw_Pixel(canvas,w-3,0,0x777777);
			Draw_Pixel(canvas,w-2,0,0x909090);

			Draw_Pixel(canvas,0,1,0x888888);
			Draw_Pixel(canvas,1,1,0x919191);
			Draw_Pixel(canvas,2,1,0xE8E8E8);
			Draw_Line(canvas,3,1,w-4,1,0xFCFCFC);
			Draw_Pixel(canvas,w-3,1,0xE8E8E8);
			Draw_Pixel(canvas,w-2,1,0x919191);
			Draw_Pixel(canvas,w-1,1,0x888888);

			Draw_Pixel(canvas,0,2,0x757575);
			Draw_Pixel(canvas,1,2,0xEAEAEA);
			Draw_Pixel(canvas,w-2,2,0xEAEAEA);
			Draw_Pixel(canvas,w-1,2,0x757575);
			if(h==6)
			{
				Draw_Line(canvas,2,2,w-3,2,0xF2F2F2);
				Draw_Line(canvas,2,3,w-2,3,0xCFCFCF);
			}
			else if(h==7)
			{
				Draw_Line(canvas,2,2,w-3,2,0xF2F2F2);
				Draw_Line(canvas,2,3,w-3,3,0xDDDDDD);
				Draw_Line(canvas,2,4,w-3,4,0xCFCFCF);
			}
			else
			{
				double lt = 228/240.0,lb = 221/240.0;
				int n = (h-4)/2;
				HSL hsl = { 160/240.0*360.0, 0.0, lt };
				RGB rgb;
				for(int i=0;i<n;++i)
				{
					hsl.l = lt+(lb-lt)*i/(n-1);
					rgb = HSLtoRGB(hsl);
					Draw_Line(canvas,2,2+i,w-3,2+i,rgb.r<<16|rgb.g<<8|rgb.b);
				}
				lt = 208/240.0,lb = 195/240.0;
				n = h-4-n;
				for(int i=0;i<n;++i)
				{
					hsl.l = lt+(lb-lt)*i/(n-1);
					rgb = HSLtoRGB(hsl);
					Draw_Line(canvas,2,h/2+i,w-3,h/2+i,rgb.r<<16|rgb.g<<8|rgb.b);
				}
			}
			Draw_Pixel(canvas,2,2,0xFAFAFA);
			Draw_Pixel(canvas,w-3,2,0xFAFAFA);

			Draw_Line(canvas,0,3,0,h-4,0x707070);
			Draw_Line(canvas,1,3,1,h-4,0xFBFBFB);
			Draw_Line(canvas,w-2,3,w-2,h-4,0xFBFBFB);
			Draw_Line(canvas,w-1,3,w-1,h-4,0x707070);

			Draw_Pixel(canvas,0,h-3,0x757575);
			Draw_Pixel(canvas,1,h-3,0xE2E2E2);
			Draw_Pixel(canvas,2,h-3,0xECECEC);
			Draw_Pixel(canvas,w-3,h-3,0xECECEC);
			Draw_Pixel(canvas,w-2,h-3,0xE2E2E2);
			Draw_Pixel(canvas,w-1,h-3,0x757575);

			Draw_Pixel(canvas,0,h-2,0x888888);
			Draw_Pixel(canvas,1,h-2,0x8F8F8F);
			Draw_Pixel(canvas,2,h-2,0xE4E4E4);
			Draw_Line(canvas,3,h-2,w-4,h-2,0xF3F3F3);
			Draw_Pixel(canvas,w-3,h-2,0xE4E4E4);
			Draw_Pixel(canvas,w-2,h-2,0x8F8F8F);
			Draw_Pixel(canvas,w-1,h-2,0x888888);

			Draw_Pixel(canvas,1,h-1,0x868686);
			Draw_Pixel(canvas,2,h-1,0x757575);
			Draw_Line(canvas,3,h-1,w-4,h-1,0x707070);
			Draw_Pixel(canvas,w-3,h-1,0x757575);
			Draw_Pixel(canvas,w-2,h-1,0x868686);
			if(temp!=NULL) apply_surface((w-temp->w)/2,(h-temp->h)/2,temp,canvas);
			SDL_FreeSurface(temp);
		}
		redraw = false;
	}
	apply_surface(x,y,canvas,screen);
}

void wsg::PushButton::event(SDL_Event &_event)
{
	switch(_event.type)
	{
	case SDL_MOUSEMOTION:
		DWEOS
		break;
	case SDL_KEYDOWN:
		if(state&ENTER)
		{
			state |= DOWN;
			redraw = true;
			parent.repaint(x,y,w,h);
		}
		break;
	case SDL_KEYUP:
		if(state&ENTER)
		{
			state &= (ACTIVE|ENTER);
			redraw = true;
			parent.repaint(x,y,w,h);
			callback();
		}
		break;
	default:break;
	}
}

wsg::PushButton::~PushButton()
{

}