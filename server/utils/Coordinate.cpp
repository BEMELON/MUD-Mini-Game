//
// Created by BEMELON on 22. 12. 8.
//

#include "../header/Coordinate.h"

Coordinate::Coordinate(int x, int y) {
    this->setX(x);
    this->setY(y);
}

Coordinate::Coordinate() {
    this->setX(0);
    this->setY(0);
}

void Coordinate::setY(int y) {
    this->y = y;
}

void Coordinate::setX(int x) {
    this->x = x;
}

int Coordinate::getX() {
    return this->x;
}

int Coordinate::getY() {
    return this->y;
}

