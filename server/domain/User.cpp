//
// Created by BEMELON on 22. 12. 8.
//

#include "../header/User.h"

User::User(string id) {
    this->id = id;
    this->hp = 30;
    this->str = 3;
    this->addPotion(new HpPotion());
    this->addPotion(new StrPotion());
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

list<HpPotion *> User::getHpPotions() {
    list<HpPotion *> hpPotions;
    for(IPotion* potion: this->potions) {
        auto* hpPotion = dynamic_cast<HpPotion *>(potion);
        if (hpPotion != nullptr)
            hpPotions.push_back(hpPotion);
    }
    return hpPotions;
}

list<StrPotion *> User::getStrPotions() {
    list<StrPotion *> strPotions;
    for(IPotion* potion: this->potions) {
        auto* strPotion = dynamic_cast<StrPotion *>(potion);
        if (strPotion != nullptr)
            strPotions.push_back(strPotion);
    }
    return strPotions;
}

void User::setHpPotion(int cnt) {
    int diff = cnt - getHpPotions().size();
    while (diff > 0) {
        this->addPotion(new HpPotion());
        diff -= 1;
    }
}

void User::setStrPotion(int cnt) {
    int diff = cnt - getStrPotions().size();
    while (diff > 0) {
        this->addPotion(new StrPotion());
        diff -= 1;
    }
}
