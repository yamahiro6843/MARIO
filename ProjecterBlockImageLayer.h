
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

		// ���C���[�̃Q�[�����W���̍���
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

			// �l�p�`�̕ϊ��O�ƕϊ���̑Ή����钸�_�����ꂼ��Z�b�g��
			// cvWarpPerspective��p���ē������e�ϊ��s������߂�
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

			// �w�肳�ꂽ�������e�ϊ��s��ɂ��CcvWarpPerspective��p���ĉ摜��ϊ�������
			cvWarpPerspective( this->block_image.image , this->transed_img.image , map_matrix, CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS , cvScalarAll (0));

			return this->transed_img;
		}

		BlockImageLayer(){};
	private:
		// �֑�����
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
			//// W�L�[�F�E�B���h�E���[�h�؂�ւ�
			//if( Keyboard::getIsKeyInputStart(KEY_INPUT_W) ){
			//	static bool windowFlag = TRUE;
			//	windowFlag = !windowFlag;
			//	DxLib::ChangeWindowMode(windowFlag);
			//}
			//// S�L�[�F�R���t�B�O�f�[�^�Z�[�u
			//ef( Keyboard::getIsKeyInputStart(KEY_INPUT_S) ){
			//	IO::saveConfigData();
			//}
			//// C�L�[�F�L�����u���[�V�������[�h�ύX
			//ef( Keyboard::getIsKeyInputStart(KEY_INPUT_C) ){
			//	this->calibFlag = !this->calibFlag;
			//}
			//// B�L�[�F�u���b�N�\���؂�ւ�
			//ef( Keyboard::getIsKeyInputStart(KEY_INPUT_B) ){
			//	this->blockDispFlag = !this->blockDispFlag;
			//}
			//// 1�L�[�FMover 1���W�F�l���[�g
			//ef( Keyboard::getIsKeyInputStart(KEY_INPUT_1) ){
			//	this->generateMover(1);
			//}
			//// 2�L�[�FMover 2���W�F�l���[�g
			//ef( Keyboard::getIsKeyInputStart(KEY_INPUT_2) ){
			//	this->generateMover(2);
			//}
			//// 3�L�[�FMover 3���W�F�l���[�g
			//ef( Keyboard::getIsKeyInputStart(KEY_INPUT_3) ){
			//	this->generateMover(3);
			//}



			///* �L�����u���[�V�����̎��̂ݍs������ */
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
		void push_back( const BlockImageLayer& layer ) // �O�������push_back�֎~
		{
			vector::push_back(layer);
		}
	};
}