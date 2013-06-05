

#include "Projecter.h"
#include "Thread.h"
#include "Window.h"
#include <string>

DWORD WINAPI ProjFuncThread(LPVOID args);
LRESULT CALLBACK ProjWndProc(HWND, UINT, WPARAM, LPARAM);

// プログラムは WinMain から始まります
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine, int nCmdShow )
{
	DWORD dwThId;
	Thread proj_thrd(ProjFuncThread, &dwThId);
	Window win( _T("Proj_Window_Class") , _T("Projecter Widnow") , ProjWndProc , hInstance );

	// メッセージループ
	MSG msg;

	while( 1 )
	{
		BOOL ret = GetMessage( &msg, NULL, 0, 0 );  // メッセージを取得する
		if( ret == 0 || ret == -1 )
		{
			// アプリケーションを終了させるメッセージが来ていたら、
			// あるいは GetMessage() が失敗したら( -1 が返されたら ）、ループを抜ける
			break;
		}
		else
		{
			// メッセージを処理する
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
	}
	return EXIT_SUCCESS ;
}

// スレッド関数
DWORD WINAPI ProjFuncThread(LPVOID args)
{
	::Projecter::SysProj::Instance().mainFlow();
	return 0;
}


LRESULT CALLBACK ProjWndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch( msg )
	{
	case WM_COPYDATA:
		{
			PCOPYDATASTRUCT pData = (PCOPYDATASTRUCT) lp;

			if( pData->cbData == 12 )
			{
				int* pInt = (int*) pData->lpData;
				Projecter::FieldState::FieldData fd;
				fd.p.x = pInt[0];
				fd.p.y = pInt[1];
				fd.p.z = pInt[2];
				Projecter::FieldState::SysFieldState::Instance().UpdateState(fd);
			}
			return 0;
		}
	case WM_DESTROY:  // ウィンドウを破棄するとき
		{
			PostQuitMessage( 0 );
			return 0;
		}
	}

	// 他のメッセージは、デフォルトの処理を行う
	return DefWindowProc( hWnd, msg, wp, lp );
}


