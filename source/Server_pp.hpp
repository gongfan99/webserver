#ifndef __OZO_SERVER_PP_HPP__
#define __OZO_SERVER_PP_HPP__

#include "./websocketpp/config/asio_no_tls.hpp"
#include "./websocketpp/server.hpp"
#include "OVR_CAPI.h"
#include <vector>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/format.hpp>
#include "utils.hpp"

namespace ozo {

class Server_pp {
public:
	//external input interface from OculusDK2
	OculusInterface* OcuInf;

	//external input interfaces from DecoderQR
	std::string *decoder_data;
	boost::mutex *mutex; //mutex for decoder_data

	Server_pp();
	~Server_pp();
	void process();
private:
	websocketpp::server<websocketpp::config::asio> server;
	websocketpp::connection_hdl mHandle;
	bool mSocketConnected;
	ovrQuatf quat;
	ovrVector3f  pos;
	std::string currentPage;
	std::string incomingPage;
	std::string tempString;
	void on_open(websocketpp::connection_hdl hdl);
	void on_close(websocketpp::connection_hdl hdl);
	void on_message(websocketpp::connection_hdl hdl, websocketpp::server<websocketpp::config::asio>::message_ptr msg);
};

} //namespace ozo

#endif // __OZO_SERVER_PP_HPP__