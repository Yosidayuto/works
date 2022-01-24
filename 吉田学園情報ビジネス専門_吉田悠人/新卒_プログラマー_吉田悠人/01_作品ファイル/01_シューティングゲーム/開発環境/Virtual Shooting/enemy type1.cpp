//=============================================================================
//
// エネミータイプ1処理 [enemy type1.cpp]
// Author : 吉田悠人
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "enemy type1.h"
#include "manager.h"
#include "renderer.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define TYPE1_SIZE	(100.0f)//サイズ
#define TYPE1_LIFE	(2)		//ライフ
#define TYPE1_SCORE (100)	//スコア
#define TYPE1_SPEED (5.5f)	//スピード

//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CEnemyType1::m_TextureData = { NULL,"data/TEXTURE/Enemy_1.png", };
//=============================================================================
// コンストラクト
//=============================================================================
CEnemyType1::CEnemyType1()
{
}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CEnemyType1::Load(void)
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
void CEnemyType1::Unload(void)
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
CEnemyType1 * CEnemyType1::Create(ENEMY_MOVE_PATTERN MoveType,ENEMY_ATTACK_PATTERN AttackType,int nInTime,int nActionTime,int nAttacTime,int nReturnTime,D3DXVECTOR3 pos,float fSpeed,int nLife)						
{
	//メモリ確保
	CEnemyType1* pEnemyType1 = NULL;
	pEnemyType1 = new CEnemyType1;

	//NULLチェック
	if (pEnemyType1 != NULL)
	{
		//行動パターン
		pEnemyType1->SetMovePattern(MoveType);
		//攻撃パターン
		pEnemyType1->SetAttackPattern(AttackType);
		//出現時間
		pEnemyType1->SetInTime(nInTime);
		//行動時間
		pEnemyType1->SetActionTime(nActionTime);
		//攻撃までの時間設定
		pEnemyType1->SetAttackTime(nAttacTime);
		//帰還までの時間設定
		pEnemyType1->SetOutTime(nReturnTime);
		//位置設定
		pEnemyType1->SetPos(pos);
		//スピード設定
		pEnemyType1->SetSpeed(fSpeed);
		//ライフ設定
		pEnemyType1->SetLife(nLife);
		//サイズ設定
		pEnemyType1->SetSize(D3DXVECTOR3(TYPE1_SIZE / 2.0f, TYPE1_SIZE / 2.0f, 0.0f));
		//スコア設定
		pEnemyType1->SetScore(TYPE1_SCORE);
		//テクスチャセット
		pEnemyType1->BindTexture(m_TextureData.m_Texture);
		//初期化処理
		pEnemyType1->Init();
	}
	return pEnemyType1;
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemyType1::Update(void)
{
	//攻撃処理
	Bullet();
	CEnemyBase::Update();
}

