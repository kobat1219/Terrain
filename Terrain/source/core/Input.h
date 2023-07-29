/**
* @file input.h
* @brief 入力について記述されている
*/
#pragma once

#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib,"xinput.lib")

//! コントローラの最大数
#define GAMEPAD_MAX_AMOUNT 4

/**------------------------------------------------------------
* @brief	入力クラス
* @details	Updateは毎フレーム呼び出せばいい。@n
*			すべてStaticで構成されているので使い方は
*			Input::～になる。@n
*			渡す引数は
*			英数字は'A'や'1'みたいな感じ@n
*			それ以外のF1や右矢印キー等はVK_F1やVK_RIGHT
--------------------------------------------------------------*/
class Input final
{
public:
	
	/**
	* @fn Update
	* @brief 入力の毎フレームの更新処理
	* @details 呼び出すのはメインループの一番初めにしている
	*/
	static void Update();
	
	#pragma region Keyboard

	/**
	* @fn GetKeyPress
	* @brief プレスのモードでキー情報を取得
	* @details 前フレームのキー状態に関係なく今のフレームに押されているかの判定を返す
	* @param[in] vkey キーコードを入力。'A'やVK_LEFT
	* @return 押されているかの情報
	*/
	static bool GetKeyPress(int);

	/**
	* @fn GetKeyPress
	* @brief トリガーのモードでキー情報を取得
	* @details 前フレームにキーが押されていない時今のフレームに押されているかの判定を返す
	* @param[in] vkey キーコードを入力。'A'やVK_LEFT
	* @return 押されているかの情報
	*/
	static bool GetKeyTrigger(int);

	/**
	* @fn GetKeyRelease
	* @brief リリースのモードでキー情報を取得
	* @details 指定キーの入力が離されたかの判定を返す
	* @param[in] vkey キーコードを入力。'A'やVK_LEFT
	* @return 押されているかの情報
	*/
	static bool GetKeyRelease(int);

	#pragma endregion

	#pragma region GamePad
	
	/**
	* @fn GetPadButtonPress
	* @brief プレスのモードでPad情報を取得
	* @details 前フレームのPad状態に関係なく今のフレームに押されているかの判定を返す
	* @param[in] _padNum Padの番号(0~3)
	* @param[in] _id Pad用のマクロ
	* @return 押されているかの情報
	*/
	static bool GetPadButtonPress(int,WORD);

	/**
	* @fn GetPadButtonTrigger
	* @brief トリガーのモードでPad情報を取得
	* @details 前フレームにPadが押されていない時今のフレームに押されているかの判定を返す
	* @param[in] _padNum Padの番号(0~3)
	* @param[in] _id Pad用のマクロ
	* @return 押されているかの情報
	*/
	static bool GetPadButtonTrigger(int, WORD);

	/**
	* @fn GetPadTriggerLeft
	* @brief 左トリガーの押込み取得
	* @details 0~255までのBYTE型が返ってくる。
	* @param[in] _padNum Padの番号(0~3)
	* @return 左トリガーの押込み
	*/
	static BYTE GetPadTriggerLeft(int);

	/**
	* @fn GetPadTriggerLeftPress
	* @brief 左トリガーの押込み取得
	* @details 今押されているかが返ってくる。
	* @param[in] _padNum Padの番号(0~3)
	* @param[in] _range 押し込み判定をする幅(0~255)
	* @return 押されているかの情報
	*/
	static bool GetPadTriggerLeftPress(int,int _range = 120);

	/**
	* @fn GetPadTriggerLeftTrigger
	* @brief トリガーのモードで左トリガーの押込み取得
	* @details 前フレームにPadが押されていない時今のフレームに押されているかの判定を返す
	* @param[in] _padNum Padの番号(0~3)
	* @param[in] _range 押し込み判定をする幅(0~255)
	* @return 左トリガーが押されているかの情報
	*/
	static bool GetPadTriggerLeftTrigger(int,int _range = 120);

	/**
	* @fn GetPadTriggerRight
	* @brief 右トリガーの押込み取得
	* @details 0~255までのBYTE型が返ってくる。
	* @param[in] _padNum Padの番号(0~3)
	* @return 右トリガーの押込み
	*/
	static BYTE GetPadTriggerRight(int);

	/**
	* @fn GetPadTriggerRightPress
	* @brief 右トリガーの押込み取得
	* @details 今押されているかが返ってくる。
	* @param[in] _padNum Padの番号(0~3)
	* @param[in] _range 押し込み判定をする幅(0~255)
	* @return 押されているかの情報
	*/
	static bool GetPadTriggerRightPress(int,int _range =120);

	/**
	* @fn GetPadTriggerRightTrigger
	* @brief トリガーのモードで右トリガーの押込み取得
	* @details 前フレームにPadが押されていない時今のフレームに押されているかの判定を返す
	* @param[in] _padNum Padの番号(0~3)
	* @param[in] _range 押し込み判定をする幅(0~255)
	* @return 右トリガーが押されているかの情報
	*/
	static bool GetPadTriggerRightTrigger(int,int _range = 120);

	/**
	* @fn GetPadAnalogStickLeftX
	* @brief 左アナログスティックのX座標取得
	* @details -32768~32767までのSHORT型が返ってくる。
	* @param[in] _padNum Padの番号(0~3)
	* @return 左スティックのX座標
	*/
	static SHORT GetPadAnalogStickLeftX(int);

	/**
	* @fn GetPadAnalogStickLeftY
	* @brief 左アナログスティックのY座標取得
	* @details -32768~32767までのSHORT型が返ってくる。
	* @param[in] _padNum Padの番号(0~3)
	* @return 左スティックのY座標
	*/
	static SHORT GetPadAnalogStickLeftY(int);
	
	/**
	* @fn GetPadAnalogStickLeftPressX
	* @brief 左アナログスティックのX軸の倒したかどうかの判定取得
	* @details bool型が返ってくる。第2引数で右か左かの指定をする
	* @param[in] _padNum Padの番号(0~3)
	* @param[in] _right 右左どちらに判定を取りたいか指定
	* @return 左スティックの倒したかのフラグ
	*/
	static bool GetPadAnalogStickLeftPressX(int,bool);

	/**
	* @fn GetPadAnalogStickLeftPressY
	* @brief 左アナログスティックのY軸の倒したかどうかの判定取得
	* @details bool型が返ってくる。第2引数で上か下かの指定をする
	* @param[in] _padNum Padの番号(0~3)
	* @param[in] _up 上下どちらに判定を取りたいか指定
	* @return 左スティックの倒したかのフラグ
	*/
	static bool GetPadAnalogStickLeftPressY(int,bool);
	
	/**
	* @fn GetPadAnalogStickLeftPressX
	* @brief 左アナログスティックのX軸の倒したかどうかの判定取得
	* @details bool型が返ってくる。第2引数で右か左かの指定をする
	* @param[in] _padNum Padの番号(0~3)
	* @param[in] _right 右左どちらに判定を取りたいか指定
	* @param[in] _range 判定を取る範囲指定
	* @return 左スティックの倒したかのフラグ
	*/
	static bool GetPadAnalogStickLeftPressX(int,bool,int);

	/**
	* @fn GetPadAnalogStickLeftPressY
	* @brief 左アナログスティックのY軸の倒したかどうかの判定取得
	* @details bool型が返ってくる。第2引数で上か下かの指定をする
	* @param[in] _padNum Padの番号(0~3)
	* @param[in] _up 上下どちらに判定を取りたいか指定
	* @param[in] _range 判定を取る範囲指定
	* @return 左スティックの倒したかのフラグ
	*/
	static bool GetPadAnalogStickLeftPressY(int,bool,int);

	/**
	* @fn GetPadAnalogStickLeftTriggerX
	* @brief 左アナログスティックのX軸の倒したかどうかの判定取得
	* @details bool型が返ってくる。第2引数で右か左かの指定をする
	* @param[in] _padNum Padの番号(0~3)
	* @param[in] _right 右左どちらに判定を取りたいか指定
	* @return 左スティックの倒したかのフラグ
	*/
	static bool GetPadAnalogStickLeftTriggerX(int,bool);

	/**
	* @fn GetPadAnalogStickLeftTriggerY
	* @brief 左アナログスティックのY軸の倒したかどうかの判定取得
	* @details bool型が返ってくる。第2引数で上か下かの指定をする
	* @param[in] _padNum Padの番号(0~3)
	* @param[in] _up 上下どちらに判定を取りたいか指定
	* @return 左スティックの倒したかのフラグ
	*/
	static bool GetPadAnalogStickLeftTriggerY(int,bool);
	
	/**
	* @fn GetPadAnalogStickLeftTriggerX
	* @brief 左アナログスティックのX軸の倒したかどうかの判定取得
	* @details bool型が返ってくる。第2引数で右か左かの指定をする
	* @param[in] _padNum Padの番号(0~3)
	* @param[in] _right 右左どちらに判定を取りたいか指定
	* @param[in] _range 判定を取る範囲指定
	* @return 左スティックの倒したかのフラグ
	*/
	static bool GetPadAnalogStickLeftTriggerX(int,bool,int);

	/**
	* @fn GetPadAnalogStickLeftTriggerY
	* @brief 左アナログスティックのY軸の倒したかどうかの判定取得
	* @details bool型が返ってくる。第2引数で上か下かの指定をする
	* @param[in] _padNum Padの番号(0~3)
	* @param[in] _up 上下どちらに判定を取りたいか指定
	* @param[in] _range 判定を取る範囲指定
	* @return 左スティックの倒したかのフラグ
	*/
	static bool GetPadAnalogStickLeftTriggerY(int,bool,int);

	/**
	* @fn GetPadAnalogStickLeftAngle
	* @brief 左アナログスティックのY座標取得
	* @details 0～360までのfloat型が返ってくる。
	* @param[in] _padNum Padの番号(0~3)
	* @return 左スティックの角度
	*/
	static float GetPadAnalogStickLeftAngle(int);

	/**
	* @fn GetPadAnalogStickRightX
	* @brief 右アナログスティックのX座標取得
	* @details -32768~32767までのSHORT型が返ってくる。
	* @param[in] _padNum Padの番号(0~3)
	* @return 右スティックのX座標
	*/
	static SHORT GetPadAnalogStickRightX(int);

	/**
	* @fn GetPadAnalogStickRightY
	* @brief 右アナログスティックのY座標取得
	* @details -32768~32767までのSHORT型が返ってくる。
	* @param[in] _padNum Padの番号(0~3)
	* @return 右スティックのY座標
	*/
	static SHORT GetPadAnalogStickRightY(int);
	
	/**
	* @fn GetPadAnalogStickRightPressX
	* @brief 右アナログスティックのX軸の倒したかどうかの判定取得
	* @details bool型が返ってくる。第2引数で右か左かの指定をする
	* @param[in] _padNum Padの番号(0~3)
	* @param[in] _right 右左どちらに判定を取りたいか指定
	* @return 右スティックの倒したかのフラグ
	*/
	static bool GetPadAnalogStickRightPressX(int,bool);

	/**
	* @fn GetPadAnalogStickRightPressY
	* @brief 右アナログスティックのY軸の倒したかどうかの判定取得
	* @details bool型が返ってくる。第2引数で上か下かの指定をする
	* @param[in] _padNum Padの番号(0~3)
	* @param[in] _up 上下どちらに判定を取りたいか指定
	* @return 右スティックの倒したかのフラグ
	*/
	static bool GetPadAnalogStickRightPressY(int,bool);

	/**
	* @fn GetPadAnalogStickRightPressX
	* @brief 右アナログスティックのX軸の倒したかどうかの判定取得
	* @details bool型が返ってくる。第2引数で右か左かの指定をする
	* @param[in] _padNum Padの番号(0~3)
	* @param[in] _right 右左どちらに判定を取りたいか指定
	* @param[in] _range 判定を取る範囲指定
	* @return 右スティックの倒したかのフラグ
	*/
	static bool GetPadAnalogStickRightPressX(int,bool,int);

	/**
	* @fn GetPadAnalogStickRightPressY
	* @brief 右アナログスティックのY軸の倒したかどうかの判定取得
	* @details bool型が返ってくる。第2引数で上か下かの指定をする
	* @param[in] _padNum Padの番号(0~3)
	* @param[in] _up 上下どちらに判定を取りたいか指定
	* @param[in] _range 判定を取る範囲指定
	* @return 右スティックの倒したかのフラグ
	*/
	static bool GetPadAnalogStickRightPressY(int,bool,int);

	/**
	* @fn GetPadAnalogStickRightTriggerX
	* @brief 右アナログスティックのX軸の倒したかどうかの判定取得
	* @details bool型が返ってくる。第2引数で右か左かの指定をする
	* @param[in] _padNum Padの番号(0~3)
	* @param[in] _right 右左どちらに判定を取りたいか指定
	* @return 右スティックの倒したかのフラグ
	*/
	static bool GetPadAnalogStickRightTriggerX(int,bool);

	/**
	* @fn GetPadAnalogStickRightTriggerY
	* @brief 右アナログスティックのY軸の倒したかどうかの判定取得
	* @details bool型が返ってくる。第2引数で上か下かの指定をする
	* @param[in] _padNum Padの番号(0~3)
	* @param[in] _up 上下どちらに判定を取りたいか指定
	* @return 右スティックの倒したかのフラグ
	*/
	static bool GetPadAnalogStickRightTriggerY(int,bool);

	/**
	* @fn GetPadAnalogStickRightTriggerX
	* @brief 右アナログスティックのX軸の倒したかどうかの判定取得
	* @details bool型が返ってくる。第2引数で右か左かの指定をする
	* @param[in] _padNum Padの番号(0~3)
	* @param[in] _right 右左どちらに判定を取りたいか指定
	* @param[in] _range 判定を取る範囲指定
	* @return 右スティックの倒したかのフラグ
	*/
	static bool GetPadAnalogStickRightTriggerX(int,bool,int);

	/**
	* @fn GetPadAnalogStickRightTriggerY
	* @brief 右アナログスティックのY軸の倒したかどうかの判定取得
	* @details bool型が返ってくる。第2引数で上か下かの指定をする
	* @param[in] _padNum Padの番号(0~3)
	* @param[in] _up 上下どちらに判定を取りたいか指定
	* @param[in] _range 判定を取る範囲指定
	* @return 右スティックの倒したかのフラグ
	*/
	static bool GetPadAnalogStickRightTriggerY(int,bool,int);

	/**
	* @fn GetPadAnalogStickRightAngle
	* @brief 右アナログスティックの角度取得
	* @details 0～360までのfloat型が返ってくる。
	* @param[in] _padNum Padの番号(0~3)
	* @return 右スティックの角度
	*/
	static float GetPadAnalogStickRightAngle(int);

	#pragma endregion

	#pragma region Mouse

	// keycodeに普通にあるとは思わなんだ。Mouseのボタンコードあるとは。

	/**
	* @fn GetMousePressLeft
	* @brief プレスのモードで左クリックを取得
	* @details 前フレームの状態に関係なく今のフレームに押されているかの判定を返す
	* @return 押されているかの情報
	*/
	static bool GetMousePressLeft();
	/**
	* @fn GetMousePressRight
	* @brief プレスのモードで右クリックを取得
	* @details 前フレームの状態に関係なく今のフレームに押されているかの判定を返す
	* @return 押されているかの情報
	*/
	static bool GetMousePressRight();
	/**
	* @fn GetMousePressMiddle
	* @brief プレスのモードで中クリックを取得
	* @details 前フレームの状態に関係なく今のフレームに押されているかの判定を返す
	* @return 押されているかの情報
	*/
	static bool GetMousePressMiddle();

	/**
	* @fn GetMousePressSideUp
	* @brief プレスのモードでサイド上ボタン入力を取得
	* @details 前フレームの状態に関係なく今のフレームに押されているかの判定を返す
	* @return 押されているかの情報
	*/
	static bool GetMousePressSideUp();
	/**
	* @fn GetMousePressSideDown
	* @brief プレスのモードでサイド下ボタン入力を取得
	* @details 前フレームの状態に関係なく今のフレームに押されているかの判定を返す
	* @return 押されているかの情報
	*/
	static bool GetMousePressSideDown();

	static bool GetMouseTriggerLeft();
	static bool GetMouseTriggerRight();
	static bool GetMouseTriggerMiddle();

	static bool GetMouseTriggerSideUp();
	static bool GetMouseTriggerSideDown();

	static POINT GetCurPos();
	static POINT GetCursorPosOnScreen();
	static bool GetCursorPosOnScreen(POINT& _point);
	#pragma endregion

private:
	//! キー状態保存用
	static BYTE mKeyState[256];
	//! 1フレーム前のキー状態保存用
	static BYTE mOldKeyState[256];
	//! パッド状態保存用
	static XINPUT_STATE mXPadState[GAMEPAD_MAX_AMOUNT];
	//! 1フレーム前のキー状態保存用
	static XINPUT_STATE mOldXPadState[GAMEPAD_MAX_AMOUNT];

};

/*EOF*/