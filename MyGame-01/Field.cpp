#include "Field.h"
#include "Model.h"

#include <DxLib.h>

namespace
{
    // �O���t�B�b�N���
    const char* const kGreenModelFilename = "Data/Model/GreenCube.mv1";
    const char* const kRedModelFilename = "Data/Model/RedCube.mv1";
    const char* const kBlueModelFilename = "Data/Model/BlueCube.mv1";
    const char* const kYellowModelFilename = "Data/Model/YellowCube.mv1";
    const char* const kPurpleModelFilename = "Data/Model/PurpleCube.mv1";

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

        m_pGreenModel.push_back(std::make_shared<Model>(kGreenModelFilename));
        m_pRedModel.push_back(std::make_shared<Model>(kRedModelFilename));
        m_pBlueModel.push_back(std::make_shared<Model>(kBlueModelFilename));
        m_pYellowModel.push_back(std::make_shared<Model>(kYellowModelFilename));
        m_pPurpleModel.push_back(std::make_shared<Model>(kPurpleModelFilename));

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
                    // ���W�w��
                    m_pGreenModel.back()->SetPos(modelPos);
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
                //for (auto& model : m_pModel)
                //{
                //    model->SetColor(m_field[row][col]);
                //}
                // �Z���̒������W���v�Z
                float x = col * kCellSize;
                float y = -kCellSize / 2.0f;
                float z = row * kCellSize;
                
                if (m_field[row][col] == FieldState::GREEN)
                {
                    // ���f���̈ʒu��ݒ�
                    VECTOR modelPos = VGet(x, y, z);
                    // ���W�w��
                    m_pGreenModel.back()->SetPos(modelPos);

                }
                else if (m_field[row][col] == FieldState::RED)
                {
                    // ���f���̈ʒu��ݒ�
                    VECTOR modelPos = VGet(x, y, z);
                    // ���W�w��
                    m_pRedModel.back()->SetPos(modelPos);
                }
                else if (m_field[row][col] == FieldState::BLUE)
                {
                    // ���f���̈ʒu��ݒ�
                    VECTOR modelPos = VGet(x, y, z);
                    // ���W�w��
                    m_pBlueModel.back()->SetPos(modelPos);
                }
                else if (m_field[row][col] == FieldState::YELLOW)
                {
                    // ���f���̈ʒu��ݒ�
                    VECTOR modelPos = VGet(x, y, z);
                    // ���W�w��
                    m_pYellowModel.back()->SetPos(modelPos);
                }
                else if (m_field[row][col] == FieldState::PURPLE)
                {
                    // ���f���̈ʒu��ݒ�
                    VECTOR modelPos = VGet(x, y, z);
                    // ���W�w��
                    m_pPurpleModel.back()->SetPos(modelPos);
                }
            }
        }
    }
}

void Field::Draw()
{
    // �`��
    for (auto& model : m_pGreenModel)
    {
        model->Draw();
    }

    for (auto& model : m_pRedModel)
    {
        model->Draw();
    }

    for (auto& model : m_pBlueModel)
    {
        model->Draw();
    }

}
