#include "Battlefield.h"
#include "Player_ai.h"
#include "Player_human.h"
#include "DataBase.h"
#include "Info.h"

namespace GAME
{

Battlefield::Battlefield(const Tmap &tmap)
    : started(false)
{
    Target tmp;
    for (auto i : tmap.wall)
    {
        tmp.blood = tmp.maxblood = DataBase::DefaultWallBlood;
        tmp.owner = -1;
        tmp.shape = sandbox.AddWall(Wall(1, i));
        tmp.type = 1;
        barrier[tmp.shape] = target.insert(tmp);
    }
    for (auto i : tmap.badarea)
    {
        tmp.blood = tmp.maxblood = DataBase::Infinite;
        tmp.owner = -1;
        tmp.shape = sandbox.AddWall(Wall(1, i));
        tmp.type = 1;
        barrier[tmp.shape] = target.insert(tmp);
    }
}

bool Battlefield::CanStart()
{
    for (auto i : player)
        if (i->tank.target == -1)
            return false;
    return true;
}

void Battlefield::PlayerInfoInit()
{
    for (auto i : info)
    {
        i.shell = &shell;
        i.barrier = &barrier;
        i.target = &target;
        i.ball = &sandbox.balls;
        i.wall = &sandbox.walls;
    }
    for (int i = 0; i < player.size(); ++i)
    {
        info[i].playerinfo.resize(player.size());
        for (int j = 0; j < player.size(); ++j)
        {
            PlayerInfo &tmp = info[i].playerinfo[j];
            tmp.group = player[j]->group;
            tmp.id = player[j]->id;
            tmp.name = player[j]->name;
            tmp.tank = NULL;
        }
    }
}

void Battlefield::PlayerThreadStart(Battlefield *self, int id)
{
    self->player[id]->run();
}

void Battlefield::ThreadStart()
{
    for (int i = 0; i < player.size(); ++i)
        threads.push_back(std::thread(Battlefield::PlayerThreadStart, this, i));
}

void Battlefield::UpdatePlayerInfo()
{
    for (int i = 0; i < player.size(); ++i)
        for (int j = 0; j < player.size(); ++j)
        {
            if (PlayerVisible(player[i], player[j]))
                info[i].playerinfo[j].tank = &player[j]->tank;
            else
                info[i].playerinfo[j].tank = NULL;
        }
}

bool Battlefield::PlayerVisible(const Player *p1, const Player *p2)
{
    //Point centerpos = Geo_Calc::GetPolygonCenter(sandbox.balls[target[p1->tank.target].shape].shape);
    Point centerpos = sandbox.balls[target[p1->tank.target].shape].cent;
    const std::set<int> *index;
    std::set<int>::const_iterator iter;
    for (auto i : sandbox.balls[target[p2->tank.target].shape].shape.points)
    {
        bool vis = true;
        index = sandbox.balls.GetIndex();
        for (iter = index->begin(); vis && iter != index->end(); ++iter)
            if (*iter != p1->tank.target && *iter != p2->tank.target)
                if (!Geo_Calc::CheckVisible(centerpos, i, sandbox.balls[*iter].shape))
                    vis = false;
        index = sandbox.walls.GetIndex();
        for (iter = index->begin(); vis && iter != index->end(); ++iter)
            if (!Geo_Calc::CheckVisible(centerpos, i, sandbox.walls[*iter].shape))
                vis = false;
        if (vis)
            return true;
    }
    return false;
}

int Battlefield::Run()
{
    if (!started)
        PlayerInfoInit();
    UpdatePlayerInfo();
    if (!started)
        ThreadStart(), started = true;
    DealOperation();
    sandbox.Refresh();
    self = this;
    while (sandbox.Run(sandbox.GetNextTime(), DealBW, DealBB));
    return check_winner();
}

int Battlefield::check_winner()
{
    int winner = -1;
    for (int i = 0; i < player.size(); ++i)
        if (target[player[i]->tank.target].blood != 0)
        {
            if (winner == -1)
                winner = i;
            else if (winner != i)
                return -1;
        }
    return winner;
}

int Battlefield::AddPlayer(int type, const std::string &name, int money)
{
    if (player.size() == tmap.birthplace.size())
        return -1;
    info.push_back(Info());
    op.push_back(Operation());
    Player *a;
    switch (type)
    {
    case 0:
        a = new Player_human(name, &info.back(), &op.back());
    case 1:
        a = new Player_ai(name, &info.back(), &op.back());
    default:
        a = NULL;
    }
    if (a == NULL)
    {
        info.pop_back();
        op.pop_back();
        return -1;
    }
    a->id = player.size();
    a->group = a->id;
    a->money = money;
    a->tank.target = -1;
    player.push_back(a);
    return a->id;
}

bool Battlefield::check_playerid(int id)
{
    return id >= 0 && id < player.size();
}

void Battlefield::SetArmor(int id, const std::vector<Armor> &armor)
{
    if (!check_playerid(id))
        return;
    player[id]->tank.armor = armor;
}

void Battlefield::SetItem(int id, const std::vector<Item> &item)
{
    if (!check_playerid(id))
        return;
    player[id]->item = item;
}

void Battlefield::SetSensor(int id, const std::vector<Sensor_Tank> &sensor)
{
    if (!check_playerid(id))
        return;
    player[id]->tank.sensor = sensor;
}

void Battlefield::SetWeapon(int id, const std::vector<Weapon> &weapon)
{
    if (!check_playerid(id))
        return;
    player[id]->tank.weapon = weapon;
}

void Battlefield::SetGroup(int id, int group)
{
    if (!check_playerid(id))
        return;
    player[id]->group = group;
}

void Battlefield::SetTank(int id, const Polygon &shape, double power, double view, int blood, double mass)
{
    if (!check_playerid(id))
        return;
    Target tgt;
    tgt.blood = tgt.maxblood = blood;
    tgt.owner = id;
    Polygon newshape(shape);
    newshape.MoveTo(tmap.birthplace[id]);
    tgt.shape = sandbox.AddBall(Ball_Polygon(1, mass, Point(), DataBase::Infinite/*MAXV*/, newshape));
    tgt.type = 0;
    Tank &tmp = player[id]->tank;
    tmp.view = tmp.oldview = view;
    tmp.target = target.insert(tgt);
}

void Battlefield::Close()
{
    for (auto i : info)
        i.quit = true;
    for (int i = 0; i < player.size(); ++i)
        threads[i].join();
    for (auto i : player)
        delete i;
}

void Battlefield::DealOperation()
{
    for (int i = 0; i < op.size(); ++i)
    {
        DealOperation_Move(i, op[i].dir);
        if (op[i].shoot)
            DealOperation_Shoot(i, op[i].gundir, op[i].weapon);
        if (op[i].item != -1)
            DealOperation_Item(i, op[i].item);
    }
}

void Battlefield::DealOperation_Move(int id, const Point &dir)
{
    Point dir2;
    double len = Geo_Calc::Length(dir);
    if (len > 1)
        dir2 = dir / len;
    else
        dir2 = dir;
    Tank &tnk = player[id]->tank;
    sandbox.AddForce(Force(dir2 * tnk.power, target[tnk.target].shape, 1));
}

void Battlefield::DealOperation_Shoot(int id, const Point &gundir, int wpn)
{
    try
    {
        Tank &tnk = player[id]->tank;
        DataBase::WeaponShoot(this, sandbox.balls[target[tnk.target].shape], tnk.weapon[wpn], gundir);
    }
    catch (...) {}
}

void Battlefield::DealOperation_Item(int id, int item)
{

}

Battlefield *Battlefield::self;

void Battlefield::DealBW(SandBox *box, int a, int b, Point dir)
{
    int typea = GetBallType(a);
    Hit(a, typea, target[barrier[b]);
    SandBox::DefaultDealBW(box, a, b, dir);
}

void Battlefield::DealBB(SandBox *box, int a, int b, Point dir)
{
    int typea = GetBallType(a);
    int typeb = GetBallType(b);
    SandBox::DefaultDealBB(box, a, b, dir);
}

int Battlefield::GetBallType(int id)
{
}

}
