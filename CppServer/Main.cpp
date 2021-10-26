#include "utils.h"
#include "Server.h"

#include <iostream>
#include <string>
#include <fstream>

const uint16 port = 0xCAFE;

std::string read_content(std::string file_name) {
	std::ifstream file(file_name);

	return std::string(std::istreambuf_iterator<char>(file),
		               std::istreambuf_iterator<char>());
}

HTTP::Response mainFunc(HTTP::Request req) {
	HTTP::Response res;
	res.state = HTTP::State::NOTFOUND;

	res.header["Content-Type"] = "text/html";

	res.body = "<html><head><title>title</title></head><body>body</body></html>";

	return res;
}

int main() {
	WSADATA wsaData;
	WSAStartup(0x0202, &wsaData);
	
	HTTP::Server serv(port);
	serv.Open(mainFunc);

	WSACleanup();

	return 0;
}