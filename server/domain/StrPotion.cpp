//
// Created by BEMELON on 22. 12. 8.
//

#include "../header/StrPotion.h"


void StrPotion::action(User *user) {
    user->setStr(user->getStr() + 3);
}
