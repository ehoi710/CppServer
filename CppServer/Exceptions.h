#pragma once

#include <exception>

#ifdef __linux__
class BaseException : public std::exception {
private:
	std::string _str;

public:
	BaseException(const char* message) {
		_str = std::string(message);
	}

	const char* what() {
		return _str;
	}
};
#elif _WIN32
using BaseException = std::exception;
#endif

// Exception thrown by socket
class SocketException : public BaseException {
public:
	SocketException(const char* message) : BaseException(message) { }
};

class NotImplementedException : BaseException {
public:
	NotImplementedException(const char* message) : BaseException(message) { }
};