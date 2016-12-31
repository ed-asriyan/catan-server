//
// Created by ed on 29.11.16.
//

#include "TcpServer.hpp"

Network::TcpServer::TcpServer(unsigned short port) noexcept : port(port) {
	if (port <= 0) {
		throw std::invalid_argument("Port is out of range.");
	}
}

void Network::TcpServer::start() throw(Exceptions::NetworkException) {
	try {
		boost::thread(listen);
	} catch (...) {
		throw Exceptions::NetworkException();
	}
}

void Network::TcpServer::stop() noexcept {
	running = false;
}

void Network::TcpServer::listen() throw(Exceptions::NetworkException) {
	try {
		if (running) {
			return;
		}

		running = true;

		ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), port));

		while (running) {
			socket_ptr socket(new ip::tcp::socket(service));
			acceptor.accept(*socket);
			try {
				boost::thread(boost::bind(&TcpServer::handleConnection, this, socket));
			} catch (...) {}
		}
	} catch (...) {
		throw Exceptions::NetworkException();
	}

}

unsigned short Network::TcpServer::get_port() const noexcept {
	return port;
}

bool Network::TcpServer::is_running() const noexcept {
	return running;
}

void Network::TcpServer::handleConnection(socket_ptr socket) noexcept {
	try {
		onConnect(connection_ptr(new TcpConnection(socket)));
	} catch (...) {}
}
