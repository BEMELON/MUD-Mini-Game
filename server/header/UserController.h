//
// Created by BEMELON on 22. 12. 11.
//

#ifndef MUD_SERVER_USERCONTROLLER_H
#define MUD_SERVER_USERCONTROLLER_H


#include "../interface/IUserController.h"

class UserController : public IUserController {
private:
    string getUserId(const string &path);
protected:
    IUserService* userService;
public:
    UserController();
    void addRoute(IRequestHandler* handler) override;
    IResponseDTO * get(IRequestDTO* body, IResponseDTO* resp) override;
    void setUserService(IUserService* iUserService) override;
    void setLogger(ILogger *iLogger) override;

    bool login(IRequestDTO* &body, IResponseDTO* &resp) override;
    bool getAllUser(IRequestDTO* &body, IResponseDTO* &resp) override;
    bool getUserInfo(IRequestDTO* &body, IResponseDTO* &resp) override;
    bool moveUser(IRequestDTO* &body, IResponseDTO* &resp) override;
    bool attack(IRequestDTO* &body, IResponseDTO* &resp) override;
    bool sendMsg(IRequestDTO* &body, IResponseDTO* &resp) override;
    bool event(IRequestDTO* &body, IResponseDTO* &resp) override;
    bool usePotion(IRequestDTO* &req, IResponseDTO* &res) override;
};


#endif //MUD_SERVER_USERCONTROLLER_H
