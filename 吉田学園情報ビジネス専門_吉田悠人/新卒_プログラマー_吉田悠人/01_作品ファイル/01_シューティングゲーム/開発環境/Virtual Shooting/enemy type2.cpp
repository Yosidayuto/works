//=============================================================================
//
// エネミータイプ2処理 [enemy type2.cpp]
// Author : 吉田悠人
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "enemy type2.h"
#include "manager.h"
#include "renderer.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define TYPE1_SIZE	(100.0f)	//サイズ
#define TYPE1_LIFE	(2)		//ライフ
#define TYPE1_SCORE (100)	//スコア
//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CEnemyType2::m_TextureData = { NULL,"data/TEXTURE/Enemy_2.png", };
//=============================================================================
// コンストラクト
//=============================================================================
CEnemyType2::CEnemyType2(int nPriorit)
{
}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CEnemyType2::Load(void)
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
void CEnemyType2::Unload(void)
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
CEnemyType2 * CEnemyType2::Create(ENEMY_MOVE_PATTERN MoveType, ENEMY_ATTACK_PATTERN AttackType, int nInTime, int nActionTime, int nAttacTime, int nReturnTime, D3DXVECTOR3 pos, float fSpeed, int nLife)
{
	//メモリ確保
	CEnemyType2* pEnemyType2 = NULL;
	pEnemyType2 = new CEnemyType2;

	//NULLチェック
	if (pEnemyType2 != NULL)
	{
		//行動パターン
		pEnemyType2->SetMovePattern(MoveType);
		//攻撃パターン
		pEnemyType2->SetAttackPattern(AttackType);
		//出現時間
		pEnemyType2->SetInTime(nInTime);
		//行動時間
		pEnemyType2->SetActionTime(nActionTime);
		//攻撃までの時間設定
		pEnemyType2->SetAttackTime(nAttacTime);
		//帰還までの時間設定
		pEnemyType2->SetOutTime(nReturnTime);
		//位置設定
		pEnemyType2->SetPos(pos);
		//スピード設定
		pEnemyType2->SetSpeed(fSpeed);
		//ライフ設定
		pEnemyType2->SetLife(nLife);
		//サイズ設定
		pEnemyType2->SetSize(D3DXVECTOR3(TYPE1_SIZE / 2.0f, TYPE1_SIZE / 2.0f, 0.0f));
		//スコア設定
		pEnemyType2->SetScore(TYPE1_SCORE);
		//テクスチャセット
		pEnemyType2->BindTexture(m_TextureData.m_Texture);
		//初期化処理
		pEnemyType2->Init();

	}
	return pEnemyType2;
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemyType2::Update(void)
{
	//回転処理
	Rotate();
	//攻撃処理
	Bullet();
	CEnemyBase::Update();
}
