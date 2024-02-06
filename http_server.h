#ifndef INCLUDED_HTTP_SERVER
#define INCLUDED_HTTP_SERVER
#define MAXLINE 4096

#include <string>
#include <cstdlib>
#include <iostream>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>  
#include <unistd.h>
#include <string.h>
#include <cstring>
#include <fstream>
#include <sstream>
#include <errno.h>


class TcpServer {
	public:
		TcpServer(int portIn);
		~TcpServer();
	private:
		void tcp_err(std::string errmsg);
		int startServer();
		int portnum;
		char* gethtml(const char* filename);
};

#endif // !INCLUDED_HTTP_SERVER
