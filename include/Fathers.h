/************************
    父类
************************/

#ifndef FATHERS_H
#define FATHERS_H


#include <vector>
#include <string>
#include <cmath>
#include <queue>
#include <cstdio>
#include <tuple>

#ifndef M_PI
#define M_PI 3.1415926
#endif

namespace GAME
{
extern int TIME_COUNT;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int SCREEN_DEEPTH;
extern double eps;
extern int keyboard[200];
extern int DIE;

class Object
{
public:
    //static const std::string CLASS_NAME;

    void print();
};

class Entity: public Object
{
public:
    //static const std::string CLASS_NAME;
    int LAST_TIME;
    Entity()
    {
        Update_TIME();
    }
    void Update_TIME()
    {
        LAST_TIME = TIME_COUNT;
    }
    void Draw();
};

class Ghost: public Object
{
public:
    //static const std::string CLASS_NAME;

};
}

#endif
