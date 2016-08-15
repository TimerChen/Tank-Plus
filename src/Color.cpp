#include "Color.h"
namespace GAME
{
const short Color::MAX_VAL = 255;
const short Color::MIN_VAL = 0;


Color operator + ( const Color &a ,const Color &b )
{
    Color c;
    c = Color(a.r+b.r,a.g+b.g,a.b+b.b,a.alpha+b.alpha);
    return c;
}

Color operator - ( const Color &a ,const Color &b )
{
    Color c;
    c = Color(a.r-b.r,a.g-b.g,a.b-b.b,a.alpha-b.alpha);
    return c;
}

}
