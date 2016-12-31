//
// Created by ed on 30.12.16.
//

#ifndef NETWORK_CATANREQUEST_HPP
#define NETWORK_CATANREQUEST_HPP

#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace Network {
	using namespace boost::property_tree;

	/**
	 * @brief Type, which contains request info such as type, method and data.
	 */
	class CatanRequest {
		public:
			/**
			 * @brief Creates request instance.
			 * @param method Request method.
			 */
			static CatanRequest parse(const ptree& params);

			bool havePostParams() const;

			/**
			 * @brief Returns method name.
			 * @return Method name.
			 */
			const std::string& get_method() const;

			/**
			 * @brief Returns POST data, if it exists; otherwise empty ptree.
			 * @return POST data, if it exists; otherwise empty ptree.
			 */
			const ptree& get_post_data() const;

		private:
			CatanRequest(const std::string& method, const ptree& data);

			const std::string method;
			const ptree post_data;
	};
}


#endif //NETWORK_CATANREQUEST_HPP
