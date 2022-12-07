//
// Created by BEMELON on 22. 12. 8.
//

#ifndef MUD_SERVER_USER_H
#define MUD_SERVER_USER_H


#include "Coordinate.h"
#include "Potion_hp.h"
#include "Potion_str.h"
#include <list>
#include <string>

using namespace std;
class User {
private:
    string id;
    Coordinate pos;
    int hp;
    int str;
    list<Potion_hp> hp_potions;
    list<Potion_str> str_potions;

public:
    User(string id);

    void setHp(int hp);
    void setStr(int str);
    void setPos(Coordinate pos);
    void setPos(int x, int y);

    void addHp(int diff);
    void addstr(int diff);
    void move(int vec_x, int vec_y);
    void addHpPotion(Potion_hp potion);
    void addStrPotion(Potion_str potion);

    string getId();
    Coordinate getPos();
    int getHp();
    int getStr();

    
};


#endif //MUD_SERVER_USER_H
