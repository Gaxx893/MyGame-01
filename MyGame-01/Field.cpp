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
    m_field.push_back({ 1, 3, 1, 1, 1, 1 });
    m_field.push_back({ 1, 3, 1, 1, 1, 1 });
    m_field.push_back({ 1, 2, 1, 0, 1, 1 });
    m_field.push_back({ 1, 2, 1, 0, 1, 1 });
    m_field.push_back({ 1, 1, 1, 0, 1, 1 });
    m_field.push_back({ 1, 1, 1, 1, 1, 1 });
    m_field.push_back({ 1, 1, 1, 1, 1, 1 });

    // �s�Ɨ�̃T�C�Y���擾
    size_t numRows = m_field.size();
    if (numRows > 0) {
        // 0�ԗ�̗v�f�����݂Ă��Ȃ��ׁA0�ԗ�ȊO�̗v�f��ύX���Ă��������s���Ȃ�
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
                    float y = -kCellSize / 2.0f;
                    float z = row * kCellSize;

                    // ���f���̈ʒu��ݒ�
                    VECTOR modelPos = VGet(x, y, z);
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
            //    model[row][col]->SetColor(m_field[row][col]);


                //int modelColor = m_field[row][col];

                //COLOR_F modelColorRGB = GetColorF(0.0f, 1.0f, 0.0f, 1.0f);
                //if (m_field[row][col] == FieldState::RED)
                //{
                //    // ���f���̃}�e���A���̃f�B�t���[�Y�J���[��Ԃɂ���
                //    for (auto& model : m_pModel)
                //    {
                //        if (modelColor == FieldState::RED)
                //        {
                //            modelColorRGB = GetColorF(1.0f, 0.0f, 0.0f, 1.0f);
                //            model->SetColor(modelColorRGB);
                //        }
                //    }
                //}


                //if (modelColor == FieldState::BLUE)
                //{
                //    // ���f���̃}�e���A���̃f�B�t���[�Y�J���[��Ԃɂ���
                //    for (auto& model : m_pModel)
                //    {
                //        if (model->GetPos().x == x && model->GetPos().y == y && model->GetPos().z == z)
                //        {
                //            modelColorRGB = GetColorF(0.0f, 0.0f, 1.0f, 1.0f);
                //            model->SetColor(modelColorRGB);
                //        }
                //    }
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
