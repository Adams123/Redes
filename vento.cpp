#include "functions.cpp"
#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    udp_client_server::udp_client* client = new udp_client_server::udp_client("localhost", 3000);

    int velVento = 0;

    while (1) {
        // velocidade do vento oscila entre 10km e 90km
        if (rand() % 100 > 50) {
            velVento += 2;
        } else {
            velVento -= 2;
        }
        if (velVento > 90)
        {
            velVento = 90;
        }
        if (velVento < 10)
        {
            velVento = 10;
        }
        printf("Velocidade do vento: %d\n", velVento);
        std::string s = std::to_string(velVento);
        s = "E" + s;
        client->send(s.c_str(), s.length() + 1);
        usleep(rand() % tempo + tempo); // entre meio segundo e um segundo
    }

    return 0;
}