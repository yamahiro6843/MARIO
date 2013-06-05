
#pragma once

#include <opencv2\opencv.hpp>
#include <vector>
#include "Point.h"
#include "Vector.h"
#include "ProjecterUtils.h"
#include "ProjecterCarib.h"
#include "ProjecterFieldState.h"

namespace Projecter 
{
	class BlockImageLayer
	{
	public:
		int num;
		CalibrationData calib_data;
		FieldState* p_field_state;
		Image block_image;
		Image transed_img;

		BlockImageLayer( int _num , FieldState* _p_field_state )
			: num( _num )
			, p_field_state( _p_field_state )
			, calib_data( _num )
		{
			int i = 0;
		};
		~BlockImageLayer()
		{
		};

		// レイヤーのゲーム座標内の高さ
		int height() const
		{
			return teisuu_block_size * this->num ;
		}

		void ClearImage()
		{
			this->block_image.ClearImage();
		}
		void DrawShadow( ::Projecter::FieldState::Character::Shadow shadow )
		{
			this->block_image += shadow( this->height() ) ;
			//if( this->num == 0 )
			//	cvShowImage( "raw shadow on layer 0" , this->block_image.image );
			//if( this->num == 1 )
			//	cvShowImage( "raw shadow on layer 1" , this->block_image.image );
			//if( this->num == 2 )
			//	cvShowImage( "raw shadow on layer 2" , this->block_image.image );
			//if( this->num == 3 )
			//	cvShowImage( "raw shadow on layer 3" , this->block_image.image );

			//if( this->num == 0 )
			//	cvShowImage( "mask0" , this->p_field_state->BlockSurfaceOfLayer( this->num ).image );
			//if( this->num == 1 )
			//	cvShowImage( "mask1" , this->p_field_state->BlockSurfaceOfLayer( this->num ).image );
			//if( this->num == 2 )
			//	cvShowImage( "mask2" , this->p_field_state->BlockSurfaceOfLayer( this->num ).image );
			//if( this->num == 3 )
			//	cvShowImage( "mask3" , this->p_field_state->BlockSurfaceOfLayer( this->num ).image );

			this->block_image *= this->p_field_state->BlockSurfaceOfLayer( this->num );
			//if( this->num == 0 )
			//	cvShowImage( "masked shadow on layer 0" , this->block_image.image );
			//if( this->num == 1 )
			//	cvShowImage( "masked shadow on layer 1" , this->block_image.image );
			//if( this->num == 2 )
			//	cvShowImage( "masked shadow on layer 2" , this->block_image.image );
			//if( this->num == 3 )
			//	cvShowImage( "masked shadow on layer 3" , this->block_image.image );
		}

		const Image& transformed_image() const
		{
			CvMat *map_matrix;
			CvPoint2D32f src_pnt[4], dst_pnt[4];

			// 四角形の変換前と変換後の対応する頂点をそれぞれセットし
			// cvWarpPerspectiveを用いて透視投影変換行列を求める
			int yoko = teisuu_block_size * teisuu_yoko;
			int oku  = teisuu_block_size * teisuu_oku ;
			src_pnt[0] = cvPoint2D32f ( 0	, 0   ); // left_up
			src_pnt[1] = cvPoint2D32f ( yoko, 0   ); // right_up
			src_pnt[2] = cvPoint2D32f (	yoko, oku ); // right_down
			src_pnt[3] = cvPoint2D32f ( 0	, oku ); // left_down

			dst_pnt[0] = this->calib_data.CornerAt(0);
			dst_pnt[1] = this->calib_data.CornerAt(1);
			dst_pnt[2] = this->calib_data.CornerAt(2);
			dst_pnt[3] = this->calib_data.CornerAt(3);

			map_matrix = cvCreateMat (3, 3, CV_32FC1);
			cvGetPerspectiveTransform (src_pnt, dst_pnt, map_matrix);

			// 指定された透視投影変換行列により，cvWarpPerspectiveを用いて画像を変換させる
			cvWarpPerspective( this->block_image.image , this->transed_img.image , map_matrix, CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS , cvScalarAll (0));

			return this->transed_img;
		}

		BlockImageLayer(){};
	private:
		// 禁則事項
	};

	class BlockImageLayers : public std::vector<BlockImageLayer>
	{
	public:
		BlockImageLayers( int layer_num , FieldState* p_field_state )
		{
			this->resize( layer_num );
			for( int i = 0 ; i < layer_num ; i++)
			{
				(*this)[i] =  BlockImageLayer( i , p_field_state ) ;
			}
		}

		void GetCalibrationInfo()
		{
			//// Wキー：ウィンドウモード切り替え
			//if( Keyboard::getIsKeyInputStart(KEY_INPUT_W) ){
			//	static bool windowFlag = TRUE;
			//	windowFlag = !windowFlag;
			//	DxLib::ChangeWindowMode(windowFlag);
			//}
			//// Sキー：コンフィグデータセーブ
			//ef( Keyboard::getIsKeyInputStart(KEY_INPUT_S) ){
			//	IO::saveConfigData();
			//}
			//// Cキー：キャリブレーションモード変更
			//ef( Keyboard::getIsKeyInputStart(KEY_INPUT_C) ){
			//	this->calibFlag = !this->calibFlag;
			//}
			//// Bキー：ブロック表示切り替え
			//ef( Keyboard::getIsKeyInputStart(KEY_INPUT_B) ){
			//	this->blockDispFlag = !this->blockDispFlag;
			//}
			//// 1キー：Mover 1をジェネレート
			//ef( Keyboard::getIsKeyInputStart(KEY_INPUT_1) ){
			//	this->generateMover(1);
			//}
			//// 2キー：Mover 2をジェネレート
			//ef( Keyboard::getIsKeyInputStart(KEY_INPUT_2) ){
			//	this->generateMover(2);
			//}
			//// 3キー：Mover 3をジェネレート
			//ef( Keyboard::getIsKeyInputStart(KEY_INPUT_3) ){
			//	this->generateMover(3);
			//}



			///* キャリブレーションの時のみ行うこと */
			//if( this->calibFlag ){
			//	double shiftTime = (Keyboard::getKeyInputFrame(KEY_INPUT_LSHIFT)!=0) ? 0.1 : 1.0;
			//	if( Keyboard::getKeyInputFrame(KEY_INPUT_LBRACKET) ){
			//		IO::configData.zoom += (0.1*shiftTime);
			//	}
			//	ef( Keyboard::getKeyInputFrame(KEY_INPUT_RBRACKET) ){
			//		IO::configData.zoom -= (0.1*shiftTime);
			//	}

			//	if( Keyboard::getKeyInputFrame(KEY_INPUT_UP) ){
			//		IO::configData.fieldStartPoint.y += (int)(10*shiftTime);
			//	}
			//	ef( Keyboard::getKeyInputFrame(KEY_INPUT_DOWN) ){
			//		IO::configData.fieldStartPoint.y -= (int)(10*shiftTime);
			//	}
			//	if( Keyboard::getKeyInputFrame(KEY_INPUT_LEFT) ){
			//		IO::configData.fieldStartPoint.x += (int)(10*shiftTime);
			//	}
			//	ef( Keyboard::getKeyInputFrame(KEY_INPUT_RIGHT) ){
			//		IO::configData.fieldStartPoint.x -= (int)(10*shiftTime);
			//	}
			//}
			//mada_zissou_sitenai();
		};

		void ClearImage()
		{
			foreach( it , *this )
			{
				it->ClearImage();
			}
		}

		void DrawShadow( ::Projecter::FieldState::Character::Shadow shadow )
		{
			foreach( it , *this )
			{
				it->DrawShadow( shadow );
			}
		}

	private:
		BlockImageLayers();
		void push_back( const BlockImageLayer& layer ) // 外部からのpush_back禁止
		{
			vector::push_back(layer);
		}
	};
}