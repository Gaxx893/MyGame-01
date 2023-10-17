#include "Field.h"
#include "Model.h"

#include <DxLib.h>

namespace
{
    // �O���t�B�b�N���
    const char* const kModelFilename = "Data/Model/Cube_Grass_Single.mv1";

    // 5x5�̃Z����
    constexpr int kCellX = 6;
    constexpr int kCellZ = 6;

    // �Z���̃T�C�Y
    constexpr float kCellSize = 210.0f;
}

Field::Field(VECTOR PlayerattackPos) :
    playerAttackPos(PlayerattackPos)
{
    // 2����vector�ɗv�f��ǉ�
    m_field.push_back({ 2, 1, 1, 1, 1, 1 });
    m_field.push_back({ 1, 1, 1, 1, 1, 1 });
    m_field.push_back({ 1, 1, 1, 1, 1, 1 });
    m_field.push_back({ 1, 2, 1, 0, 1, 1 });
    m_field.push_back({ 1, 2, 1, 0, 1, 1 });
    m_field.push_back({ 1, 1, 1, 0, 1, 1 });
    m_field.push_back({ 1, 1, 1, 1, 1, 1 });
    m_field.push_back({ 1, 1, 1, 1, 1, 1 });

    // �s�Ɨ�̃T�C�Y���擾
    size_t numRows = m_field.size();
    if (numRows > 0) {
        // �ŏ��̔z��̗v�f�����݂Ă��Ȃ��ׁA�ŏ��̗v�f�ȊO�ɗv�f��ǉ����Ă��������s���Ȃ�
        size_t numCols = m_field[0].size();

        // 3D���f���̓ǂݍ���
        // ���f����z�u
        for (int row = 0; row < numRows; row++)
        {
            for (int col = 0; col < numCols; col++)
            {
                if (m_field[row][col] != FieldState::NONE)
                {
                    // �Z���̒������W���v�Z
                    float x = col * kCellSize;
                    float z = row * kCellSize;

                    // ���f���̈ʒu��ݒ�
                    VECTOR modelPos = VGet(x, -kCellSize / 2.0f, z);
                    // ���f���̃C���X�^���X����
                    m_pModel.push_back(std::make_shared<Model>(kModelFilename));
                    // ���W�w��
                    m_pModel.back()->SetPos(modelPos);
                }
            }
        }
    }
}

Field::~Field()
{
}

void Field::Update()
{
    size_t numRows = m_field.size();
    if (numRows > 0) {
        // �ŏ��̔z��̗v�f�����݂Ă��Ȃ��ׁA�ŏ��̗v�f�ȊO�ɗv�f��ǉ����Ă��������s���Ȃ�
        size_t numCols = m_field[0].size();

        // 3D���f���̓ǂݍ���
        // ���f����z�u
        for (int row = 0; row < numRows; row++)
        {
            for (int col = 0; col < numCols; col++)
            {
                // �Z���̒������W���v�Z
                float x = col * kCellSize;
                float z = row * kCellSize;

                // ���f���̈ʒu��ݒ�
                VECTOR modelPos = VGet(x, -kCellSize / 2.0f, z);

                if (m_field[row][col] == FieldState::RED)
                {
                    // ���f���̃}�e���A���̃f�B�t���[�Y�J���[��Ԃɂ���
                    MV1SetMaterialDifColor(m_pModel[ col + row * numCols]->GetModelHandle(), 0, GetColorF(1.0f, 0.0f, 0.0f, 1.0f));
                }

                //if (m_field[row][col] == FieldState::BLUE)
                //{
                //    // ���f���̃}�e���A���̃f�B�t���[�Y�J���[��ɂ���
                //    MV1SetMaterialDifColor(m_pModel.back()->GetModelHandle(), 0, GetColorF(0.0f, 0.0f, 1.0f, 0.0f));
                //}
            }
        }
    }
}

void Field::Draw()
{
    // �`��
    for (auto& model : m_pModel)
    {
        model->Draw();
    }
}
