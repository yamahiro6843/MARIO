#pragma once

#include <Windows.h>


class ERROR_INIT
{
public:
	ERROR_INIT(){};
};

class Window
{
private:
	Window();

private:
	WNDCLASSEX wc;

public:
	HWND hWnd;

	Window( LPCSTR class_name , LPCSTR window_name , LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM) ,  HINSTANCE hInst )
	{
		if( init( class_name , window_name , WndProc , hInst ) == 1 )
			throw ERROR_INIT();
	}

	int init( LPCSTR class_name , LPCSTR window_name , LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM) ,  HINSTANCE hInst )
	{
		// �E�B���h�E�N���X�̏���ݒ�
		wc.cbSize = sizeof(wc);               // �\���̃T�C�Y
		wc.style = CS_HREDRAW | CS_VREDRAW;   // �X�^�C��
		wc.lpfnWndProc = WndProc;             // �E�B���h�E�v���V�[�W��
		wc.cbClsExtra = 0;                    // �g�����P
		wc.cbWndExtra = 0;                    // �g�����Q
		wc.hInstance = hInst;                 // �C���X�^���X�n���h��
		wc.hIcon = (HICON)LoadImage(          // �A�C�R��
			NULL, MAKEINTRESOURCE(IDI_APPLICATION), IMAGE_ICON,
			0, 0, LR_DEFAULTSIZE | LR_SHARED
			);
		wc.hIconSm = wc.hIcon;                // �q�A�C�R��
		wc.hCursor = (HCURSOR)LoadImage(      // �}�E�X�J�[�\��
			NULL, MAKEINTRESOURCE(IDC_ARROW), IMAGE_CURSOR,
			0, 0, LR_DEFAULTSIZE | LR_SHARED
			);
		wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // �E�B���h�E�w�i
		wc.lpszMenuName = NULL;                     // ���j���[��
		wc.lpszClassName = class_name;// �E�B���h�E�N���X��

		// �E�B���h�E�N���X��o�^����
		if( RegisterClassEx( &wc ) == 0 ){ return 1; }

		// �E�B���h�E���쐬����
		hWnd = CreateWindow(
			wc.lpszClassName,      // �E�B���h�E�N���X��
			window_name,  // �^�C�g���o�[�ɕ\�����镶����
			WS_OVERLAPPEDWINDOW,   // �E�B���h�E�̎��
			CW_USEDEFAULT,         // �E�B���h�E��\������ʒu�iX���W�j
			CW_USEDEFAULT,         // �E�B���h�E��\������ʒu�iY���W�j
			CW_USEDEFAULT,         // �E�B���h�E�̕�
			CW_USEDEFAULT,         // �E�B���h�E�̍���
			NULL,                  // �e�E�B���h�E�̃E�B���h�E�n���h��
			NULL,                  // ���j���[�n���h��
			hInst,                 // �C���X�^���X�n���h��
			NULL                   // ���̑��̍쐬�f�[�^
			);
		if( hWnd == NULL ){ return 1; }

		// �E�B���h�E��\������
		ShowWindow( hWnd, SW_SHOW );
		UpdateWindow( hWnd );

		return 0;
	}

};