// #ifndef _CELL_HPP_
// #define _CELL_HPP_ 

// // #include "sources.hpp"

// using namespace std;

// class Cell
// {
// public:
// 	Cell();
// 	virtual ~Cell();

// 	virtual CellType type();

// 	Building building;

// protected:
// 	CellType type_;

// };

// class BlankCell : public Cell
// {
// public:
// 	BlankCell();
// 	~BlankCell();

// };

// class Gexagon : public Cell
// {
// public:
// 	Gexagon();
// 	~Gexagon();

// 	Resource resource;
// };

// class Intersection : public Cell
// {
// public:
// 	Intersection();
// 	~Intersection();

// 	Harbor harbor;
// };

// class Edge : public Cell
// {
// public:
// 	Edge();
// 	~Edge();

// };

// #endif