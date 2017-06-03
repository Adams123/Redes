#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <sys/types.h>
#include <sys/socket.h> //contem funcoes e variaveis referentes a operacoes com sockets
#include <netdb.h> //biblioteca de operacoes de base de dados de redes
#include <stdexcept> //biblioteca de excessoes
#include <string>

#define tempo 500000

namespace udp_client_server
{

class udp_client_server_runtime_error : public std::runtime_error
{
public:
    udp_client_server_runtime_error(const char *w) : std::runtime_error(w) {} //apenas para exibir erros
};


class udp_client
{
public:
    udp_client(const std::string& addr, int port);
    ~udp_client();

    int get_socket() const; //retorna o socket
    int get_port() const; //retorna porta do socket criado
    std::string get_addr() const; //retorna endereco (ip) do socket criado

    int send(const char *msg, size_t size); //envia uma mensagem msg de tamanho size

private:
    int f_socket; //representacao do socket de fato
    int f_port; //guarda a porta
    std::string f_addr; //guarda endereco
    struct addrinfo * f_addrinfo; //ponteiro para informacoes do socket no end/porta
};


class udp_server
{
public:
    udp_server(const std::string& addr, int port);
    ~udp_server();

    int get_socket() const; //retorna o socket
    int get_port() const; //retorna porta do socket criado
    std::string get_addr() const; //retorna endereco (ip) do socket criado

    int recv(char *msg, size_t max_size); //recebe uma menasgem msg de tamanho max_size

private:
    int f_socket; //representacao do socket de fato
    int f_port; //guarda a porta
    std::string f_addr; //guarda endereco
    struct addrinfo * f_addrinfo; //ponteiro para informacoes do socket no end/porta
};

}
#endif