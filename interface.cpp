#include "interface.h"

udp_client_server::udp_server* server = new udp_client_server::udp_server("localhost", 3000);
udp_client_server::udp_client* client = new udp_client_server::udp_client("localhost", 3000);
