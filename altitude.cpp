#include "functions.cpp"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    udp_client_server::udp_client* client = new udp_client_server::udp_client("localhost", 3000);

    int currentAltitude = 0;

    srand (time(0));
    while (1) {
        // altitude oscila entre 0 e 20000
        if (rand() % 100 > 50) {
            currentAltitude += 100;
        } else {
            currentAltitude -= 100;
        }
        if (currentAltitude > 20000)
        {
            currentAltitude = 20000;
        }
        if (currentAltitude < 0)
        {
            currentAltitude = 0;
        }
        printf("Altitude: %d\n", currentAltitude);
        std::string s = std::to_string(currentAltitude);
        s = "A" + s;
        client->send(s.c_str(), s.length() + 1);
        usleep(rand() % tempo + tempo); // entre meio segundo e um segundo
    }

    return 0;
}