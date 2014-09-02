#ifndef __SERVER_PP_HPP__
#define __SERVER_PP_HPP__

#include "../lib/websocketpp/config/asio_no_tls.hpp"
#include "../lib/websocketpp/server.hpp"
#include "Server.hpp"
#include "OculusDK2.hpp"
#include <boost/format.hpp>

namespace ozo {

class Server_pp : public Server {
private:
	websocketpp::server<websocketpp::config::asio> server;
	websocketpp::connection_hdl mHandle;
	bool mSocketConnected;
	ovrQuatf quat;
	ovrVector3f  pos;
	std::string currentPage;
	std::string incomingPage;
public:
	Server_pp(OculusBase *o, ImageDecoder *d);
	~Server_pp();
	void process();
	void on_open(websocketpp::connection_hdl hdl);
	void on_close(websocketpp::connection_hdl hdl);
};

} //namespace ozo

#endif // __SERVER_PP_HPP__