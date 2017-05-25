#include "functions.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    udp_client_server::udp_server* server = new udp_client_server::udp_server("localhost", 3000);

    while (1) {
        char *msg;
        server->recv(msg, 10);
        printf("Mensagem: %s\n", msg);
        if (msg[0] == 'A')
        {
            printf("Altitude: %s\n", msg + 1);
        } else if (msg[0] == 'T') {
            printf("Temperatura: %s\n", msg + 1);
        }else if (msg[0] == 'D') {
            printf("Distancia: %s\n", msg + 1);
        }else if (msg[0] == 'P') {
            printf("Passageiros: %s\n", msg + 1);
        }else if (msg[0] == 'E') {
            printf("Velocidade do vento: %s\n", msg + 1);
        }else if (msg[0] == 'I') {
            printf("Velocidade do aviao: %s\n", msg + 1);
        }

    }

    return 0;
}