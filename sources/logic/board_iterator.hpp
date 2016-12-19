#ifndef _BOARD_ITERATOR_HPP_
#define _BOARD_ITERATOR_HPP_ 

#include <vector>
#include <map>

class BoardGexIterator;
#include "board.hpp"
#include "settings.hpp"

class BoardIterator
{
public:
	BoardIterator(Board&);
	~BoardIterator();

	void operator++();
	Coordinates operator*();
	bool operator()();

protected:
	Board& board_;
	int index_;
	int limit_;
	std::vector<Coordinates> coord_;
};


class BoardGexIterator : public BoardIterator
{
public:
	BoardGexIterator(Board&);
};


class GexesByNumberIterator : public BoardIterator 
{
public:
	GexesByNumberIterator(Board&, int);
};


class EdgesByEdgeIterator : public BoardIterator
{
public:
	EdgesByEdgeIterator(Board&, Coordinates);
};


class IntersectionsByIntersectionIterator : public BoardIterator 
{
public:
	IntersectionsByIntersectionIterator(Board&, Coordinates);
};


class IntersectionsByGexIterator : public BoardIterator 
{
public:
	IntersectionsByGexIterator(Board&, Coordinates);
};


class EdgesByIntersectionIterator : public BoardIterator
{
public:
	EdgesByIntersectionIterator(Board&, Coordinates);
};


class IntersectionsByEdgeIterator : public BoardIterator
{
public:
	IntersectionsByEdgeIterator(Board&, Coordinates);
};

#endif