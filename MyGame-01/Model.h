#pragma once
#include <Dxlib.h>
#include <vector>
#include <memory>
class Model
{
public:
	//ファイル名を指定してロードを行う
	Model(const char* fileName);
	//指定されたハンドルのモデルをDuplicateModelして生成する
	Model(int orgModel);
	virtual ~Model();

	// 当たり判定設定
	void SetUseCollision(bool isUse, bool isNeedUpdate);

	void Update();
	void Draw();

	//モデルハンドル取得
	int GetModelHandle() const { return m_modelHandle; }

	// 当たり判定に使用するフレームインデックスを取得する
	int GetColFrameIndex() const { return m_colFrameIndex; }

	//表示位置の設定
	void SetPos(VECTOR pos);

	VECTOR GetPos() { return m_Pos; }

	// 回転状態の設定
	void SetRot(VECTOR rot);

	// 拡大状態の設定
	void SetScale(VECTOR scale);

	// 落下状態の設定
	void SetFall(bool isFall);

	bool GetFall() { return m_isFall; }

	// アニメーションの制御
	/// <summary>
	/// アニメーションを設定する(ぱっと切り替える)
	/// </summary>
	/// <param name="animNo">変更先アニメーション番号</param>
	/// <param name="isLoop">アニメーションをループさせるか</param>
	/// <param name="isForceChange">すでに指定されたアニメが再生されている場合も変更するか</param>
	void SetAnimation(int animNo, bool isLoop, bool isForceChange);

	// アニメーションを変化させる(changeFrameフレームかけて切り替える)
	void ChangeAnimation(int animNo, bool isLoop, bool isForceChange, int changeFrame);

	// 現在のアニメーションが終了しているかどうかを取得する(Loopアニメの場合は取得できない = falseを返す)
	bool IsAnimEnd();

public:
	// 存在を消す
	void DeleteExist() { m_isExist = false; }
	// 存在状態の取得
	bool GetExist() { return m_isExist; }

private:
	//アニメーション情報
	struct AnimData
	{
		int animNo;			// アニメーション番号

		int attachNo;		// アタッチ番号
		float totalTime;	// アニメーションの総再生時間
		bool isLoop;		// アニメーションがループするか
	};
private:
	//モデルの位置
	VECTOR m_Pos;
	// アニメーションデータのクリア
	void clearAnimData(AnimData& anim);

	// アニメーションの更新
	void updateAnim(AnimData anim, float dt = 1.0f);

	// 現在のアニメーション切り替わり情報からアニメーションのブレンド率を設定する
	void updateAnimBlendRate();

private:
	// モデルのハンドル
	int m_modelHandle;

	// 当たり判定情報を使用する
	bool m_isUseCollision;
	// 当たり判定情報を毎フレーム更新する
	bool m_isUpdateCollision;
	// 当たり判定として使用するフレームのインデックス
	int m_colFrameIndex;

	// 存在状態
	bool m_isExist = true;
	// 落下状態
	bool m_isFall = false;

	// アニメーション変更速度
	int m_animSpeed;

	// アニメーションのアタッチ番号
	AnimData m_animPrev;	// 変更前アニメーション情報
	AnimData m_animNext;	// 変更後アニメーションデータ

	//アニメーションの切り替え情報
	int m_animChangeFrame;			// 現在の切り替えフレーム数
	int m_animChangeFrameTotal;		// 切り替えにかける総フレーム数
};

