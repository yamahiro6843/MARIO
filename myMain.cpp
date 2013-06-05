#include "myMain.h"
#include "myMacro.h"
#include "color.h"

#include <ppl.h>
using namespace Concurrency;


myMain::myMain()
	: _ball ( UseDxPoint<3>(0,0,0) , UseDxVector<3>(3,5,0) , new Color(255,255,255) , 5 )
{
	static int yoko_num = 8;
	static int tate_num = 6;
	static int size = 40;

	_boxes.reserve(yoko_num);
	int screen_x = UseDxLib::ScreenSingleton::Instance().ScreenSize().x;
	int screen_y = UseDxLib::ScreenSingleton::Instance().ScreenSize().y;

	for( int i = 0 ; i < yoko_num ; i++)
	{
		_boxes.push_back( std::vector<Box>(tate_num) ) ;
	}
	for( int i = 0 ; i < yoko_num ; i++ )
	{
		for( int j = 0 ; j < tate_num ; j++)
		{
			_boxes.at(i).at(j) = Box( UseDxPoint<3>((size+10)*i,screen_y - (size+10)*j,0) , new Color(255,255,255) , size );
		}
	}

}

// initialize before main loop process
UseDxLibMessage::MESSAGE myMain::init()
{
	auto	position	= UseDxPoint<3>( 320, 240 , -800.0f ) ;
	auto	target		= UseDxPoint<3>( 320 , 240 , 1.0f ) ;
	auto	up			= UseDxVector<3>( 0.0f , 1.0f , 0.0f ) ;
	UseDxLib::CameraSingleton::Instance().SetPositionAndTargetAndUpVec( position , target , up ) ;

	return UseDxLibMessage::MESSAGE::CORRECT ;
}

UseDxLibMessage::MESSAGE myMain::loop_init()
{
	MoverReg::Instance().doit();
	ActionAutonomyReg::Instance().doit();
	ActionDeleter::Instance().doit();

	static Camera& c = UseDxLib::CameraSingleton::Instance();
	static Screen& s = UseDxLib::ScreenSingleton::Instance();
	static Mouse& m = UseDxLib::MouseSingleton::Instance();

	UseDxPoint<3> pos = c._position;
	printfDx("pos x  %f , pos y %f , pos z %f\n",pos.x,pos.y,pos.z);

	if( 
		m._pre_data._buttons.at(Mouse::BUTTON::LEFT).isPushed() &&
		m._now_data._buttons.at(Mouse::BUTTON::LEFT).isPushed()
		)
	{
		UseDxVector<3> dif = m._now_data._point - m._pre_data._point;
		dif = UseDxVector<3>( -dif.x , dif.y , 0 );
		pos = pos + dif;
	}

	if( 
		m._pre_data._buttons.at(Mouse::BUTTON::RIGHT).isPushed() &&
		m._now_data._buttons.at(Mouse::BUTTON::RIGHT).isPushed()
		)
	{
		UseDxVector<3> dif = m._now_data._point - m._pre_data._point;
		dif = UseDxVector<3>( 0 , 0 , dif.y );
		pos = pos + dif;
	}


	UseDxPoint<3> _position(  pos.x , pos.y , pos.z ) ;
	UseDxPoint<3> _target( pos.x , pos.y , 1.0f ) ;
	printfDx("pos x  %f , pos y %f , pos z %f\n",pos.x,pos.y,pos.z);
	c.SetPositionAndTargetAndUpVec( _position , _target ) ;

	return UseDxLibMessage::MESSAGE::CORRECT ;
};

UseDxLibMessage::MESSAGE myMain::loop_enit()
{
	DrawerReg::Instance().doit();

	int bunnkatsusuu_sayuu = 20;
	int bunnkatsusuu_jouge = 20;

	float yoko = (float) UseDxLib::ScreenSingleton::Instance().ScreenSize().x / bunnkatsusuu_sayuu;
	float tate = (float) UseDxLib::ScreenSingleton::Instance().ScreenSize().y / bunnkatsusuu_jouge;

	for( int i = 0 ; i < bunnkatsusuu_sayuu ; ++i)
	{
		for( int j = 0 ; j < bunnkatsusuu_jouge ; ++j )
		{
			Color col;
			if( ( i + j ) %2 == 0 )
			{
				col = Color();
			}
			else
			{
				col = Color(0,0,0) ;
			}
			DrawBox( yoko * i , tate * j , yoko * (i+1) , tate * (j+1) , col.IntColor() , TRUE );
		}
	}


	return UseDxLibMessage::MESSAGE::CORRECT ;
};

UseDxLibMessage::MESSAGE myMain::doit()
{

	return UseDxLibMessage::MESSAGE::CORRECT ;
}









