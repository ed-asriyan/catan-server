//
// Created by ed on 30.12.16.
//

#include "CatanRequest.hpp"

Network::CatanRequest::CatanRequest(const std::string& method, const boost::property_tree::ptree& data)
	: method(method), post_data(data) {}

Network::CatanRequest Network::CatanRequest::parse(const boost::property_tree::ptree& params) {
	// todo: check for 'method' property

	return CatanRequest(params.get<std::string>("method"), params.get_child("data", ptree()));
}

const std::string& Network::CatanRequest::get_method() const {
	return method;
}

const boost::property_tree::ptree& Network::CatanRequest::get_post_data() const {
	return post_data;
}

bool Network::CatanRequest::havePostParams() const {
	return !post_data.empty();
}
