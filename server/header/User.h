//
// Created by BEMELON on 22. 12. 8.
//

#ifndef MUD_SERVER_USER_H
#define MUD_SERVER_USER_H


#include "Coordinate.h"
#include "../interface/IPotion.h"
#include <list>
#include <string>
using namespace std;

class IPotion;
class User {
private:
    string id;
    Coordinate pos;
    int hp;
    int str;
    list<IPotion *> potions;

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
    void addPotion(IPotion* potion);
    list<IPotion *> getPotions();

};


#endif //MUD_SERVER_USER_H
