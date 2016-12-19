#ifndef _BOARD_ITERATOR_HPP_
#define _BOARD_ITERATOR_HPP_ 

class BoardGexIterator;
#include "board.hpp"
#include "settings.hpp"

class BoardGexIterator
{
public:
	BoardGexIterator(Board& board);
	~BoardGexIterator();

	void operator++();
	Coordinates operator*();
	bool operator()();

private:
	Board& board_;
	int index;
};

#endif