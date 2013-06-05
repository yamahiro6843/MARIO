#pragma once 
#include <vector>
#include <fstream>
#include "Point.h"
#include "Vector.h"
#include "Geometry.h"
#include "defines.hpp"
#include <string>
#include <memory>
#include <opencv2\opencv.hpp>
#include "ProjecterTeisuu.h"


// ゲーム内座標と描画座標の変換
namespace Projecter
{
	class DrawCoodPoint;
	class GameCoodPoint : public Point<3,float>
	{
	public:
		GameCoodPoint(float x = 0 , float y = 0 , float z = 0 )
			: Point(x,y,z)
		{}
		GameCoodPoint( const DrawCoodPoint& obj );
	};

	class DrawCoodPoint : public Point<3,float>
	{
	public:
		DrawCoodPoint( float x = 0 , float y = 0 , float z = 0 )
			: Point(x,y,z)
		{};
		DrawCoodPoint( const Point<3,float>& p )
			: Point( p ) 
		{}
		DrawCoodPoint( const GameCoodPoint& obj );
	};
}



// 描画イメージクラス
namespace Projecter
{
	class Image
	{
		class myIplImage : public IplImage
		{
		public:
			void* operator new( size_t size )
			{
				Vector<2,int>& s = ::Projecter::teisuu_window_size;
				CvSize cs = cvSize( s.x , s.y );
				return ( myIplImage* ) cvCreateImage( cs , IPL_DEPTH_8U , 3 );
			}

			void operator delete( void* pt )
			{
				cvReleaseImage( (IplImage**) &pt );
			}

		};

	public:
		std::tr1::shared_ptr<myIplImage> spImage;

	public:
		Image()
			: spImage( new myIplImage )
		{
			int i = 0;
		}
		~Image()
		{}
		const Image& operator += ( const Image& rhs )
		{
			cvAdd( this->spImage.get() , rhs.spImage.get() , this->spImage.get() );
			return *this;
		}
		void ClearImage()
		{
			cvSetZero( this->spImage.get() ) ;
		}
	};

	class LayerImage : public Image
	{
	public:
		int height;

		void DrawShadow( DrawCoodPoint _point )
		{
			this->ClearImage();
			if( this->height >= 0 )
			{
				CvPoint center = cvPoint( _point.x , _point.y ) ;
				cvCircle
					( this->spImage.get() , center , teisuu_radius 
					, teisuu_shadow_color , CV_FILLED );
			}
		}
	};
}

namespace Projecter
{
	static Point<2,int> mouse_point(teisuu_margin,teisuu_margin);

	static int key ;
	static void mouse_call_back(int event, int x, int y, int flags, void* param)
	{
		if( event == CV_EVENT_LBUTTONDOWN )
		{
			mouse_point.x = x;
			mouse_point.y = y;
		}
		else if( event == CV_EVENT_MOUSEMOVE && ( flags & CV_EVENT_FLAG_LBUTTON ) )
		{
			mouse_point.x = x ;
			mouse_point.y = y ;
		}
	}
}


namespace Projecter 
{
	//class Image;
	//class LayerImage;

	class CalibrationData
	{
	public:
		typedef Loki::SingletonHolder<CalibrationData> SysCalibData; 
		enum Corner
		{
			LEFT_UP		= 0,
			RIGHT_UP	= 1,
			RIGHT_DOWN	= 2,
			LEFT_DOWN	= 3,
		};

	private:
		std::vector<DrawCoodPoint> corners;

	public:
		DrawCoodPoint proj_pos;

	public:
		Corner calib_point ;
		bool calib_flag ;

		CalibrationData( )
			: corners( 4 )
			, proj_pos( teisuu_window_size.x/ 2 , teisuu_window_size.y /2  , teisuu_distance_to_projecter )
			, calib_point ( Corner::LEFT_UP )
			, calib_flag ( true )
		{
			this->corners[ LEFT_UP		] 
			= DrawCoodPoint( teisuu_margin , teisuu_margin );
			this->corners[ RIGHT_UP		] 
			= DrawCoodPoint( teisuu_window_size.x - teisuu_margin , teisuu_margin );
			this->corners[ RIGHT_DOWN	] 
			= DrawCoodPoint( teisuu_window_size.x - teisuu_margin , teisuu_window_size.y - teisuu_margin );
			this->corners[ LEFT_DOWN	] 
			= DrawCoodPoint( teisuu_margin , teisuu_window_size.y - teisuu_margin );
		}
		DrawCoodPoint CornerAt( Corner num )
		{
			return this->corners[num];
		}
		void UpdateInfo( Image dst_img )
		{
			int text_pos_y = 0;
			int text_height = 40;
			CvFont font;
			cvInitFont( &font , CV_FONT_HERSHEY_SIMPLEX , 1.0f , 1.0f );
			if( key  == 'c' )
			{
				calib_flag = !calib_flag;	
			}
			if( calib_flag )
			{
				text_pos_y += text_height ; 
				cvPutText( dst_img.spImage.get() ,  "KEY R : read calib data from file" , cvPoint(0,text_pos_y) , &font , cvScalarAll(0) );
				text_pos_y += text_height ; 
				cvPutText( dst_img.spImage.get() ,  "KEY S : save calib data to file" , cvPoint(0,text_pos_y) , &font , cvScalarAll(0) );
				if( key == 'r' )
				{
					std::ifstream ifs( "calib_data.txt" );
					if( !ifs )
					{
						MessageBox( NULL , "calib_data.txt not exist" , NULL , MB_OK );
						return ;
					}
					ifs >> this->proj_pos.x ;
					ifs >> this->proj_pos.y ;
					ifs >> this->proj_pos.z ;
					ifs >> this->corners[0].x ;
					ifs >> this->corners[0].y ;
					ifs >> this->corners[0].z ;
					ifs >> this->corners[1].x ;
					ifs >> this->corners[1].y ;
					ifs >> this->corners[1].z ;
					ifs >> this->corners[2].x ;
					ifs >> this->corners[2].y ;
					ifs >> this->corners[2].z ;
					ifs >> this->corners[3].x ;
					ifs >> this->corners[3].y ;
					ifs >> this->corners[3].z ;
					::Projecter::mouse_point.x = corners[calib_point].x;
					::Projecter::mouse_point.y = corners[calib_point].y;
				}
				if( key == 's' )
				{
					std::ofstream ofs( "calib_data.txt" );
					ofs << this->proj_pos.x << std::endl ;
					ofs << this->proj_pos.y << std::endl ;
					ofs << this->proj_pos.z << std::endl ;
					ofs << this->corners[0].x << std::endl ;
					ofs << this->corners[0].y << std::endl ;
					ofs << this->corners[0].z << std::endl ;
					ofs << this->corners[1].x << std::endl ;
					ofs << this->corners[1].y << std::endl ;
					ofs << this->corners[1].z << std::endl ;
					ofs << this->corners[2].x << std::endl ;
					ofs << this->corners[2].y << std::endl ;
					ofs << this->corners[2].z << std::endl ;
					ofs << this->corners[3].x << std::endl ;
					ofs << this->corners[3].y << std::endl ;
					ofs << this->corners[3].z << std::endl ;
				}
				static bool corner_calib_flag = true ;

				for( int i = 0 ; i < 4 ; ++i )
				{
					cvCircle( dst_img.spImage.get() , cvPoint(  this->corners[i].x , this->corners[i].y  ) , 5 , cvScalarAll(0) , CV_FILLED );
				}

				if( key  == 'p' )
				{
					corner_calib_flag = !corner_calib_flag ;
					if( corner_calib_flag )
					{
						mouse_point.x = corners[ this->calib_point ].x;
						mouse_point.y = corners[ this->calib_point ].y;
					}
				}

				if( corner_calib_flag ) // 四隅のキャリブ
				{
					text_pos_y += text_height ; 
					cvPutText( dst_img.spImage.get() ,  "please select calib point " , cvPoint(0,text_pos_y) , &font , cvScalarAll(0) );
					text_pos_y += text_height ; 
					cvPutText( dst_img.spImage.get() ,  "   KEY 1 is LEFT_UP    point " , cvPoint(0,text_pos_y) , &font , cvScalarAll(0) );
					text_pos_y += text_height ; 
					cvPutText( dst_img.spImage.get() ,  "   KEY 2 is RIGHT_UP   point " , cvPoint(0,text_pos_y) , &font , cvScalarAll(0) );
					text_pos_y += text_height ; 
					cvPutText( dst_img.spImage.get() ,  "   KEY 3 is RIGHT_DOWN point " , cvPoint(0,text_pos_y) , &font , cvScalarAll(0) );
					text_pos_y += text_height ; 
					cvPutText( dst_img.spImage.get() ,  "   KEY 4 is LEFT_DOWN  point " , cvPoint(0,text_pos_y) , &font , cvScalarAll(0) );
					text_pos_y += text_height ; 
					cvPutText( dst_img.spImage.get() ,  "Push P To calibrate Projecter Position " , cvPoint(0,text_pos_y) , &font , cvScalarAll(0) );

					cvCircle
						( dst_img.spImage.get() 
						, cvPoint( this->CornerAt(this->calib_point).x , this->CornerAt(this->calib_point).y )
						, 5 , CV_RGB(255,255,0) , CV_FILLED );

					if( key  == '1' )
					{
						calib_point = Corner::LEFT_UP;
						mouse_point.x = CornerAt( Corner::LEFT_UP ).x;
						mouse_point.y = CornerAt( Corner::LEFT_UP ).y;
					}
					if( key  == '2')
					{
						calib_point = Corner::RIGHT_UP;
						mouse_point.x = CornerAt( Corner::RIGHT_UP ).x;
						mouse_point.y = CornerAt( Corner::RIGHT_UP ).y;
					}
					if( key  == '3' )
					{
						calib_point = Corner::RIGHT_DOWN;
						mouse_point.x = CornerAt( Corner::RIGHT_DOWN ).x;
						mouse_point.y = CornerAt( Corner::RIGHT_DOWN ).y;
					}
					if( key  == '4' )
					{
						calib_point = Corner::LEFT_DOWN;
						mouse_point.x = CornerAt( Corner::LEFT_DOWN ).x;
						mouse_point.y = CornerAt( Corner::LEFT_DOWN ).y;
					}


					if( calib_point == Corner::LEFT_UP ) 
					{
						text_pos_y += text_height ; 
						cvPutText( dst_img.spImage.get() ,  "now selected point is LEFT_UP " , cvPoint(0,text_pos_y) , &font , cvScalarAll(0) );
						cvCircle( dst_img.spImage.get() , cvPoint(  this->corners[LEFT_UP].x , this->corners[LEFT_UP].y ) , 5 , CV_RGB(255,255,0) , CV_FILLED );
					}
					if( calib_point == Corner::LEFT_DOWN ) 
					{
						text_pos_y += text_height ; 
						cvPutText( dst_img.spImage.get() ,  "now selected point is LEFT_DOWN " , cvPoint(0,text_pos_y) , &font , cvScalarAll(0) );
						cvCircle( dst_img.spImage.get() , cvPoint(  this->corners[LEFT_DOWN].x , this->corners[LEFT_DOWN].y ) , 5 , CV_RGB(255,255,0) , CV_FILLED );
					}
					if( calib_point == Corner::RIGHT_UP ) 
					{
						text_pos_y += text_height ; 
						cvPutText( dst_img.spImage.get() ,  "now selected point is RIGHT_UP " , cvPoint(0,text_pos_y) , &font , cvScalarAll(0) );
						cvCircle( dst_img.spImage.get() , cvPoint(  this->corners[RIGHT_UP].x , this->corners[RIGHT_UP].y ) , 5 , CV_RGB(255,255,0) , CV_FILLED );
					}
					if( calib_point == Corner::RIGHT_DOWN ) 
					{
						text_pos_y += text_height ; 
						cvPutText( dst_img.spImage.get() ,  "now selected point is RIGHT_DOWN " , cvPoint(0,text_pos_y) , &font , cvScalarAll(0) );
						cvCircle( dst_img.spImage.get() , cvPoint(  this->corners[RIGHT_DOWN].x , this->corners[RIGHT_DOWN].y ) , 5 , CV_RGB(255,255,0) , CV_FILLED );
					}

					text_pos_y += text_height ; 
					cvPutText( dst_img.spImage.get() , " Please Click Mouse to calibrate selected_point  " , cvPoint(0,text_pos_y) , &font , cvScalarAll(0) ) ;

					this->corners[calib_point].x = mouse_point.x;
					this->corners[calib_point].y = mouse_point.y;

				}
				else // projecter calibration
				{
					text_pos_y += text_height ; 
					cvPutText( dst_img.spImage.get() ,  "Projceter Positoin calibration " , cvPoint(0,text_pos_y) , &font , cvScalarAll(0) );
					text_pos_y += text_height ; 
					cvPutText( dst_img.spImage.get() ,  "KEY H : change calib precision" , cvPoint(0,text_pos_y) , &font , cvScalarAll(0) );
					static bool high_precision_mode = false;
					if( key == 'h' )
					{
						high_precision_mode = !high_precision_mode ;
					}

					char buf[1000];
					sprintf( buf , "   proj_pos : %.0f , %.0f" , this->proj_pos.x , this->proj_pos.y );
					text_pos_y += text_height ; 
					cvPutText( dst_img.spImage.get() , buf , cvPoint(0,text_pos_y) , &font , cvScalarAll(0) );

					sprintf( buf , "   proj_height %f(pix)" , this->proj_pos.z );
					text_pos_y += text_height ; 
					cvPutText( dst_img.spImage.get() , buf , cvPoint(0,text_pos_y) , &font , cvScalarAll(0) );

					sprintf( buf , "   proj_height %f(cm)" , this->proj_pos.z / game_pixel_per_cm );
					text_pos_y += text_height ; 
					cvPutText( dst_img.spImage.get() , buf , cvPoint(0,text_pos_y) , &font , cvScalarAll(0) );

					text_pos_y += text_height ; 
					cvPutText( dst_img.spImage.get() ,  "   Please Push U, D , TOP , BOTTOM , LEFT , RIGHT " , cvPoint(0,text_pos_y) , &font , cvScalarAll(0) );
					text_pos_y += text_height ; 
					cvPutText( dst_img.spImage.get() ,  "Push P To calibrate Corner Position " , cvPoint(0,text_pos_y) , &font , cvScalarAll(0) );

					const int CV_WAITKEY_CURSORKEY_TOP    = 2490368;
					const int CV_WAITKEY_CURSORKEY_BOTTOM = 2621440;
					const int CV_WAITKEY_CURSORKEY_RIGHT  = 2555904;
					const int CV_WAITKEY_CURSORKEY_LEFT   = 2424832;
					if( key == 'u' )
					{
						if( high_precision_mode )
						{
							this->proj_pos.z += 1;
						}
						else
						{
							this->proj_pos.z += 10;
						}

					}
					if( key == 'd' )
					{
						if( high_precision_mode )
						{
							this->proj_pos.z -= 1;
						}
						else
						{
							this->proj_pos.z -= 10;
						}
					}
					if( key == CV_WAITKEY_CURSORKEY_TOP )
					{
						if( high_precision_mode )
						{
							this->proj_pos.y -= 1;
						}
						else
						{
							this->proj_pos.y -= 10;
						}
					}
					if( key == CV_WAITKEY_CURSORKEY_BOTTOM )
					{
						if( high_precision_mode )
						{
							this->proj_pos.y += 1;
						}
						else
						{
							this->proj_pos.y += 10;
						}
					}
					if( key == CV_WAITKEY_CURSORKEY_LEFT )
					{
						if( high_precision_mode )
						{
							this->proj_pos.x -= 1;
						}
						else
						{
							this->proj_pos.x -= 10;
						}
					}
					if( key == CV_WAITKEY_CURSORKEY_RIGHT )
					{
						if( high_precision_mode )
						{
							this->proj_pos.x += 1;
						}
						else
						{
							this->proj_pos.x += 10;
						}
					}
				}

			}

		};

		Image transform( LayerImage _layer_img )
		{
			CalibrationData& calib_data = SysCalibData::Instance();


			//Point<3,float> PROJ_POS
			//	( this->proj_pos.x , this->proj_pos.y , this->proj_pos.z );
			DrawCoodPoint PROJ_POS( this->proj_pos ) ;

			Point<3,float> GROUND_LEFT_UP		= CornerAt( CalibrationData::Corner::LEFT_UP ); 
			Point<3,float> GROUND_RIGHT_UP		= CornerAt( CalibrationData::Corner::RIGHT_UP ); 
			Point<3,float> GROUND_RIGHT_DOWN	= CornerAt( CalibrationData::Corner::RIGHT_DOWN );
			Point<3,float> GROUND_LEFT_DOWN		= CornerAt( CalibrationData::Corner::LEFT_DOWN ); 

			float distance_between_layer_and_proj = PROJ_POS.z - _layer_img.height ;
			float dis = distance_between_layer_and_proj;

			Point<3,float> LAYER_LEFT_UP		= PROJ_POS + ( ( GROUND_LEFT_UP		- PROJ_POS ) * ( dis / PROJ_POS.z ) ) ; 
			Point<3,float> LAYER_RIGHT_UP		= PROJ_POS + ( ( GROUND_RIGHT_UP	- PROJ_POS ) * ( dis / PROJ_POS.z ) ) ; 
			Point<3,float> LAYER_RIGHT_DOWN		= PROJ_POS + ( ( GROUND_RIGHT_DOWN	- PROJ_POS ) * ( dis / PROJ_POS.z ) ) ; 
			Point<3,float> LAYER_LEFT_DOWN		= PROJ_POS + ( ( GROUND_LEFT_DOWN	- PROJ_POS ) * ( dis / PROJ_POS.z ) ) ; 

			CvMat *map_matrix;
			CvPoint2D32f src_pnt[4], dst_pnt[4];

			// (2)四角形の変換前と変換後の対応する頂点をそれぞれセットし
			//    cvWarpPerspectiveを用いて透視投影変換行列を求める
			src_pnt[0] = cvPoint2D32f ( LAYER_LEFT_UP.x		, LAYER_LEFT_UP.y );
			src_pnt[1] = cvPoint2D32f ( LAYER_RIGHT_UP.x	, LAYER_RIGHT_UP.y );
			src_pnt[2] = cvPoint2D32f ( LAYER_RIGHT_DOWN.x	, LAYER_RIGHT_DOWN.y );
			src_pnt[3] = cvPoint2D32f ( LAYER_LEFT_DOWN.x	, LAYER_LEFT_DOWN.y );

			dst_pnt[0] = cvPoint2D32f ( GROUND_LEFT_UP.x	, GROUND_LEFT_UP.y );
			dst_pnt[1] = cvPoint2D32f ( GROUND_RIGHT_UP.x	, GROUND_RIGHT_UP.y );
			dst_pnt[2] = cvPoint2D32f ( GROUND_RIGHT_DOWN.x	, GROUND_RIGHT_DOWN.y );
			dst_pnt[3] = cvPoint2D32f ( GROUND_LEFT_DOWN.x	, GROUND_LEFT_DOWN.y );

			map_matrix = cvCreateMat (3, 3, CV_32FC1);
			cvGetPerspectiveTransform (src_pnt, dst_pnt, map_matrix);

			// ちょっと強引なstatic
			static Image ground_img;
			ground_img.ClearImage();

			// (3)指定された透視投影変換行列により，cvWarpPerspectiveを用いて画像を変換させる
			cvWarpPerspective 
				( _layer_img.spImage.get() , ground_img.spImage.get() , map_matrix 
				, CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS , cvScalarAll(0) );

			return ground_img ;
		};
	};

}

