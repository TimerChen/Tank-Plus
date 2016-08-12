#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include "SandBox.h"
#include "Tmap.h"
#include "Player.h"
#include <vector>
#include <string>
#include <thread>

namespace GAME
{
class Battlefield
{
public:
	std::vector<Player*> player;
	SandBox sandbox;
    std::vector<Target> target;
    Tmap tmap;
    Barrier barrier;
    std::vector<Shell> shell;

	Battlefield(const Tmap &tmap);
	int AddPlayer(int type, const std::string &name, int money, double view);//return id
	//type 0:human 1:ai
	void SetItem(int id, const std::vector<Item> &item);
    void SetWeapon(int id, const std::vector<Weapon> &weapon);
    void SetArmor(int id, const std::vector<Armor> &armor);
    void SetSensor(int id, const std::vector<Sensor_Tank> &sensor);
    void SetGroup(int id, int group);
    bool Start();
	int Run(); // return winner, if no winner, return -1

private:
    std::vector<Operation> op;
    std::vector<Info> info;

    int check_winner();

    std::vector<std::thread> threads;
};
}

#endif // BATTLEFIELD_H
