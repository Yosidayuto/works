//=============================================================================
//
// ボスデリートエフェクト3処理 [delete effect3.h]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "delete effect3.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_TEXTURE		(90)	//最大テクスチャのコマ数
#define MAX_ANIME_COUNT (2)		//最大アニメーションカウンタ
#define LOOP_SWITCH		(false)	//ループするか
//=============================================================================
//静的メンバー変数
//=============================================================================
TEXTURE_DATA CDeleteEffect3::m_TextureData = { NULL,"data/TEXTURE/DeleteEffect_2.png" };

//=============================================================================
// コンストラクト
//=============================================================================
CDeleteEffect3::CDeleteEffect3()
{
}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CDeleteEffect3::Load(void)
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
void CDeleteEffect3::Unload(void)
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
CDeleteEffect3 * CDeleteEffect3::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	CDeleteEffect3* pDeleteEffect3 = NULL;
	pDeleteEffect3 = new CDeleteEffect3;

	//NULLチェック
	if (pDeleteEffect3 != NULL)
	{
		//位置セット
		pDeleteEffect3->SetPos(pos);
		//サイズセット
		pDeleteEffect3->SetSize(size);
		//テクスチャの設定
		pDeleteEffect3->BindTexture(m_TextureData.m_Texture);
		//初期化処理
		pDeleteEffect3->Init();
		//最大テクスチャのコマ数セット
		pDeleteEffect3->SetMaxTexture(MAX_TEXTURE);
		//最大アニメーションカウンタセット
		pDeleteEffect3->SetCountAnime(MAX_ANIME_COUNT);
		//ループ設定セット
		pDeleteEffect3->SetLoop(LOOP_SWITCH);

		return pDeleteEffect3;
	}
	return NULL;
}

