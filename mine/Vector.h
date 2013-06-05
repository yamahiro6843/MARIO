#pragma once

#include <cmath>

template < int dimension = 3 , typename T = float>
class Vector;

template < typename T >
class Vector< 1 , T >
{
public:
	T x;		///< X座標

public:
	Vector()
		: x	( 0 )
	{
	}

	Vector( const Vector<1,T>& In )
		: x	( In.x )
	{
	}

	template <typename U>
	Vector( const Vector<1,U>& In )
		: x	( static_cast<T>(In.x) )
	{
	}

	Vector( T _x)
		: x	( _x )
	{
	}

	template <typename U>
	Vector<1,T> operator + ( const Vector<1,U>& In ) const
	{
		return Vector<1,T>( x + static_cast<T>(In.x) ) ;
	}

	template <typename U>
	Vector<1,T> operator - ( const Vector<1,U>& In ) const
	{
		return Vector<1,T>( x - static_cast<T>(In.x) ) ;
	}

	template <typename U>
	Vector<1,T> operator * ( const Vector<1,U>& In ) const
	{
		return Vector<1,T>( x - static_cast<T>(In.x) ) ;
	}

	template <typename U>
	Vector<1,T> operator / ( const Vector<1,U>& In ) const
	{
		return Vector<1,T>( x / static_cast<T>(In.x) ) ;
	}

	template <typename U>
	Vector<1,T>& operator += ( const Vector<1,U>& In )
	{
		x += static_cast<T>(In.x);
		return *this;
	}

	template <typename U>
	Vector<1,T>& operator -= ( const Vector<1,U>& In )
	{
		x -= static_cast<T>(In.x);
		return *this;
	}

	template <typename U>
	Vector<1,T>& operator *= ( const Vector<1,U>& In )
	{
		x *= static_cast<T>(In.x);
		return *this;
	}

	template <typename U>
	Vector<1,T>& operator /= ( const Vector<1,U>& In )
	{
		x /= static_cast<T>(In.x);
		return *this;
	}

	template <typename U>
	Vector<1,T> operator + ( U In ) const
	{
		return Vector<1,T>( x + static_cast<T>(In) ) ;
	}

	template <typename U>
	Vector<1,T> operator - ( U In ) const
	{
		return Vector<1,T>( x - static_cast<T>(In) ) ;
	}

	template <typename U>
	Vector<1,T> operator * ( U In ) const
	{
		return Vector<1,T>( x * static_cast<T>(In) ) ;
	}

	template <typename U>
	Vector<1,T> operator / ( U In ) const
	{
		return Vector<1,T>( x / static_cast<T>(In) ) ;
	}

	template <typename U>
	Vector<1,T>& operator += ( U In )
	{
		x += static_cast<T>(In);
		return *this;
	}

	template <typename U>
	Vector<1,T>& operator -= ( U In )
	{
		x -= static_cast<T>(In);
		return *this;
	}

	template <typename U>
	Vector<1,T>& operator *= ( U In )
	{
		x *= static_cast<T>(In);
		return *this;
	}

	template <typename U>
	Vector<1,T>& operator /= ( U In )
	{
		x /= static_cast<T>(In);
		return *this;
	}

	template <typename U>
	Vector<1,T>& operator = ( const Vector<1,U>& In )
	{
		x = static_cast<T>(In.x);
		return *this;
	}

};

template < typename T = float >
class Scalar : public Vector<1,T>
{
public:
	T& val;

	Scalar(){};

	Scalar(T v)
		: Vector(v)
		, val( Vector::x )
	{};

};

#include "Angle.h"

template < typename T >
class Vector< 2 , T >
{
public:
	T x;		///< X座標
	T y;		///< Y座標

public:
	Vector()
		: x	( 0 )
		, y	( 0 )
	{
	}

	Vector( T _x, T _y )
		: x	( _x )
		, y	( _y )
	{
	}

	Vector( const Vector<2,T>& In )
		: x	( In.x )
		, y	( In.y )
	{
	}

	template <typename U>
	Vector( const Vector<2,U>& In )
		: x	( static_cast<T>(In.x) )
		, y	( static_cast<T>(In.y) )
	{
	}

	Vector( Angle& ang )
		: x ( cos(ang) )
		, y ( sin(ang) )
	{};

	template <typename U>
	Vector<2,T> operator + ( const Vector<2,U>& In ) const
	{
		return Vector<2,T>
			( x + static_cast<T>(In.x)
			, y + static_cast<T>(In.y)
			);
	}

	template <typename U>
	Vector<2,T> operator - ( const Vector<2,U>& In ) const
	{
		return Vector<2,T>
			( x - static_cast<T>(In.x)
			, y - static_cast<T>(In.y)
			);
	}

	template <typename U>
	Vector<2,T> operator * ( const Vector<2,U>& In ) const
	{
		return Vector<2,T>
			( x * static_cast<T>(In.x)
			, y * static_cast<T>(In.y)
			);
	}

	template <typename U>
	Vector<2,T> operator / ( const Vector<2,U>& In ) const
	{
		return Vector<2,T>
			( x / static_cast<T>(In.x)
			, y / static_cast<T>(In.y)
			);
	}

	template <typename U>
	Vector<2,T>& operator += ( const Vector<2,U>& In )
	{
		x += static_cast<T>(In.x);
		y += static_cast<T>(In.y);
		return *this;
	}

	template <typename U>
	Vector<2,T>& operator -= ( const Vector<2,U>& In )
	{
		x -= static_cast<T>(In.x);
		y -= static_cast<T>(In.y);
		return *this;
	}

	template <typename U>
	Vector<2,T>& operator *= ( const Vector<2,U>& In )
	{
		x *= static_cast<T>(In.x);
		y *= static_cast<T>(In.y);
		return *this;
	}

	template <typename U>
	Vector<2,T>& operator /= ( const Vector<2,U>& In )
	{
		x /= static_cast<T>(In.x);
		y /= static_cast<T>(In.y);
		return *this;
	}

	template <typename U>
	Vector<2,T> operator + ( U In ) const
	{
		return Vector<2,T>
			( x + static_cast<T>(In)
			, y + static_cast<T>(In)
			);
	}

	template <typename U>
	Vector<2,T> operator - ( U In ) const
	{
		return Vector<2,T>
			( x - static_cast<T>(In)
			, y - static_cast<T>(In)
			);
	}

	template <typename U>
	Vector<2,T> operator * ( U In ) const
	{
		return Vector<2,T>
			( x * static_cast<T>(In)
			, y * static_cast<T>(In)
			);
	}

	template <typename U>
	Vector<2,T> operator / ( U In ) const
	{
		return Vector<2,T>
			( x / static_cast<T>(In)
			, y / static_cast<T>(In)
			);
	}

	template <typename U>
	Vector<2,T>& operator += ( U In )
	{
		x += static_cast<T>(In);
		y += static_cast<T>(In);
		return *this;
	}

	template <typename U>
	Vector<2,T>& operator -= ( U In )
	{
		x -= static_cast<T>(In);
		y -= static_cast<T>(In);
		return *this;
	}

	template <typename U>
	Vector<2,T>& operator *= ( U In )
	{
		x *= static_cast<T>(In);
		y *= static_cast<T>(In);
		return *this;
	}

	template <typename U>
	Vector<2,T>& operator /= ( U In )
	{
		x /= static_cast<T>(In);
		y /= static_cast<T>(In);
		return *this;
	}

	template <typename U>
	Vector<2,T>& operator = ( const Vector<2,U>& In )
	{
		x = static_cast<T>(In.x);
		y = static_cast<T>(In.y);
		return *this;
	}

	float Length() const
	{
		return sqrtf( (float) (x * x) + (y * y) );
	}

	T Square() const
	{
		return (x * x) + (y * y) ;
	}

	Vector<2,T>& SetLength( float Limit )
	{
		float Length = sqrtf( (x * x) + (y * y) );
		float Div = Limit / Length;
		x *= Div;
		y *= Div;

		return *this;
	}

	Vector<2,T>& Normalize()
	{
		return SetLength( 1.0f );
	}

	Vector<2,T> Norm() const
	{
		Vector<2,T> _temp(*this);
		return _temp.Normalize():
	}

};

template <typename T>
inline bool operator == ( const Vector<2,T>& lhs, const Vector<2,T>& rhs )
{
	if ( lhs.x == rhs.x  && lhs.y == rhs.y )
		return true;
	else
		return false;
}

template <typename T>
inline bool operator != ( const Vector<2,T>& lhs, const Vector<2,T>& rhs )
{
	return !(lhs == rhs);
}

typedef Vector<2,int>	Vector2DI;
typedef Vector<2,float>	Vector2DF;


template< typename T >
class Vector< 3 , T >
{
public:
public:
	T x;		///< X座標
	T y;		///< Y座標
	T z;		///< Z座標

public:
	Vector()
		: x	( 0 )
		, y	( 0 )
		, z	( 0 )
	{
	}

	Vector( T _x, T _y, T _z )
		: x	( _x )
		, y	( _y )
		, z	( _z )
	{
	}

	Vector( const Vector<3,T>& In )
		: x	( In.x )
		, y	( In.y )
		, z	( In.z )
	{
	}

	template <typename U>
	Vector( const Vector<3,U>& In )
		: x	( static_cast<T>(In.x) )
		, y	( static_cast<T>(In.y) )
		, z	( static_cast<T>(In.z) )
	{
	}

	template <typename U>
	Vector( const Vector<2,U>& In )
		: x	( static_cast<T>(In.x) )
		, y	( static_cast<T>(In.y) )
		, z	( 0.0 )
	{
	}

	Vector( Angle& VRotate , Angle& HRotate )
		: x ( cos(HRotate) * cos(VRotate) )
		, y	( 1.0		   * sin(VRotate) )
		, z	( sin(HRotate) * cos(VRotate) )
	{};

	template <typename U>
	Vector<3,T> operator + ( const Vector<3,U>& In ) const
	{
		Vector<3,T> Out;
		Out.x = x + static_cast<T>(In.x);
		Out.y = y + static_cast<T>(In.y);
		Out.z = z + static_cast<T>(In.z);
		return Out;
	}

	template <typename U>
	Vector<3,T> operator - ( const Vector<3,U>& In ) const
	{
		Vector<3,T> Out;
		Out.x = x - static_cast<T>(In.x);
		Out.y = y - static_cast<T>(In.y);
		Out.z = z - static_cast<T>(In.z);
		return Out;
	}

	template <typename U>
	Vector<3,T> operator * ( const Vector<3,U>& In ) const
	{
		Vector<3,T> Out;
		Out.x = x * static_cast<T>(In.x);
		Out.y = y * static_cast<T>(In.y);
		Out.z = z * static_cast<T>(In.z);
		return Out;
	}

	template <typename U>
	Vector<3,T> operator / ( const Vector<3,U>& In ) const
	{
		Vector<3,T> Out;
		Out.x = x / static_cast<T>(In.x);
		Out.y = y / static_cast<T>(In.y);
		Out.z = z / static_cast<T>(In.z);
		return Out;
	}

	template <typename U>
	Vector<3,T>& operator += ( const Vector<3,U>& In )
	{
		x += static_cast<T>(In.x);
		y += static_cast<T>(In.y);
		z += static_cast<T>(In.z);
		return *this;
	}

	template <typename U>
	Vector<3,T>& operator -= ( const Vector<3,U>& In )
	{
		x -= static_cast<T>(In.x);
		y -= static_cast<T>(In.y);
		z -= static_cast<T>(In.z);
		return *this;
	}

	template <typename U>
	Vector<3,T>& operator *= ( const Vector<3,U>& In )
	{
		x *= static_cast<T>(In.x);
		y *= static_cast<T>(In.y);
		z *= static_cast<T>(In.z);
		return *this;
	}

	template <typename U>
	Vector<3,T>& operator /= ( const Vector<3,U>& In )
	{
		x /= static_cast<T>(In.x);
		y /= static_cast<T>(In.y);
		z /= static_cast<T>(In.z);
		return *this;
	}

	template <typename U>
	Vector<3,T> operator + ( const U In ) const
	{
		Vector<3,T> Out;
		Out.x = x + static_cast<T>(In);
		Out.y = y + static_cast<T>(In);
		Out.z = z + static_cast<T>(In);
		return Out;
	}

	template <typename U>
	Vector<3,T> operator - ( const U In ) const
	{
		Vector<3,T> Out;
		Out.x = x - static_cast<T>(In);
		Out.y = y - static_cast<T>(In);
		Out.z = z - static_cast<T>(In);
		return Out;
	}

	template <typename U>
	Vector<3,T> operator * ( const U In ) const
	{
		Vector<3,T> Out;
		Out.x = x * static_cast<T>(In);
		Out.y = y * static_cast<T>(In);
		Out.z = z * static_cast<T>(In);
		return Out;
	}

	template <typename U>
	Vector<3,T> operator / ( const U In ) const
	{
		Vector<3,T> Out;
		Out.x = x / static_cast<T>(In);
		Out.y = y / static_cast<T>(In);
		Out.z = z / static_cast<T>(In);
		return Out;
	}

	template <typename U>
	Vector<3,T>& operator += ( const U In )
	{
		x += static_cast<T>(In);
		y += static_cast<T>(In);
		z += static_cast<T>(In);
		return *this;
	}

	template <typename U>
	Vector<3,T>& operator -= ( const U In )
	{
		x -= static_cast<T>(In);
		y -= static_cast<T>(In);
		z -= static_cast<T>(In);
		return *this;
	}

	template <typename U>
	Vector<3,T>& operator *= ( const U In )
	{
		x *= static_cast<T>(In);
		y *= static_cast<T>(In);
		z *= static_cast<T>(In);
		return *this;
	}

	template <typename U>
	Vector<3,T>& operator /= ( const U In )
	{
		x /= static_cast<T>(In);
		y /= static_cast<T>(In);
		z /= static_cast<T>(In);
		return *this;
	}

	template <typename U>
	Vector<3,T>& operator = ( const Vector<3,U>& In )
	{
		x = static_cast<T>(In.x);
		y = static_cast<T>(In.y);
		z = static_cast<T>(In.z);
		return *this;
	}
};

template <typename T>
inline bool operator == ( const Vector<3,T>& lhs, const Vector<3,T>& rhs )
{
	if ( lhs.x != rhs.x ) return false;
	if ( lhs.y != rhs.y ) return false;
	if ( lhs.z != rhs.z ) return false;
	return true;
}

template <typename T>
inline bool operator != ( const Vector<3,T>& lhs, const Vector<3,T>& rhs )
{
	return !(lhs == rhs);
}

typedef Vector<3,int>	Vector3DI;
typedef Vector<3,float>	Vector3DF;


