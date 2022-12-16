//
// Created by BEMELON on 22. 12. 8.
//

#include "../header/User.h"

User::User(string id) {
    this->id = id;
    this->hp = 30;
    this->str = 3;
    this->hp_potions = 1;
    this->str_potions = 1;
    this->setPos(-1, -1);
}

int User::getHp() const {
    return this->hp;
}

string User::getId() {
     void printInfo();
   return this->id;
}


int User::getStr() const {
    return this->str;
}

void User::setHp(int hp) {
    this->hp = hp;
}

void User::setStr(int str) {
    this->str = str;
}

void User::setPos(int x, int y) {
    if (x <= 0) x = 1;
    else if (y <= 0) y = 1;
    else if (x > 30) x = 30;
    else if (y > 30) y = 30;

    this->x = x;
    this->y = y;
}

void User::setHpPotion(int cnt) {
    this->hp_potions = cnt;
}

void User::setStrPotion(int cnt) {
    this->str_potions = cnt;
}

list<string> User::getMessages() {
    return this->msgs;
}

void User::setMessages(list<string> &messages) {
    this->msgs = messages;
}

void User::addMessage(string &message) {
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

int User::getHpPotions() const {
    return this->hp_potions;
}

int User::getStrPotions() const {
    return this->str_potions;
}

int User::getX() {
    return this->x;
}

int User::getY() {
    return this->y;
}
