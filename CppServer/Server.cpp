#include "Server.h"

#include <iostream>
namespace HTTP {
	// Constructor
	Server::Server(uint16 port) {
		this->port = port;

		this->server = Socket(port);
		this->server.Listen();
	}

	// Open server with main function 'func'.
	// 'func' is mapping requests to responses.
	void Server::Open(ServerFunc func) {
		Request req;

		while (true) {
			// if there is no access, server stuck here.
			client = server.Accept();

			try {
				req = ReceiveRequest();
				SendResponse(func(req));
			}
			catch (std::exception e) {
				printf("%s\n", e.what());
			}

			client.Dispose();
		}
	}

	Request Server::ReceiveRequest() {
		char buf[1024] = { 0, };
		int i = 0;

		Request req;

		client.ReadLine(buf, 1024);
		if (strncmp(buf, "GET", 3) == 0) {
			req.method = Method::GET;
			i += 4; // "GET "
		}
		if (strncmp(buf, "POST", 4) == 0) {
			req.method = Method::POST;
			i += 5; // "POST "
		}
		req.target = std::string(buf + i, std::find(buf + i, buf + 1024, ' '));

		while (true) {
			if (client.ReadLine(buf, 1024) == 0) break;
			char* deli = std::find(buf, buf + 1024, ':');

			std::string key(buf, deli);
			std::string value(deli + 2, buf + strlen(buf));

			req.header[key] = value;
		}

		if (req.method == Method::GET) {
			return req;
		}

		throw NotImplementedException("POST decoding is not implemented!");

		return req;
	}

	int Server::SendResponse(const Response& response) {
		std::string res = "HTTP/1.0 " + std::string(response.state.toString()) + "\n";

		for (const auto& header : response.header) {
			res += (header.first + ": " + header.second + "\n");
		}
		res += "\n";

		res += response.body;

		return client.Send(res);
	}
}