//=============================================================================
//
// セレクトのマウスポインター [select pointer.cpp]
// Author : 吉田悠人
//
//=============================================================================
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "select pointer.h"
#include "inputmouse.h"
#include "manager.h"
#include "renderer.h"
//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CSelectPointer::m_TextureData = { NULL,"data/TEXTURE/MousePointer_Select.png", };

//=============================================================================
// コンストラクタ
//=============================================================================
CSelectPointer::CSelectPointer()
{
}


//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CSelectPointer::Load(void)
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
void CSelectPointer::Unload(void)
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
CSelectPointer * CSelectPointer::Create(void)
{
	//メモリ確保
	CSelectPointer* pSelectPointer = NULL;
	pSelectPointer = new CSelectPointer;

	//NULLチェック
	if (pSelectPointer != NULL)
	{
		//テクスチャ設定
		pSelectPointer->BindTexture(m_TextureData.m_Texture);
		//初期化処理
		pSelectPointer->Init();

	}
	
	return pSelectPointer;
}

//=============================================================================
// 更新処理
//=============================================================================
void CSelectPointer::Update(void)
{
	//マウスポインタ移動処理
	MouseMove();

	CPointer::Update();
}

