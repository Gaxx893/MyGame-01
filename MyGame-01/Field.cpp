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

    // 5x5のセル数
    constexpr int kCellX = 6;
    constexpr int kCellZ = 6;

    // セルのサイズ
    constexpr float kCellSize = 210.0f;
}

Field::Field(VECTOR PlayerattackPos) :
    playerAttackPos(PlayerattackPos)
{
    // 2次元vectorに要素を追加
    m_field.push_back({ 2, 1, 1, 1, 1, 1 });
    m_field.push_back({ 1, 3, 1, 1, 1, 1 });
    m_field.push_back({ 1, 3, 1, 1, 1, 1 });
    m_field.push_back({ 1, 2, 1, 0, 1, 1 });
    m_field.push_back({ 1, 2, 1, 0, 1, 1 });
    m_field.push_back({ 1, 1, 1, 0, 1, 1 });
    m_field.push_back({ 1, 1, 1, 1, 1, 1 });
    m_field.push_back({ 1, 1, 1, 1, 1, 1 });

    // 行と列のサイズを取得
    size_t numRows = m_field.size();
    if (numRows > 0) {
        // 0番列の要素しかみていない為、0番列以外の要素を変更しても処理が行われない
        size_t numCols = m_field[0].size();

        m_pGreenModel.push_back(std::make_shared<Model>(kGreenModelFilename));
        m_pRedModel.push_back(std::make_shared<Model>(kRedModelFilename));
        m_pBlueModel.push_back(std::make_shared<Model>(kBlueModelFilename));
        m_pYellowModel.push_back(std::make_shared<Model>(kYellowModelFilename));
        m_pPurpleModel.push_back(std::make_shared<Model>(kPurpleModelFilename));

        // 3Dモデルの読み込み
        // モデルを配置
        for (int row = 0; row < numRows; row++)
        {
            for (int col = 0; col < numCols; col++)
            {
                if (m_field[row][col] != FieldState::NONE)
                {
                    // セルの中央座標を計算
                    float x = col * kCellSize;
                    float y = -kCellSize / 2.0f;
                    float z = row * kCellSize;

                    // モデルの位置を設定
                    VECTOR modelPos = VGet(x, y, z);
                    // 座標指定
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
        // 最初の配列の要素しかみていない為、最初の要素以外に要素を追加しても処理が行われない
        size_t numCols = m_field[0].size();

        // 3Dモデルの読み込み
        // モデルを配置
        for (int row = 0; row < numRows; row++)
        {
            for (int col = 0; col < numCols; col++)
            {
                //for (auto& model : m_pModel)
                //{
                //    model->SetColor(m_field[row][col]);
                //}
                // セルの中央座標を計算
                float x = col * kCellSize;
                float y = -kCellSize / 2.0f;
                float z = row * kCellSize;
                
                if (m_field[row][col] == FieldState::GREEN)
                {
                    // モデルの位置を設定
                    VECTOR modelPos = VGet(x, y, z);
                    // 座標指定
                    m_pGreenModel.back()->SetPos(modelPos);

                }
                else if (m_field[row][col] == FieldState::RED)
                {
                    // モデルの位置を設定
                    VECTOR modelPos = VGet(x, y, z);
                    // 座標指定
                    m_pRedModel.back()->SetPos(modelPos);
                }
                else if (m_field[row][col] == FieldState::BLUE)
                {
                    // モデルの位置を設定
                    VECTOR modelPos = VGet(x, y, z);
                    // 座標指定
                    m_pBlueModel.back()->SetPos(modelPos);
                }
                else if (m_field[row][col] == FieldState::YELLOW)
                {
                    // モデルの位置を設定
                    VECTOR modelPos = VGet(x, y, z);
                    // 座標指定
                    m_pYellowModel.back()->SetPos(modelPos);
                }
                else if (m_field[row][col] == FieldState::PURPLE)
                {
                    // モデルの位置を設定
                    VECTOR modelPos = VGet(x, y, z);
                    // 座標指定
                    m_pPurpleModel.back()->SetPos(modelPos);
                }
            }
        }
    }
}

void Field::Draw()
{
    // 描画
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
