//
// Created by BEMELON on 22. 12. 8.
//

#ifndef MUD_SERVER_IPOTION_H
#define MUD_SERVER_IPOTION_H
#define interface class
class User;

interface IPotion {
public:
    virtual void action(User *user) = 0;
};
#endif //MUD_SERVER_IPOTION_H
