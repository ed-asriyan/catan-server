//
// Created by ed on 29.11.16.
//

#include "TcpServer.h"

Network::TcpServer::TcpServer(unsigned short port) : port(port) {
	if (port <= 0) {
		throw std::invalid_argument("Port is out of range.");
	}
}

unsigned short Network::TcpServer::get_port() const {
	return port;
}
