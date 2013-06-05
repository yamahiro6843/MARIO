#pragma once

#include "point.h"
#include "Vector.h"


/*

ˆÈ‰º‚Ì‚æ‚¤‚È•Ô‚è’l
1) Point + Vector = Point
2) Point - Vector = Point
3) Point - Point = Vector

ŒvŽZ’l‚ÌŒ^‚Í‘O•û‚ÉˆË‘¶
  Point<int> - Point<float> = Vector<int>

4) Vector +- Vector = Vector <- class‚ÅŽÀ‘•Ï‚Ý
5) Vector +- Point = NOTHING // –³Œø
6) Point + Point = NOTHING // –³Œø

*/


// 2ŽŸŒ³‰‰ŽZ

// 1) Point + Vector = Point
template < typename T , typename U >
Point<2,T> operator+( const Point<2,T>& p , const Vector<2,U>& v )
{
	return Point<2,T>
		( p.x + v.x
		, p.y + v.y
		) ;
}


// 2) Point - Vector = Point
template < typename T , typename U >
Point<2,T> operator-( const Point<2,T>& p , const Vector<2,U>& v )
{
	return Point<2,T>
		( p.x - v.x
		, p.y - v.y
		) ;
}


// 2) Point - Point = Vector
template < typename T , typename U >
Vector<2,T> operator-( const Point<2,T>& p1 , const Point<2,U>& p2 )
{
	return Vector<2,T>
		( p1.x - p2.x
		, p1.y - p2.y
		) ;
}



// 3ŽŸŒ³‰‰ŽZ

// 1) Point + Vector = Point
template < typename T , typename U >
Point<3,T> operator+( const Point<3,T>& p , const Vector<3,U>& v )
{
	return Point<3,T>
		( p.x + v.x
		, p.y + v.y
		, p.z + v.z
		) ;
}


// 2) Point - Vector = Point
template < typename T , typename U >
Point<3,T> operator-( const Point<3,T>& p , const Vector<3,U>& v )
{
	return Point<3,T>
		( p.x - v.x
		, p.y - v.y
		, p.z - v.z
		) ;
}


// 3) Point - Point = Vector
template < typename T , typename U >
Vector<3,T> operator-( const Point<3,T>& p1 , const Point<3,U>& p2 )
{
	return Vector<3,T>
		( p1.x - p2.x
		, p1.y - p2.y
		, p1.z - p2.z
		) ;
}
