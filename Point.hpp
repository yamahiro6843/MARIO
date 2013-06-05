#pragma once
#include <boost/serialization/serialization.hpp>

/*---------------------- Class Point----------------------------

�ړI�F2�������W�̔ėp�N���X

�����F�e���v���[�g

--------------------------------------------------------------------------*/

template <class T>
class Point
{
	friend class boost::serialization::access;

	public:
		//���W�l
		T x,y;

		//�V���A���C�Y�p
		template<class Archive>
		void serialize( Archive& ar, unsigned int ver )
		{
			ar & boost::serialization::make_nvp("x", this->x);
			ar & boost::serialization::make_nvp("y", this->y);
		}

		double distance( Point<T> const & p ) const 
		{
			return sqrt( powf( (float)( this->x - p.x ), 2 ) + powf( (float)( this->y - p.y ), 2 ) );
		}

		//�R���X�g���N�^
		Point()
		{
			x = 0;
			y = 0;
		}
      
		//�R���X�g���N�^
		Point(const T& t1, const T& t2)
		{
			x = t1;
			y = t2;
		}

		//�R���X�g���N�^
		Point(double const t1, double const t2)
		{
			x = (const T)t1;
			y = (const T)t2;
		}

		// +���Z�q�I�[�o�[���[�h
		Point<T> operator+(const Point<T>& obj) const
		{
			Point tmp;
			tmp.x = x + obj.x;
			tmp.y = y + obj.y;
			return tmp;
		}


		// -���Z�q�I�[�o�[���[�h
		Point<T> operator-(const Point<T>& obj) const
		{
			Point tmp;
			tmp.x = x - obj.x;
			tmp.y = y - obj.y;
			return tmp;
		}

		// *���Z�q�I�[�o�[���[�h
		Point<T> operator*(const double& d) const
		{
			Point tmp;
			tmp.x = (T)(this->x * d);
			tmp.y = (T)(this->y * d);
			return tmp;
		}

		// /���Z�q�I�[�o�[���[�h
		Point<T> operator/(const double& d) const
		{
			Point tmp;
			tmp.x = (T)(this->x / d);
			tmp.y = (T)(this->y / d);
			return tmp;
		}

		// +=���Z�q�I�[�o�[���[�h
		Point<T>& operator+=(const Point<T>& obj)
		{
			x += obj.x;
			y += obj.y;
			return *this;
		}

		// -=���Z�q�I�[�o�[���[�h
		Point<T>& operator-=(const Point<T>& obj)
		{
			x -= obj.x;
			y -= obj.y;
			return *this;
		}

		// *=���Z�q�I�[�o�[���[�h
		Point<T>& operator*=(const double d)
		{
			(T)(this->x *= d);
			(T)(this->y *= d);
			return *this;
		}
		
		// /=���Z�q�I�[�o�[���[�h
		Point<T>& operator/=(const double d)
		{
			(T)(this->x /= d);
			(T)(this->y /= d);
			return *this;
		}

		// =���Z�q�I�[�o�[���[�h
		Point<T>& operator=(const Point<T>& obj)
		{
			x = obj.x;
			y = obj.y;
			return *this;
		}

		// ==���Z�q�I�[�o�[���[�h
		bool operator==(const Point<T>& obj) const
		{
			if( x == obj.x && y == obj.y)
				return true;
			else
				return false;
		}
		
		// !=���Z�q�I�[�o�[���[�h
		bool operator!=(const Point<T>& obj) const
		{
			if( x != obj.x || y != obj.y)
				return true;
			else
				return false;
		}

		// <���Z�q�I�[�o�[���[�h
		bool operator<(const Point<T>& obj) const
		{
			if( x*100 + y < obj.x*100 + obj.y )
				return true;
			else
				return false;
		}



};