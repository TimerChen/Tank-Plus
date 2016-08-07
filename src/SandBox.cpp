#include "SandBox.h"
#include "Geo_Calc.h"

SandBox::SandBox(){}
int SandBox::KickWalls( Ball b )
{
	int re=0;
	int i;
    for(i=0; i<walls.size(); i++)
    if(Geo_Calc::CheckKick_PolygonToPolygon(b.shape, walls[i].shape))
		re = re|(1 << walls[i].type);
	return re;
}
bool SandBox::KickTmpBalls( Ball b, int ignore )
{
	return 0;
    int i;
    for(i=0; i<TmpB.size(); i++)
	if( i!=ignore && Geo_Calc::CheckKick_PolygonToPolygon( b.shape, TmpB[i].shape ) )
		return 1;
	return 0;

}
int SandBox::CantMove( int i )
{
	return KickWalls(TmpB[i]);// || KickTmpBalls(TmpB[i], i) ;
}
bool SandBox::GetNextBall( double time )
{
	bool ok = 0;
    for( int i = 0; i < balls.size(); i++ )
    {

        TmpB[i] = balls[i];
        TmpB[i].Addv( forces[i]/balls[i].m );
        TmpB[i].shape.Move( TmpB[i].v*time );
        //if( KickWalls(TmpB[i]) ) ok = 1;

    }
    //for( int i = 0; !ok && i < balls.size(); i++ )   if(KickTmpBalls(TmpB[i], i))ok=1;
    for( int i = 0; i < balls.size(); i++ )
    {
		int tmp = CantMove(i);
		if(tmp&1) ok = 1;
		if(tmp&2) GAME::DIE = 1;
    }

	return ok;
}
void SandBox::GoNext()
{

	for( int i=0; i<balls.size(); i++ )
		balls[i] = TmpB[i];

}
void SandBox::GetKick( double use, short type )
{
	using namespace std;
	using namespace GAME;
	int dn = wait_f.size();
	forces.clear();
	forces.resize( balls.size() );
	for( int i = 1,j; i <= dn; i++ )
	{
        tuple<Point, int, double >now = wait_f.front();wait_f.pop();
		get<2>(now) -= use;
		if(get<2>(now) < -eps)continue;
		j = get<1>(now);
        forces[j] = forces[j] + get<0>(now);
        if(get<2>(now) < eps)continue;
        wait_f.push(now);
	}
	if(type)return;
    for( int i = 0; i < balls.size(); i++ )
    {
        forces[i] = forces[i] + Field_Force;
		Ball nb;Point tv;
		double XS[2][2]={{-0.3,-0.3}, {-0.7,0}}, MC[2][2] = { {0.5,0.5}, {0.7,1}  };
        //check forces
        if( fabs(forces[i].x) > eps )
        {
			nb = balls[i];
			tv = Geo_Calc::Zero(Point(forces[i].x, 0))*2*eps;
			nb.shape.Move(tv);
			if( KickWalls(nb)&1 )
			{
                forces[i].x = 0;//,printf("NOFORCES1\n");

				balls[i].v.y = balls[i].v.y*MC[0][forces[i].x > eps];
			}
        }
        if( fabs(forces[i].y) > eps )
        {
			nb = balls[i];
			tv = Geo_Calc::Zero(Point(0, forces[i].y))*2*eps;
			nb.shape.Move(tv);
			if( KickWalls(nb)&1 )
			{
                forces[i].y = 0;
                //printf("NOFORCES2\n");
                if(keyboard[GLUT_KEY_LEFT]==0 && keyboard[GLUT_KEY_RIGHT]==0)
                balls[i].v.x = balls[i].v.x*MC[1][forces[i].y > eps];
			}
        }
		balls[i].Addv(forces[i]/balls[i].m);

        //get v
        if( fabs(balls[i].v.x) > eps )
        {
			nb = balls[i];
			tv = Geo_Calc::Zero(Point(balls[i].v.x, 0))*4*eps;
			nb.shape.Move(tv);
			if( KickWalls(nb)&1 )
                balls[i].v.x = balls[i].v.x*XS[0][balls[i].v.x > eps];//,
                //printf("BACK1\n");
        }
        if( fabs(balls[i].v.y) > eps )
        {
			nb = balls[i];
			tv = Geo_Calc::Zero(Point(0, balls[i].v.y))*4*eps;
			nb.shape.Move(tv);
			if( KickWalls(nb)&1 )
                balls[i].v.y = balls[i].v.y*XS[1][balls[i].v.y > eps];//,
                //printf("BACK2\n");
        }

    }

}
void SandBox::Update( double time )
{
	using namespace GAME;
	//printf("st\n");
	GetKick(0, 1);

    double L,R,left = time,SaveL;
    TmpB.clear();
    TmpB.resize( balls.size() );
    std::vector<Ball>SaveB;
    bool nomove=0,ok;
    L = 0;
    R = time;
    while( left > 0 )
    {
		//printf("[left]%f\n",left);
		L = 0;R = left;ok=0;SaveL=0;
		while( R-L > eps/10)
		{

			double MID = (L+R)/2;
			if( !GetNextBall( MID ) )SaveB = TmpB,ok=1,SaveL = L = MID;
			else R = MID;

		}

		//printf("%.2f %.2f\n",balls[0].v.x, balls[0].v.y);
        if(ok){
			//printf("CantMove?:%d\n",CantMove(0));
			//printf("%.6f\n",SaveL);
			left -= SaveL;
			//printf("MOVE\n");
            TmpB = SaveB;
            GoNext();
            nomove = 0;
        }
		else
		{
				if(!nomove)
				{
					nomove=1;
					//printf("CAN'T MOVE\n");

				}
				else{
					//printf("CAN'T MOVE\n");
					//printf("%.2f %.2f\n",balls[0].v.x, balls[0].v.y);
					return;
				}
		}
		GetKick(SaveL);

    }

	/*
	using namespace std;
	int i, j;
	i = KickWalls(balls[0]);
	printf("[now]%d\n",i);
	//printf("%d\n");
	//add forces
	forces.clear();
	forces.resize( balls.size() );
    for(i=1,j=wait_f.size();i<=j;i++)
    {
        tuple<Point, int, int> tmp;
        tmp = wait_f.front();wait_f.pop();
        if(get<1>(tmp) < forces.size() && get<1>(tmp) >= 0)
			forces[get<1>(tmp)] = forces[get<1>(tmp)] + get<0>(tmp);
        get<2>(tmp)--;
        if(get<2>(tmp) > 0)wait_f.push(tmp);
    }
    //Field Force
    Point testf = Geo_Calc::Zero(Field_Force);
    //printf("[testf]%.3f %.3f\n",testf.x,testf.y);
    for(i=0; i<balls.size(); i++)
    {
        Ball tmp = balls[i];
        //tmp.shape.Move(testf);
        tmp.v = Point();
		tmp.Addv(Field_Force);
		tmp.shape.Move( Field_Force );
		//printf("[tmp]%.3f %.3f\n",tmp.shape.points[0].x,tmp.shape.points[0].y);
        if(!KickWalls(tmp))forces[i] = forces[i] + Field_Force;
        else forces[i] = forces[i] + Field_Force*-0.9,printf("No Field Force\n");

    }
    //printf("[testf]%.3f %.3f\n",forces[0].x,forces[0].y);
    TmpB.resize(balls.size());
    //Get Next Ball
    for(i=0; i<balls.size(); i++)
    {
		Point a;
		TmpB[i] = balls[i];
		a = forces[i] / TmpB[i].m;
		//printf("a=%.3f\n",a);
		//TmpB[i].v = TmpB[i].v + a;
		TmpB[i].Addv( a );
		TmpB[i].shape.Move( TmpB[i].v );
    }

    printf("ok\n");
    printf("%.3f %.3f\n",balls[0].shape.points[0].x,balls[0].shape.points[0].y);
    printf("%.3f %.3f\n",TmpB[0].shape.points[0].x,TmpB[0].shape.points[0].y);
	//Move
	for(i=0; i<balls.size(); i++)
	if(!KickWalls( TmpB[i] ) && !KickTmpBalls( TmpB[i], i ))
	{
		//printf("move\n");
        balls[i] = TmpB[i];
	}
	else{
		using namespace GAME;
		Point tv;
        if(fabs(balls[i].v.x) > eps)
        {

            tv = Point(balls[i].v.x, 0);
            //double l,r;

        }
        if(fabs(balls[i].v.y) > eps)
        {
            if(tv.y < 0)
            {

				tv = Point(0, balls[i].v.y);

            }
            else
            {

				tv = Point(0, balls[i].v.y);

            }

        }
		//printf("no move\n");
	}*/
}
void SandBox::AddForce( Point F, int aim, int life )
{
    if(aim >= balls.size())return;
    wait_f.push(std::tuple<Point, int, int>(F,aim,life));
}
