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

Field::Field()
{
    // 2次元vectorに要素を追加
    m_field.push_back({ 1, 1, 1, 1, 1, 1 });
    m_field.push_back({ 1, 1, 1, 1, 1, 1 });
    m_field.push_back({ 1, 1, 1, 1, 1, 1 });
    m_field.push_back({ 1, 1, 1, 0, 1, 1 });
    m_field.push_back({ 1, 1, 1, 0, 1, 1 });
    m_field.push_back({ 1, 1, 1, 0, 1, 1 });
    m_field.push_back({ 1, 1, 1, 1, 1, 1 });
    m_field.push_back({ 1, 1, 1, 1, 1, 1 });

    // 行と列のサイズを取得
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
                if (m_field[row][col] == 1)
                {
                    // セルの中央座標を計算
                    float x = col * kCellSize;
                    float z = row * kCellSize;

                    // モデルの位置を設定
                    VECTOR modelPos = VGet(x, -kCellSize / 2.0f, z);
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

}

void Field::Draw()
{
    // 描画
    for (auto& model : m_pModel)
    {
        model->Draw();
    }
}
