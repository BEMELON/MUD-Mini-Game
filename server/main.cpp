//
// Created by BEMELON on 22. 12. 5.
//

#include "header/Server.h"
#include "header/BasicLogger.h"
#include "header/BasicRequestDto.h"
#include "header/BasicResponseDto.h"
#include "header/RedisRepository.h"
#include "header/UserController.h"
#include "header/UserService.h"
#include "header/BasicUserRepository.h"
#include "interface/IUserController.h"
#include "header/EpollEventHandler.h"
#include "header/HealthController.h"

using namespace std;

int main() {
    ILogger* logger = new BasicLogger();
    IRequestHandler* requestHandler = new EpollEventHandler();
    IRequestDTO* requestDto = new BasicRequestDto();
    IResponseDTO* responseDto = new BasicResponseDto();
    IDataRepository* dataRepository = new RedisRepository();

    IController* healthController = new HealthController();

    // user stack
    IUserController* userController = new UserController();
    IUserRepository* userRepository = new BasicUserRepository();
    IUserService* userService = new UserService();

    Server server = Server(logger);
    server.setDataRepository(dataRepository);
    server.setEventHandler(requestHandler, requestDto, responseDto);
    server.setHealthController(healthController);
    server.setUserStack(userController, userService, userRepository);

    server.listen();
}

