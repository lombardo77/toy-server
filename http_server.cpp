#include "http_server.h"


TcpServer::TcpServer(int portIn) 
{
	portnum = portIn;
	startServer();
}

TcpServer::~TcpServer() 
{
}

int TcpServer::startServer() 
{
	int listenfd, connfd, n;
	struct sockaddr_in servaddr;
	uint8_t buff[MAXLINE + 1];
	uint8_t recvline[MAXLINE + 1];


	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		tcp_err("socket error");
	}
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(portnum);

	// binds an address to socket
	if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) 
		tcp_err("bind error");
	
	// listening on socket
	if (listen(listenfd, 10) < 0) 
		tcp_err("listen error");
	

	while (true) {
		struct sockaddr_in addr;
		socklen_t addr_len;

		std::cout << "waiting for connection\n";
		// wait until we accept a connection
		connfd = accept(listenfd, (struct sockaddr*) NULL, NULL);
		bzero(recvline, sizeof(servaddr));

		while ((n = read(connfd, recvline, MAXLINE-1)) > 0) {
			fprintf(stdout, "\n%s\n", recvline);

			if (recvline[n - 1] == '\n')
				break;
			bzero(recvline, sizeof(servaddr));
		}
		if (n < 0) 
			tcp_err(0);
		
		char* buffer_test = gethtml("index.html");

		write(connfd, (char*)buffer_test ,strlen(buffer_test));
		free(buffer_test);
		close(connfd);
	}


	return 1;
}

void TcpServer::tcp_err(std::string errmsg) 
{
	std::cout << errmsg << ": "<< strerror(errno) << "\n";
	exit(1);
}

char* TcpServer::gethtml(const char* filename) 
{
	FILE* file;
	file = fopen(filename, "r");
	fseek(file, 0, SEEK_END);
	int length = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* buff = (char*)malloc(sizeof(char) * (length + 1));
	char c;
	int i = 0;

	while ((c = fgetc(file)) != EOF) {
		buff[i] = c;
		i ++;
	}
	buff[i] = '\0';
	fclose(file);
	return buff;
}

