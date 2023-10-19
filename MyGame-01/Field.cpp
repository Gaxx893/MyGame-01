#include "Field.h"
#include "Model.h"

#include <DxLib.h>

namespace
{
    // グラフィック情報
    const char* const kModelFilename = "Data/Model/Cube_Grass_Single.mv1";

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
                    // モデルのインスタンス生成
                    m_pModel.push_back(std::make_shared<Model>(kModelFilename));
                    // 座標指定
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
        // 最初の配列の要素しかみていない為、最初の要素以外に要素を追加しても処理が行われない
        size_t numCols = m_field[0].size();

        // 3Dモデルの読み込み
        // モデルを配置
        for (int row = 0; row < numRows; row++)
        {
            for (int col = 0; col < numCols; col++)
            {
            //    model[row][col]->SetColor(m_field[row][col]);


                //int modelColor = m_field[row][col];

                //COLOR_F modelColorRGB = GetColorF(0.0f, 1.0f, 0.0f, 1.0f);
                //if (m_field[row][col] == FieldState::RED)
                //{
                //    // モデルのマテリアルのディフューズカラーを赤にする
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
                //    // モデルのマテリアルのディフューズカラーを赤にする
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
    // 描画
    for (auto& model : m_pModel)
    {
        model->Draw();
    }
}
