#pragma once

#include "Socket.h"
#include "Packet.h"

#include "Exceptions.h"

namespace HTTP {
	using ServerFunc = Response(*)(Request);

	// HTTP Server
	class Server {
	public:
		Server(uint16 port);

	public:
		void Open(ServerFunc func);

		Request ReceiveRequest();
		int SendResponse(const Response& response);

	private:
		uint16 port;

		Socket server;
		Socket client;
	};
}