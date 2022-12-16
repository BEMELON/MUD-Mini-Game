//
// Created by BEMELON on 22. 12. 5.
//

#include "../header/Client.h"
#include "../header/NaiveLogger.h"

using namespace std;

int main(){
    Client client = Client(8080, new BasicLogger());
    client.connect();
    client.start();
    while (true) {
        bool status = client.getCmd();
        if (!status)
            break;
        client.getMessage();
    }

    client.close();
}