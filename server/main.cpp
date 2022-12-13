//
// Created by BEMELON on 22. 12. 5.
//

#include "header/Server.h"
#include "header/BasicLogger.h"
#include "header/BasicController.h"
#include "header/BasicRequestDto.h"
#include "header/BasicResponseDto.h"
#include "header/RedisRepository.h"
#include "header/UserController.h"

using namespace std;

int main() {
    IController *controllers[2];
    controllers[0] = new BasicController();
    controllers[1] = new UserController();

    Server server = Server( new BasicLogger(),
                            new BasicRequestHandler(),
                            controllers,
                            new BasicRequestDto(),
                            new BasicResponseDto(),
                            new RedisRepository());
    server.listen();
}

