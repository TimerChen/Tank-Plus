#include "Sprite_Circle.h"
#include "Geo_Calc.h"
#include <cstdio>

namespace TankPlus
{
const double Sprite_Circle::MIN_LENGTH = 1;
const int Sprite_Circle::MAX_POINT= 100;


Sprite_Circle::Sprite_Circle( int X, int Y, int Z, Circle CIR, short dis ):
Sprite_Base( X, Y, Z ), cir(CIR), DISPLAY(dis) {}

void Sprite_Circle::Draw()
{
	if(!DISPLAY)return;

	double len = 2*M_PI*cir.r, Per_Rad, Now_Rad;
    int Need_Point = len / MIN_LENGTH;
	Need_Point = std::min( Need_Point, MAX_POINT );

	//Need_Point = 360;

    Per_Rad = M_PI*2 / Need_Point;
    Point p;

	//v = Point( 0, cir.r );
    //Draw Inside

	//setcolor
	DrawTool::SetColor( Color_Inside );
	Now_Rad=0;

    glBegin(GL_POLYGON);
    for(int i=0; i<Need_Point; i++)
    {
		p = Geo_Calc::GetPoint_OnCircle( cir.r, Now_Rad );
		DrawTool::DrawPoint3( x + p.x +0.5, y + p.y +0.5, z );
        Now_Rad += Per_Rad;

    }
    glEnd();

    //v = Point( 0, cir.r );
	//Draw Edges

    //setcolor
	DrawTool::SetColor( Color_Edge );
	Now_Rad=0;

    glBegin(GL_LINE_LOOP);

    //printf("%g\n",Per_Rad*Need_Point);
    for(int i=0; i<Need_Point; i++)
    {
		p = Geo_Calc::GetPoint_OnCircle( cir.r, Now_Rad );
		DrawTool::DrawPoint3( x + p.x +0.5, y + p.y +0.5, z );
        Now_Rad += Per_Rad;
    }
    glEnd();


}
}

