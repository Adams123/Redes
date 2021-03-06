#include "functions.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    udp_client_server::udp_client* client = new udp_client_server::udp_client("localhost", 3001);

    int currentDist = 0;

    srand (time(0));
    while (1) {
        // distancia oscila entre 0 e 1000m
        if (rand() % 100 > 40) {
            currentDist += 10;
        } else {
            currentDist -= 10;
        }
        if (currentDist > 1000)
        {
            currentDist = 1000;
        }
        if (currentDist < 0)
        {
            currentDist = 0;
        }
        std::string s = std::to_string(currentDist);
        s = "D" + s;
        client->send(s.c_str(), s.length() + 1);
        usleep(rand() % tempo + tempo); // entre meio segundo e um segundo
    }

    return 0;
}