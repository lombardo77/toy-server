#include "http_server.h"

int main(int argc, char *argv[])
{
	TcpServer server = TcpServer(atoi(argv[1]));
	
	return 0;
}
