#pragma once

#include "Vector.h"
#include "myMacro.h"
#include <cmath>

class Radian : public Scalar<float>
{
public:
	Radian( float val )
		: Scalar( val )
	{};
};

class Degree : public Scalar<float>
{
public:
	Degree(float val)
		: Scalar( val )
	{};
};

class Angle : public Radian
{
public:

	Angle( Radian rad )
		: Radian( rad ) 
	{}

	Angle( Degree deg )
		: Radian( deg2rad(deg.val) ) 
	{}

	operator Radian()
	{
		return (Radian) *this;
	}

	operator Degree()
	{
		return Degree( rad2deg(this->val) );
	}

};


inline static Degree rad2deg( Radian rad )
{
	return Degree( rad2deg(rad.val) ) ;
}

inline static Radian deg2rad( Degree deg )
{
	return Radian( deg2rad(deg.val) ) ;
}




inline static float sin(Angle ang)
{
	return sin( Radian(ang).val );
}

inline static float cos(Angle ang)
{
	return cos( Radian(ang).val );
}

inline static float tan(Angle ang)
{
	return tan( Radian(ang).val );
}



