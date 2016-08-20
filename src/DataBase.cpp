#include "DataBase.h"
#include <stdexcept>
#include <cmath>

namespace GAME
{
namespace DataBase
{
bool CheckWeaponId(int id)
{
    return id >= 0 && id < WEAPON_NUM;
}
Polygon ShellShape[WEAPON_NUM] =
{
    Polygon(Point(0, 0), Point(1, 1))
};
void WeaponShoot(Battlefield *field, const Ball_Polygon &shooter, const Weapon &weapon, const Point &gundir)
{
    if (!CheckWeaponId(weapon.id))
        throw std::out_of_range("weapon id wrong");
    if (Geo_Calc::Length(gundir) < 1e-5)
        throw std::logic_error("no gundir");
    Target tgt;
    tgt.owner = -1;
    tgt.blood = tgt.maxblood = ShellBlood[weapon.id];
    tgt.shape = field->sandbox.balls.insert(ShellBall(weapon.id, shooter, gundir));
    tgt.type = 0;
    int tgt_id = field->target.insert(tgt);
    Shell shell;
    shell.target = tgt_id;
    shell.attack = weapon.attack;
    ShellEffect(weapon.id, shell);
    field->shell.insert(shell);
}
Ball_Polygon ShellBall(int id, const Ball_Polygon &shooter, const Point &gundir)
{
    double angle = atan2(gundir.y, gundir.x);
    Point speed = shooter.v + Geo_Calc::Zero(gundir) * ShellVelocity[id];
    Point cent = shooter.cent + speed; /* let shell leave tank */
    return Ball_Polygon(1, ShellMass[id], speed, Infinite, ShellShape[id], 0, angle, cent);
}
void ShellEffect(int id, Shell &shell)
{

}
}
}
