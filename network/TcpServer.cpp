//
// Created by ed on 29.11.16.
//

#include "TcpServer.h"

Network::TcpServer::TcpServer(unsigned short port) : port(port) {
	if (port <= 0) {
		throw std::invalid_argument("Port is out of range.");
	}
}

void Network::TcpServer::start() {
	boost::thread(listen);
}

void Network::TcpServer::stop() {
	running = false;
}

void Network::TcpServer::listen() {
	if (running) {
		return;
	}

	running = true;

	ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), port));

	while (running) {
		socket_ptr socket(new ip::tcp::socket(service));
		acceptor.accept(*socket);
		boost::thread(boost::bind(&TcpServer::handleConnection, this, socket));
	}

}

unsigned short Network::TcpServer::get_port() const {
	return port;
}

bool Network::TcpServer::is_running() const {
	return running;
}

void Network::TcpServer::handleConnection(socket_ptr socket) {
	try {
		onConnect(connection_ptr(new TcpConnection(socket)));
	} catch (...) {

	}
}
