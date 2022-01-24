//=============================================================================
//
// ボスエフェクト3処理 [boss effect3.h]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "boss effect3.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_TEXTURE		(60)	//最大テクスチャのコマ数
#define MAX_ANIME_COUNT (2)		//最大アニメーションカウンタ
#define LOOP_SWITCH		(true)	//ループするか
//=============================================================================
//静的メンバー変数
//=============================================================================
TEXTURE_DATA CBossEffectType3::m_TextureData = { NULL,"data/TEXTURE/BossAnime_2.png" };

//=============================================================================
// コンストラクト
//=============================================================================
CBossEffectType3::CBossEffectType3()
{
}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CBossEffectType3::Load(void)
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
void CBossEffectType3::Unload(void)
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
CBossEffectType3 * CBossEffectType3::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	CBossEffectType3* pBossEffectType3 = NULL;
	pBossEffectType3 = new CBossEffectType3;

	//NULLチェック
	if (pBossEffectType3 != NULL)
	{
		//位置セット
		pBossEffectType3->SetPos(pos);
		//サイズセット
		pBossEffectType3->SetSize(size);
		//テクスチャの設定
		pBossEffectType3->BindTexture(m_TextureData.m_Texture);

		//初期化処理
		pBossEffectType3->Init();
		//最大テクスチャのコマ数セット
		pBossEffectType3->SetMaxTexture(MAX_TEXTURE);
		//最大アニメーションカウンタセット
		pBossEffectType3->SetCountAnime(MAX_ANIME_COUNT);
		//ループ設定セット
		pBossEffectType3->SetLoop(LOOP_SWITCH);

		return pBossEffectType3;
	}
	return NULL;
}

