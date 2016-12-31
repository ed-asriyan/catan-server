//
// Created by ed on 08.12.16.
//

#include "CatanProtoServer.hpp"

Network::CatanProtoServer::CatanProtoServer(unsigned short port) : TcpServer(port) {

}

void Network::CatanProtoServer::onConnect(Network::connection_ptr connection) {
	// todo: authorization block

	std::istringstream is(connection->receive());
	ptree pt;
	read_json(is, pt);

	// todo: exceptions catcher-handler
	ptree result;
	auto response = onRequest(CatanRequest::parse(pt));
	result.put_child("response", response);

	std::ostringstream os;
	write_json(os, result, false);
	connection->send(os.str());
}