//=============================================================================
//
// ボスエフェクト1処理 [boss effect1.h]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "boss effect1.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_TEXTURE		(45)	//最大テクスチャのコマ数
#define MAX_ANIME_COUNT (2)		//最大アニメーションカウンタ
#define LOOP_SWITCH		(true)	//ループするか
//=============================================================================
//静的メンバー変数
//=============================================================================
TEXTURE_DATA CBossEffectType1::m_TextureData = { NULL,"data/TEXTURE/BossAnime_0.png" };

//=============================================================================
// コンストラクト
//=============================================================================
CBossEffectType1::CBossEffectType1()
{
}


//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CBossEffectType1::Load(void)
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
void CBossEffectType1::Unload(void)
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
CBossEffectType1 * CBossEffectType1::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	CBossEffectType1* pBossEffectType1 = NULL;
	pBossEffectType1 = new CBossEffectType1;
	
	//NULLチェック
	if (pBossEffectType1!=NULL)
	{
		//位置セット
		pBossEffectType1->SetPos(pos);
		//サイズセット
		pBossEffectType1->SetSize(size);
		//テクスチャの設定
		pBossEffectType1->BindTexture(m_TextureData.m_Texture);
		//初期化処理
		pBossEffectType1->Init();
		//最大テクスチャのコマ数セット
		pBossEffectType1->SetMaxTexture(MAX_TEXTURE);
		//最大アニメーションカウンタセット
		pBossEffectType1->SetCountAnime(MAX_ANIME_COUNT);
		//ループ設定セット
		pBossEffectType1->SetLoop(LOOP_SWITCH);

	}
	return pBossEffectType1;
}

