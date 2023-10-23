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

    const char* const cubeModelPath = "resource/model/Cube.mv1";

    const char* const blueTexturePath = "resource/model/texture/Blue.png";
    const char* const pinkTexturePath = "resource/model/texture/Pink.png";

    // 5x5�̃Z����
    constexpr int kCellX = 8;
    constexpr int kCellZ = 8;
    constexpr int kStageMaxSize = kCellX * kCellZ;

    // �Z���̃T�C�Y
    constexpr float kCellSize = 210.0f;
}

Field::Field(VECTOR PlayerattackPos) :
    playerAttackPos(PlayerattackPos)
{
/*    m_field =
    {
        {
            {1, 1, 2, 1, 3, 1, 0, 1},
            {1, 1, 2, 1, 3, 1, 0, 1},
            {1, 1, 2, 1, 3, 1, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1},
        }
    };

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
                    m_pGreenModel.push_back(std::make_shared<Model>(kGreenModelFilename));
                    m_pRedModel.push_back(std::make_shared<Model>(kRedModelFilename));
                    m_pBlueModel.push_back(std::make_shared<Model>(kBlueModelFilename));
                    m_pYellowModel.push_back(std::make_shared<Model>(kYellowModelFilename));
                    m_pPurpleModel.push_back(std::make_shared<Model>(kPurpleModelFilename));

                    //// �Z���̒������W���v�Z
                    //float x = col * kCellSize;
                    //float y = -kCellSize / 2.0f;
                    //float z = row * kCellSize;

                   
                    //// ���f���̈ʒu��ݒ�
                    //VECTOR modelPos = VGet(x, y, z);
                    //// ���W�w��
                    //m_pGreenModel.back()->SetPos(modelPos);
                }
            }
        }
    }*/
}

Field::~Field()
{
}

void Field::Update()
{
 /*   size_t numRows = m_field.size();
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
                float y = -kCellSize / 2.0f;
                float z = row * kCellSize;
                
                // ���f���̈ʒu��ݒ�
                VECTOR modelPos = VGet(x, y, z);

                if (m_field[row][col] == FieldState::GREEN)
                {
                    // ���W�w��
                    m_pGreenModel.back()->SetPos(modelPos);
                }
                else if (m_field[row][col] == FieldState::RED)
                {
                    // ���W�w��
                    m_pRedModel.back()->SetPos(modelPos);
                }
                else if (m_field[row][col] == FieldState::BLUE)
                {
                    // ���W�w��
                    m_pBlueModel.back()->SetPos(modelPos);
                }
                //else if (m_field[row][col] == FieldState::YELLOW)
                //{
                //    // ���W�w��
                //    m_pYellowModel.back()->SetPos(modelPos);
                //}
                //else if (m_field[row][col] == FieldState::PURPLE)
                //{
                //    // ���W�w��
                //    m_pPurpleModel.back()->SetPos(modelPos);
                //}
            }
        }
    }*/
}

void Field::Draw()
{

}

void Field::LoadModelHandle()
{
    model.resize(kStageMaxSize);

    //���f���̓ǂݍ���
    const int cubeHandle = MV1LoadModel(cubeModelPath);

    const int colorBlue = LoadGraph(blueTexturePath);
    const int colorPink = LoadGraph(pinkTexturePath);
    for (int i = 0; i < stageMaxSize; i++)
    {
        //2�F�̃��f�������݂ɔz�u����
        //�����������ł��Ă��Ȃ����߉��P�]�n����
        const int duplicateModel = MV1DuplicateModel(cubeHandle);

        if (i / stageSize % 2 == i % 2) MV1SetTextureGraphHandle(duplicateModel, 0, colorBlue, false);
        else MV1SetTextureGraphHandle(duplicateModel, 0, colorPink, false);

        model[i].handle = duplicateModel;
        model[i].isFall = false;
    }

    modelSize = { 1.0f, 1.0f , 1.0f };
}
