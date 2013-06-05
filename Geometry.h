#pragma once

#include "point.h"
#include "Vector.h"


/*

�ȉ��̂悤�ȕԂ�l
1) Point + Vector = Point
2) Point - Vector = Point
3) Point - Point = Vector

�v�Z�l�̌^�͑O���Ɉˑ�
  Point<int> - Point<float> = Vector<int>

4) Vector +- Vector = Vector <- class�Ŏ����ς�
5) Vector +- Point = NOTHING // ����
6) Point + Point = NOTHING // ����

*/


// 2�������Z

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



// 3�������Z

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
