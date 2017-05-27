#include "gerenciador.h"
#include "functions.cpp"


udp_client_server::udp_server* serverMain = new udp_client_server::udp_server("localhost", 3000); //server e client para comunicar com o usuario
udp_client_server::udp_client* clientMain = new udp_client_server::udp_client("localhost", 3000);

udp_client_server::udp_client* clientSensores;
udp_client_server::udp_server* serverSensores;

int parseOpt(char *opt)
{
	char *msgRcv = (char*)malloc(sizeof(char)*20);
	switch(opt[0])
	{
		case 'L': //sensor de alien
		break;
		case 'O': //sensor se esta ou nao na rota certa
		break;
		case 'P': //sensor do peso
		break;
		case 'Z': //sensor da zoeira
		break;
		case 'A': //sensor da altitude
		clientSensores = new udp_client_server::udp_client("localhost", 3001); //cria um cliente para pedir requisicao para um sensor
		serverSensores = new udp_client_server::udp_server("localhost", 3001); //cria um host para esperar resposta de um sensor
		clientSensores->send("S",2); //envia sinal que quer do server na porta 3001
		serverSensores->recv(msgRcv,2); //espera a resposta
		printf("Mensagem recebida do sensor: %s\n", msgRcv);
		if(msgRcv[0]=='A')
		{
			return 10;
		}
		break;
		case 'T': //sensor de temperatura
		break;
		case 'D': //sensor de distancia ao objeto mais proximo
		break;
		case 'Q': //sensor de quantidade de passageiros
		break;
		case 'E': //sensor da direcao do vento (0 a 3, 4 direcoes basicas)
		break;
		case 'I': //sensor da velocidade do aviao
		break;
		default:
		return -1;
		break;
	}
	return 1;
}


int main()
{
	while(1)
	{	
		char *msg=(char*)malloc(sizeof(char));
		serverMain->recv(msg,2); //recebe a mensagem do usuario
		printf("Recebido %s\n", msg);
		std::string s;
		std::cin >> s;
		std::cout << "Enviando " << s << std::endl;
		clientMain->send(s.c_str(),s.length()+1);


		// if(parseOpt(msg)==10)//verifica q q o user quer
		// {
		// 	printf("Altitide veio!");
		// } 
		// else printf("N SEI - %s\n", msg);
	}	
}