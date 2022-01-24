//=============================================================================
//
// エネミータイプ1処理 [enemy type4.cpp]
// Author : 吉田悠人
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "enemy type4.h"
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
TEXTURE_DATA CEnemyType4::m_TextureData = { NULL,"data/TEXTURE/Enemy_4.png" };
//=============================================================================
// コンストラクト
//=============================================================================
CEnemyType4::CEnemyType4(int nPriorit)
{
}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CEnemyType4::Load(void)
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
void CEnemyType4::Unload(void)
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
CEnemyType4 * CEnemyType4::Create(ENEMY_MOVE_PATTERN MoveType, ENEMY_ATTACK_PATTERN AttackType, int nInTime, int nActionTime, int nAttacTime, int nReturnTime, D3DXVECTOR3 pos, float fSpeed, int nLife)
{
	//メモリ確保
	CEnemyType4* pEnemyType4 = NULL;
	pEnemyType4 = new CEnemyType4;

	//NULLチェック
	if (pEnemyType4 != NULL)
	{
		//行動パターン
		pEnemyType4->SetMovePattern(MoveType);
		//攻撃パターン
		pEnemyType4->SetAttackPattern(AttackType);
		//出現時間
		pEnemyType4->SetInTime(nInTime);
		//行動時間
		pEnemyType4->SetActionTime(nActionTime);
		//攻撃までの時間設定
		pEnemyType4->SetAttackTime(nAttacTime);
		//帰還までの時間設定
		pEnemyType4->SetOutTime(nReturnTime);
		//位置設定
		pEnemyType4->SetPos(pos);
		//スピード設定
		pEnemyType4->SetSpeed(fSpeed);
		//ライフ設定
		pEnemyType4->SetLife(nLife);
		//サイズ設定
		pEnemyType4->SetSize(D3DXVECTOR3(TYPE1_SIZE / 2.0f, TYPE1_SIZE / 2.0f, 0.0f));
		//スコア設定
		pEnemyType4->SetScore(TYPE1_SCORE);
		//テクスチャセット
		pEnemyType4->BindTexture(m_TextureData.m_Texture);
		//初期化処理
		pEnemyType4->Init();

	}
	return pEnemyType4;
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemyType4::Update(void)
{
	//攻撃処理
	Bullet();

	CEnemyBase::Update();
}

