#include <cassert>
#include <DxLib.h>

#include "SceneManager.h"
#include "SceneBase.h"
#include "SceneTitle.h"
#include "SceneDebug.h"
#include "../Util/Pad.h"

SceneManager::SceneManager() :
	m_pScene()
{
}
SceneManager::~SceneManager()
{
	// �����Ȃ�
}

void SceneManager::Init()
{
#ifdef NDEBUG
	// �w�肵���N���X�̃C���X�^���X�̃|�C���^���Z�b�g
	m_pScene.reset(new SceneTitle);
	m_pScene->Init();
#else
	// �w�肵���N���X�̃C���X�^���X�̃|�C���^���Z�b�g
	m_pScene.reset(new SceneDebug);
	m_pScene->Init();
#endif
}

void SceneManager::End()
{
	// �L���ȃ|�C���g(nullptr�łȂ���)���m�F
	assert(m_pScene);
	// �����ȃ|�C���^(nullptr)�̏ꍇ�A�V�[���̏I���������s��Ȃ�
	if (!m_pScene)	return;

	// �V�[���̏I������
	m_pScene->End();
}

void SceneManager::Update()
{
	// �L���ȃ|�C���g(nullptr�łȂ���)���m�F
	assert(m_pScene);
	// �����ȃ|�C���^(nullptr)�̏ꍇ�A�V�[���̍X�V�������s��Ȃ�
	if (!m_pScene)	return;

	Pad::update();
	// ���̃V�[���I�u�W�F�N�g�̃|�C���^���擾
	// (/*�R�߂���Ɏ��₵����*/)
	SceneBase* pScene = m_pScene->Update();
	// �擾�����|�C���^�����݂̃V�[���I�u�W�F�N�g�̃|�C���^�Ɠ�������Ȃ����
	if (pScene != m_pScene.get())
	{
		// ���݂̃V�[���̏I������
		m_pScene->End();

		// �V�[���I�u�W�F�N�g�̃|�C���^���Z�b�g���A
		// ���V�[���ւ̐؂�ւ����s��
		// (/*�R�߂���Ɏ��₵����*/)
		m_pScene.reset(pScene);
		// �V�[���̏�����
		m_pScene->Init();
	}
}

void SceneManager::Draw()
{
	// �L���ȃ|�C���g(nullptr�łȂ���)���m�F
	assert(m_pScene);
	// �����ȃ|�C���^(nullptr)�̏ꍇ�A�V�[���̕`�揈�����s��Ȃ�
	if (!m_pScene)	return;
	// �V�[���̕`��
	m_pScene->Draw();
}