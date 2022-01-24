//=============================================================================
//
// ボスエフェクトベース処理 [boss effect base.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "boss effect base.h"
#include "boss effect1.h"
#include "boss effect2.h"
#include "boss effect3.h"
#include "delete effect1.h"
#include "delete effect2.h"
#include "delete effect3.h"

//=============================================================================
// コンストラクト
//=============================================================================
CBossEffectBase::CBossEffectBase(int nPriorit):CScene2d(nPriorit)
{
	m_nMaxCount			= 0;
	m_nMaxCountAnime	= 0;
	m_nCounterAnim		= 0;
	m_nPatternAnimX		= 0;
	m_bLoop				= false;
	//タイプ処理
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);
}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CBossEffectBase::Load(void)
{
	CBossEffectType1::Load();
	CBossEffectType2::Load();
	CBossEffectType3::Load();
	CDeleteEffect1::Load();
	CDeleteEffect2::Load();
	CDeleteEffect3::Load();

	return S_OK;
}
//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CBossEffectBase::Unload(void)
{
	CBossEffectType1::Unload();
	CBossEffectType2::Unload();
	CBossEffectType3::Unload();
	CDeleteEffect1::Unload();
	CDeleteEffect2::Unload();
	CDeleteEffect3::Unload();
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBossEffectBase::Init(void)
{
	//テクスチャ用
	D3DXVECTOR2 Texture[4];
	//初期化処理
	CScene2d::Init();
	//テクスチャ設定
	Texture[0] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)m_nMaxCount), 0.0f);
	Texture[1] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)m_nMaxCount) + (1.0f / (float)m_nMaxCount), 0.0f);
	Texture[2] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)m_nMaxCount), 1.0f);
	Texture[3] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)m_nMaxCount) + (1.0f / (float)m_nMaxCount), 1.0f);
	//テクスチャアニメ設定
	TextureAnim(Texture);
	
	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CBossEffectBase::Update(void)
{
	//テクスチャ用
	D3DXVECTOR2 Texture[4];

	//テクスチャ設定
	Texture[0] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)m_nMaxCount), 0.0f);
	Texture[1] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)m_nMaxCount) + (1.0f / (float)m_nMaxCount), 0.0f);
	Texture[2] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)m_nMaxCount), 1.0f);
	Texture[3] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)m_nMaxCount) + (1.0f / (float)m_nMaxCount), 1.0f);

	//テクスチャアニメ設定
	TextureAnim(Texture);
	//アニメーションカウント
	m_nCounterAnim++;
	if (m_nCounterAnim >= m_nMaxCountAnime)
	{
		//アニメーションの絵を次の絵に変える
		m_nCounterAnim = 0;
		m_nPatternAnimX++;
		if (m_nPatternAnimX == m_nMaxCount)
		{
			m_nPatternAnimX = 0;
			if (m_bLoop == false)
			{
				Uninit();
				return;
			}
		}
	}

	CScene2d::Update();
}


//=============================================================================
// テクスチャの最大コマ数セッター
//=============================================================================
void CBossEffectBase::SetMaxTexture(int nMaxTexture)
{
	m_nMaxCount = nMaxTexture;
}

//=============================================================================
// テクスチャの最大コマ数ゲッター
//=============================================================================
int CBossEffectBase::GetMaxTexture(void)
{
	return m_nMaxCount;
}

//=============================================================================
// アニメーションカウントセッター
//=============================================================================
void CBossEffectBase::SetCountAnime(int nCountAnime)
{
	m_nMaxCountAnime = nCountAnime;
}

//=============================================================================
// アニメーションカウンタゲッター
//=============================================================================
int CBossEffectBase::GetCountAnime(void)
{
	return m_nMaxCountAnime;
}

//=============================================================================
// ループゲッター
//=============================================================================
void CBossEffectBase::SetLoop(bool bLoop)
{
	m_bLoop = bLoop;
}

//=============================================================================
// ループセッター
//=============================================================================
bool CBossEffectBase::GetLoop(void)
{
	return m_bLoop;
}
