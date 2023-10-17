#pragma once

// ゲームシーン基底クラス
class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase() {}

	virtual void Init() {}
	virtual void End() {}

	virtual SceneBase* Update() { return this; }// 何でthisを返しているかわからない
	virtual void Draw() {}

	// フェード関連
	void UpdateFade();
	void DrawFade() const;

	bool IsFadingIn() const;	// フェードイン中
	bool IsFadingOut() const;	// フェードアウト中
	bool IsFading() const { return IsFadingIn() || IsFadingOut(); }	// フェードインorアウト中

	/// <summary>
	/// フェードの明るさを取得
	/// </summary>
	/// <returns>0(フェードしていない)～255(真っ黒)</returns>
	int GetFadeBright() const { return m_fadeBrightness; }

private:
	// フェード関連処理
	int m_fadeColor;		// フェード処理に用いる背景色
	int m_fadeBrightness;	// 現在の明るさ
	int m_fadeSpeed;		// フェード処理の速度
};