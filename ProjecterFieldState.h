
#pragma once

#include <opencv2\opencv.hpp>
#include <vector>
#include "ProjecterUtils.h"
#include "Point.h"
#include "Vector.h"
#include "Singleton.h"
#include "myMutex.h"

namespace Projecter 
{

	class FieldState
	{
	public:
		typedef Loki::SingletonHolder<FieldState> SysFieldState ;

		class Character
		{
		private:
			LayerImage layer_image;

		private:
			GameCoodPoint pos;

		public:
			Character( GameCoodPoint _pos = GameCoodPoint(50,50,1) )
				: pos( _pos )
			{
			};

			~Character()
			{
			}

			GameCoodPoint Pos() const
			{
				return this->pos;
			}

			void ChangePos(GameCoodPoint _pos)
			{
				this->pos = _pos;
				layer_image.height = this->pos.z;
			}
			int height() const
			{
				return pos.z;
			}
			GameCoodPoint center() const
			{
				return this->pos;
			}
			LayerImage CastShadowToLayer()
			{
				this->layer_image.height = this->pos.z ;
				this->layer_image.DrawShadow( this->center() );
				return this->layer_image;
			}
		};
		class Block{};
		class FieldData
		{
		public:
			GameCoodPoint p;
		};
	private:
		std::vector<Character> charas;
		GameCoodPoint test[6];

	public:

		const std::vector<Character>& Charas()
		{
			return this->charas;
		}

		FieldState()
		{
			charas.resize(1);
			test[0] = GameCoodPoint( 50,50, 100);
			test[1] = GameCoodPoint( 150,50, 200);
			test[2] = GameCoodPoint( 250,50, 300);
			test[3] = GameCoodPoint( 50,150, 200);
			test[4] = GameCoodPoint( 150,150, 300);
			test[5] = GameCoodPoint( 250,150, 100);
			charas[0].ChangePos( test[0] );

		};

		void UpdateState()
		{
			static int interval = 0;
			static int te_num = 0;
			static bool stop_flag = false;
			if( key == 'b' )
			{
				stop_flag = !stop_flag ;
			}
			if( !stop_flag )
			{
				++interval;
			}
			interval %= 60 ;
			if( interval == 0 )
			{
				++interval;
				++te_num ;
				te_num %= 6 ;
			}
			charas[0].ChangePos( test[te_num] );
		}

		void UpdateState( const FieldData& new_data )
		{
			charas[0].ChangePos( new_data.p );
		}
	};
}

