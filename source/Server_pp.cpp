#include "Server_pp.hpp"
#include <iostream>

using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

namespace ozo {

Server_pp::Server_pp() : mSocketConnected(false) {
	server.set_open_handler(bind(&Server_pp::on_open,this,::_1));
	//server.set_fail_handler(bind(&Server_pp::on_fail,this,::_1));
	server.set_close_handler(bind(&Server_pp::on_close,this,::_1));
	server.set_message_handler(bind(&Server_pp::on_message,this,::_1,::_2));
	
	server.init_asio();
	server.listen(9002);
	server.start_accept();
}

Server_pp::~Server_pp() {
	if (mSocketConnected) server.close(mHandle, websocketpp::close::status::normal, "Connection closed.");
}

void Server_pp::process() {
    if( mSocketConnected ) {
		quat = oculus_data->HeadPose.ThePose.Orientation;
		pos = oculus_data->HeadPose.ThePose.Position;
		
        boost::format fmt("{ \"m\" : \"update\", \"o\" : [%f,%f,%f,%f], \"a\" : [%f,%f,%f] }");

        fmt % quat.w;
        fmt % quat.x;
        fmt % quat.y;
        fmt % quat.z;

        fmt % pos.x;
        fmt % pos.y;
        fmt % pos.z;

        server.send(mHandle, fmt.str(), websocketpp::frame::opcode::TEXT);
		
		{
			boost::unique_lock<boost::mutex> lock1(*mutex, boost::try_to_lock);
			if (lock1.owns_lock()) incomingPage = *decoder_data;
		}
		if (currentPage != incomingPage){
			currentPage = incomingPage;
			server.send(mHandle, "{ \"m\" : \"updatepage\", \"p\" : \"" + currentPage + "\" }", websocketpp::frame::opcode::TEXT);
		}
	}
	server.poll();
}

void Server_pp::on_open(websocketpp::connection_hdl hdl) {
	mHandle = hdl;
	std::cout << server.get_con_from_hdl(mHandle)->get_host() << std::endl;
    // Only accept connections from localhost
    if( server.get_con_from_hdl(mHandle)->get_host() != "localhost"){
        server.close(hdl, websocketpp::close::status::normal, "Connection closed.");
		return;
    }
   
    mSocketConnected = true;
    std::cout << "Connected..\n";

	server.send(mHandle, meshString(meshData), websocketpp::frame::opcode::TEXT);
}

void Server_pp::on_close(websocketpp::connection_hdl hdl) {
    std::cout << "Disonnected..\n";
    mSocketConnected = false;
}

//void Server_pp::on_fail(websocketpp::connection_hdl hdl) {}
void Server_pp::on_message(websocketpp::connection_hdl hdl, 
							websocketpp::server<websocketpp::config::asio>::message_ptr msg) {
	std::cout << msg->get_payload() << std::endl;
}

} //namespace ozo