//=============================================================================
//
// エネミータイプ3処理 [enemy type3.cpp]
// Author : 吉田悠人
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "enemy type3.h"
#include "manager.h"
#include "renderer.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define TYPE1_SIZE	(100.0f)	//サイズ
#define TYPE1_LIFE	(2)			//ライフ
#define TYPE1_SCORE (100)		//スコア
//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CEnemyType3::m_TextureData = { NULL,"data/TEXTURE/Enemy_3.png", };
//=============================================================================
// コンストラクト
//=============================================================================
CEnemyType3::CEnemyType3(int nPriorit)
{
}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CEnemyType3::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, m_TextureData.m_cFileName, &m_TextureData.m_Texture);
	return S_OK;
}

//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CEnemyType3::Unload(void)
{
	//テクスチャの破棄
	if (m_TextureData.m_Texture != NULL)
	{
		m_TextureData.m_Texture->Release();
		m_TextureData.m_Texture = NULL;
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CEnemyType3 * CEnemyType3::Create(ENEMY_MOVE_PATTERN MoveType, ENEMY_ATTACK_PATTERN AttackType, int nInTime, int nActionTime, int nAttacTime, int nReturnTime, D3DXVECTOR3 pos, float fSpeed, int nLife)
{
	//メモリ確保
	CEnemyType3* pEnemyType3 = NULL;
	pEnemyType3 = new CEnemyType3;

	//NULLチェック
	if (pEnemyType3 != NULL)
	{
		//行動パターン
		pEnemyType3->SetMovePattern(MoveType);
		//攻撃パターン
		pEnemyType3->SetAttackPattern(AttackType);
		//出現時間
		pEnemyType3->SetInTime(nInTime);
		//行動時間
		pEnemyType3->SetActionTime(nActionTime);
		//攻撃までの時間設定
		pEnemyType3->SetAttackTime(nAttacTime);
		//帰還までの時間設定
		pEnemyType3->SetOutTime(nReturnTime);
		//位置設定
		pEnemyType3->SetPos(pos);
		//スピード設定
		pEnemyType3->SetSpeed(fSpeed);
		//ライフ設定
		pEnemyType3->SetLife(nLife);
		//サイズ設定
		pEnemyType3->SetSize(D3DXVECTOR3(TYPE1_SIZE / 2.0f, TYPE1_SIZE / 2.0f, 0.0f));
		//スコア設定
		pEnemyType3->SetScore(TYPE1_SCORE);
		//テクスチャセット
		pEnemyType3->BindTexture(m_TextureData.m_Texture);
		//初期化処理
		pEnemyType3->Init();
	}
	return pEnemyType3;
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemyType3::Update(void)
{
	//攻撃処理
	Bullet();

	CEnemyBase::Update();
}
