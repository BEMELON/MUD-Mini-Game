//
// Created by BEMELON on 22. 12. 5.
//

#include "header/Server.h"
#include "header/BasicLogger.h"
#include "header/RequestDto.h"
#include "header/ResponseDto.h"
#include "header/RedisRepository.h"
#include "header/UserController.h"
#include "header/UserService.h"
#include "header/UserRepository.h"
#include "interface/IUserController.h"
#include "header/EpollEventHandler.h"
#include "header/HealthController.h"

using namespace std;

int main() {
    ILogger* logger = new BasicLogger();
    IRequestHandler* requestHandler = new EpollEventHandler();
    IRequestDTO* requestDto = new RequestDto();
    IResponseDTO* responseDto = new ResponseDto();
    IDataRepository* dataRepository = new RedisRepository();

    IController* healthController = new HealthController();

    // user stack
    IUserController* userController = new UserController();
    IUserRepository* userRepository = new UserRepository();
    IUserService* userService = new UserService();

    Server server = Server(logger);
    server.setDataRepository(dataRepository);
    server.setEventHandler(requestHandler, requestDto, responseDto);
    server.setHealthController(healthController);
    server.setUserStack(userController, userService, userRepository);

    server.listen();
}

