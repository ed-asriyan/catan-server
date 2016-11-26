#ifndef _COMMUNICATE_HPP_
#define _COMMUNICATE_HPP_ 

class Request
{
public:
	Request();
	~Request();

	void getMessage();
};

class Response
{
public:
	Response();
	~Response();

	void sentMessage();
};

#endif