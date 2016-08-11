/************************
    颜色
************************/

#ifndef COLOR_H
#define COLOR_H

#include "Fathers.h"
namespace GAME
{
class Color: public Ghost
{

public:

	//static ////const std::string CLASS_NAME;

	static const short MAX_VAL;
	static const short MIN_VAL;

    short r, g, b, alpha;

    Color(short R = 0, short G = 0, short B = 0, short ALPHA = 255):
    r(R), g(G), b(B), alpha(ALPHA)
    {
		using namespace std;
        r = min(MAX_VAL, r);	r = max(MIN_VAL, r);
		g = min(MAX_VAL, g);	g = max(MIN_VAL, g);
		b = min(MAX_VAL, b);	b = max(MIN_VAL, b);
		alpha = min(MAX_VAL, alpha);	alpha = max(MIN_VAL, alpha);
    }

};

//extern static const short MAX_VAL = 255;
//extern static const short MIN_VAL = 0;
//const std::string Color::CLASS_NAME = "Color";


Color operator + ( const Color &a ,const Color &b );

Color operator - ( const Color &a ,const Color &b );
}
#endif // COLOR_H
