

#include "Projecter.h"
#include "Thread.h"
#include "Window.h"
#include <string>

DWORD WINAPI ProjFuncThread(LPVOID args);
LRESULT CALLBACK ProjWndProc(HWND, UINT, WPARAM, LPARAM);

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine, int nCmdShow )
{
	DWORD dwThId;
	Thread proj_thrd(ProjFuncThread, &dwThId);
	Window win( _T("Proj_Window_Class") , _T("Projecter Widnow") , ProjWndProc , hInstance );

	// ���b�Z�[�W���[�v
	MSG msg;

	while( 1 )
	{
		BOOL ret = GetMessage( &msg, NULL, 0, 0 );  // ���b�Z�[�W���擾����
		if( ret == 0 || ret == -1 )
		{
			// �A�v���P�[�V�������I�������郁�b�Z�[�W�����Ă�����A
			// ���邢�� GetMessage() �����s������( -1 ���Ԃ��ꂽ�� �j�A���[�v�𔲂���
			break;
		}
		else
		{
			// ���b�Z�[�W����������
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
	}
	return EXIT_SUCCESS ;
}

// �X���b�h�֐�
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
	case WM_DESTROY:  // �E�B���h�E��j������Ƃ�
		{
			PostQuitMessage( 0 );
			return 0;
		}
	}

	// ���̃��b�Z�[�W�́A�f�t�H���g�̏������s��
	return DefWindowProc( hWnd, msg, wp, lp );
}


