#include "Field.h"
#include "Model.h"

#include <DxLib.h>

namespace
{
    // グラフィック情報
    const char* const kGreenModelFilename = "Data/Model/GreenCube.mv1";
    const char* const kRedModelFilename = "Data/Model/RedCube.mv1";
    const char* const kBlueModelFilename = "Data/Model/BlueCube.mv1";
    const char* const kYellowModelFilename = "Data/Model/YellowCube.mv1";
    const char* const kPurpleModelFilename = "Data/Model/PurpleCube.mv1";

    const char* const cubeModelPath = "resource/model/Cube.mv1";

    const char* const blueTexturePath = "resource/model/texture/Blue.png";
    const char* const pinkTexturePath = "resource/model/texture/Pink.png";

    // 5x5のセル数
    constexpr int kCellX = 8;
    constexpr int kCellZ = 8;
    constexpr int kStageMaxSize = kCellX * kCellZ;

    // セルのサイズ
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

    // 行と列のサイズを取得
    size_t numRows = m_field.size();
    if (numRows > 0) {
        // 0番列の要素しかみていない為、0番列以外の要素を変更しても処理が行われない
        size_t numCols = m_field[0].size();

        // 3Dモデルの読み込み
        // モデルを配置
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

                    //// セルの中央座標を計算
                    //float x = col * kCellSize;
                    //float y = -kCellSize / 2.0f;
                    //float z = row * kCellSize;

                   
                    //// モデルの位置を設定
                    //VECTOR modelPos = VGet(x, y, z);
                    //// 座標指定
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
        // 最初の配列の要素しかみていない為、最初の要素以外に要素を追加しても処理が行われない
        size_t numCols = m_field[0].size();

        // 3Dモデルの読み込み
        // モデルを配置
        for (int row = 0; row < numRows; row++)
        {
            for (int col = 0; col < numCols; col++)
            {
                // セルの中央座標を計算
                float x = col * kCellSize;
                float y = -kCellSize / 2.0f;
                float z = row * kCellSize;
                
                // モデルの位置を設定
                VECTOR modelPos = VGet(x, y, z);

                if (m_field[row][col] == FieldState::GREEN)
                {
                    // 座標指定
                    m_pGreenModel.back()->SetPos(modelPos);
                }
                else if (m_field[row][col] == FieldState::RED)
                {
                    // 座標指定
                    m_pRedModel.back()->SetPos(modelPos);
                }
                else if (m_field[row][col] == FieldState::BLUE)
                {
                    // 座標指定
                    m_pBlueModel.back()->SetPos(modelPos);
                }
                //else if (m_field[row][col] == FieldState::YELLOW)
                //{
                //    // 座標指定
                //    m_pYellowModel.back()->SetPos(modelPos);
                //}
                //else if (m_field[row][col] == FieldState::PURPLE)
                //{
                //    // 座標指定
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

    //モデルの読み込み
    const int cubeHandle = MV1LoadModel(cubeModelPath);

    const int colorBlue = LoadGraph(blueTexturePath);
    const int colorPink = LoadGraph(pinkTexturePath);
    for (int i = 0; i < stageMaxSize; i++)
    {
        //2色のモデルを交互に配置する
        //偶数時しかできていないため改善余地あり
        const int duplicateModel = MV1DuplicateModel(cubeHandle);

        if (i / stageSize % 2 == i % 2) MV1SetTextureGraphHandle(duplicateModel, 0, colorBlue, false);
        else MV1SetTextureGraphHandle(duplicateModel, 0, colorPink, false);

        model[i].handle = duplicateModel;
        model[i].isFall = false;
    }

    modelSize = { 1.0f, 1.0f , 1.0f };
}
