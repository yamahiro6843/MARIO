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
		WaitForSingleObject(hMutex,INFINITE); //mutex 間は他のスレッドから変数を変更できない
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