//
// Created by BEMELON on 22. 12. 8.
//

#include "../header/User.h"

User::User(string id) {
    this->id = id;
}

int User::getHp() {
    return this->hp;
}

string User::getId() {
    return this->id;
}


int User::getStr() {
    return this->str;
}

Coordinate User::getPos() {
    return Coordinate(this->pos.getX(), this->pos.getY());
}

void User::addHp(int diff) {
    this->hp += diff;
}

void User::addstr(int diff) {
    this->str += diff;
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

void User::move(int vec_x, int vec_y) {
    this->setPos(this->getPos().getX() + vec_x,
                 this->getPos().getY() + vec_y);
}

void User::addHpPotion(Potion_hp potion) {
    hp_potions.push_back(potion);
}

void User::addStrPotion(Potion_str potion) {
    str_potions.push_back(potion);
}
