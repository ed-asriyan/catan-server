//
// Created by ed on 30.11.16.
//

#include "TcpConnection.hpp"

Network::TcpConnection::TcpConnection(Network::socket_ptr socket) throw(std::invalid_argument) : socket(socket) {
	if (socket == nullptr) throw std::invalid_argument("Socket is nullptr.");
}

void Network::TcpConnection::send(const std::string& string) throw(Exceptions::NetworkException) {
	auto data = string.c_str();

	try {
		socket->write_some(boost::asio::buffer(data, sizeof(*data) * (string.length() + 1)));
	} catch (...) {
		throw Exceptions::NetworkException();
	}
}

std::string Network::TcpConnection::receive() throw(Exceptions::NetworkException) {
	try {
		streambuf buffer;
		boost::asio::read_until(*socket, buffer, '\0');
		auto response = std::string(std::istreambuf_iterator<char>(&buffer), std::istreambuf_iterator<char>());
		response.pop_back();
		return response;
	} catch (...) {
		throw Exceptions::NetworkException();
	}
}

std::string Network::TcpConnection::get_remote_ip() const noexcept {
	return socket->remote_endpoint().address().to_string();
}

std::string Network::TcpConnection::get_local_ip() const noexcept {
	return socket->local_endpoint().address().to_string();
}
