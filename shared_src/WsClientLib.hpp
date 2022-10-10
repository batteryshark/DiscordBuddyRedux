#ifndef EASYWSCLIENT_HPP_20120819_MIOFVASDTNUASZDQPLFD
#define EASYWSCLIENT_HPP_20120819_MIOFVASDTNUASZDQPLFD

// This code is based on:
// https://github.com/dhbaird/easywsclient
// https://github.com/GameSparks/gamesparks-cpp-unreal

// include required headers
//#if defined(USE_STD_STL)
#	include <string>
#	include <vector>
#	include <list>
#	include <map>
#	include <algorithm>
#	include <set>
//#endif /* defined(USE_STD_STL) */

// This namespace provides forwarding to the concrete STL implementation used.
namespace stlimpl
{
	using namespace std;
	//using std::function;
}

namespace WsClientLib {
	/* Used to pass Errors to the error callback */
	struct WSError
	{
		enum Code
		{
			UNEXPECTED_MESSAGE, ///< The server sent an unexpected message
			DNS_LOOKUP_FAILED,  ///< gethostbyname failed to lookup the host
			RECV_FAILED, ///< recv or SSL_read returned a nagative value
			CONNECTION_CLOSED, ///< the connection was closed - i.e. recv or SSL_read returned zero. Not necessarily an error
			SEND_FAILED, ///< send or SSL_write returned a nagative value
			SOCKET_CREATION_FAILED, ///< The socket constructor returned INVALID_SOCKET
			CONNECT_FAILED, ///< The call to connect() returned SOCKET_ERROR
			SSL_CTX_NEW_FAILED, ///< SSL_CTX_new returned null
			SSL_NEW_FAILED, ///< SSL_new returned null
			SSL_SET_FD_FAILED, ///< SSL_set_fd returned 0
			SSL_CONNECT_FAILED, ///< SSL_connect returned a value not equal to 1
			CLOSED_DURING_WS_HANDSHAKE, ///< recv or SSL_read returned 0 during the websocket handshake
			INVALID_STATUS_LINE_DURING_WS_HANDSHAKE, ///< the status line received from the server during the websocket handshake was to long to fit into the buffer
			BAD_STATUS_CODE ///< the HTTP status code returned was not 101 (Switching Protocols)
		};

		WSError(Code code_, const stlimpl::string& message_) : code(code_), message(message_) {}

		const Code code; ///< one of the error codes
		const stlimpl::string message; ///< a more or less human readable error description

	private:
		const WSError& operator=(const WSError&);
	};

	class WebSocket
	{
	public:
		typedef void (*WSMessageCallback)(const stlimpl::string&, void*);
		typedef void(*WSErrorCallback)(const WSError&, void*);
		typedef WebSocket* pointer;
		typedef enum readyStateValues { CLOSING, CLOSED, CONNECTING, OPEN } readyStateValues;
		static const char* getStateValueDesc(const readyStateValues& val) {
			switch (val)
			{
			case WsClientLib::WebSocket::CLOSING:
				return "CLOSING";
			case WsClientLib::WebSocket::CLOSED:
				return "CLOSED";
			case WsClientLib::WebSocket::CONNECTING:
				return "CONNECTING";
			case WsClientLib::WebSocket::OPEN:
				return "OPEN";
			default:
				return "???";
			}
		}

		// Factories:
		static pointer create_dummy();
		static pointer from_url(const stlimpl::string& url, const stlimpl::string& origin = stlimpl::string());
		static pointer from_url_no_mask(const stlimpl::string& url, const stlimpl::string& origin = stlimpl::string());

		// Interfaces:
		virtual ~WebSocket() { }
		virtual void connect() = 0; // change vs GameSparks implementation
		virtual void poll(int timeout, WSErrorCallback errorCallback, void* userData) = 0; // timeout in milliseconds
		virtual void send(const stlimpl::string& message) = 0;
		virtual void sendPing() = 0;
		virtual void close() = 0;
		virtual readyStateValues getReadyState() const = 0;

		void dispatch(WSMessageCallback messageCallback, WSErrorCallback errorCallback, void* userData) {
			_dispatch(messageCallback, errorCallback, userData);
		}

	protected:
		//struct Callback { virtual void operator()(const stlimpl::string& message) = 0; };
		virtual void _dispatch(WSMessageCallback message_callback, WSErrorCallback error_callback, void* data) = 0;

	protected:
		enum dnsLookup
		{
			keNone,
			keInprogress,
			keComplete,
			keFailed
		};

		volatile dnsLookup ipLookup;

		stlimpl::string m_host;
		stlimpl::string m_path;
		stlimpl::string m_url;
		stlimpl::string m_origin;

		int m_port;
	};

} // namespace WsClientLib

#endif /* EASYWSCLIENT_HPP_20120819_MIOFVASDTNUASZDQPLFD */