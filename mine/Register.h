#pragma once

#include <set>
#include <Singleton.h>
#include <iostream>
#include "myMacro.h"

template< typename T >
class Registry
{
public:
	typedef T* HoldType;

protected:
	std::set<HoldType> _holder;

public:

	Registry(){};
	virtual ~Registry(){};

	void Register(HoldType ptr)
	{
		_holder.insert( ptr );
	}

	void Deregister(HoldType ptr)
	{
		_holder.erase( ptr );
	}

	// all Registees doit()
	virtual void doit()
	{
		//class DoItFunc
		//{
		//public:
		//	void operator () (HoldType ptr)
		//	{
		//		ptr->doit();
		//	};
		//};
		//std::for_each( _holder.begin() , _holder.end() , DoItFunc() );

		auto func = [](HoldType ptr){ptr->doit();};
		foreach( _holder , func );


		foreach( _holder , [](HoldType ptr)
		{
			ptr -> doit();
		} );

		//for each (auto ptr in _holder)
		//{
		//	ptr->doit();
		//}

	};

};

template < typename T >
class Registee : public T
{
private:
	Registry<T>* _reg;

public:

	Registee()
		: _reg( &( Loki::SingletonHolder<Registry<T>>::Instance() ) )
	{
		_reg->Register( this );
	}

	virtual ~Registee()
	{
		_reg->Deregister( this );
	}

};

template < typename Act >
class Autonomy 
{
private:
	//protection
	void* operator new[];

private:
	Act* _act;

public:

	Autonomy()
		: _act( new Act )
	{};

	virtual ~Autonomy()
	{
		delete _act;
	};

	void doit()
	{
		_act->doit();
		if( _act->DeleteCondition() )
		{
			Loki::SingletonHolder<Deleter<Autonomy<Act>>>::Instance().Register(this);
		}
	}

};

template < typename Act >
class Auto : public Registee< Autonomy<Act> >
{};


template < typename T >
class Deleter : public Registry<T>
{
	class DeleteFunc
	{
	public:
		void operator () (typename Registry<T>::HoldType ptr)
		{
			delete ptr;
		};
	};

public:
	void doit()
	{
		for_each( _holder.begin() , _holder.end() , DeleteFunc() );
		_holder.swap( std::set<Registry<T>::HoldType>() );
	};
};




