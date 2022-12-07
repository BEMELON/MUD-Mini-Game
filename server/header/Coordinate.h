//
// Created by BEMELON on 22. 12. 8.
//

#ifndef MUD_SERVER_COORDINATE_H
#define MUD_SERVER_COORDINATE_H


class Coordinate {
private:
    int x{};
    int y{};
public:
    Coordinate(int x, int y);
    Coordinate();

    void setX(int x);
    void setY(int y);
    int getX();
    int getY();
};


#endif //MUD_SERVER_COORDINATE_H
