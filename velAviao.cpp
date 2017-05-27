#include "functions.cpp"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    udp_client_server::udp_client* client = new udp_client_server::udp_client("localhost", 3000);

    int velAviao = 0;

    srand (time(0));
    while (1) {
        // velocidade do vento oscila entre 0km/h e 900km/h
        if (rand() % 100 > 50) {
            velAviao += 10;
        } else {
            velAviao -= 10;
        }
        if (velAviao > 900)
        {
            velAviao = 900;
        }
        if (velAviao < 0)
        {
            velAviao = 0;
        }
        printf("Velocidade do aviao: %d\n", velAviao);
        std::string s = std::to_string(velAviao);
        s = "I" + s;
        client->send(s.c_str(), s.length() + 1);
        usleep(rand() % tempo + tempo); // entre meio segundo e um segundo
    }

    return 0;
}