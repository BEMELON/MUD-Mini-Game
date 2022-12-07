//
// Created by BEMELON on 22. 12. 8.
//

#ifndef MUD_SERVER_POTION_STR_H
#define MUD_SERVER_POTION_STR_H


#include "../interface/IPotion.h"

class Potion_str: IPotion {
    void action(User *user) override;
};


#endif //MUD_SERVER_POTION_STR_H
