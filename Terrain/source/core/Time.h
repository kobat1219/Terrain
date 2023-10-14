#pragma once
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>

/**
* @brief	時間管理。マイクロ秒に対応。
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
	/// 経過時間。マイクロ秒を返す。
	/// </summary>
	double DeltaTime();	
};

