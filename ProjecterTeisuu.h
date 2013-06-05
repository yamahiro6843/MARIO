#pragma once

#include <vector>
#include "Point.h"
#include "Vector.h"
#include "Geometry.h"
#include "defines.hpp"
//#include ""
#include <string>
#include <memory>
#include <opencv2\opencv.hpp>
#include <map>


// 定数とか
namespace Projecter
{
	static int		teisuu_takasa = 2 ;
	static int		teisuu_yoko = 3;
	static int		teisuu_oku = 2;
	static int		teisuu_radius = 20;
	static int		teisuu_bokashi_method = CV_GAUSSIAN ;
	static int		teisuu_bokashi_size = 19 ;
	static CvScalar	teisuu_shadow_color = cvScalarAll( 255 );
	static int		teisuu_character_suu = 3;
	static float	teisuu_factor = (float) 0.1 ;
	static int		teisuu_block_size = 100;
	static Vector<2,int> teisuu_window_size( 800 , 600 );
	static int		teisuu_margin = 100; // must < window_size / 2 

	#define game_pixel_per_cm  ( (float) 100 / 6 ) 
	// ゲーム内座標における床からプロジェクターまでの距離
	static float teisuu_distance_to_projecter = 86 * game_pixel_per_cm ; 
}






