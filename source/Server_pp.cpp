#include "Server_pp.hpp"
#include <iostream>
#include <sstream>
#include <fstream>

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
	int i;
	std::ostringstream tempString;
	mHandle = hdl;
	std::cout << server.get_con_from_hdl(mHandle)->get_host() << std::endl;
    // Only accept connections from localhost
    if( server.get_con_from_hdl(mHandle)->get_host() != "localhost"){
        server.close(hdl, websocketpp::close::status::normal, "Connection closed.");
		return;
    }
    
    mSocketConnected = true;
    std::cout << "Connected..\n";


	tempString << "{ \"m\" : \"mesh\", \"VertexCount\" : " << meshData[1]->VertexCount;
	tempString << ", \"IndexCount\" : " << meshData[1]->IndexCount << ", ";
	
	tempString << "\"ScreenPosNDC\" : [";
	for ( i = 0; i < meshData[1]->VertexCount; ++i ) {
		tempString << meshData[1]->pVertexData[i].ScreenPosNDC.x << ",";
		tempString << meshData[1]->pVertexData[i].ScreenPosNDC.y;
		if ( i != meshData[1]->VertexCount-1 ) tempString << ",";
	}
	
	tempString << "], \"TimeWarpFactor\" : [";
	for ( i = 0; i < meshData[1]->VertexCount; ++i ) {
		tempString << meshData[1]->pVertexData[i].TimeWarpFactor;
		if ( i != meshData[1]->VertexCount-1 ) tempString << ",";
	}

	tempString << "], \"VignetteFactor\" : [";
	for ( i = 0; i < meshData[1]->VertexCount; ++i ) {
		tempString << meshData[1]->pVertexData[i].VignetteFactor;
		if ( i != meshData[1]->VertexCount-1 ) tempString << ",";
	}

	tempString << "], \"TanEyeAnglesR\" : [";
	for ( i = 0; i < meshData[1]->VertexCount; ++i ) {
		tempString << meshData[1]->pVertexData[i].TanEyeAnglesR.x << ",";
		tempString << meshData[1]->pVertexData[i].TanEyeAnglesR.y;
		if ( i != meshData[1]->VertexCount-1 ) tempString << ",";
	}

	tempString << "], \"TanEyeAnglesG\" : [";
	for ( i = 0; i < meshData[1]->VertexCount; ++i ) {
		tempString << meshData[1]->pVertexData[i].TanEyeAnglesG.x << ",";
		tempString << meshData[1]->pVertexData[i].TanEyeAnglesG.y;
		if ( i != meshData[1]->VertexCount-1 ) tempString << ",";
	}

	tempString << "], \"TanEyeAnglesB\" : [";
	for ( i = 0; i < meshData[1]->VertexCount; ++i ) {
		tempString << meshData[1]->pVertexData[i].TanEyeAnglesB.x << ",";
		tempString << meshData[1]->pVertexData[i].TanEyeAnglesB.y;
		if ( i != meshData[1]->VertexCount-1 ) tempString << ",";
	}

	tempString << "], \"pIndexData\" : [";
	for ( i = 0; i < meshData[1]->IndexCount; ++i ) {
		tempString << meshData[1]->pIndexData[i];
		if ( i != meshData[1]->IndexCount-1 ) tempString << ",";
	}
	
	tempString << "] }";

	std::ofstream myfile;
	myfile.open ("mesh.txt", std::fstream::out | std::fstream::trunc);
	myfile << tempString.str();
	myfile.close();

	server.send(mHandle, tempString.str(), websocketpp::frame::opcode::TEXT);
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