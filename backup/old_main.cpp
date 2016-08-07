#include "GL/glut.h"

#include "Sprite_Circle.h"
#include "Sprite_Polygon.h"
#include "Geo_Calc.h"
#include "Rect.h"
#include "DrawTool.h"

#include <cstdio>
using namespace GAME;
double last[2];

void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
	//glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	//glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
	//glDepthRange(0, 1);
	//glClearDepth(1);
	//glDepthFunc(GL_LEQUAL);

	Sprite_Circle O1(100,100,7,Circle(300),1),O2(250,300,4,Circle(150),1),O3(200,330,1,Circle(70),1);
    //O1.Draw();
	//O1.x += rand()%50;
	//O1.y += rand()%50;
    O1.Color_Inside = Color(50,50,100,200);
    O1.Color_Edge = Color(255,255,255);

	//O2.x += rand()%50;
	//O2.y += rand()%50;
	O2.Color_Inside = Color(50,100,50,200);
    O2.Color_Edge = Color(255,255,200);

	//O3.x += rand()%50;
	//O3.y += rand()%50;
	O3.Color_Inside = Color(100,50,50,200);
    O3.Color_Edge = Color(255,255,255);
    //glDepthMask(GL_FALSE);


	last[0] += 0.04;
	last[1] += 0.01;
	if(last[0] > M_PI*6) last[0] -= M_PI*6;
	if(last[1] > M_PI*2) last[1] -= M_PI*2;
	if(last[1] < 0) last[1] += M_PI*2;

	//glDepthMask(GL_TRUE);
    Rect rr = Rect(0,0,150,70);
    //Point CEN = Point(0,70);


	//Sprite_Polygon R1(200,330-70,7,TmpCir.to_poly( 3, last[0] ),1);

    Circle TmpCir = Circle( 10 );
	Sprite_Polygon R1;

	R1 = Sprite_Polygon(O1.x,O1.y-O1.cir.r,O1.z,TmpCir.to_poly( 3, last[0] ),1);
    R1.poly = Geo_Calc::Rotate( Point(0,O1.cir.r), R1.poly, last[1] );
	R1.Color_Inside = Color(170,150,180,255);
    R1.Color_Edge = Color(170+30,150+30,180+30);
    O1.Draw();
	R1.Draw();


	R1 = Sprite_Polygon(O2.x,O2.y-O2.cir.r,O2.z,TmpCir.to_poly( 3, last[0] ),1);
    R1.poly = Geo_Calc::Rotate( Point(0,O2.cir.r), R1.poly, last[1]+0.7 );
	R1.Color_Inside = Color(170,150,180,255);
    R1.Color_Edge = Color(170+30,150+30,180+30);
    O2.Draw();
	R1.Draw();


	R1 = Sprite_Polygon(O3.x,O3.y-O3.cir.r,O3.z,TmpCir.to_poly( 3, last[0] ),1);
    R1.poly = Geo_Calc::Rotate( Point(0,O3.cir.r), R1.poly, last[1]-0.2 );
	R1.Color_Inside = Color(170,150,180,255);
    R1.Color_Edge = Color(170+30,150+30,180+30);
    O3.Draw();
	R1.Draw();

	//DrawTool::SetColor(Color(255,255,255,255));

    glutSwapBuffers();
}
int main(int argc, char *argv[])
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(GAME::SCREEN_WIDTH, GAME::SCREEN_HEIGHT);

    glutCreateWindow("Jump!");

	//glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    printf("%d %d\n",GAME::SCREEN_WIDTH, GAME::SCREEN_HEIGHT);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}
