//
// Created by BEMELON on 22. 12. 8.
//

#ifndef MUD_SERVER_HPPOTION_H
#define MUD_SERVER_HPPOTION_H


#include "../interface/IPotion.h"
#include "../header/User.h"
class User;

class HpPotion: public IPotion {
    void action(User *user) override;
};


#endif //MUD_SERVER_HPPOTION_H
