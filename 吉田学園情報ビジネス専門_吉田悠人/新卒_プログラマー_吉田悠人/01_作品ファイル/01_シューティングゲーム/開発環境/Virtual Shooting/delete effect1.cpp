//=============================================================================
//
// ボスデリートエフェクト1処理 [delete effect1.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "delete effect1.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_TEXTURE		(45)	//最大テクスチャのコマ数
#define MAX_ANIME_COUNT (2)		//最大アニメーションカウンタ
#define LOOP_SWITCH		(false)	//ループするか
//=============================================================================
//静的メンバー変数
//=============================================================================
TEXTURE_DATA CDeleteEffect1::m_TextureData = { NULL,"data/TEXTURE/DeleteEffect_0.png" };

//=============================================================================
// コンストラクト
//=============================================================================
CDeleteEffect1::CDeleteEffect1()
{
}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CDeleteEffect1::Load(void)
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
void CDeleteEffect1::Unload(void)
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
CDeleteEffect1 * CDeleteEffect1::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	CDeleteEffect1* pDeleteEffect1 = NULL;
	pDeleteEffect1 = new CDeleteEffect1;

	//NULLチェック
	if (pDeleteEffect1 != NULL)
	{
		//位置セット
		pDeleteEffect1->SetPos(pos);
		//サイズセット
		pDeleteEffect1->SetSize(size);
		//テクスチャの設定
		pDeleteEffect1->BindTexture(m_TextureData.m_Texture);
		//初期化処理
		pDeleteEffect1->Init();
		//最大テクスチャのコマ数セット
		pDeleteEffect1->SetMaxTexture(MAX_TEXTURE);
		//最大アニメーションカウンタセット
		pDeleteEffect1->SetCountAnime(MAX_ANIME_COUNT);
		//ループ設定セット
		pDeleteEffect1->SetLoop(LOOP_SWITCH);

		return pDeleteEffect1;
	}
	return NULL;
}