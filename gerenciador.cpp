#include "gerenciador.h"
#include "functions.cpp"

/*Identificadores de cada sensor:
A = sensor da altitude
T = sensor de temperatura
D = sensor de distancia ao objeto mais proximo
Q = sensor de quantidade de passageiros
E = sensor da direcao do vento (0 a 3, 4 direcoes basicas)
I = sensor da velocidade do aviao
*/

// declaracao das variaveis globais
char altitude[10];
char temperatura[10];
char distancia[10];
char passageiros[10];
char direcaoVento[10];
char velocidadeAviao[10];

// sensor de alien
void detectorAliens(int distancia, int velocidade, int altitude)
{
    // uma conta qualquer que usa 3 sensores físicos
    int aliens = (altitude * 4 + distancia * 2 + velocidade) % 50;
    printf("Aliens detectados: %d\n", aliens);
}

// sensor de esta ou nao na rota
void detectaRota(int dirVento, int velAviao, int distancia)
{
    // uma conta qualquer que usa 3 sensores físicos
    int rota = dirVento * 100 + velAviao * 10 + distancia;
    if (rota % 100 > 60)
    {
        printf("Rota: Correta\n");
    }
    else
    {
        printf("Rota: Incorreta\n");
    }
}

// sensor de peso
void taPesado(int passageiros, int temperatura, int velAviao)
{
    std::string s;
    if(passageiros > 20)
        if(temperatura > 10)
            if(velAviao < 600)
            {
                s="Ta MUITO pesado";
            }
            else
            {
                s= "Ta bem pesado";
            }
        else
        {
            s= "Ta pesado";
        }

    else
        {
            s= "Ta de boa";
        }
    // sendMessage(s,"P");
    printf("Tá pesado?: %s\n", s.c_str());
}

char parseDirVento(int dirVento) {
    switch (dirVento) {
        case 0:
            return 'N';
            break;
        case 1:
            return 'S';
            break;
        case 2:
            return 'L';
            break;
        case 3:
            return 'O';
            break;
    }
    return ' ';
}

void printData() {
    system("clear");
    printf("---------- Dados dos sensores Reais ----------\n");
    printf("Altitude: %s m\n", altitude);
    printf("Temperatura: %s oC\n", temperatura);
    printf("Distancia: %s km\n", distancia);
    printf("Direcao do vento: %c\n", parseDirVento(atoi(direcaoVento)));
    printf("Passageiros: %s\n", passageiros);
    printf("Velocidade do aviao: %s km/h\n", velocidadeAviao);
    printf("---------- Dados dos sensores Virtuais ----------\n");
    detectaRota(atoi(direcaoVento), atoi(velocidadeAviao), atoi(distancia));
    taPesado(atoi(passageiros), atoi(temperatura), atoi(velocidadeAviao));
    detectorAliens(atoi(distancia), atoi(velocidadeAviao), atoi(altitude));
}

int parseOpt(char *msg)
{
    // printf("Parse\n");
    // char *msgRcv = (char*)malloc(sizeof(char)*20);
    switch(msg[0])
    {
        case 'A': //sensor da altitude
            // printf("Altitude: %s\n", msg + 1);
            strcpy(altitude, msg + 1);
            printData();
            // printf("%s\n", altitude);
            break;

        case 'T': //sensor de temperatura
            // printf("Temperatura: %s\n", msg + 1);
            strcpy(temperatura, msg + 1);
            printData();
            break;

        case 'D': //sensor de distancia ao objeto mais proximo
            // printf("Distancia: %s\n", msg + 1);
            strcpy(distancia, msg + 1);
            printData();
            break;

        case 'Q': //sensor de quantidade de passageiros
            // printf("Passageiros: %s\n", msg + 1);
            strcpy(passageiros, msg + 1);
            printData();
            break;

        case 'E': //sensor da direcao do vento (0 a 3, 4 direcoes basicas)
            // printf("Direcao do vento: %s\n", msg + 1);
            strcpy(direcaoVento, msg + 1);
            printData();
            break;

        case 'I': //sensor da velocidade do aviao
            // printf("Velocidade do aviao: %s\n", msg + 1);
            strcpy(velocidadeAviao, msg + 1);
            printData();
            break;

        default:
            return -1;
            break;
    }
    return 1;
}

int main()
{
    // inicialização das variaveis globais
    altitude[0] = '\0';
    temperatura[0] = '\0';
    distancia[0] = '\0';
    passageiros[0] = '\0';
    direcaoVento[0] = '\0';
    velocidadeAviao[0] = '\0';

    udp_client_server::udp_server* server = new udp_client_server::udp_server("localhost", 3001);

    while (1) {
        char *msg;
        server->recv(msg, 10);
        parseOpt(msg);
    }

}