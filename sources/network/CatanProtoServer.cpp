//
// Created by ed on 08.12.16.
//

#include "CatanProtoServer.hpp"

Network::CatanProtoServer::CatanProtoServer(unsigned short port) throw(std::invalid_argument) : TcpServer(port) {}

void Network::CatanProtoServer::onConnect(Network::connection_ptr connection) throw(Exceptions::NetworkException) {
	// todo: authorization block

	ptree result;

	try {
		std::istringstream is(connection->receive());
		ptree pt;
		try {
			read_json(is, pt);
		} catch (...) {
			throw Exceptions::InvalidJsonException();
		}

		auto response = onRequest(CatanRequest::parse(pt));
		result.put_child("response", response);
	} catch (const Exceptions::BaseCatanException& e) {
		result.put_child("error", e.to_ptree());
	} catch (...) {
		result.put_child("error", Exceptions::UnknownCatanException().to_ptree());
	}

	std::ostringstream os;
	write_json(os, result, false);
	connection->send(os.str());
}