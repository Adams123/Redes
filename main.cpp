#include "functions.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <iostream>

/*Identificadores de cada sensor:
L = sensor de alien
O = sensor se esta ou nao na rota certa
P = sensor do peso
Z = sensor da zoeira
A = sensor da altitude
T = sensor de temperatura
D = sensor de distancia ao objeto mais proximo
Q = sensor de quantidade de passageiros
E = sensor da direcao do vento (0 a 3, 4 direcoes basicas)
I = sensor da velocidade do aviao
*/
//Enviar mensagem para um dado sensor.
void sendMessage(float msg, std::string opt)
{
    udp_client_server::udp_client* client = new udp_client_server::udp_client("localhost", 3000);
    std::string s = std::to_string(msg);
    s=opt + s;
    client->send(s.c_str(), s.length()+1);
}
void sendMessage(int msg, std::string opt)
{
    udp_client_server::udp_client* client = new udp_client_server::udp_client("localhost", 3000);
    std::string s = std::to_string(msg);
    s=opt + s;
    client->send(s.c_str(), s.length()+1);
}
void sendMessage(std::string msg, std::string opt)
{
    udp_client_server::udp_client* client = new udp_client_server::udp_client("localhost", 3000);
    std::string s = msg;
    s=opt + s;
    client->send(s.c_str(), s.length()+1);
}


//sensor de alien
void detectorAliens(int distancia, int velocidade)
{
    int alien;
    if(distancia*velocidade > 500*500)
        alien= 0; //provavelmente tem
    else if(distancia*velocidade > 50000)
        alien= 1; //tem
    else alien= -1; //nao tem
    std::string s = std::to_string(alien);
    sendMessage(s, "L");
}

//sensor de esta ou nao na rota
void detectaRota(int dirVento)
{
    srand (time(0));
    int dir;
    int dirVentoCerta = rand() %3; //simula a direcao correta do vento
    if(dirVento != dirVentoCerta ) dir= 0;
    dir= 1;
    std::string s = std::to_string(dir);
    sendMessage(s, "O");
}

//sensor de peso
void taPesado(int passageiros, int temperatura, int velAviao)
{
    std::string s;
    if(passageiros > 300)
        if(temperatura > 30)
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
    sendMessage(s,"P");
}



float randomFloat(float max)
{
    return ((float)rand()/(float)(RAND_MAX)*max);
}


//sensor de zoeira
void nivelDaZoeira(const char* peso, int temperatura, int velocidade) //NUM SEI Q Q EH ISSO
{
    float res;
    if(temperatura>=30 && velocidade>=600)
        if(strcmp(peso, "Ta MUITO pesado")==0) res= (randomFloat(100)+80);
        if(strcmp(peso, "Ta bem pesado")==0) res= (randomFloat(100)+50);
        if(strcmp(peso, "Ta pesado")==0) res= (randomFloat(100)+20);
        if(strcmp(peso, "Ta de boa")==0) res= (randomFloat(100));
    sendMessage(res, "Z");
}


//mata um processo
void killProcess(std::string nome)
{
    std::string command;
    command = "ps axf | grep "+nome+" | grep -v grep | awk '{print \"kill -9 \" $1}' | sh";
    system(command.c_str());
}


//mata todos os sensores
void killall() //cria uma chamada de killProcess pra cada nome
{
    
    printf("Matando dirVento \n");
    printf("Matando altitude \n");
    printf("Matando distancia \n");
    printf("Matando passageiros \n");
    printf("Matando temperature \n");
    printf("Matando velAviao \n");
}

//inicializa todos os sensores
void initAll() //os printfs vao virar system() e iniciar todos os clientes
{
    printf("./dirVento&\n");
    printf("./altitude&\n");
    printf("./distancia&\n");
    printf("./passageiros&\n");
    printf("./temperature&\n");
    printf("./velAviao&\n");
}


//garante que ao apertar ctrl c para parar o programa irá encerrar todos os sensores
void sigint(int a)
{
    killall();
    exit(0);
}


/*Dúvidas:
0- A comunicação entre a interface e o gerenciador tem q ser via socket também?
1- Os sensores precisam saber quando disparar para o gerenciador ou podem ficar disparando direto e o gerenciador cuida disso?
2- Se precisar saber, como faz? Pq do jeito q foi feito, a comunicação tá via cliente/servidor, então o user funciona fazendo uma requisição para o gerenciador (ou seja, cliente envia mensagem para servidor), o gerenciador ve q q o cliente quer e dispara uma mensagem com um identificador para todos os sensores (mais cliente enviando mensagem para servidor), todos recebem mas só um dispara de volta, então todos precisam de um servidor escutando se foi requisitado ou não, e de um cliente para enviar de volta para o gerenciador, que também precisa de um cliente para disparar a requisição para os sensores e um host para receber a resposta dos sensores E para receber a requisição da interface, que também tem q ser cliente para pedir as coisas para o gerenciador E servidor para receber as informações do gerenciador
3- Se não precisar, pode todos os sensores ficarem disparando tudo o tempo todo para o gerenciador e ele cuida do q mandar pro usuário? E mais uma vez, surgem dois hosts/clientes iguais, q ta dando pau
*/



// TODO colocar aqui apenas os codigos para iniciar os outros programas
//      fazer um interface.cpp para a interface

int main()
{
    //interface();

    //signal(SIGINT, sigint);  //caso alguem de ctrl c, chama o sigint
    //udp_client_server::udp_server* server = new udp_client_server::udp_server("localhost", 3000);
    udp_client_server::udp_client* client = new udp_client_server::udp_client("localhost", 3000);
    udp_client_server::udp_server* server = new udp_client_server::udp_server("localhost", 3000);
    srand (time(0));
    char *msg = (char*)malloc(sizeof(char)*20);
    std::string s;
    while(1)
    {
        std::cin >> s;
        std::cout << "Enviando " << s.c_str() << std::endl;
        client->send(s.c_str(),s.length()+1);
        server->recv(msg, 20);
    }
    

    //initAll();
    // while (1) {
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