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
			TcpServer(unsigned short port);

			/**
			 * @brief Starts the server.
			 */
			void start();

			/**
			 * @brief Stops the server.
			 */
			void stop();

			/**
			 * @brief Run synchronous listening in current thread.
			 */
			void listen();

			/**
			 * @brief Returns listening port.
			 * @return Listening port.
			 */
			unsigned short get_port() const;

			/**
			 * @brief Returns true if server is running.
			 * @return True if server is running.
			 */
			bool is_running() const;

		private:
			void handleConnection(socket_ptr socket);

		protected:
			virtual void onConnect(connection_ptr connection) = 0;

	};
}

#endif //NETWORK_TCPSERVER_H
