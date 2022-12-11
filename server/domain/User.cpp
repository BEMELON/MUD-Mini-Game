//
// Created by BEMELON on 22. 12. 8.
//

#include "../header/User.h"

User::User(string id) {
    this->id = id;
    this->hp = 30;
    this->str = 3;
}

int User::getHp() const {
    return this->hp;
}

string User::getId() {
    return this->id;
}


int User::getStr() const {
    return this->str;
}

Coordinate User::getPos() {
    return {this->pos.getX(), this->pos.getY()};
}


void User::setHp(int hp) {
    this->hp = hp;
}

void User::setStr(int str) {
    this->str = str;
}

void User::setPos(Coordinate pos) {
    this->pos = pos;
}

void User::setPos(int x, int y) {
    this->pos = Coordinate(x, y);
}

void User::addPotion(IPotion* potion) {
    this->potions.push_back(potion);
}

list<IPotion *> User::getPotions() {
    return this->potions;
}
