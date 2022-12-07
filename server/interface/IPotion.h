//
// Created by BEMELON on 22. 12. 8.
//

#ifndef MUD_SERVER_IPOTION_H
#define MUD_SERVER_IPOTION_H

#include "../header/User.h"

#define interface class

interface IPotion {
public:
    virtual void action(User *user) = 0;
};
#endif //MUD_SERVER_IPOTION_H
