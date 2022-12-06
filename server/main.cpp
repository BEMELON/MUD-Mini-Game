//
// Created by BEMELON on 22. 12. 5.
//

#include "header/Server.h"
#include "header/BasicLogger.h"
#include "header/BasicController.h"
#include "header/BasicRequestDto.h"
#include "header/BasicResponseDto.h"

using namespace std;

int main() {
    IController *controllers[1];
    controllers[0] = new BasicController();

    Server server = Server( new BasicLogger(),
                            new BasicRequestHandler(),
                            controllers,
                            new BasicRequestDto(),
                            new BasicResponseDto());
    server.listen();
}

