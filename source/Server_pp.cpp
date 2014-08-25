#include "Server_pp.hpp"
#include <iostream>

using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

namespace ozo {

Server_pp::Server_pp() {
	mSocketConnected = true;
	
	server.set_open_handler(bind(&Server_pp::on_open,this,::_1));
	//server.set_fail_handler(bind(&Server_pp::on_fail,this,::_1));
	server.set_close_handler(bind(&Server_pp::on_close,this,::_1));
	//server.set_message_handler(bind(&Server_pp::on_message,this,::_1,::_2));
	
	server.init_asio();
	server.listen(9002);
	server.start_accept();
}

Server_pp::~Server_pp() {
	std::string d = "abcdefg";
	server.close(mHandle, close::status::normal, "Connection closed.");
}

void Server_pp::process() {
/* 	std::string d = "abcdefg";
	server->send(*mHandle, d, frame::opcode::TEXT); */
    if( mSocketConnected ) {
		quat = oculus->data->HeadPose.ThePose.Orientation;
		pos = oculus->data->HeadPose.ThePose.Position;
		
        boost::format fmt("{ \"m\" : \"update\", \"o\" : [%f,%f,%f,%f], \"a\" : [%f,%f,%f] }");

        fmt % quat.w;
        fmt % quat.x;
        fmt % quat.y;
        fmt % quat.z;

        fmt % pos.x;
        fmt % pos.y;
        fmt % pos.z;

        server.send(mHandle, fmt.str(), frame::opcode::TEXT);
	}
	server.poll();
}

void Server_pp::on_open(websocketpp::connection_hdl hdl) {
    // Only accept connections from localhost
    if( server.get_con_from_hdl(mHandle)->get_host() != "localhost"){
        server.close(hdl, close::status::normal, "Connection closed.");
		return;
    }
    
    mSocketConnected = true;
    std::cout << "Connected..\n";
	
	boost::format fmt("{ \"m\" : \"config\", \"name\" : [%s] }");
	fmt % oculus->hmd->ProductName;

	server.send(mHandle, fmt.str(), frame::opcode::TEXT);
	server.poll();
}

//Server_pp::on_fail(websocketpp::connection_hdl hdl) {}

void Server_pp::on_close(websocketpp::connection_hdl hdl) {
    std::cout << "Disonnected..\n";
    mSocketConnected = false;
}

//Server_pp::on_message(websocketpp::connection_hdl hdl, server::message_ptr msg) {}

} //namespace ozo