#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include "SandBox.h"
#include "Tmap.h"
#include "Player.h"
#include "Target.h"
#include "Shell.h"
#include "Info.h"
#include "IMvector.h"
#include <string>
#include <thread>

namespace GAME
{
class Battlefield
{
public:
	std::vector<Player*> player;
	SandBox sandbox;
    IMvector<Target> target;
    Tmap tmap;
    IMvector<int> barrier;
    IMvector<Shell> shell;

	Battlefield(const Tmap &tmap);
	int AddPlayer(int type, const std::string &name, int money);//return id
	//type 0:human 1:ai
	void SetItem(int id, const std::vector<Item> &item);
    void SetWeapon(int id, const std::vector<Weapon> &weapon);
    void SetArmor(int id, const std::vector<Armor> &armor);
    void SetSensor(int id, const std::vector<Sensor_Tank> &sensor);
    void SetGroup(int id, int group);
    void SetTank(int id, const Polygon &shape, double view, int blood, double mass);
    bool CanStart();
	int Run(); // return winner, if no winner, return -1
	void Close();

private:
    std::vector<Operation> op;
    std::vector<Info> info;

    int check_winner();

    std::vector<std::thread> threads;
    static void PlayerThreadStart(Battlefield *self, int id);
    bool check_playerid(int id);
    void PlayerInfoInit();
    void ThreadStart();
    void UpdatePlayerInfo();
    bool PlayerVisible(const Player *p1, const Player *p2);
    bool started;
};
}

#endif // BATTLEFIELD_H
