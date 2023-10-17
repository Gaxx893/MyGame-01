#include "DxLib.h"
#include "Pad.h"
#include <vector>

namespace
{
	// ログ記録フレーム数
	constexpr int kLogNum = 16;
	// パッド最大数
	constexpr int kMaxPad = 2;
	// 
	constexpr int kUsePadData[kMaxPad] =
	{
		DX_INPUT_KEY_PAD1,	// 0:最初に入力されたパッド
		DX_INPUT_PAD2		// 1:次に入力されたパッド
	};

	// 入力ログ0が最新の状態
	int padLog[kMaxPad][kLogNum];

	// キーログ
	bool				isRecordLog = false;
	int					playLogNo = -1;	// キーログ再生フレーム数
	std::vector<int>	keyLog;
}

namespace Pad
{
	// パッドの入力状態取得
	void update()
	{
		for (int padNo = 0; padNo < kMaxPad; padNo++)
		{
			// 現在の入力されたパッドのボタン番号を格納
			int padState = GetJoypadInputState(kUsePadData[padNo]);
			// キーログ再生中かつパッド番号が0番(最初に入力されたパッド)の場合
			if ((playLogNo >= 0) && (padNo == 0))
			{
				// キーログのサイズが、現在の再生位置playLogNoより大きい場合
				if (keyLog.size() > playLogNo)
				{
					// キーログから次の入力情報を取得
					padState = keyLog[playLogNo];
					playLogNo++;
				}
				else
				{
					// キーログ再生が終了
					playLogNo = -1;
				}
			}

			// ログの更新
			for (int i = kLogNum - 1; i >= 1; i--)
			{
				// 過去の入力履歴を保持？？？？
				padLog[padNo][i] = padLog[padNo][i - 1];
			}
			// 最新の状態
			padLog[padNo][0] = padState;

			// キーログ
			if (isRecordLog)
			{
				if (padNo == 0)
				{
					keyLog.push_back(padState);
				}
			}
		}
	}

	// 押し下げ判定
	bool isPress(int button, int padNo)
	{
		return (padLog[padNo][0] & button);
	}
	// トリガー判定
	bool isTrigger(int button, int padNo)
	{
		bool isNow = (padLog[padNo][0] & button);	// 現在の状態
		bool isLast = (padLog[padNo][1] & button);	// １フレーム前の状態
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