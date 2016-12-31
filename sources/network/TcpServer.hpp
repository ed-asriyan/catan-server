//
// Created by ed on 29.11.16.
//

#ifndef NETWORK_TCPSERVER_H
#define NETWORK_TCPSERVER_H

#include <stdexcept>

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/signals2.hpp>
#include <boost/asio.hpp>

#include "TcpConnection.hpp"

#include "exceptions/NetworkException.hpp"

namespace Network {
	using namespace boost::asio;

	typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;

	/**
	 * @brief Simple TCP server.
	 */
	class TcpServer {
		private:
			unsigned short port;
			io_service service;

			bool running = false;

		public:
			/**
			 * @brief TcpServer constructor.
			 * @param port Port for listening.
			 */
			TcpServer(unsigned short port) noexcept;

			/**
			 * @brief Starts the server.
			 */
			void start() throw(Exceptions::NetworkException);

			/**
			 * @brief Stops the server.
			 */
			void stop() noexcept;

			/**
			 * @brief Run synchronous listening in current thread.
			 */
			void listen() throw(Exceptions::NetworkException);

			/**
			 * @brief Returns listening port.
			 * @return Listening port.
			 */
			unsigned short get_port() const noexcept;

			/**
			 * @brief Returns true if server is running.
			 * @return True if server is running.
			 */
			bool is_running() const noexcept;

		private:
			void handleConnection(socket_ptr socket) noexcept;

		protected:
			virtual void onConnect(connection_ptr connection) throw(Exceptions::NetworkException) = 0;

	};
}

#endif //NETWORK_TCPSERVER_H
