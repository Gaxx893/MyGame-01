#include "DxLib.h"
#include "Pad.h"
#include <vector>

namespace
{
	// ���O�L�^�t���[����
	constexpr int kLogNum = 16;
	// �p�b�h�ő吔
	constexpr int kMaxPad = 2;
	// 
	constexpr int kUsePadData[kMaxPad] =
	{
		DX_INPUT_KEY_PAD1,	// 0:�ŏ��ɓ��͂��ꂽ�p�b�h
		DX_INPUT_PAD2		// 1:���ɓ��͂��ꂽ�p�b�h
	};

	// ���̓��O0���ŐV�̏��
	int padLog[kMaxPad][kLogNum];

	// �L�[���O
	bool				isRecordLog = false;
	int					playLogNo = -1;	// �L�[���O�Đ��t���[����
	std::vector<int>	keyLog;
}

namespace Pad
{
	// �p�b�h�̓��͏�Ԏ擾
	void update()
	{
		for (int padNo = 0; padNo < kMaxPad; padNo++)
		{
			// ���݂̓��͂��ꂽ�p�b�h�̃{�^���ԍ����i�[
			int padState = GetJoypadInputState(kUsePadData[padNo]);
			// �L�[���O�Đ������p�b�h�ԍ���0��(�ŏ��ɓ��͂��ꂽ�p�b�h)�̏ꍇ
			if ((playLogNo >= 0) && (padNo == 0))
			{
				// �L�[���O�̃T�C�Y���A���݂̍Đ��ʒuplayLogNo���傫���ꍇ
				if (keyLog.size() > playLogNo)
				{
					// �L�[���O���玟�̓��͏����擾
					padState = keyLog[playLogNo];
					playLogNo++;
				}
				else
				{
					// �L�[���O�Đ����I��
					playLogNo = -1;
				}
			}

			// ���O�̍X�V
			for (int i = kLogNum - 1; i >= 1; i--)
			{
				// �ߋ��̓��͗�����ێ��H�H�H�H
				padLog[padNo][i] = padLog[padNo][i - 1];
			}
			// �ŐV�̏��
			padLog[padNo][0] = padState;

			// �L�[���O
			if (isRecordLog)
			{
				if (padNo == 0)
				{
					keyLog.push_back(padState);
				}
			}
		}
	}

	// ������������
	bool isPress(int button, int padNo)
	{
		return (padLog[padNo][0] & button);
	}
	// �g���K�[����
	bool isTrigger(int button, int padNo)
	{
		bool isNow = (padLog[padNo][0] & button);	// ���݂̏��
		bool isLast = (padLog[padNo][1] & button);	// �P�t���[���O�̏��
		return (isNow && !isLast);
	}
	void startRecordLog()
	{
		isRecordLog = true;
		keyLog.clear();
	}

	void endRecordLog()
	{
		isRecordLog = false;
	}
	void startPlayLog()
	{
		playLogNo = 0;
	}
	void endPlayLog()
	{
		playLogNo = -1;
	}
}