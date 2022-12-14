//
// Created by BEMELON on 22. 12. 8.
//

#ifndef MUD_SERVER_USER_H
#define MUD_SERVER_USER_H


#include "Coordinate.h"
#include "../interface/IPotion.h"
#include "HpPotion.h"
#include "StrPotion.h"
#include <list>
#include <string>
using namespace std;
class IPotion;
class StrPotion;
class HpPotion;

class User {
private:
    string id;
    Coordinate pos;
    int hp;
    int str;
    list<IPotion *> potions;

    void addPotion(IPotion* potion);
public:
    // ID
    User(string id);
    string getId();

    // HP
    void setHp(int hp);
    int getHp() const;

    // STR
    void setStr(int str);
    int getStr() const;

    // Coordinate
    void setPos(Coordinate pos);
    void setPos(int x, int y);
    Coordinate getPos();

    // Potion
    void setHpPotion(int cnt);
    void setStrPotion(int cnt);
    list<HpPotion *> getHpPotions();
    list<StrPotion *> getStrPotions();
};


#endif //MUD_SERVER_USER_H
