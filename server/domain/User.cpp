//
// Created by BEMELON on 22. 12. 8.
//

#include "../header/User.h"
#include "../header/RandomGridGenerator.h"

User::User(string id) {
    this->id = id;
    this->hp = 30;
    this->str = 3;
    this->addPotion(new HpPotion());
    this->addPotion(new StrPotion());
    this->setPos(RandomGridGenerator::getRandom(), RandomGridGenerator::getRandom());
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
    if (pos.getX() <= 0) pos.setX(1);
    else if (pos.getY() <= 0) pos.setY(1);
    else if (pos.getX() > 30) pos.setX(30);
    else if (pos.getY() > 30) pos.setY(30);

    this->pos = pos;
}

void User::setPos(int x, int y) {
    if (x <= 0) x = 1;
    else if (y <= 0) y = 1;
    else if (x > 30) x = 30;
    else if (y > 30) y = 30;

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

list<string> User::getMessages() {
    return this->msgs;
}

void User::setMessages(list<string> &messages) {
    this->msgs = messages;
}

void User::addMessages(string &message) {
    msgs.push_back(message);
}

string User::popMessage() {
    if (msgs.empty()) {
        return "";
    }

    string msg = msgs.front();
    msgs.pop_front();
    return msg;
}
