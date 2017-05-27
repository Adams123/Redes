#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

udp_client_server::udp_server* server = new udp_client_server::udp_server("localhost", 3000);
udp_client_server::udp_client* client = new udp_client_server::udp_client("localhost", 3000);


void parseOpt(char opt)
{



	std::string msg = std::to_string(opt);
	switch(opt)
	{
		case 'L': //sensor de alien
		client->send(msg.c_str(), msg.length()+1);
		server->recv(msg,20);
		printf("Mensagem: %s\n", msg);
		break;
		case 'O': //sensor se esta ou nao na rota certa
		break;
		case 'P': //sensor do peso
		break;
		case 'Z': //sensor da zoeira
		break;
		case 'A': //sensor da altitude
		break;
		case 'T': //sensor de temperatura
		break;
		case 'D': //sensor de distancia ao objeto mais proximo
		break;
		case 'P': //sensor de quantidade de passageiros
		break;
		case 'E': //sensor da direcao do vento (0 a 3, 4 direcoes basicas)
		break;
		case 'I': //sensor da velocidade do aviao
		break;
	}
}

/*
TODO: esse switch tem q estar na main, aqui tem q ter só o send e rcv. na main tem q verificar q q a interface ta pedindo e chamar a funcao correta, pegando dos clientes corretos.
*/