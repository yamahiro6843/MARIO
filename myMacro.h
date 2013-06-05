#pragma once

#include <algorithm>
#include "Typelist.h"

template < typename T >
inline static T Abs( T val )
{
	return ( val > 0 ) ? val : -val ;
}

//inline static float rand( float _max , float _min = 0 )
//{
//	float _temp_max = _max;
//	float _temp_min= _min;
//	_max = max(_temp_max , _temp_min);
//	_min = min(_temp_max , _temp_min);
//
//	return (float) rand() / RAND_MAX * (_max - _min) + _min;
//}


namespace Loki
{

	template <class TList, template <class> class Unit>
	class GenScatterHierarchy;

	template <class T1, class T2, template <class> class Unit>
	class GenScatterHierarchy<Typelist<T1, T2>, Unit>
		: public GenScatterHierarchy<T1, Unit>
		, public GenScatterHierarchy<T2, Unit>
	{
	public:
		typedef Typelist<T1, T2> TList;
		typedef GenScatterHierarchy<T1, Unit> LeftBase;
		typedef GenScatterHierarchy<T2, Unit> RightBase;
		template <typename T> struct Rebind
		{
			typedef Unit<T> Result;
		};
	};

	template <class AtomicType, template <class> class Unit>
	class GenScatterHierarchy : public Unit<AtomicType>
	{
		typedef Unit<AtomicType> LeftBase;
		template <typename T> struct Rebind
		{
			typedef Unit<T> Result;
		};
	};

	template <template <class> class Unit>
	class GenScatterHierarchy<NullType, Unit>
	{
		template <typename T> struct Rebind
		{
			typedef Unit<T> Result;
		};
	};
}     

template < typename Container , typename Functor >
static void foreach( Container container , Functor func )
{
	std::for_each
		( container.begin()
		, container.end()
		, func 
		);

	return;
}


template < typename T >
inline static void ErrorCheck( bool check , T exception )
{
	if( check )
	{
		throw exception;
	}
}




