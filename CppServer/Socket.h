#pragma once

#include <winsock.h>

#include <exception>
#include <string>

#include "utils.h"

#include "Exceptions.h"

#pragma comment(lib, "Ws2_32.lib")

// Interface of C Socket
class Socket {
public:
	Socket();
	Socket(Socket&& rv) noexcept;
	Socket(SOCKET sock);
	Socket(uint16 port);

	~Socket();

public:
	bool IsInvalid();

	void Listen();

	Socket Accept();
	Socket Accept(sockaddr* client_addr);

	int ReadLine(char* buf, int len);

	int Send(const char* data, int length);
	int Send(std::string data);

	void Dispose();

public:
	Socket& operator=(Socket&& rv) noexcept;

private:
	SOCKET sock;
	bool isListening = false;
};