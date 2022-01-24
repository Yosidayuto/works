//=============================================================================
//
//	勝者プレイヤー[winner player.cpp]
//	Author:吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "winner player.h"
#include "resource manager.h"
//=============================================================================
// コンストラクタ
//=============================================================================
CWinnerPlayer::CWinnerPlayer(int nPriority) :CModel(nPriority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CWinnerPlayer::~CWinnerPlayer()
{

}

//=============================================================================
// 生成処理関数
//=============================================================================
CWinnerPlayer * CWinnerPlayer::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size, int nModel)
{
	//メモリ確保
	CWinnerPlayer* pWinnerPlayer = nullptr;
	pWinnerPlayer = new CWinnerPlayer;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	MODELDATA Model = pResource->ModelLoad(nModel);

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
		//初期化処理
		pWinnerPlayer->Init();
	}

	return pWinnerPlayer;
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CWinnerPlayer::Update(void)
{

}
