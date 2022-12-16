//
// Created by BEMELON on 22. 12. 8.
//

#ifndef MUD_SERVER_USER_H
#define MUD_SERVER_USER_H


#include "Coordinate.h"
#include "HpPotion.h"
#include "StrPotion.h"
#include <list>
#include <string>

using namespace std;
class StrPotion;
class HpPotion;

class User {
private:
    string id;
    Coordinate pos;
    int hp;
    int str;
    int hp_potions;
    int str_potions;
    list<string> msgs;

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
    int getHpPotions() const;
    int getStrPotions() const;

    // Messages
    list<string> getMessages();
    void setMessages(list<string> &messages);
    void addMessage(string &message);
    string popMessage();
};


#endif //MUD_SERVER_USER_H
