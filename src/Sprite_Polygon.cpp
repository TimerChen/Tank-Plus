#include "Sprite_Polygon.h"
namespace TankPlus
{
Sprite_Polygon::Sprite_Polygon( int X, int Y, int Z, Polygon POLY, short dis ):
    Sprite_Base( X, Y, Z ), poly(POLY), DISPLAY(dis) {}

void Sprite_Polygon::Draw()
{
    if(!DISPLAY)return;

    if( poly.points.size() > 2 )
    {
		//Draw Inside

		//setcolor
		DrawTool::SetColor( Color_Inside );

		glBegin(GL_POLYGON);
		for(int i=0; i<poly.points.size(); i++)
		{
			DrawTool::DrawPoint3( x + poly.points[i].x +0.5, y + poly.points[i].y +0.5, z );
		}
		glEnd();

	}

		//Draw Edges

		//setcolor
		DrawTool::SetColor( Color_Edge );

		glBegin(GL_LINE_LOOP);
		for(int i=0; i<poly.points.size(); i++)
		{
			DrawTool::DrawPoint3( x + poly.points[i].x +0.5, y + poly.points[i].y +0.5, z );
		}
		glEnd();

}
}
