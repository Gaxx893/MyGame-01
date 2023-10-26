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

    // ステージのサイズ
    constexpr int kStageSize = 8;
    constexpr int kStageMaxSize = kStageSize * kStageSize;

    // 重力
    constexpr VECTOR kGravity = { 0.0f, -0.1f, 0.0f };
}

Field::Field() :
    m_playerAttackPos(VGet(0.0f, 0.0f, 0.0f)),
    m_modelPos(VGet(0.0f, 0.0f, 0.0f))
{
    // 2次元vectorに要素を追加
    m_field.push_back({ 1, 1, 1, 1, 1, 1, 1, 1 });
    m_field.push_back({ 1, 1, 1, 1, 1, 1, 1, 1 });
    m_field.push_back({ 1, 1, 1, 1, 1, 1, 1, 1 });
    m_field.push_back({ 1, 1, 1, 1, 1, 1, 1, 1 });
    m_field.push_back({ 1, 1, 1, 1, 1, 1, 1, 1 });
    m_field.push_back({ 1, 1, 1, 1, 1, 1, 1, 1 });
    m_field.push_back({ 1, 1, 1, 1, 1, 1, 1, 1 });
    m_field.push_back({ 1, 1, 1, 1, 1, 1, 1, 1 });

    // 行と列のサイズを取得
    size_t numRows = m_field.size();
    if (numRows > 0) {
        // 0番列の要素しかみていない為、0番列以外の要素を変更しても処理が行われない
        size_t numCols = m_field[0].size();

        //m_pRedModel.push_back(std::make_shared<Model>(kRedModelFilename));
        //m_pBlueModel.push_back(std::make_shared<Model>(kBlueModelFilename));
        //m_pYellowModel.push_back(std::make_shared<Model>(kYellowModelFilename));
        //m_pPurpleModel.push_back(std::make_shared<Model>(kPurpleModelFilename));

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
                m_modelPos = VGet(x, y, z);
                m_pGreenModel.push_back(std::make_shared<Model>(kGreenModelFilename));
                // 座標指定
                m_pGreenModel.back()->SetPos(m_modelPos);
            }
        }
    }
}

Field::~Field()
{
}

void Field::Update()
{
    /*size_t numRows = m_field.size();
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
    }*/
    for (auto& model : m_pGreenModel)
    {
        if (model->GetFall())
        {
            model->SetPos(VAdd(m_modelPos, kGravity));
        }

        if(model->GetPos().y < -115.0f)
        {
            model->SetFall(false);
            model->SetPos(VGet(m_modelPos.x, -kCellSize / 2.0f, m_modelPos.z));
        }
    }

    DrawFormatString(0, 0, 0xffffff, "pos = %f", m_pGreenModel[2]->GetPos().y);
}

void Field::Draw()
{
    // ３Ｄ空間上に線分を描画する
    DrawLine3D(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 1000.0f, 0.0f), GetColor(255, 255, 255));

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

void Field::SelectFallCube(VECTOR PlayerAttackPos, VECTOR PlayerDir)
{
    const float rotateY = PlayerDir.y;
    if (rotateY < 0.0f) return;

    // プレイヤーの現在いるインデックスを算出
    int PlayerX = (PlayerAttackPos.x + kCellSize / 2) / kCellSize;
    int PlayerZ = (PlayerAttackPos.z + kCellSize / 2) / kCellSize;

    const int currentIndex = PlayerZ * kStageSize + PlayerX;

    //ステージの端からステージ外方向には処理しない
    if (PlayerZ == 0 && rotateY == downVec) return;
    if (PlayerX == 0 && rotateY == leftVec) return;
    if (PlayerZ == kStageSize - 1 && rotateY == upVec) return;
    if (PlayerX == kStageSize - 1 && rotateY == rightVec) return;

    int beginIndex = currentIndex;
    int endIndex = currentIndex;

    if (rotateY == leftVec)
    {
        beginIndex -= 1;
        endIndex = PlayerZ * kStageSize;
    }
    if (rotateY == rightVec)
    {
        beginIndex += 1;
        endIndex = PlayerZ * kStageSize + (kStageSize - 1);
    }

    if (rotateY == upVec)
    {
        beginIndex += kStageSize;
        endIndex = kStageMaxSize - (kStageSize - PlayerX);
    }
    if (rotateY == downVec)
    {
        beginIndex -= kStageSize;
        endIndex = PlayerX;
    }

    SelectCubeLine(beginIndex, endIndex, currentIndex);
}

void Field::SelectCubeLine(const int beginIndex, const int endIndex, const int currentIndex)
{
    //上方向、右方向

    if (beginIndex < endIndex)
    {
        for (int i = beginIndex; i <= endIndex; i++)
        {
            const bool widthLineCheck = i / kStageSize == currentIndex / kStageSize;
            const bool heightLineCheck = i % kStageSize == currentIndex % kStageSize;
            if (widthLineCheck || heightLineCheck) m_pGreenModel[i]->SetFall(true);
        }
    }
    //下方向、左方向
    else
    {
        for (int i = beginIndex; endIndex <= i; i--)
        {
            const bool widthLineCheck = i / kStageSize == currentIndex / kStageSize;
            const bool heightLineCheck = i % kStageSize == currentIndex % kStageSize;
            if (widthLineCheck || heightLineCheck) m_pGreenModel[i]->SetFall(true);
        }
    }
}