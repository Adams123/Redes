#include "gerenciador.h"
#include "functions.cpp"

// udp_client_server::udp_server* serverMain = new udp_client_server::udp_server("localhost", 3000); //server e client para comunicar com o usuario
// udp_client_server::udp_client* clientMain = new udp_client_server::udp_client("localhost", 3000);

// udp_client_server::udp_client* clientSensores;
// udp_client_server::udp_server* serverSensores;

int parseOpt(char *msg)
{
	// char *msgRcv = (char*)malloc(sizeof(char)*20);
	switch(msg[0])
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
			printf("Altitude: %s\n", msg + 1);
			break;

		case 'T': //sensor de temperatura
			printf("Temperatura: %s\n", msg + 1);
			break;

		case 'D': //sensor de distancia ao objeto mais proximo
			printf("Distancia: %s\n", msg + 1);
			break;

		case 'Q': //sensor de quantidade de passageiros
			printf("Passageiros: %s\n", msg + 1);
			break;

		case 'E': //sensor da direcao do vento (0 a 3, 4 direcoes basicas)
			printf("Direcao do vento: %s\n", msg + 1);
			break;

		case 'I': //sensor da velocidade do aviao
			printf("Velocidade do aviao: %s\n", msg + 1);
			break;

		default:
			return -1;
			break;
	}
	return 1;
}


// TODO a cada 1 segundo, enviar todos os dados recebidos pra interface

int main()
{
	udp_client_server::udp_server* server = new udp_client_server::udp_server("localhost", 3001);

	while (1) {
        char *msg;
        server->recv(msg, 10);
        parseOpt(msg);
    }

	/*while(1)
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
	}*/
}