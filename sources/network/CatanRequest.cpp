//
// Created by ed on 30.12.16.
//

#include "CatanRequest.hpp"

Network::CatanRequest::CatanRequest(const std::string& method, const boost::property_tree::ptree& data) noexcept
	: method(method), post_data(data) {}

Network::CatanRequest Network::CatanRequest::parse(const boost::property_tree::ptree& params) throw(Exceptions::InvalidJsonException) {
	try {
		return CatanRequest(params.get<std::string>("method"), params.get_child("data", ptree()));
	} catch (...) {
		throw Exceptions::InvalidJsonException();
	}
}

const std::string& Network::CatanRequest::get_method() const noexcept {
	return method;
}

const boost::property_tree::ptree& Network::CatanRequest::get_post_data() const noexcept {
	return post_data;
}

bool Network::CatanRequest::havePostParams() const noexcept {
	return !post_data.empty();
}
