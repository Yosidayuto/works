//=============================================================================
//
// ゲームのマウスポインター [game pointer.cpp]
// Author : 吉田悠人
//
//=============================================================================
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "game pointer.h"
#include "inputmouse.h"
#include "manager.h"
#include "renderer.h"
//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CGamePointer::m_TextureData = { NULL,"data/TEXTURE/MousePointer_Game.png", };

//=============================================================================
// コンストラクタ
//=============================================================================
CGamePointer::CGamePointer()
{
}


//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CGamePointer::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		m_TextureData.m_cFileName,
		&m_TextureData.m_Texture);

	return S_OK;
}

//=============================================================================
// テクスチャ破棄
//=============================================================================
void CGamePointer::Unload(void)
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
CGamePointer * CGamePointer::Create(void)
{
	//メモリ確保
	CGamePointer* pGamePointer = NULL;
	pGamePointer = new CGamePointer;

	//NULLチェック
	if (pGamePointer != NULL)
	{
		//テクスチャ設定
		pGamePointer->BindTexture(m_TextureData.m_Texture);
		//初期化処理
		pGamePointer->Init();

	}
	return pGamePointer;
}

//=============================================================================
// 更新処理
//=============================================================================
void CGamePointer::Update(void)
{
	//マウスポインタ移動処理
	MouseMove();

	CPointer::Update();
}

