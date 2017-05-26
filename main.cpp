#include "functions.h"
#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <signal.h>

int detectorAliens(int distancia, int velocidade)
{
    if(distancia*velocidade > 500*500)
        return 0; //provavelmente tem
    else if(distancia*velocidade > 50000)
        return 1; //tem
    else return -1; //nao tem
}

int detectaRota(int dirVento)
{
    srand (time(0));
    int dirVentoCerta = rand() %3; //simula a direcao correta do vento
    if(dirVento != dirVentoCerta ) return 0;
    return 1;
}

const char* taPesado(int passageiros, int temperatura, int velAviao)
{
    if(passageiros > 300)
        if(temperatura > 30)
            if(velAviao < 600)
                return "Ta MUITO pesado";
            else return "Ta bem pesado";
        else return "Ta pesado";
    else return "Ta de boa";
}

float randomFloat(float max)
{
    return ((float)rand()/(float)(RAND_MAX)*max);
}

float nivelDaZoeira(const char* peso, int temperatura, int velocidade) //NUM SEI Q Q EH ISSO
{
    if(temperatura>=30 && velocidade>=600)
        if(strcmp(peso, "Ta MUITO pesado")==0) return (randomFloat(100)+80);
        if(strcmp(peso, "Ta bem pesado")==0) return (randomFloat(100)+50);
        if(strcmp(peso, "Ta pesado")==0) return (randomFloat(100)+20);
        if(strcmp(peso, "Ta de boa")==0) return (randomFloat(100));
}

void killProcess(std::string nome)
{
    std::string command;
    command = "ps axf | grep "+nome+" | grep -v grep | awk '{print \"kill -9 \" $1}' | sh";
    system(command.c_str());
}
std::string Programs[]=
{
    "dirVento",
    "altitude",
    "distancia",
    "passageiros",
    "temperature",
    "velAviao"
};

void killall()
{
    for(int i=0;i<6;i++)
    {
        std::cout << "Matando " << Programs[i] << std::endl;
    }
}

void sigint(int a)
{
    killall();
    exit(0);
}

int main()
{

    interface();

    signal(SIGINT, sigint);

    udp_client_server::udp_server* server = new udp_client_server::udp_server("localhost", 3000);
    udp_client_server::udp_client* client = new udp_client_server::udp_client("localhost", 3000);
    srand (time(0));

    std::string execute = "./";
    std::string pipe = "&";
    for(int i=0;i<6;i++)
    {
        std::string command = execute + Programs[i] + pipe;
        std::cout << command << std::endl;
    }

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
            printf("Direcao do vento: %s\n", msg + 1);
        }else if (msg[0] == 'I') {
            printf("Velocidade do aviao: %s\n", msg + 1);
        }
    }
    std::atexit(killall);
    return 0;
}