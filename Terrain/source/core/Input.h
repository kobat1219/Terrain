/**
* @file input.h
* @brief ���͂ɂ��ċL�q����Ă���
*/
#pragma once

#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib,"xinput.lib")

//! �R���g���[���̍ő吔
#define GAMEPAD_MAX_AMOUNT 4

/**------------------------------------------------------------
* @brief	���̓N���X
* @details	Update�͖��t���[���Ăяo���΂����B@n
*			���ׂ�Static�ō\������Ă���̂Ŏg������
*			Input::�`�ɂȂ�B@n
*			�n��������
*			�p������'A'��'1'�݂����Ȋ���@n
*			����ȊO��F1��E���L�[����VK_F1��VK_RIGHT
--------------------------------------------------------------*/
class Input final
{
public:
	
	/**
	* @fn Update
	* @brief ���̖͂��t���[���̍X�V����
	* @details �Ăяo���̂̓��C�����[�v�̈�ԏ��߂ɂ��Ă���
	*/
	static void Update();
	
	#pragma region Keyboard

	/**
	* @fn GetKeyPress
	* @brief �v���X�̃��[�h�ŃL�[�����擾
	* @details �O�t���[���̃L�[��ԂɊ֌W�Ȃ����̃t���[���ɉ�����Ă��邩�̔����Ԃ�
	* @param[in] vkey �L�[�R�[�h����́B'A'��VK_LEFT
	* @return ������Ă��邩�̏��
	*/
	static bool GetKeyPress(int);

	/**
	* @fn GetKeyPress
	* @brief �g���K�[�̃��[�h�ŃL�[�����擾
	* @details �O�t���[���ɃL�[��������Ă��Ȃ������̃t���[���ɉ�����Ă��邩�̔����Ԃ�
	* @param[in] vkey �L�[�R�[�h����́B'A'��VK_LEFT
	* @return ������Ă��邩�̏��
	*/
	static bool GetKeyTrigger(int);

	/**
	* @fn GetKeyRelease
	* @brief �����[�X�̃��[�h�ŃL�[�����擾
	* @details �w��L�[�̓��͂������ꂽ���̔����Ԃ�
	* @param[in] vkey �L�[�R�[�h����́B'A'��VK_LEFT
	* @return ������Ă��邩�̏��
	*/
	static bool GetKeyRelease(int);

	#pragma endregion

	#pragma region GamePad
	
	/**
	* @fn GetPadButtonPress
	* @brief �v���X�̃��[�h��Pad�����擾
	* @details �O�t���[����Pad��ԂɊ֌W�Ȃ����̃t���[���ɉ�����Ă��邩�̔����Ԃ�
	* @param[in] _padNum Pad�̔ԍ�(0~3)
	* @param[in] _id Pad�p�̃}�N��
	* @return ������Ă��邩�̏��
	*/
	static bool GetPadButtonPress(int,WORD);

	/**
	* @fn GetPadButtonTrigger
	* @brief �g���K�[�̃��[�h��Pad�����擾
	* @details �O�t���[����Pad��������Ă��Ȃ������̃t���[���ɉ�����Ă��邩�̔����Ԃ�
	* @param[in] _padNum Pad�̔ԍ�(0~3)
	* @param[in] _id Pad�p�̃}�N��
	* @return ������Ă��邩�̏��
	*/
	static bool GetPadButtonTrigger(int, WORD);

	/**
	* @fn GetPadTriggerLeft
	* @brief ���g���K�[�̉����ݎ擾
	* @details 0~255�܂ł�BYTE�^���Ԃ��Ă���B
	* @param[in] _padNum Pad�̔ԍ�(0~3)
	* @return ���g���K�[�̉�����
	*/
	static BYTE GetPadTriggerLeft(int);

	/**
	* @fn GetPadTriggerLeftPress
	* @brief ���g���K�[�̉����ݎ擾
	* @details ��������Ă��邩���Ԃ��Ă���B
	* @param[in] _padNum Pad�̔ԍ�(0~3)
	* @param[in] _range �������ݔ�������镝(0~255)
	* @return ������Ă��邩�̏��
	*/
	static bool GetPadTriggerLeftPress(int,int _range = 120);

	/**
	* @fn GetPadTriggerLeftTrigger
	* @brief �g���K�[�̃��[�h�ō��g���K�[�̉����ݎ擾
	* @details �O�t���[����Pad��������Ă��Ȃ������̃t���[���ɉ�����Ă��邩�̔����Ԃ�
	* @param[in] _padNum Pad�̔ԍ�(0~3)
	* @param[in] _range �������ݔ�������镝(0~255)
	* @return ���g���K�[��������Ă��邩�̏��
	*/
	static bool GetPadTriggerLeftTrigger(int,int _range = 120);

	/**
	* @fn GetPadTriggerRight
	* @brief �E�g���K�[�̉����ݎ擾
	* @details 0~255�܂ł�BYTE�^���Ԃ��Ă���B
	* @param[in] _padNum Pad�̔ԍ�(0~3)
	* @return �E�g���K�[�̉�����
	*/
	static BYTE GetPadTriggerRight(int);

	/**
	* @fn GetPadTriggerRightPress
	* @brief �E�g���K�[�̉����ݎ擾
	* @details ��������Ă��邩���Ԃ��Ă���B
	* @param[in] _padNum Pad�̔ԍ�(0~3)
	* @param[in] _range �������ݔ�������镝(0~255)
	* @return ������Ă��邩�̏��
	*/
	static bool GetPadTriggerRightPress(int,int _range =120);

	/**
	* @fn GetPadTriggerRightTrigger
	* @brief �g���K�[�̃��[�h�ŉE�g���K�[�̉����ݎ擾
	* @details �O�t���[����Pad��������Ă��Ȃ������̃t���[���ɉ�����Ă��邩�̔����Ԃ�
	* @param[in] _padNum Pad�̔ԍ�(0~3)
	* @param[in] _range �������ݔ�������镝(0~255)
	* @return �E�g���K�[��������Ă��邩�̏��
	*/
	static bool GetPadTriggerRightTrigger(int,int _range = 120);

	/**
	* @fn GetPadAnalogStickLeftX
	* @brief ���A�i���O�X�e�B�b�N��X���W�擾
	* @details -32768~32767�܂ł�SHORT�^���Ԃ��Ă���B
	* @param[in] _padNum Pad�̔ԍ�(0~3)
	* @return ���X�e�B�b�N��X���W
	*/
	static SHORT GetPadAnalogStickLeftX(int);

	/**
	* @fn GetPadAnalogStickLeftY
	* @brief ���A�i���O�X�e�B�b�N��Y���W�擾
	* @details -32768~32767�܂ł�SHORT�^���Ԃ��Ă���B
	* @param[in] _padNum Pad�̔ԍ�(0~3)
	* @return ���X�e�B�b�N��Y���W
	*/
	static SHORT GetPadAnalogStickLeftY(int);
	
	/**
	* @fn GetPadAnalogStickLeftPressX
	* @brief ���A�i���O�X�e�B�b�N��X���̓|�������ǂ����̔���擾
	* @details bool�^���Ԃ��Ă���B��2�����ŉE�������̎w�������
	* @param[in] _padNum Pad�̔ԍ�(0~3)
	* @param[in] _right �E���ǂ���ɔ������肽�����w��
	* @return ���X�e�B�b�N�̓|�������̃t���O
	*/
	static bool GetPadAnalogStickLeftPressX(int,bool);

	/**
	* @fn GetPadAnalogStickLeftPressY
	* @brief ���A�i���O�X�e�B�b�N��Y���̓|�������ǂ����̔���擾
	* @details bool�^���Ԃ��Ă���B��2�����ŏォ�����̎w�������
	* @param[in] _padNum Pad�̔ԍ�(0~3)
	* @param[in] _up �㉺�ǂ���ɔ������肽�����w��
	* @return ���X�e�B�b�N�̓|�������̃t���O
	*/
	static bool GetPadAnalogStickLeftPressY(int,bool);
	
	/**
	* @fn GetPadAnalogStickLeftPressX
	* @brief ���A�i���O�X�e�B�b�N��X���̓|�������ǂ����̔���擾
	* @details bool�^���Ԃ��Ă���B��2�����ŉE�������̎w�������
	* @param[in] _padNum Pad�̔ԍ�(0~3)
	* @param[in] _right �E���ǂ���ɔ������肽�����w��
	* @param[in] _range ��������͈͎w��
	* @return ���X�e�B�b�N�̓|�������̃t���O
	*/
	static bool GetPadAnalogStickLeftPressX(int,bool,int);

	/**
	* @fn GetPadAnalogStickLeftPressY
	* @brief ���A�i���O�X�e�B�b�N��Y���̓|�������ǂ����̔���擾
	* @details bool�^���Ԃ��Ă���B��2�����ŏォ�����̎w�������
	* @param[in] _padNum Pad�̔ԍ�(0~3)
	* @param[in] _up �㉺�ǂ���ɔ������肽�����w��
	* @param[in] _range ��������͈͎w��
	* @return ���X�e�B�b�N�̓|�������̃t���O
	*/
	static bool GetPadAnalogStickLeftPressY(int,bool,int);

	/**
	* @fn GetPadAnalogStickLeftTriggerX
	* @brief ���A�i���O�X�e�B�b�N��X���̓|�������ǂ����̔���擾
	* @details bool�^���Ԃ��Ă���B��2�����ŉE�������̎w�������
	* @param[in] _padNum Pad�̔ԍ�(0~3)
	* @param[in] _right �E���ǂ���ɔ������肽�����w��
	* @return ���X�e�B�b�N�̓|�������̃t���O
	*/
	static bool GetPadAnalogStickLeftTriggerX(int,bool);

	/**
	* @fn GetPadAnalogStickLeftTriggerY
	* @brief ���A�i���O�X�e�B�b�N��Y���̓|�������ǂ����̔���擾
	* @details bool�^���Ԃ��Ă���B��2�����ŏォ�����̎w�������
	* @param[in] _padNum Pad�̔ԍ�(0~3)
	* @param[in] _up �㉺�ǂ���ɔ������肽�����w��
	* @return ���X�e�B�b�N�̓|�������̃t���O
	*/
	static bool GetPadAnalogStickLeftTriggerY(int,bool);
	
	/**
	* @fn GetPadAnalogStickLeftTriggerX
	* @brief ���A�i���O�X�e�B�b�N��X���̓|�������ǂ����̔���擾
	* @details bool�^���Ԃ��Ă���B��2�����ŉE�������̎w�������
	* @param[in] _padNum Pad�̔ԍ�(0~3)
	* @param[in] _right �E���ǂ���ɔ������肽�����w��
	* @param[in] _range ��������͈͎w��
	* @return ���X�e�B�b�N�̓|�������̃t���O
	*/
	static bool GetPadAnalogStickLeftTriggerX(int,bool,int);

	/**
	* @fn GetPadAnalogStickLeftTriggerY
	* @brief ���A�i���O�X�e�B�b�N��Y���̓|�������ǂ����̔���擾
	* @details bool�^���Ԃ��Ă���B��2�����ŏォ�����̎w�������
	* @param[in] _padNum Pad�̔ԍ�(0~3)
	* @param[in] _up �㉺�ǂ���ɔ������肽�����w��
	* @param[in] _range ��������͈͎w��
	* @return ���X�e�B�b�N�̓|�������̃t���O
	*/
	static bool GetPadAnalogStickLeftTriggerY(int,bool,int);

	/**
	* @fn GetPadAnalogStickLeftAngle
	* @brief ���A�i���O�X�e�B�b�N��Y���W�擾
	* @details 0�`360�܂ł�float�^���Ԃ��Ă���B
	* @param[in] _padNum Pad�̔ԍ�(0~3)
	* @return ���X�e�B�b�N�̊p�x
	*/
	static float GetPadAnalogStickLeftAngle(int);

	/**
	* @fn GetPadAnalogStickRightX
	* @brief �E�A�i���O�X�e�B�b�N��X���W�擾
	* @details -32768~32767�܂ł�SHORT�^���Ԃ��Ă���B
	* @param[in] _padNum Pad�̔ԍ�(0~3)
	* @return �E�X�e�B�b�N��X���W
	*/
	static SHORT GetPadAnalogStickRightX(int);

	/**
	* @fn GetPadAnalogStickRightY
	* @brief �E�A�i���O�X�e�B�b�N��Y���W�擾
	* @details -32768~32767�܂ł�SHORT�^���Ԃ��Ă���B
	* @param[in] _padNum Pad�̔ԍ�(0~3)
	* @return �E�X�e�B�b�N��Y���W
	*/
	static SHORT GetPadAnalogStickRightY(int);
	
	/**
	* @fn GetPadAnalogStickRightPressX
	* @brief �E�A�i���O�X�e�B�b�N��X���̓|�������ǂ����̔���擾
	* @details bool�^���Ԃ��Ă���B��2�����ŉE�������̎w�������
	* @param[in] _padNum Pad�̔ԍ�(0~3)
	* @param[in] _right �E���ǂ���ɔ������肽�����w��
	* @return �E�X�e�B�b�N�̓|�������̃t���O
	*/
	static bool GetPadAnalogStickRightPressX(int,bool);

	/**
	* @fn GetPadAnalogStickRightPressY
	* @brief �E�A�i���O�X�e�B�b�N��Y���̓|�������ǂ����̔���擾
	* @details bool�^���Ԃ��Ă���B��2�����ŏォ�����̎w�������
	* @param[in] _padNum Pad�̔ԍ�(0~3)
	* @param[in] _up �㉺�ǂ���ɔ������肽�����w��
	* @return �E�X�e�B�b�N�̓|�������̃t���O
	*/
	static bool GetPadAnalogStickRightPressY(int,bool);

	/**
	* @fn GetPadAnalogStickRightPressX
	* @brief �E�A�i���O�X�e�B�b�N��X���̓|�������ǂ����̔���擾
	* @details bool�^���Ԃ��Ă���B��2�����ŉE�������̎w�������
	* @param[in] _padNum Pad�̔ԍ�(0~3)
	* @param[in] _right �E���ǂ���ɔ������肽�����w��
	* @param[in] _range ��������͈͎w��
	* @return �E�X�e�B�b�N�̓|�������̃t���O
	*/
	static bool GetPadAnalogStickRightPressX(int,bool,int);

	/**
	* @fn GetPadAnalogStickRightPressY
	* @brief �E�A�i���O�X�e�B�b�N��Y���̓|�������ǂ����̔���擾
	* @details bool�^���Ԃ��Ă���B��2�����ŏォ�����̎w�������
	* @param[in] _padNum Pad�̔ԍ�(0~3)
	* @param[in] _up �㉺�ǂ���ɔ������肽�����w��
	* @param[in] _range ��������͈͎w��
	* @return �E�X�e�B�b�N�̓|�������̃t���O
	*/
	static bool GetPadAnalogStickRightPressY(int,bool,int);

	/**
	* @fn GetPadAnalogStickRightTriggerX
	* @brief �E�A�i���O�X�e�B�b�N��X���̓|�������ǂ����̔���擾
	* @details bool�^���Ԃ��Ă���B��2�����ŉE�������̎w�������
	* @param[in] _padNum Pad�̔ԍ�(0~3)
	* @param[in] _right �E���ǂ���ɔ������肽�����w��
	* @return �E�X�e�B�b�N�̓|�������̃t���O
	*/
	static bool GetPadAnalogStickRightTriggerX(int,bool);

	/**
	* @fn GetPadAnalogStickRightTriggerY
	* @brief �E�A�i���O�X�e�B�b�N��Y���̓|�������ǂ����̔���擾
	* @details bool�^���Ԃ��Ă���B��2�����ŏォ�����̎w�������
	* @param[in] _padNum Pad�̔ԍ�(0~3)
	* @param[in] _up �㉺�ǂ���ɔ������肽�����w��
	* @return �E�X�e�B�b�N�̓|�������̃t���O
	*/
	static bool GetPadAnalogStickRightTriggerY(int,bool);

	/**
	* @fn GetPadAnalogStickRightTriggerX
	* @brief �E�A�i���O�X�e�B�b�N��X���̓|�������ǂ����̔���擾
	* @details bool�^���Ԃ��Ă���B��2�����ŉE�������̎w�������
	* @param[in] _padNum Pad�̔ԍ�(0~3)
	* @param[in] _right �E���ǂ���ɔ������肽�����w��
	* @param[in] _range ��������͈͎w��
	* @return �E�X�e�B�b�N�̓|�������̃t���O
	*/
	static bool GetPadAnalogStickRightTriggerX(int,bool,int);

	/**
	* @fn GetPadAnalogStickRightTriggerY
	* @brief �E�A�i���O�X�e�B�b�N��Y���̓|�������ǂ����̔���擾
	* @details bool�^���Ԃ��Ă���B��2�����ŏォ�����̎w�������
	* @param[in] _padNum Pad�̔ԍ�(0~3)
	* @param[in] _up �㉺�ǂ���ɔ������肽�����w��
	* @param[in] _range ��������͈͎w��
	* @return �E�X�e�B�b�N�̓|�������̃t���O
	*/
	static bool GetPadAnalogStickRightTriggerY(int,bool,int);

	/**
	* @fn GetPadAnalogStickRightAngle
	* @brief �E�A�i���O�X�e�B�b�N�̊p�x�擾
	* @details 0�`360�܂ł�float�^���Ԃ��Ă���B
	* @param[in] _padNum Pad�̔ԍ�(0~3)
	* @return �E�X�e�B�b�N�̊p�x
	*/
	static float GetPadAnalogStickRightAngle(int);

	#pragma endregion

	#pragma region Mouse

	// keycode�ɕ��ʂɂ���Ƃ͎v��Ȃ񂾁BMouse�̃{�^���R�[�h����Ƃ́B

	/**
	* @fn GetMousePressLeft
	* @brief �v���X�̃��[�h�ō��N���b�N���擾
	* @details �O�t���[���̏�ԂɊ֌W�Ȃ����̃t���[���ɉ�����Ă��邩�̔����Ԃ�
	* @return ������Ă��邩�̏��
	*/
	static bool GetMousePressLeft();
	/**
	* @fn GetMousePressRight
	* @brief �v���X�̃��[�h�ŉE�N���b�N���擾
	* @details �O�t���[���̏�ԂɊ֌W�Ȃ����̃t���[���ɉ�����Ă��邩�̔����Ԃ�
	* @return ������Ă��邩�̏��
	*/
	static bool GetMousePressRight();
	/**
	* @fn GetMousePressMiddle
	* @brief �v���X�̃��[�h�Œ��N���b�N���擾
	* @details �O�t���[���̏�ԂɊ֌W�Ȃ����̃t���[���ɉ�����Ă��邩�̔����Ԃ�
	* @return ������Ă��邩�̏��
	*/
	static bool GetMousePressMiddle();

	/**
	* @fn GetMousePressSideUp
	* @brief �v���X�̃��[�h�ŃT�C�h��{�^�����͂��擾
	* @details �O�t���[���̏�ԂɊ֌W�Ȃ����̃t���[���ɉ�����Ă��邩�̔����Ԃ�
	* @return ������Ă��邩�̏��
	*/
	static bool GetMousePressSideUp();
	/**
	* @fn GetMousePressSideDown
	* @brief �v���X�̃��[�h�ŃT�C�h���{�^�����͂��擾
	* @details �O�t���[���̏�ԂɊ֌W�Ȃ����̃t���[���ɉ�����Ă��邩�̔����Ԃ�
	* @return ������Ă��邩�̏��
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
	//! �L�[��ԕۑ��p
	static BYTE mKeyState[256];
	//! 1�t���[���O�̃L�[��ԕۑ��p
	static BYTE mOldKeyState[256];
	//! �p�b�h��ԕۑ��p
	static XINPUT_STATE mXPadState[GAMEPAD_MAX_AMOUNT];
	//! 1�t���[���O�̃L�[��ԕۑ��p
	static XINPUT_STATE mOldXPadState[GAMEPAD_MAX_AMOUNT];

};

/*EOF*/