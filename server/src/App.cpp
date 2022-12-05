//
// Created by BEMELON on 22. 12. 5.
//

#include "../header/Server.h"

using namespace std;

int main() {

    Server server = Server(8080);
    server.listen();
}

