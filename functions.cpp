#include "functions.h"
#include <string.h>
#include <unistd.h>

namespace udp_client_server
{


// ------------------------- CLIENTE ------------------------

// Inicializa um cliente com o ip e a porta especificada, com socket aberto.
udp_client::udp_client(const std::string& addr, int port)
    : f_port(port)
    , f_addr(addr)
{
    char decimal_port[16]; //informacoes da porta
    snprintf(decimal_port, sizeof(decimal_port), "%d", f_port);
    decimal_port[sizeof(decimal_port) / sizeof(decimal_port[0]) - 1] = '\0';
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; //nao espeficado a familia do socket
    hints.ai_socktype = SOCK_DGRAM; //seta para tipo socket diagram
    hints.ai_protocol = IPPROTO_UDP; //seta protocolo UDP
    int r(getaddrinfo(addr.c_str(), decimal_port, &hints, &f_addrinfo));
    if(r != 0 || f_addrinfo == NULL)
    {
        throw udp_client_server_runtime_error(("Endereco ou porta invalidos").c_str());
    }
    f_socket = socket(f_addrinfo->ai_family, SOCK_DGRAM, IPPROTO_UDP);
    if(f_socket == -1)
    {
        freeaddrinfo(f_addrinfo);
        throw udp_client_server_runtime_error(("Impossivel criar o socket neste endereco").c_str());
    }
}

udp_client::~udp_client()
{
    freeaddrinfo(f_addrinfo);
    close(f_socket);
}

int udp_client::get_socket() const
{
    return f_socket;
}

int udp_client::get_port() const
{
    return f_port;
}

std::string udp_client::get_addr() const
{
    return f_addr;
}

//envia uma mensagem através do cliente udp, com o destino definido no objeto client.
int udp_client::send(const char *msg, size_t size)
{
    return sendto(f_socket, msg, size, 0, f_addrinfo->ai_addr, f_addrinfo->ai_addrlen);
}



// ------------------------- SERVER ------------------------

// Inicializa um server (host), para receber mensagens. 
udp_server::udp_server(const std::string& addr, int port)
    : f_port(port)
    , f_addr(addr)
{
    char decimal_port[16]; //informacoes da porta
    snprintf(decimal_port, sizeof(decimal_port), "%d", f_port);
    decimal_port[sizeof(decimal_port) / sizeof(decimal_port[0]) - 1] = '\0';
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; //nao espeficado a familia do socket
    hints.ai_socktype = SOCK_DGRAM; //seta para tipo socket diagram
    hints.ai_protocol = IPPROTO_UDP; //seta protocolo UDP
    int r(getaddrinfo(addr.c_str(), decimal_port, &hints, &f_addrinfo));
    if(r != 0 || f_addrinfo == NULL)
    {
        throw udp_client_server_runtime_error(("Endereco ou porta invalido").c_str());
    }
    f_socket = socket(f_addrinfo->ai_family, SOCK_DGRAM, IPPROTO_UDP);
    if(f_socket == -1)
    {
        freeaddrinfo(f_addrinfo);
        throw udp_client_server_runtime_error(("Impossivel criar o socket no endereco fornecido").c_str());
    }
    r = bind(f_socket, f_addrinfo->ai_addr, f_addrinfo->ai_addrlen);
    if(r != 0)
    {
        freeaddrinfo(f_addrinfo);
        close(f_socket);
        throw udp_client_server_runtime_error(("Nao foi possivel associar o socket com o endereco fornecido").c_str());
    }
}
udp_server::~udp_server()
{
    freeaddrinfo(f_addrinfo);
    close(f_socket);
}
int udp_server::get_socket() const
{
    return f_socket;
}
int udp_server::get_port() const
{
    return f_port;
}
std::string udp_server::get_addr() const
{
    return f_addr;
}

//Espera por uma mensagem. Utiliza chamada bloqueante.
int udp_server::recv(char *msg, size_t max_size)
{
    return ::recv(f_socket, msg, max_size, 0);
}