#pragma once
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>

/**
* @brief	���ԊǗ��B�}�C�N���b�ɑΉ��B
*/
class Time
{
	Time(){
		Init();
	}

	LARGE_INTEGER frequency;
	LARGE_INTEGER current_time;
	LARGE_INTEGER last_time;

	LONGLONG delta_time;

public:
	Time(const Time&) = delete;
	Time& operator=(const Time&) = delete;
	Time(Time&&) = delete;
	Time& operator=(Time&&) = delete;

	static Time* GetInstance() {
		static Time instance;
		return &instance;
	}

	void Init();
	void Update();

	/// <summary>
	/// �o�ߎ��ԁB�}�C�N���b��Ԃ��B
	/// </summary>
	double DeltaTime();	
};

