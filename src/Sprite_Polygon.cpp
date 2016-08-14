#include "Sprite_Polygon.h"
namespace GAME
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
			//printf("%d\n",i);
			//printf("x,y:%d,%d\n",int(x),int(y));
			//printf("x2,y2:%d,%d\n",int(x + poly.points[i].x +0.5),int(y + poly.points[i].y +0.5));
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
