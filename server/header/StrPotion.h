//
// Created by BEMELON on 22. 12. 8.
//

#ifndef MUD_SERVER_STRPOTION_H
#define MUD_SERVER_STRPOTION_H


#include "../interface/IPotion.h"
#include "../header/User.h"
class User;

class StrPotion: public IPotion {
    void action(User *user) override;
};


#endif //MUD_SERVER_STRPOTION_H
