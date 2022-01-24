//=============================================================================
//
// ボスエフェクト2処理 [boss effect2.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "boss effect2.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_TEXTURE		(50)	//最大テクスチャのコマ数
#define MAX_ANIME_COUNT (2)		//最大アニメーションカウンタ
#define LOOP_SWITCH		(true)	//ループするか
//=============================================================================
//静的メンバー変数
//=============================================================================
TEXTURE_DATA CBossEffectType2::m_TextureData = { NULL,"data/TEXTURE/BossAnime_1.png" };

//=============================================================================
// コンストラクト
//=============================================================================
CBossEffectType2::CBossEffectType2()
{
}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CBossEffectType2::Load(void)
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
void CBossEffectType2::Unload(void)
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
CBossEffectType2 * CBossEffectType2::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	CBossEffectType2* pBossEffectType2 = NULL;
	pBossEffectType2 = new CBossEffectType2;

	//NULLチェック
	if (pBossEffectType2 != NULL)
	{
		//位置セット
		pBossEffectType2->SetPos(pos);
		//サイズセット
		pBossEffectType2->SetSize(size);
		//テクスチャの設定
		pBossEffectType2->BindTexture(m_TextureData.m_Texture);
		//初期化処理
		pBossEffectType2->Init();
		//最大テクスチャのコマ数セット
		pBossEffectType2->SetMaxTexture(MAX_TEXTURE);
		//最大アニメーションカウンタセット
		pBossEffectType2->SetCountAnime(MAX_ANIME_COUNT);
		//ループ設定セット
		pBossEffectType2->SetLoop(LOOP_SWITCH);

		return pBossEffectType2;
	}
	return NULL;
}
