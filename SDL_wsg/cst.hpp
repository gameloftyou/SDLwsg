/*======================
 * name: ColorSpaceTool
 * coder: gameloftyou
 * version: v1.00
 *======================*/

#ifndef __CST_HPP__
#define __CST_HPP__
#define ABS(a) (a>0?a:-a)
#define PCS 1E-15

typedef struct 
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
} RGB;

typedef struct 
{
	double h;
	double s;
	double l;
} HSL;

HSL RGBtoHSL(RGB rgb)
{
	double r = rgb.r/255.0;
	double g = rgb.g/255.0;
	double b = rgb.b/255.0;
	double maxcolor,mincolor,l,s,h;
	HSL hsl;

	if(r>g)
	{
		if(r>b)
		{
			maxcolor = r;
			if(g>b) mincolor = b;
			else mincolor = g;
		}
		else
		{
			maxcolor = b;
			mincolor = g;
		}
	}
	else
	{
		if(g>b)
		{
			maxcolor = g;
			if(r>b) mincolor = b;
			else mincolor = r;
		}
		else
		{
			maxcolor = b;
			mincolor = r;
		}
	}
	l = (maxcolor+mincolor)/2;
	if((maxcolor-mincolor)<PCS)
	{
		s = 0;
		h = 0;
	}
	else
	{
		if(l<0.5) s = (maxcolor-mincolor)/(maxcolor+mincolor);
		else s = (maxcolor-mincolor)/(2.0-maxcolor-mincolor);
		if(maxcolor==r) h = (g-b)/(maxcolor-mincolor);
		else if(maxcolor==g) h = 2.0+(b-r)/(maxcolor-mincolor);
		else h = 4.0+(r-g)/(maxcolor-mincolor);
		h*=60.0;
		if(h<0) h+=360.0;
	}
	hsl.h = h;
	hsl.s = s;
	hsl.l = l;
	return hsl;
}

double HSL2RGB(double temp1,double temp2,double temp3)
{
	if(temp3<0) temp3+=1.0;
	else if(temp3>1) temp3-=1.0;
	if(6.0*temp3<1) return temp1+(temp2-temp1)*6.0*temp3;
	else if(2.0*temp3<1) return temp2;
	else if(3.0*temp3<2) return temp1+(temp2-temp1)*(2.0/3.0-temp3)*6.0;
	return temp1;
}

RGB HSLtoRGB(HSL hsl)
{
	double h = hsl.h;
	double s = hsl.s;
	double l = hsl.l;
	double temp1,temp2;
	unsigned char r,g,b;
	RGB rgb;

	if(s<PCS)
	{
		r = g = b = (unsigned char)(l*255);
	}
	else
	{
		if(l<0.5) temp2 = l*(1.0+s);
		else temp2 = l+s-l*s;
		temp1 = 2.0*l-temp2;
		h/=360.0;
		r = (unsigned char)(255*HSL2RGB(temp1,temp2,h+1.0/3.0));
		g = (unsigned char)(255*HSL2RGB(temp1,temp2,h));
		b = (unsigned char)(255*HSL2RGB(temp1,temp2,h-1.0/3.0));
	}
	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
	return rgb;
}

#endif //__CST_HPP__