#pragma once 

#include "Singleton.h"
#include "ProjecterFieldState.h"
#include "ProjecterCarib.h"
#include "ProjecterDispImage.h"

namespace Projecter
{
	class Projecter;
	typedef Loki::SingletonHolder<::Projecter::Projecter> SysProj;

	class Projecter
	{
	public:
		Projecter()
			: calib_data( CalibrationData::SysCalibData::Instance() )
			, field_state( FieldState::SysFieldState::Instance() )
		{
			// 書き換えることも可能
			//teisuu_takasa = 1 ;
			//ChangeWindowMode( TRUE );
			//SetDrawScreen( DX_SCREEN_BACK );
			//DxLib_Init();
			cvNamedWindow( "Projecter Image" , 0 );
			cvSetMouseCallback( "Projecter Image" ,  mouse_call_back );
			cvSetWindowProperty( "Projecter Image" , CV_WND_PROP_FULLSCREEN,CV_WINDOW_FULLSCREEN);		
		}
		~Projecter()
		{
			//DxLib_End();
		}

		int mainFlow()
		{
			for(;;)
			{
				key = cvWaitKey(1) ;
				// フィールド状態
				this->UpdateFieldState();
				// 影の形の画像生成
				this->GetShadowImage();
				// キャリブレーション情報
				this->UpdateCalibInfo();
				// 表示
				this->DisplayToWindow();
				// 終了条件下で終わり
				if( this -> EndCondition() ) break;
			}

			return EXIT_SUCCESS;
		}

	private:
		void UpdateFieldState()
		{
//			this->field_state.UpdateState();
		}

		//void GetShadowImage()
		//{
		//	this->proj_disp_image.ClearImage();
		//	foreach( chara , this->field_state.charas )
		//	{
		//		this->proj_disp_image += this->calib_data.transform( chara->CastShadowToLayer() );
		//		//LayerImage shadow( chara->CastShadowToLayer() );
		//		//cvShowImage( "original shadow" , shadow.spImage.get() );
		//		//Image transfm( calib_data.transform( shadow ) );
		//		//cvShowImage( "transfmed shadow" , transfm.spImage.get() );
		//		//proj_disp_image += transfm;
		//		//cvShowImage( "added shadow" , proj_disp_image.spImage.get() );
		//		//cvWaitKey();
		//	}
		//}

		void GetShadowImage()
		{
			cvRectangle
				( this->proj_disp_image.spImage.get() 
				, cvPoint(0,0) , cvPoint( teisuu_window_size.x , teisuu_window_size.y)
				, cvScalarAll( 255 ) , CV_FILLED 
				);
			DrawCoodPoint chara_pos =  this->field_state.Charas().at(0).Pos();
			DrawCoodPoint proj_pos =  calib_data.proj_pos;
			if( chara_pos.z < proj_pos.z )
			{
				float dis_bet_proj_ground = proj_pos.z;
				float dis_bet_proj_layer  = proj_pos.z - chara_pos.z;
				float rate = dis_bet_proj_ground / dis_bet_proj_layer ;
				DrawCoodPoint draw_point = proj_pos + ( ( chara_pos - proj_pos ) * rate );
				float draw_radius = teisuu_radius * rate;
				cvCircle
					( this->proj_disp_image.spImage.get()
					, cvPoint( draw_point.x , draw_point.y )
					, draw_radius , cvScalarAll(0) , CV_FILLED 
					);
				CvPoint left_up		= cvPoint( draw_point.x - draw_radius - teisuu_bokashi_size , draw_point.y - draw_radius - teisuu_bokashi_size ) ;
				CvPoint right_down	= cvPoint( draw_point.x + draw_radius + teisuu_bokashi_size , draw_point.y + draw_radius + teisuu_bokashi_size ) ; 
				if( left_up.x < 0 ) 
					left_up.x = 0;
				if( left_up.x > teisuu_window_size.x ) 
					left_up.x = teisuu_window_size.x - 1 ;
				if( left_up.y < 0 ) 
					left_up.y = 0;
				if( left_up.y > teisuu_window_size.y ) 
					left_up.y = teisuu_window_size.y - 1 ;
				if( right_down.x < 0 ) 
					right_down.x = 0;
				if( right_down.x > teisuu_window_size.x ) 
					right_down.x = teisuu_window_size.x - 1 ;
				if( right_down.y < 0 ) 
					right_down.y = 0;
				if( right_down.y > teisuu_window_size.y ) 
					right_down.y = teisuu_window_size.y - 1 ;
				CvRect rect = cvRect( left_up.x , left_up.y , right_down.x - left_up.x , right_down.y - left_up.y ) ;
				cvSetImageROI( proj_disp_image.spImage.get() , rect ) ; 
				cvSmooth
					( this->proj_disp_image.spImage.get() 
					, this->proj_disp_image.spImage.get()
					, teisuu_bokashi_method , teisuu_bokashi_size
					);
				cvResetImageROI( proj_disp_image.spImage.get() ) ;
					
			}
		};

		void UpdateCalibInfo()
		{
			this->calib_data.UpdateInfo(this->proj_disp_image);
		}

		//void DisplayToWindow()
		//{
		//	this->proj_disp_image.DisplayToWindow();
		//}

		void DisplayToWindow()
		{
			cvShowImage( "Projecter Image" , proj_disp_image.spImage.get() ) ;
		}

		bool EndCondition()
		{
			const bool _continue = false;
			const bool _end		 = true; 

			if( key == 27 ) return _end;

			return _continue;
		}

		// フィールドの状態
		FieldState& field_state;
		// キャリブレーションのデータ
		CalibrationData& calib_data;
		// 表示画像
		DispImage proj_disp_image;

	};
}