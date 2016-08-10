#include "DrawTool.h"
#include "GL/glut.h"
namespace TankPlus
{
double DrawTool::Getx( int X )
{

	return ( 2.0*X / SCREEN_WIDTH ) - 1;

}

double DrawTool::Gety( int Y )
{

	return -( ( 2.0*Y / SCREEN_HEIGHT ) - 1 );

}

double DrawTool::Getz( int Z )
{

	return ( 1.0*Z / SCREEN_DEEPTH );

}

void DrawTool::DrawPoint3( int X, int Y, int Z )
{

	double x, y, z;
    x = Getx(X);
    y = Gety(Y);
    z = Getz(Z);
    //printf("%d\n",Z);
    //if(z > 0)printf("%.3f\n",z);
	glVertex3f( x, y, z );

}

void DrawTool::SetColor( Color c )
{

	glColor4ub( c.r, c.g, c.b, c.alpha );

}
}
