#include "functions.cpp"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    udp_client_server::udp_client* client = new udp_client_server::udp_client("localhost", 3000);

    int dirVento = 0;

    srand (time(0));
    while (1) {
        // velocidade do vento oscila entre 10km e 90km
        dirVento = rand() % 3;
        printf("Direcao do vento: %d\n", dirVento);
        std::string s = std::to_string(dirVento);
        s = "E" + s;
        client->send(s.c_str(), s.length() + 1);
        usleep(rand() % tempo + tempo); // entre meio segundo e um segundo
    }

    return 0;
}