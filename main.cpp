#include "functions.cpp"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
    udp_client_server::udp_server* server = new udp_client_server::udp_server("localhost", 3000);
    udp_client_server::udp_client* client = new udp_client_server::udp_client("localhost", 3000);
    printf("%d \n",client->send("olar",5));
    char *msg;
    printf("%d \n",server->recv(msg, 5));
    printf("%s \n", msg);
    return 0;
}