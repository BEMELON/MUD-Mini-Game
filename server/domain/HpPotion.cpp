//
// Created by BEMELON on 22. 12. 8.
//

#include "../header/HpPotion.h"

void HpPotion::action(User *user) {
    user->setHp(user->getHp() + 10);
}
