#include "functions.cpp"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    udp_client_server::udp_client* client = new udp_client_server::udp_client("localhost", 3001);

    int passageiros = 0;

    srand (time(0));
    while (1) {
        // passageiros oscila entre 0 e 500
        if (rand() % 100 > 50) {
            passageiros += 5;
        } else {
            passageiros -= 5;
        }
        if (passageiros > 500)
        {
            passageiros = 500;
        }
        if (passageiros < 0)
        {
            passageiros = 0;
        }
        std::string s = std::to_string(passageiros);
        s = "Q" + s;
        client->send(s.c_str(), s.length() + 1);
        usleep(rand() % tempo + tempo); // entre meio segundo e um segundo
    }

    return 0;
}