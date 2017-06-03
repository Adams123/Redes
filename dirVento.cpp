#include "functions.cpp"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    udp_client_server::udp_client* client = new udp_client_server::udp_client("localhost", 3001);

    int dirVento = 0;

    srand (time(0));
    while (1) {
        // velocidade do vento oscila entre 0, 1, 2 e 3
        dirVento = rand() % 3;
        std::string s = std::to_string(dirVento);
        s = "E" + s;
        client->send(s.c_str(), s.length() + 1);
        usleep(rand() % tempo + tempo); // entre meio segundo e um segundo
    }

    return 0;
}