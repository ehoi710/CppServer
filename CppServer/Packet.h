#pragma once
#pragma warning(disable : 26812)

#include <string>
#include <unordered_map>

#include "utils.h"

// Protocol version HTTP 1.0
namespace HTTP {
	using Header = std::unordered_map<std::string, std::string>;
	using Body = std::string;

	// HTTP protocol request method
	class Method {
	public:
		enum _method {
			GET,
			POST
		};

		Method() = default;
		Method(_method method) : method(method) { }

		operator _method() const { return method; }

		bool operator==(Method m) const { return method == m.method; }
		bool operator!=(Method m) const { return method != m.method; }

		bool operator==(_method m) const { return method == m; }
		bool operator!=(_method m) const { return method != m; }

		const char* toString() const {
			switch (method) {
			case GET:  return "GET";
			case POST: return "POST";
			}

			return NULL;
		}

	private:
		_method method;
	};
	
	// HTTP protocol response state
	class State {
	public:
		enum _state {
			OK = 200,
			NOTFOUND = 404
		};

		State() = default;
		State(_state state) : state(state) { }

		operator _state() const { return state; }

		bool operator==(State s) const { return state == s.state; }
		bool operator!=(State s) const { return state != s.state; }

		bool operator==(_state s) const { return state == s; }
		bool operator!=(_state s) const { return state != s; }

		const char* toString() const {
			switch (state) {
			case State::OK:       return "200 OK";
			case State::NOTFOUND: return "404 Not Found";
			}

			return NULL;
		}

	private:
		_state state;
	};

	// HTTP Request Packet
	struct Request {
		Method method;
		std::string target;

		Header header;
		Body body;
	};

	// HTTP Response Packet
	struct Response {
		State state;

		Header header;
		Body body;
	};
}