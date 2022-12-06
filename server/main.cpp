//
// Created by BEMELON on 22. 12. 5.
//

#include "header/Server.h"
#include "header/NaiveLogger.h"
#include "header/NaiveController.h"

using namespace std;

int main() {
    IController *controllers[1];
    controllers[0] = new NaiveController();

    Server server = Server(8080,
                           new NaiveLogger(),
                           new MultiProcessRequestHandler(),
                          controllers
    );
    server.listen();
}

