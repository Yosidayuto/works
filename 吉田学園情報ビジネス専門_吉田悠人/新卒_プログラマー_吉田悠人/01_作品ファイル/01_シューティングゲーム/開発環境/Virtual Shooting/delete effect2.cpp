//=============================================================================
//
// ボスデリートエフェクト2処理 [delete effect2.h]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "delete effect2.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_TEXTURE		(60)	//最大テクスチャのコマ数
#define MAX_ANIME_COUNT (3)		//最大アニメーションカウンタ
#define LOOP_SWITCH		(false)	//ループするか
//=============================================================================
//静的メンバー変数
//=============================================================================
TEXTURE_DATA CDeleteEffect2::m_TextureData = { NULL,"data/TEXTURE/DeleteEffect_1.png" };

//=============================================================================
// コンストラクト
//=============================================================================
CDeleteEffect2::CDeleteEffect2()
{
}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CDeleteEffect2::Load(void)
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
void CDeleteEffect2::Unload(void)
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
CDeleteEffect2 * CDeleteEffect2::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	CDeleteEffect2* pDeleteEffect2 = NULL;
	pDeleteEffect2 = new CDeleteEffect2;

	//NULLチェック
	if (pDeleteEffect2 != NULL)
	{
		//位置セット
		pDeleteEffect2->SetPos(pos);
		//サイズセット
		pDeleteEffect2->SetSize(size);
		//テクスチャの設定
		pDeleteEffect2->BindTexture(m_TextureData.m_Texture);
		//初期化処理
		pDeleteEffect2->Init();
		//最大テクスチャのコマ数セット
		pDeleteEffect2->SetMaxTexture(MAX_TEXTURE);
		//最大アニメーションカウンタセット
		pDeleteEffect2->SetCountAnime(MAX_ANIME_COUNT);
		//ループ設定セット
		pDeleteEffect2->SetLoop(LOOP_SWITCH);

		return pDeleteEffect2;
	}
	return NULL;
}
