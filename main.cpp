#include "functions.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

/*Identificadores de cada sensor:
L = sensor de alien
O = sensor se esta ou nao na rota certa
P = sensor do peso
Z = sensor da zoeira
A = sensor da altitude
T = sensor de temperatura
D = sensor de distancia ao objeto mais proximo
P = sensor de quantidade de passageiros
E = sensor da direcao do vento (0 a 3, 4 direcoes basicas)
I = sensor da velocidade do aviao
*/

void detectorAliens(int distancia, int velocidade)
{
    udp_client_server::udp_client* client = new udp_client_server::udp_client("localhost", 3000);
    int alien;
    if(distancia*velocidade > 500*500)
        alien= 0; //provavelmente tem
    else if(distancia*velocidade > 50000)
        alien= 1; //tem
    else alien= -1; //nao tem
    std::string s = std::to_string(alien);
    s="L" + s;
    client->send(s.c_str(), s.length()+1);
}

void detectaRota(int dirVento)
{
    udp_client_server::udp_client* client = new udp_client_server::udp_client("localhost", 3000);
    srand (time(0));
    int dir;
    int dirVentoCerta = rand() %3; //simula a direcao correta do vento
    if(dirVento != dirVentoCerta ) dir= 0;
    dir= 1;
    std::string s = std::to_string(dir);
    s="O" + s;
    client->send(s.c_str(), s.length()+1);
}

void taPesado(int passageiros, int temperatura, int velAviao)
{
    udp_client_server::udp_client* client = new udp_client_server::udp_client("localhost", 3000);
    std::string s;
    if(passageiros > 300)
        if(temperatura > 30)
            if(velAviao < 600)
            {
                s="PTa MUITO pesado";
            }
            else 
            {
                s= "PTa bem pesado";
            }
        else 
        {
            s= "PTa pesado";
        }

    else 
        {
            s= "PTa de boa";
        }
        client->send(s.c_str(), s.length()+1);
}

float randomFloat(float max)
{
    return ((float)rand()/(float)(RAND_MAX)*max);
}

void nivelDaZoeira(const char* peso, int temperatura, int velocidade) //NUM SEI Q Q EH ISSO
{
    udp_client_server::udp_client* client = new udp_client_server::udp_client("localhost", 3000);
    float res;
    if(temperatura>=30 && velocidade>=600)
        if(strcmp(peso, "Ta MUITO pesado")==0) res= (randomFloat(100)+80);
        if(strcmp(peso, "Ta bem pesado")==0) res= (randomFloat(100)+50);
        if(strcmp(peso, "Ta pesado")==0) res= (randomFloat(100)+20);
        if(strcmp(peso, "Ta de boa")==0) res= (randomFloat(100));
    std::string s = std::to_string(res);
    s="Z" + s;
    client->send(s.c_str(), s.length()+1);
}

void killProcess(std::string nome)
{
    std::string command;
    command = "ps axf | grep "+nome+" | grep -v grep | awk '{print \"kill -9 \" $1}' | sh";
    system(command.c_str());
}

void killall() //vira uma chamada de killProcess pra cada nome
{
    
    printf("Matando dirVento \n");
    printf("Matando altitude \n");
    printf("Matando distancia \n");
    printf("Matando passageiros \n");
    printf("Matando temperature \n");
    printf("Matando velAviao \n");
}

void initAll() //os printfs vao virar system() e iniciar todos os clientes
{
    printf("./dirVento&\n");
    printf("./altitude&\n");
    printf("./distancia&\n");
    printf("./passageiros&\n");
    printf("./temperature&\n");
    printf("./velAviao&\n");
}

void sigint(int a)
{
    killall();
    exit(0);
}
int main()
{

    //interface();

    //signal(SIGINT, sigint);  //caso alguem de ctrl c, chama o sigint
    udp_client_server::udp_server* server = new udp_client_server::udp_server("localhost", 3000);
    udp_client_server::udp_client* client = new udp_client_server::udp_client("localhost", 3000);
    srand (time(0));
    char *msg;
    //initAll();
    taPesado(350,35,200);
    server->recv(msg, 20);
        printf("Mensagem: %s\n", msg);
    detectaRota(0);
    server->recv(msg, 20);
        printf("Mensagem: %s\n", msg);
    detectorAliens(500,500);
    server->recv(msg, 20);
        printf("Mensagem: %s\n", msg);
    nivelDaZoeira("Ta MUITO pesado", 35, 650);
    // while (1) {
        
        server->recv(msg, 20);
        printf("Mensagem: %s\n", msg);
        // if (msg[0] == 'A')
        // {
        //     printf("Altitude: %s\n", msg + 1);
        // } else if (msg[0] == 'T') {
        //     printf("Temperatura: %s\n", msg + 1);
        // }else if (msg[0] == 'D') {
        //     printf("Distancia: %s\n", msg + 1);
        // }else if (msg[0] == 'P') {
        //     printf("Passageiros: %s\n", msg + 1);
        // }else if (msg[0] == 'E') {
        //     printf("Direcao do vento: %s\n", msg + 1);
        // }else if (msg[0] == 'I') {
        //     printf("Velocidade do aviao: %s\n", msg + 1);
        // }
    // }
    //std::atexit(killall); //executa a funcao caso o programa encerre
    return 0;
}