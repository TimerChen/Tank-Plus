
#include <GL/glut.h>



#include "Sprite_Circle.h"
#include "Sprite_Polygon.h"
#include "Geo_Calc.h"
#include "Rect.h"
#include "DrawTool.h"
#include "Sprite_SandBox.h"

#include <cstdio>
#include <ctime>
using namespace GAME;
double last[2];
Sprite_SandBox screen;
SandBox box;
int Last = clock();
/*
int AllZ;
Point S;
void DealWithKey()
{


    if(keyboard[GLUT_KEY_UP]){
		//printf("push up\n");
		if(AllZ - keyboard[GLUT_KEY_UP] <= 10)
		{
			//box.balls[0].v.y=0;
			box.balls[0].Addv(Point(0,-1));
			//printf("ljs");
		}
		//box.AddForce(Point(0,-2),0,2);
    }
    if(keyboard[GLUT_KEY_LEFT]){
		//printf("push left\n");
        box.AddForce(Point(-2,0),0,2);
        //box.balls[0].v.x=0;
        //box.balls[0].Addv(Point(-2,0));
        //box.balls[0].v.x = -7;
    }
    if(keyboard[GLUT_KEY_RIGHT]){
		//printf("push right\n");
		box.AddForce(Point(2,0),0,2);
		//box.balls[0].v.x=0;
		//box.balls[0].Addv(Point(2,0));
		//box.balls[0].v.x = 7;
    }
    if(keyboard[GLUT_KEY_DOWN]){
		//printf("push down\n");
		box.AddForce(Point(0,2),0,2);
    }

}
void PushKB( int key,int x,int y ){
	if(keyboard[key])return;
    keyboard[key]=AllZ;

    if(key == GLUT_KEY_UP)
    {
		box.balls[0].v.y=0;
        box.balls[0].Addv(Point(0,-4));
        //box.AddForce(Point(0,-0.5),0,5);
        //printf("push [UP]\n");
    }



}
void UpKB( int key, int x, int y )
{
	keyboard[key]=0;
	if(key == GLUT_KEY_UP){
		//printf("ERROR\n");
	}
}
void display()
{
	++AllZ;
	//Clac Fps
	char Title[50];int now;
	now = clock();
	//printf("%d %d : %d\n",now,Last,CLOCKS_PER_SEC);
	if(now - Last >= CLOCKS_PER_SEC){
		sprintf(Title,"Jump!\t[ Fps:%d ]",RunTimes);
		glutSetWindowTitle(Title);
        Last = now;
        RunTimes=0;
	}RunTimes++;
	//DealWith Keyboard
	DealWithKey();
	//Start Get
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
	//glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	//glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
	//glDepthRange(0, 1);
	//glClearDepth(1);
	//glDepthFunc(GL_LEQUAL);
/*
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

	//DrawTool::SetColor(Color(255,255,255,255));*
	Point cent = Point(400,150);
	cent = box.balls[0].shape.points[0];
    //box.AddForce(box.Field_Force*-1,1,1);
    if(box.balls.size() > 1){
        box.AddForce((cent - box.balls[1].shape.points[0])*0.1,1,1);
        cent = box.balls[1].shape.points[0];
    }
    //box.AddForce((cent - box.balls[0].shape.points[0])*0.01,0,1);
    //box.AddForce(box.Field_Force,1,1);

	Sprite_Polygon sp;
	sp = Sprite_Polygon( 0,0,7,box.walls[0].shape,1 );
	sp.Color_Edge = Color(255,255,255);
	sp.Draw();
	box.Update();
	if( GAME::DIE )
	{
        box.balls[0].shape.MoveTo(S);
        DIE = 0;
	}
	screen.Draw();
    glutSwapBuffers();
}
void kb( unsigned char key,int x,int y )
{
    if(key == ' ')
    {
    }

}

void testup( unsigned char key, int x, int y )
{
	putchar(key);
	fflush(stdout);
}
void initialize(){
    screen = Sprite_SandBox( 0,0,5,&box,1 );
    printf("%d %d %d\n",screen.x,screen.y,screen.z);
    screen.Color_Ball_Edge = Color(255,255,255);
    screen.Color_Ball_Inside = Color(200,150,150,200);
    screen.Color_Wall_Edge = Color(255,255,255);
    screen.Color_Wall_Inside =Color(100,100,100,200);
    //Polygon poly;
    box.Field_Force = Point( 0,2 );
    Point hh = Point(100,GAME::SCREEN_HEIGHT*2/3-7);
    S = hh = Point(100,50);
    box.balls.push_back( Ball(Polygon(hh, hh + Point(20,20)),7,Point(),10) );
    hh = hh + Point(100,100);
    //box.balls.push_back( Ball(Polygon(hh, hh + Point(7,7)),7,Point(),5) );

    box.walls.push_back( Polygon(Point(+5,+5), Point(SCREEN_WIDTH-5,GAME::SCREEN_HEIGHT-5)) );
    box.walls.push_back( Polygon(Point(0,GAME::SCREEN_HEIGHT*2/3), Point(GAME::SCREEN_WIDTH,GAME::SCREEN_HEIGHT)) );
    box.walls.push_back( Polygon(Point(200,GAME::SCREEN_HEIGHT*1.7/3), Point(200+50,GAME::SCREEN_HEIGHT)) );
    //for(int i=1;i<=50;i++)
    box.walls.push_back( Polygon(Point(100,GAME::SCREEN_HEIGHT*1.3/3), Point(100+50,GAME::SCREEN_HEIGHT)) );

	box.walls.push_back( Polygon(Point(30,100), Point(230,130)) );

	box.walls.push_back( Wall(Circle( 17,Point(530,GAME::SCREEN_HEIGHT*2/3 - 17*2/3)).to_poly(3,M_PI),1) );

    for(int i=1;i<=120;i++)
        box.walls.push_back( Wall(Circle( 17,Point(530,GAME::SCREEN_HEIGHT*2/3 - 17*2/3)).to_poly(3,M_PI),1) );

	box.walls[0].Default_InsideColor = 0;
	box.walls[0].Color_Inside = Color(2,2,2,0);
	box.balls[0].Default_InsideColor = 0;
	box.balls[0].Color_Inside = Color(250,150,70);
}*/
void initialize()
{

    screen = Sprite_SandBox( 0,0,5,&box,1 );
    screen.Color_Ball_Edge = Color(255,255,255);
    screen.Color_Ball_Inside = Color(200,150,150,200);
    screen.Color_Wall_Edge = Color(255,255,255);
    screen.Color_Wall_Inside =Color(100,100,100,200);
    box.Field_Force = Point(0,2);

    Ball_Polygon nb;
    Wall nw;
    nw = Wall(1,GAME::Polygon(Point(1,GAME::SCREEN_HEIGHT-80-50), Point(GAME::SCREEN_WIDTH,GAME::SCREEN_HEIGHT-50) ) );
    box.AddWall(nw);
    nw = Wall(1,GAME::Polygon(Point(1,1), Point(GAME::SCREEN_WIDTH,7) ) );
    box.AddWall(nw);
    nw = Wall(1,GAME::Polygon(Point(1,1), Point(7,GAME::SCREEN_HEIGHT-1) ) );
    box.AddWall(nw);
    nw = Wall(1,GAME::Polygon(Point(GAME::SCREEN_WIDTH-7,1), Point(GAME::SCREEN_WIDTH,GAME::SCREEN_HEIGHT) ) );
    box.AddWall(nw);

    nw = Wall(1,GAME::Geo_Calc::CircleToPolygon(GAME::Circle(40,Point(GAME::SCREEN_WIDTH/2,GAME::SCREEN_HEIGHT-80-50)),3,M_PI/3) ) ;
    box.AddWall(nw);

    nb = Ball_Polygon(1,2,0,8, GAME::Polygon(Point(-15,-15), Point(+15,+15)) );

    //nb.shape = GAME::Geo_Calc::CircleToPolygon(Circle(15),7,0);

    nb.pos =Point(GAME::SCREEN_WIDTH/2-50,40);
    int ids_b[10],ids_w[10];
    ids_b[0] = box.AddBall(nb);

    nb.pos = nb.pos + Point(0,40);

	nb.Default_InsideColor = 0;
	nb.Color_Inside = Color(250,150,70);
    nb.rotate_v = 0.2;
    ids_b[1] = box.AddBall(nb);
    box.AddTracing(1,0);
    /*
    ids_b[1] = box.AddBall(nb);

    nb.pos = nb.pos + Point(30,5);
    nb.Color_Inside = nb.Color_Inside + Color(2,15,30);
    box.AddBall(nb);

    nb.pos = nb.pos + Point(30,5);
    nb.Color_Inside = nb.Color_Inside + Color(2,15,30);
    box.AddBall(nb);

    nb.pos = nb.pos + Point(30,5);
    nb.Color_Inside = nb.Color_Inside + Color(2,15,30);
    box.AddBall(nb);

    box.AddForce(Point(-1.5,-0.7),ids_b[1],5);
    */
    system("pause");
}
void display()
{
    RunTimes++;
    printf("go%d\n",RunTimes);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
	//glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
    /*
	box.Field_Force = GAME::Geo_Calc::Rotate(box.Field_Force,0.01);

    Point center = Point(GAME::SCREEN_WIDTH/2,GAME::SCREEN_HEIGHT/2);
	glBegin(GL_LINES);
	DrawTool::SetColor(Color(255,255,255));
	DrawTool::DrawPoint3(center.x,center.y,0);
	DrawTool::DrawPoint3(center.x+box.Field_Force.x*100,center.y+box.Field_Force.y*100,0);
	//DrawTool::DrawPoint3(20,70,0);
	glEnd();
    */

    box.Refresh();
    while(box.Run(box.GetNextTime(), SandBox::DefaultDealBW,SandBox::DefaultDealBB ));
    Sleep(1000/60);
    screen.Draw();
    glutSwapBuffers();
    //system("pause");
}
int main(int argc, char *argv[])
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(GAME::SCREEN_WIDTH, GAME::SCREEN_HEIGHT);
    //glutInitWindowSize(100,100);

    glutCreateWindow("Tank: Plus!");
    printf("initialize\n");
    initialize();

    /*glutKeyboardFunc(kb);
    glutSpecialFunc(PushKB);
	glutSpecialUpFunc(UpKB);
	glutKeyboardUpFunc(testup);
	initialize();*/
	//glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    //printf("%d %d\n",GAME::SCREEN_WIDTH, GAME::SCREEN_HEIGHT);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}
