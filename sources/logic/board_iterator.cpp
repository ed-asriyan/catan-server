#include "board_iterator.hpp"

BoardIterator::BoardIterator(Board& board): 
	board_(board), index_(0)
{
	limit_ = 0;
	coord_ = {};
}

BoardIterator::~BoardIterator()
{

}

void BoardIterator::operator++()
{
	++index_;
}

Coordinates BoardIterator::operator*()
{
	return coord_[index_];
}

bool BoardIterator::operator()()
{
	return index_ != limit_;
}

BoardGexIterator::BoardGexIterator(Board& board) : BoardIterator(board)
{
	limit_ = GEX_AMOUNT;
	coord_ = Settings::gexCoordinates;
}

GexesByNumberIterator::GexesByNumberIterator(Board& board, int number) : BoardIterator(board)
{
	coord_ = Settings::gex_numbers[number];
	limit_ = coord_.size();
}

EdgesByEdgeIterator::EdgesByEdgeIterator(Board& board, Coordinates edge) : BoardIterator(board)
{
	for (int i = -2; i < 3; ++i)
	{
		for (int j = -2; j < 3; ++j)
		{
			int x = edge.x + i;
			int y = edge.y + j;
			if (x > 0 && x < FIELD_SIZE && y > 0 && y < FIELD_SIZE)
			{
				Cell cell = board_[{x, y}];
				if (cell.type == EDGE)
				{
					coord_.push_back({x, y});
					++limit_;
				}
			}
		}
	}
}

IntersectionsByIntersectionIterator::IntersectionsByIntersectionIterator(Board& board, Coordinates inter) : 
	BoardIterator(board)
{
	for (int i = -2; i < 3; ++i)
	{
		for (int j = -2; j < 3; ++j)
		{
			int x = inter.x + i;
			int y = inter.y + j;
			if (x > 0 && x < FIELD_SIZE && y > 0 && y < FIELD_SIZE)
			{
				Cell cell = board_[{x, y}];
				Cell cell_between = board_[{ ((x + inter.x) / 2), ((y + inter.y) / 2) }];
				if (cell.type == INTERSECTION && cell_between.type == EDGE)
				{
					coord_.push_back({x, y});
					++limit_;
				}
			}
		}
	}
}

IntersectionsByGexIterator::IntersectionsByGexIterator(Board& board, Coordinates gex) :
	BoardIterator(board)
{
	for (int i = -2; i < 3; ++i)
	{
		for (int j = -2; j < 3; ++j)
		{
			int x = gex.x + i;
			int y = gex.y + j;
			if (x > 0 && x < FIELD_SIZE && y > 0 && y < FIELD_SIZE)
			{
				Cell cell = board_[{x, y}];
				if (cell.type == INTERSECTION)
				{
					coord_.push_back({x, y});
					++limit_;
				}
			}
		}
	}
}

EdgesByIntersectionIterator::EdgesByIntersectionIterator(Board& board, Coordinates inter) : 
	BoardIterator(board)
{
	for (int i = -1; i < 2; ++i)
	{
		for (int j = -1; j < 2; ++j)
		{
			int x = inter.x + i;
			int y = inter.y + j;
			if (x > 0 && x < FIELD_SIZE && y > 0 && y < FIELD_SIZE)
			{
				Cell cell = board_[{x, y}];
				if (cell.type == EDGE)
				{
					coord_.push_back({x, y});
					++limit_;
				}
			}
		}
	}
}

IntersectionsByEdgeIterator::IntersectionsByEdgeIterator(Board& board, Coordinates edge) : 
	BoardIterator(board)
{
	for (int i = -1; i < 2; ++i)
	{
		for (int j = -1; j < 2; ++j)
		{
			int x = edge.x + i;
			int y = edge.y + j;
			if (x > 0 && x < FIELD_SIZE && y > 0 && y < FIELD_SIZE)
			{
				Cell cell = board_[{x, y}];
				if (cell.type == INTERSECTION)
				{
					coord_.push_back({x, y});
					++limit_;
				}
			}
		}
	}
}