#pragma once

#include <Windows.h>

class myMutex
{
private:
	myMutex();

private:
	HANDLE _hMutex;

public:
	myMutex(HANDLE hMutex)
	{
		_hMutex = hMutex;
		WaitForSingleObject(hMutex,INFINITE); //mutex �Ԃ͑��̃X���b�h����ϐ���ύX�ł��Ȃ�
	}

	~myMutex()
	{
		ReleaseMutex(_hMutex);
	}

	void Release()
	{
		ReleaseMutex(_hMutex);
	}
};