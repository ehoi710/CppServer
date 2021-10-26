#include "Socket.h"

// Default constructor
Socket::Socket() {
	this->sock = INVALID_SOCKET;
}

// Move constructor
Socket::Socket(Socket&& rv) noexcept {
	this->sock = rv.sock;
	rv.sock = INVALID_SOCKET;
}

// Constructor with c socket
Socket::Socket(SOCKET sock) {
	this->sock = sock;
}

// Constructor with port
Socket::Socket(uint16 port) {
	sockaddr_in addr = { 0, };
	
	addr.sin_family = AF_INET; // IPv4
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;

	this->sock = socket(
		AF_INET,		// Domain  : AF_INET(IPv4)
		SOCK_STREAM,	// Type    : SOCK_STREAM(TCP)
		0				// Protocol: 0(Type¿¡¼­ °áÁ¤µÊ)
	);

	if (this->sock == INVALID_SOCKET) 
		throw SocketException("Socket Allocation Failed");

	if (bind(this->sock, (sockaddr*)&addr, sizeof(sockaddr)) == SOCKET_ERROR)
		throw SocketException("Binding Failed");
}

// Destructor
Socket::~Socket() {
	this->Dispose();
}

/*****/

// Check if socket is invalid
bool Socket::IsInvalid() { 
	return (this->sock == INVALID_SOCKET); 
}

// Make socket to listening socket
void Socket::Listen() {
	if (::listen(this->sock, 5) == SOCKET_ERROR)
		throw SocketException("Listening Failed");

	this->isListening = true;
}

// Accept new client socket
Socket Socket::Accept() {
	sockaddr_in client_addr = { 0, };

	if (this->IsInvalid())
		throw SocketException("Invalid Socket");

	if (!isListening)
		throw std::exception("This socket is not listening socket");

	int clientSize = sizeof(sockaddr_in);
	SOCKET accepted = ::accept(this->sock, (sockaddr*)&client_addr, &clientSize);
	return Socket(accepted);
}

// Accept new client socket with client address
Socket Socket::Accept(sockaddr* client_addr) {
	if (this->IsInvalid())
		throw SocketException("Invalid Socket");

	if (!isListening)
		throw std::exception("This socket is not listening socket");

	int client_size = sizeof(sockaddr_in);
	SOCKET accepted = ::accept(this->sock, client_addr, &client_size);
	return Socket(accepted);
}

// Receive line from socket
// Return length of string
int Socket::ReadLine(char* buf, int len) {
	char ch;
	int i = 0;

	while (i < len - 1) {
		int status = ::recv(this->sock, &ch, 1, 0);
		
		if (status == SOCKET_ERROR)
			throw SocketException("Receive Failed");

		else if (status == 0) break;

		if (ch == '\r') continue;
		if (ch == '\n') break;

		buf[i++] = ch;
	}

	buf[i] = '\0';
	return i;
}

// Send data to socket
int Socket::Send(const char* data, int len) {
	if (IsInvalid())
		throw SocketException("Invalid Socket");

	return ::send(this->sock, data, len, 0);
}

// Send data to socket
int Socket::Send(std::string data) {
	if (IsInvalid())
		throw SocketException("Invalid Socket");

	return ::send(this->sock, data.c_str(), data.size(), 0);
}

// Close socket
void Socket::Dispose() {
	::closesocket(this->sock);
	this->sock = INVALID_SOCKET;
}

/*****/

// Move assignment operator
Socket& Socket::operator=(Socket&& rv) noexcept {
	this->sock = rv.sock;
	rv.sock = INVALID_SOCKET;

	return *this;
}