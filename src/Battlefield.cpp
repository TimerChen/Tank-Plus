#include "Battlefield.h"
#include "Player_ai.h"
#include "Player_human.h"

namespace GAME
{

Battlefield::Battlefield(const Tmap &tmap)
{
}

void Battlefield::Start()
{
    for (int i = 0; i < player.size(); ++i)
        threads.push_back(std::thread(Battlefield::PlayerStart, this, i));
}

void Battlefield::PlayerStart(Battlefield *self, int id)
{
    self->player[id]->run();
}

int Battlefield::Run()
{
    // 在这一帧做一些事情。。。
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

int Battlefield::AddPlayer(int type, const std::string &name, int money, double view)
{
    if (player.size() == tmap.birthplace.size())
        return -1;
    info.push_back(Info());
    op.push_back(Operation());
    Player *a;
    switch (type)
    {
    case 0:
        a = new Player_human(&info.back(), &op.back());
    case 1:
        a = new Player_ai(&info.back(), &op.back());
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
    a->tank.name = name;
    a->tank.view = a->tank.oldview = view;
    player.push_back(a);
    return a->id;
}

void Battlefield::SetArmor(int id, const std::vector<Armor> &armor)
{
    player[id]->tank.armor = armor;
}

void Battlefield::SetItem(int id, const std::vector<Item> &item)
{
    player[id]->item = item;
}

void Battlefield::SetSensor(int id, const std::vector<Sensor_Tank> &sensor)
{
    player[id]->tank.sensor = sensor;
}

void Battlefield::SetWeapon(int id, const std::vector<Weapon> &weapon)
{
    player[id]->tank.weapon = weapon;
}

void Battlefield::SetGroup(int id, int group)
{
    player[id]->group = group;
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

}
