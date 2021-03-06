#include "functions.cpp"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    udp_client_server::udp_client* client = new udp_client_server::udp_client("localhost", 3001);

    int currentTemperature = 20;

    srand (time(0));
    while (1) {
        // temperatura oscila entre 0 e 40
        if (rand() % 100 > 50) {
            currentTemperature += 1;
        } else {
            currentTemperature -= 1;
        }
        if (currentTemperature > 40)
        {
            currentTemperature = 40;
        }
        if (currentTemperature < 0)
        {
            currentTemperature = 0;
        }
        std::string s = std::to_string(currentTemperature);
        s = "T" + s;
        client->send(s.c_str(), s.length() + 1);
        usleep(rand() % tempo + tempo); // entre meio segundo e um segundo
    }

    return 0;
}