#include "board_iterator.hpp"

BoardGexIterator::BoardGexIterator(Board& board): board_(board)
{
	index = 0;
}

BoardGexIterator::~BoardGexIterator()
{

}

void BoardGexIterator::operator++()
{
	++index;
}

Coordinates BoardGexIterator::operator*()
{
	return Settings::gexCoordinates[index];
}

bool BoardGexIterator::operator()()
{
	return index != GEX_AMOUNT;
}
