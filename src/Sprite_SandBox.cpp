#include "Sprite_SandBox.h"
#include "Sprite_Polygon.h"
#include "Ball.h"
namespace GAME
{
Sprite_SandBox::Sprite_SandBox( int X, int Y, int Z, SandBox* AIM, short dis ):
//Sprite_Base(X, Y, Z),aim(AIM), DISPLAY(dis){  }
x(X), y(Y), z(Z),aim(AIM), DISPLAY(dis){  }

void Sprite_SandBox::Draw()
{
	if(!DISPLAY || aim == NULL)return;
	int i;

    Sprite_Polygon s_tmp;
    s_tmp = Sprite_Polygon( x, y, z );
	//printf("%d %d %d\n",x,y,z);
    s_tmp.DISPLAY = 1;

    for( i=0; i< aim->walls.size(); i++)
    {
        s_tmp.poly = aim->walls[i].shape;
        if(aim->walls[i].Default_EdgeColor) s_tmp.Color_Edge = Color_Wall_Edge;
        else s_tmp.Color_Edge = aim->walls[i].Color_Edge;
        if(aim->walls[i].Default_InsideColor) s_tmp.Color_Inside = Color_Wall_Inside;
        else s_tmp.Color_Inside = aim->walls[i].Color_Inside;
        s_tmp.Draw();
    }


    for( i=0; i< aim->balls.size(); i++)
    {
        s_tmp.poly = aim->balls[i].shape;
        if(aim->balls[i].Default_EdgeColor) s_tmp.Color_Edge = Color_Ball_Edge;
        else s_tmp.Color_Edge = aim->balls[i].Color_Edge;
        if(aim->balls[i].Default_InsideColor) s_tmp.Color_Inside = Color_Ball_Inside;
        else s_tmp.Color_Inside = aim->balls[i].Color_Inside;
        s_tmp.Draw();
    }

}
}
