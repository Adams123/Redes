#include "functions.cpp"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int requisitado(char *msg)
{
    if(msg[0]=='S')
        return 1;
    return 0;
}

int main()
{
    // udp_client_server::udp_server* server = new udp_client_server::udp_server("localhost", 3001);
    udp_client_server::udp_client* client = new udp_client_server::udp_client("localhost", 3001);

    int currentAltitude = 0;
    // char *msg;

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
        std::string s = std::to_string(currentAltitude);
        s = "A" + s;
        // server->timed_recv(msg, 2, 1); //espera até 1 seg pela requisicao
        // if(requisitado(msg)) //verifica se o manager pediu por mensagem.
        // {
        //     client->send(s.c_str(), s.length() + 1);
        // }
        client->send(s.c_str(), s.length() + 1);
        usleep(rand() % tempo + tempo); // entre meio segundo e um segundo de intervalo para gerar mais valores
    }

    return 0;
}