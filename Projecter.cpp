#include "Projecter.h"
#include "defines.hpp"
#include <DxLib.h>


#define HERE Projecter


namespace Projecter
{
	GameCoodPoint::GameCoodPoint( const DrawCoodPoint& draw_p )
	{
		CalibrationData& calib_data = CalibrationData::SysCalibData::Instance();
		DrawCoodPoint LEFT_UP	 = calib_data.CornerAt( CalibrationData::Corner::LEFT_UP	);
		DrawCoodPoint RIGHT_DOWN = calib_data.CornerAt( CalibrationData::Corner::RIGHT_DOWN	);
		int dif_x = RIGHT_DOWN.x - LEFT_UP.x ;
		int dif_y = RIGHT_DOWN.y - LEFT_UP.y ;
		int field_yoko = teisuu_block_size * teisuu_yoko ;
		int field_oku  = teisuu_block_size * teisuu_oku  ;
		float rate_x = (float) field_yoko / dif_x ;
		float rate_y = (float) field_oku  / dif_y ;

		this->x = (draw_p.x - LEFT_UP.x) * rate_x ;
		this->y = (draw_p.y - LEFT_UP.y) * rate_y ;
		this->z = draw_p.z ;
	}

	DrawCoodPoint::DrawCoodPoint( const GameCoodPoint& game_p )
	{
		CalibrationData& calib_data = CalibrationData::SysCalibData::Instance();
		DrawCoodPoint LEFT_UP	 = calib_data.CornerAt( CalibrationData::Corner::LEFT_UP	);
		DrawCoodPoint RIGHT_DOWN = calib_data.CornerAt( CalibrationData::Corner::RIGHT_DOWN	);
		int dif_x = RIGHT_DOWN.x - LEFT_UP.x ;
		int dif_y = RIGHT_DOWN.y - LEFT_UP.y ;
		int field_yoko = teisuu_block_size * teisuu_yoko ;
		int field_oku  = teisuu_block_size * teisuu_oku  ;
		float rate_x = (float) dif_x / field_yoko ;
		float rate_y = (float) dif_y / field_oku  ;

		this->x = LEFT_UP.x + game_p.x * rate_x;
		this->y = LEFT_UP.y + game_p.y * rate_y;
		this->z = game_p.z ;
	}
}




#undef HERE
