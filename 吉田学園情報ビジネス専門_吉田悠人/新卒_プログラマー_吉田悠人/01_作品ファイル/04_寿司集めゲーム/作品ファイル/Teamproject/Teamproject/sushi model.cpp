//=============================================================================
//
//	寿司モデル[model sushi.cpp]
//	Author:林川
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "sushi model.h"
#include "resource manager.h"

#define MOVE_SPEED (5)
//=============================================================================
// コンストラクタ
//=============================================================================
CSushiModel::CSushiModel(int nPriority) :CModel(nPriority)
{
	m_RandAddRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

//=============================================================================
// デストラクタ
//=============================================================================
CSushiModel::~CSushiModel()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CSushiModel * CSushiModel::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size, int nModel)
{
	//メモリ確保
	CSushiModel* pWinnerPlayer = nullptr;
	pWinnerPlayer = new CSushiModel;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	MODELDATA Model = pResource->ModelLoad(20 + nModel);

	//NULLチェック
	if (pWinnerPlayer != nullptr)
	{
		//位置設定
		pWinnerPlayer->SetPos(Pos);
		//向き設定
		pWinnerPlayer->SetRot(Rot);
		//カラー設定
		pWinnerPlayer->SetSize(Size);
		//モデルデータ設定
		pWinnerPlayer->SetModelData(Model);
		float nRandRotX = float(rand() % 100) / 10000;
		float nRandRotY = float(rand() % 100) / 10000;
		float nRandRotZ = float(rand() % 100) / 10000;
		pWinnerPlayer->m_RandAddRot = D3DXVECTOR3(nRandRotX, nRandRotY, nRandRotZ);
		//初期化処理
		pWinnerPlayer->Init();
	}

	return pWinnerPlayer;
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CSushiModel::Update(void)
{
	SetRot(GetRot() + m_RandAddRot);

	SetPos(D3DXVECTOR3(GetPos().x, GetPos().y, GetPos().z - MOVE_SPEED));

	//画面外に出ているか
	if (GetPos().z <= -500)
	{
		//画面外にいる時に消去
		Uninit();
	}
}
