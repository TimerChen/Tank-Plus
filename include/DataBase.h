#ifndef DATABASE_H
#define DATABASE_H

#include "Point.h"
#include "Battlefield.h"
#include "Weapon.h"

namespace GAME
{
namespace DataBase
{
const int DefaultWallBlood = 1000;
const int Infinite = 100000000;

const int WEAPON_NUM = 1;
constexpr int ShellBlood[WEAPON_NUM] = {1};
constexpr int ShellMass[WEAPON_NUM] = {1};
constexpr int ShellVelocity[WEAPON_NUM] = {5};
extern Polygon ShellShape[WEAPON_NUM];
bool CheckWeaponId(int id);
void WeaponShoot(Battlefield *field, const Ball_Polygon &shooter, const Weapon &weapon, const Point &gundir);
Ball_Polygon ShellBall(int id, const Ball_Polygon &shooter, const Point &gundir);
void ShellEffect(int id, Shell &shell);
}
}

#endif // DATABASE_H
