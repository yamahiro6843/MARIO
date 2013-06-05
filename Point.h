#pragma once

template < int dimension = 3 , typename ValueType = float >
class Point;

template < typename ValueType >
class Point< 2 , ValueType >
{
public:
	ValueType x;
	ValueType y;

	Point() :
		x(0) , y(0) 
	{};

	Point( ValueType tx , ValueType ty ) :
		x(tx) , y(ty) 
	{};

	bool operator == ( const Point<2,ValueType>& rhs )
	{
		return ( this->x == rhs.x ) && ( this->y == rhs.y );
	}
	bool operator != ( const Point<2,ValueType>& rhs )
	{
		return !( (*this) == rhs );
	}

};

template < typename ValueType >
class Point< 3 , ValueType >
{
public:
	ValueType x;
	ValueType y;
	ValueType z;

	Point() :
		x(0) , y(0) , z(0)
	{};

	Point( ValueType tx , ValueType ty , ValueType tz ) :
		x(tx) , y(ty) , z(tz)
	{};

	template <typename ValueType>
	Point( Point<2 , ValueType> _2D_point ) :
		x( _2D_point.x ) , y( _2D_point.y ) , z(0)
	{};
	
};





