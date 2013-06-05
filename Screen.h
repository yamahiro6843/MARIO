#pragma once
#include "UseDxMacro.h"
#include "UseDxLibMessage.h"
#include <string>
#include <DxLib.h>
#include "Point.h"

typedef Point<2,int> ScreenPoint;

class Screen
{
private:
	ScreenPoint _screen_size;
	int _fps;

public:
	typedef UseDxLibMessage::EXCEPTION_BAD_INIT ERROR_INIT;
	enum SCREEN{ BACK = DX_SCREEN_BACK , FRONT = DX_SCREEN_FRONT };
	enum BLEND_MODE
	{ 
		NOBLEND	= DX_BLENDMODE_NOBLEND	, 	//ノーブレンド（デフォルト）
		ALPHA	= DX_BLENDMODE_ALPHA	,	//αブレンド
		ADD		= DX_BLENDMODE_ADD		,	//加算ブレンド
		SUB		= DX_BLENDMODE_SUB		,	//減算ブレンド
		MULA	= DX_BLENDMODE_MULA		,	//乗算ブレンド
		INVSRC	= DX_BLENDMODE_INVSRC		//反転ブレンド
	};
	enum DRAW_MODE
	{
		NEAREST	 = DX_DRAWMODE_NEAREST	,	 // ネアレストネイバー法で描画する
		BILINEAR = DX_DRAWMODE_BILINEAR		// バイリニア法で描画する
	};

	Screen
		( ScreenPoint screen_size = ScreenPoint( DEFAULT_SCREEN_SIZE_X , DEFAULT_SCREEN_SIZE_Y ) 
		, int FPS = 60
		)
		: _screen_size( screen_size )
		, _fps( FPS )
	{
		SetGraphMode( _screen_size );
	};

	virtual ~Screen()
	{};

	void init()
	{
		SetDrawScreen( SCREEN::BACK );
		SetDrawMode( DRAW_MODE::BILINEAR );
		SetDrawBright( 255 , 255 , 255 );
		SetDrawBlendMode( BLEND_MODE::NOBLEND , 255 );
		SetDrawArea( ScreenPoint(0,0) , _screen_size );
	}

	void SetDrawScreen( Screen::SCREEN screen )
	{
		UseDxLibErrorCheck<ERROR_INIT>( ::SetDrawScreen( screen ) ) ;
	}

	void SetDrawMode( Screen::DRAW_MODE mode )
	{
		UseDxLibErrorCheck<ERROR_INIT>( ::SetDrawMode( mode ) ) ;
	}

	void SetDrawBright( int red , int green , int blue )
	{
		UseDxLibErrorCheck<ERROR_INIT>( ::SetDrawBright( red , green , blue ) ) ;
	}

	void SetDrawBlendMode( BLEND_MODE mode , int param )
	{
		UseDxLibErrorCheck<ERROR_INIT>( ::SetDrawBlendMode( mode , param ) ) ;
	}

	void SetDrawArea( ScreenPoint p1 , ScreenPoint p2 )
	{
		UseDxLibErrorCheck<ERROR_INIT>( ::SetDrawArea( p1.x , p1.y , p2.x , p2.y ) ) ;
	}

	void SetGraphMode( ScreenPoint size , int ColorBitNum = 16 )
	{
		_screen_size = size;
		UseDxLibErrorCheck<ERROR_INIT>( ::SetGraphMode( size.x , size.y , ColorBitNum ) ) ;
	}

	void ClearDrawScreen()
	{
		clsDx();
		UseDxLibErrorCheck<ERROR_INIT>( ::ClearDrawScreen() );
	}

	void SetFps(int fps)
	{
		_fps = fps;
	}

	void waitFps()
	{
		if( _fps != 60 )
		{
			static int pre_count = GetNowCount();
			int now_count = GetNowCount();
			int time_of_process = now_count - pre_count;
			float time_of_frame = 1000.0f / _fps; 
			if( time_of_process < time_of_frame )
			{
				Sleep( time_of_frame - time_of_process );
			}

			pre_count = now_count;
		}

		return;
	}

	void ScreenFlip()
	{
		waitFps();
		UseDxLibErrorCheck<ERROR_INIT>( ::ScreenFlip() );
	}

	void SaveToPNG
		( std::string filename
		, ScreenPoint p1 = ScreenPoint(0,0) 
		, ScreenPoint p2 = ScreenPoint(0,0) 
		)
	{
		if( p2 == ScreenPoint(0,0) )
			p2 = _screen_size;
		filename += ".png";
		SaveDrawScreenToPNG( p1.x , p1.y , p2.x , p2.y , filename.c_str() , 0 );
	}

	void SaveToJPEG
		( std::string filename
		, ScreenPoint p1 = ScreenPoint(0,0) 
		, ScreenPoint p2 = ScreenPoint(0,0) 
		)
	{
		if( p2 == ScreenPoint(0,0) )
			p2 = _screen_size;
		filename += ".jpg";
		SaveDrawScreenToPNG( p1.x , p1.y , p2.x , p2.y , filename.c_str() , 0 );
	}

	ScreenPoint ScreenSize()
	{
		return _screen_size;
	}
};


