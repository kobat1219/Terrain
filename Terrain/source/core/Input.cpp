/**
* @file input.cpp
* @brief 入力についての処理が記述されている
*/
#include "Input.h"
#include <math.h>
#include "Application.h"

BYTE Input::mKeyState[256];
BYTE Input::mOldKeyState[256];
XINPUT_STATE Input::mXPadState[GAMEPAD_MAX_AMOUNT];
XINPUT_STATE Input::mOldXPadState[GAMEPAD_MAX_AMOUNT];

#define PI 3.1415926f

void Input::Update()
{
	// 前のフレームのキー状態を保存
	memcpy_s(mOldKeyState, sizeof(mOldKeyState), mKeyState, sizeof(mKeyState));

	GetKeyboardState(mKeyState);

	for (int i = 0; i < GAMEPAD_MAX_AMOUNT; i++)
	{
		mOldXPadState[i] = mXPadState[i];

		XInputGetState(i, &mXPadState[i]);
	}
}

bool Input::GetKeyPress(int vkey)
{
	return mKeyState[vkey] & 0x80;
}

bool Input::GetKeyTrigger(int vkey)
{
	return (mKeyState[vkey] & 0x80) && !(mOldKeyState[vkey] & 0x80);
}

bool Input::GetKeyRelease(int vkey)
{
	return !(mKeyState[vkey] & 0x80) && (mOldKeyState[vkey] & 0x80);
}

bool Input::GetPadButtonPress(int _padNum,WORD _id)
{
	return mXPadState[_padNum].Gamepad.wButtons & _id;
}

bool Input::GetPadButtonTrigger(int _padNum,WORD _id)
{
	return (mXPadState[_padNum].Gamepad.wButtons & _id) & (~(mOldXPadState[_padNum].Gamepad.wButtons & _id));
}

BYTE Input::GetPadTriggerLeft(int _padNum)
{
	return mXPadState[_padNum].Gamepad.bLeftTrigger;
}

bool Input::GetPadTriggerLeftPress(int _padNum,int _range)
{
	return (mXPadState[_padNum].Gamepad.bLeftTrigger > _range);
}

bool Input::GetPadTriggerLeftTrigger(int _padNum, int _range)
{
	return (mXPadState[_padNum].Gamepad.bLeftTrigger > _range)&&!(mOldXPadState[_padNum].Gamepad.bLeftTrigger > _range);
}


BYTE Input::GetPadTriggerRight(int _padNum)
{
	return mXPadState[_padNum].Gamepad.bRightTrigger;
}

bool Input::GetPadTriggerRightPress(int _padNum, int _range)
{
	return (mXPadState[_padNum].Gamepad.bRightTrigger > _range);
}

bool Input::GetPadTriggerRightTrigger(int _padNum, int _range)
{
	return (mXPadState[_padNum].Gamepad.bRightTrigger > _range)&&!(mOldXPadState[_padNum].Gamepad.bRightTrigger > _range);
}

SHORT Input::GetPadAnalogStickLeftX(int _padNum)
{
	return mXPadState[_padNum].Gamepad.sThumbLX;
}

SHORT Input::GetPadAnalogStickLeftY(int _padNum)
{
	return mXPadState[_padNum].Gamepad.sThumbLY;
}

bool Input::GetPadAnalogStickLeftPressX(int _padNum, bool _right)
{
	if (_right)
	{
		return (mXPadState[_padNum].Gamepad.sThumbLX>10000);
	}
	else
	{
		return (mXPadState[_padNum].Gamepad.sThumbLX < -10000);
	}
	return false;
}

bool Input::GetPadAnalogStickLeftPressY(int _padNum, bool _up)
{
	if (_up)
	{
		return (mXPadState[_padNum].Gamepad.sThumbLY > 10000);
	}
	else
	{
		return (mXPadState[_padNum].Gamepad.sThumbLY < -10000);
	}
	return false;
}

bool Input::GetPadAnalogStickLeftPressX(int _padNum, bool _right, int _range)
{
	if (_right)
	{
		return (mXPadState[_padNum].Gamepad.sThumbLX > _range);
	}
	else
	{
		return (mXPadState[_padNum].Gamepad.sThumbLX < -_range);
	}
	return false;
}

bool Input::GetPadAnalogStickLeftPressY(int _padNum, bool _up, int _range)
{
	if (_up)
	{
		return (mXPadState[_padNum].Gamepad.sThumbLY > _range);
	}
	else
	{
		return (mXPadState[_padNum].Gamepad.sThumbLY < -_range);
	}
	return false;
}

bool Input::GetPadAnalogStickLeftTriggerX(int _padNum, bool _right)
{
	if(_right)
	{
		return ((mXPadState[_padNum].Gamepad.sThumbLX > 10000)&& !(mOldXPadState[_padNum].Gamepad.sThumbLX > 10000));
	}
	else
	{
		return ((mXPadState[_padNum].Gamepad.sThumbLX < -10000)&&!((mOldXPadState[_padNum].Gamepad.sThumbLX < -10000)));
	}
	return false;
}

bool Input::GetPadAnalogStickLeftTriggerY(int _padNum, bool _up)
{
	if (_up)
	{
		return ((mXPadState[_padNum].Gamepad.sThumbLY > 10000) && !(mOldXPadState[_padNum].Gamepad.sThumbLY > 10000));
	}
	else
	{
		return ((mXPadState[_padNum].Gamepad.sThumbLY < -10000) && !((mOldXPadState[_padNum].Gamepad.sThumbLY < -10000)));
	}
	return false;
}

bool Input::GetPadAnalogStickLeftTriggerX(int _padNum, bool _right, int _range)
{
	if (_right)
	{
		return ((mXPadState[_padNum].Gamepad.sThumbLX > _range) && !(mOldXPadState[_padNum].Gamepad.sThumbLX > _range));
	}
	else
	{
		return ((mXPadState[_padNum].Gamepad.sThumbLX < -_range) && !((mOldXPadState[_padNum].Gamepad.sThumbLX < -_range)));
	}
	return false;
}

bool Input::GetPadAnalogStickLeftTriggerY(int _padNum, bool _up, int _range)
{
	if (_up)
	{
		return ((mXPadState[_padNum].Gamepad.sThumbLY > _range) && !(mOldXPadState[_padNum].Gamepad.sThumbLY > _range));
	}
	else
	{
		return ((mXPadState[_padNum].Gamepad.sThumbLY < -_range) && !((mOldXPadState[_padNum].Gamepad.sThumbLY < -_range)));
	}
	return false;
}

float Input::GetPadAnalogStickLeftAngle(int _padNum)
{
	float angle = 0;
	angle =
		(float)(atan2(
			mXPadState[_padNum].Gamepad.sThumbLY,
			mXPadState[_padNum].Gamepad.sThumbLX)
		* 180.0 / PI
		+ 180);
	return angle;
}

SHORT Input::GetPadAnalogStickRightX(int _padNum)
{
	return mXPadState[_padNum].Gamepad.sThumbRX;
}

SHORT Input::GetPadAnalogStickRightY(int _padNum)
{
	return mXPadState[_padNum].Gamepad.sThumbRY;
}

bool Input::GetPadAnalogStickRightPressX(int _padNum, bool _right)
{
	if (_right)
	{
		return (mXPadState[_padNum].Gamepad.sThumbRX > 10000);
	}
	else
	{
		return (mXPadState[_padNum].Gamepad.sThumbRX < -10000);
	}
	return false;
}

bool Input::GetPadAnalogStickRightPressY(int _padNum, bool _up)
{
	if (_up)
	{
		return (mXPadState[_padNum].Gamepad.sThumbRY > 10000);
	}
	else
	{
		return (mXPadState[_padNum].Gamepad.sThumbRY < -10000);
	}
	return false;
}

bool Input::GetPadAnalogStickRightPressX(int _padNum, bool _right, int _range)
{
	if (_right)
	{
		return (mXPadState[_padNum].Gamepad.sThumbRX > _range);
	}
	else
	{
		return (mXPadState[_padNum].Gamepad.sThumbRX < -_range);
	}
	return false;
}

bool Input::GetPadAnalogStickRightPressY(int _padNum, bool _up, int _range)
{
	if (_up)
	{
		return (mXPadState[_padNum].Gamepad.sThumbRY > _range);
	}
	else
	{
		return (mXPadState[_padNum].Gamepad.sThumbRY < -_range);
	}
	return false;
}

bool Input::GetPadAnalogStickRightTriggerX(int _padNum, bool _right)
{
	if (_right)
	{
		return ((mXPadState[_padNum].Gamepad.sThumbRX > 10000) && !(mOldXPadState[_padNum].Gamepad.sThumbRX > 10000));
	}
	else
	{
		return ((mXPadState[_padNum].Gamepad.sThumbRX < -10000) && !((mOldXPadState[_padNum].Gamepad.sThumbRX < -10000)));
	}
	return false;
}

bool Input::GetPadAnalogStickRightTriggerY(int _padNum, bool _up)
{
	if (_up)
	{
		return ((mXPadState[_padNum].Gamepad.sThumbRY > 10000) && !(mOldXPadState[_padNum].Gamepad.sThumbRY > 10000));
	}
	else
	{
		return ((mXPadState[_padNum].Gamepad.sThumbRY < -10000) && !((mOldXPadState[_padNum].Gamepad.sThumbRY < -10000)));
	}
	return false;
}

bool Input::GetPadAnalogStickRightTriggerX(int _padNum, bool _right, int _range)
{
	if (_right)
	{
		return ((mXPadState[_padNum].Gamepad.sThumbRX > _range) && !(mOldXPadState[_padNum].Gamepad.sThumbRX > _range));
	}
	else
	{
		return ((mXPadState[_padNum].Gamepad.sThumbRX < -_range) && !((mOldXPadState[_padNum].Gamepad.sThumbRX < -_range)));
	}
	return false;
}

bool Input::GetPadAnalogStickRightTriggerY(int _padNum, bool _up, int _range)
{
	if (_up)
	{
		return ((mXPadState[_padNum].Gamepad.sThumbRY > _range) && !(mOldXPadState[_padNum].Gamepad.sThumbRY > _range));
	}
	else
	{
		return ((mXPadState[_padNum].Gamepad.sThumbRY < -_range) && !((mOldXPadState[_padNum].Gamepad.sThumbRY < -_range)));
	}
	return false;
}

float Input::GetPadAnalogStickRightAngle(int _padNum)
{
	float angle = 0;
	angle =
		(float)(atan2(
			mXPadState[_padNum].Gamepad.sThumbRY,
			mXPadState[_padNum].Gamepad.sThumbRX)
		* 180.0 / PI
		+ 180);
	return angle;
}

bool Input::GetMousePressLeft()
{
	return mKeyState[VK_LBUTTON] & 0x80;
}

bool Input::GetMousePressRight()
{
	return mKeyState[VK_RBUTTON] & 0x80;
}

bool Input::GetMousePressMiddle()
{
	return mKeyState[VK_MBUTTON] & 0x80;
}

bool Input::GetMousePressSideUp()
{
	return mKeyState[VK_XBUTTON1] & 0x80;
}

bool Input::GetMousePressSideDown()
{
	return mKeyState[VK_XBUTTON2] & 0x80;
}

bool Input::GetMouseTriggerLeft()
{
	return (mKeyState[VK_LBUTTON] & 0x80) && !(mOldKeyState[VK_LBUTTON] & 0x80);
}

bool Input::GetMouseTriggerRight()
{
	return (mKeyState[VK_RBUTTON] & 0x80) && !(mOldKeyState[VK_RBUTTON] & 0x80);
}

bool Input::GetMouseTriggerMiddle()
{
	return (mKeyState[VK_MBUTTON] & 0x80) && !(mOldKeyState[VK_MBUTTON] & 0x80);
}

bool Input::GetMouseTriggerSideUp()
{
	return (mKeyState[VK_XBUTTON1] & 0x80) && !(mOldKeyState[VK_XBUTTON2] & 0x80);
}

bool Input::GetMouseTriggerSideDown()
{
	return (mKeyState[VK_XBUTTON1] & 0x80) && !(mOldKeyState[VK_XBUTTON2] & 0x80);
}

POINT Input::GetCurPos()
{	
	POINT pout = { 0,0 };
	if (GetCursorPos(&pout))
	{
		return pout;
	}
	return pout;
}

POINT Input::GetCursorPosOnScreen()
{
	POINT curpoint = GetCurPos();
	ScreenToClient(Application::Instance()->GetHWnd(), &curpoint);
	return curpoint;
}

bool Input::GetCursorPosOnScreen(POINT& _point)
{
	_point = GetCursorPosOnScreen();

	if (_point.x<0||_point.x>Application::CLIENT_WIDTH||_point.y<0||_point.y>Application::CLIENT_HEIGHT)
	{
		return false;
	}
	return true;
}
