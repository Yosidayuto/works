//=============================================================================
//
// ボスタイプ3処理 [boss type3.cpp]
// Author : 吉田悠人
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "boss type3.h"
#include "manager.h"
#include "renderer.h"
#include "boss effect3.h"
#include "delete effect3.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define BOSS_TYPE3_SIZE		(500.0f)	//サイズ
#define BOSS_TYPE3_LIFE		(225)		//ライフ
#define BOSS_TYPE3_SCORE	(10000)		//スコア
#define BOSS_TYPE3_COOLTIME	(300)		//攻撃のクールタイム
//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CBossType3::m_TextureData = { NULL,"data/TEXTURE/Boss_3.png", };
//=============================================================================
// コンストラクト
//=============================================================================
CBossType3::CBossType3(int nPriorit)
{
}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CBossType3::Load(void)
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
void CBossType3::Unload(void)
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
CBossType3 * CBossType3::Create(D3DXVECTOR3 pos)
{
	//メモリ確保
	CBossType3* pBossType3 = NULL;
	pBossType3 = new CBossType3;

	//NULLチェック
	if (pBossType3 != NULL)
	{
		//位置設定
		pBossType3->SetPos(pos);
		//サイズ設定
		pBossType3->SetSize(D3DXVECTOR3(BOSS_TYPE3_SIZE / 2.0f, BOSS_TYPE3_SIZE / 2.0f, 0.0f));
		//ライフ設定
		pBossType3->SetLife(BOSS_TYPE3_LIFE);
		//スコア設定
		pBossType3->SetScore(BOSS_TYPE3_SCORE);
		//攻撃のクールタイム設定
		pBossType3->SetCoolTime(BOSS_TYPE3_COOLTIME);
		//テクスチャセット
		pBossType3->BindTexture(m_TextureData.m_Texture);
		//初期化処理
		pBossType3->Init();

	}
	return pBossType3;
}

//=============================================================================
// 更新処理
//=============================================================================
void CBossType3::Update(void)
{
	//攻撃処理
	Bullet();
	CBossBase::Update();
}

//=============================================================================
// エフェクト生成
//=============================================================================
void CBossType3::Effect(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//サイズ取得
	D3DXVECTOR3 size = GetSize();

	//エフェクト生成
	m_Effect = CBossEffectType3::Create(pos, size);
}

//=============================================================================
// 描画処理
//=============================================================================
void CBossType3::DisEffect(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//サイズ取得
	D3DXVECTOR3 size = GetSize();

	//エフェクト終了処理
	if (m_Effect != NULL)
	{
		m_Effect->Uninit();
	}

	//やられたときのエフェクト生成
	CDeleteEffect3::Create(pos, D3DXVECTOR3(STAGE_SIZE, size.y, 0.0f));
}
