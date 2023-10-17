#pragma once

// �Q�[���V�[�����N���X
class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase() {}

	virtual void Init() {}
	virtual void End() {}

	virtual SceneBase* Update() { return this; }// ����this��Ԃ��Ă��邩�킩��Ȃ�
	virtual void Draw() {}

	// �t�F�[�h�֘A
	void UpdateFade();
	void DrawFade() const;

	bool IsFadingIn() const;	// �t�F�[�h�C����
	bool IsFadingOut() const;	// �t�F�[�h�A�E�g��
	bool IsFading() const { return IsFadingIn() || IsFadingOut(); }	// �t�F�[�h�C��or�A�E�g��

	/// <summary>
	/// �t�F�[�h�̖��邳���擾
	/// </summary>
	/// <returns>0(�t�F�[�h���Ă��Ȃ�)�`255(�^����)</returns>
	int GetFadeBright() const { return m_fadeBrightness; }

private:
	// �t�F�[�h�֘A����
	int m_fadeColor;		// �t�F�[�h�����ɗp����w�i�F
	int m_fadeBrightness;	// ���݂̖��邳
	int m_fadeSpeed;		// �t�F�[�h�����̑��x
};