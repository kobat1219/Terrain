#pragma once
#include <iostream>
#include <string>

#include "Application.h"

/**
* @class �f�o�b�N�N���X
* @brief ���̃N���X�́A�R���\�[���E�B���h�E�Ƀf�[�^��\������N���X
* @details �h���֎~�A���̖����Astatic�Ȋ֐��Q
*/
class Debug final
{
public:

	// ���͖̂���
	Debug() = delete;
	~Debug() = delete;
	Debug(Debug&&) = delete;
	Debug(const Debug&) = delete;
	Debug& operator=(const Debug&) = delete;
	Debug& operator=(Debug&&) = delete;

	template <typename T>
	static inline void Log(const T& _data) 
	{
		using namespace std;
		WORD colset = 0;
		colset |= FOREGROUND_INTENSITY;
		colset |= FOREGROUND_BLUE;
		colset |= FOREGROUND_GREEN;
		colset |= FOREGROUND_RED;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colset);
		cout << "Log:" << _data << endl;
	}

	template <typename T>
	static void Error(const T& _data)
	{
		using namespace std;
		WORD colset = 0;
		colset |= FOREGROUND_INTENSITY;
		colset |= FOREGROUND_RED;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colset);
		cout <<"Error!:" << _data << endl;
	}

	template <typename T>
	static void Warning(const T& _data)
	{
		using namespace std;
		WORD colset = 0;
		colset |= FOREGROUND_INTENSITY;
		colset |= FOREGROUND_GREEN;
		colset |= FOREGROUND_RED;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colset);
		cout << "Warning!:" << _data << endl;
	}

};

