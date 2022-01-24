//=============================================================================
//
//	ボタン [button.h]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "button.h"
#include "renderer.h"
#include "manager.h"
#include "select.h"
#include "inputmouse.h"
#include "scene2d.h"
#include "telop.h"
//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CButton::m_TextureData[BUTTON_STATE_MAX] =
{	NULL,"data/TEXTURE/buttonA.png",
	NULL,"data/TEXTURE/buttonC_over.png"};

//=============================================================================
// コンストラクタ
//=============================================================================
CButton::CButton(int nPriorit)
{
	m_pScene2d = NULL;
}


//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CButton::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	for (int nCountBotton = 0; nCountBotton<BUTTON_STATE_MAX; nCountBotton++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			m_TextureData[nCountBotton].m_cFileName,
			&m_TextureData[nCountBotton].m_Texture);
	}

	return S_OK;
}

//=============================================================================
// テクスチャの破棄
//=============================================================================
void CButton::Unload(void)
{
	for (int nCountBotton = 0; nCountBotton < BUTTON_STATE_MAX; nCountBotton++)
	{
		//テクスチャの破棄
		if (m_TextureData[nCountBotton].m_Texture != NULL)
		{
			m_TextureData[nCountBotton].m_Texture->Release();
			m_TextureData[nCountBotton].m_Texture = NULL;
		}
	}
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CButton::Init(void)
{
	//位置設定
	D3DXVECTOR3 pos = D3DXVECTOR3(GetPos().x, GetPos().y, GetPos().z);
	//サイズ設定
	D3DXVECTOR3 size = D3DXVECTOR3(GetSize().x, GetSize().y, GetSize().z);

	m_pScene2d = CScene2d::Create(pos, size,0.0f, m_TextureData[BUTTON_STATE_NORMAL].m_Texture,1);
	//オブジェクト2D初期化
	CScene2d::Init();
	return S_OK;
}


//=============================================================================
// 当たり判定処理
//=============================================================================
bool CButton::Hit(void)
{
	//マウスポインタ取得
	CInihMouse *pMouse = CManager::GetMouse();	
	//マウス位置取得
	D3DXVECTOR3 MousePos = D3DXVECTOR3((float)pMouse->GetMousePos().x, (float)pMouse->GetMousePos().y, 0.0f);
	//ボタン位置取得
	D3DXVECTOR3 ButtonPos = m_pScene2d->GetPos();
	//ボタンサイズ取得
	D3DXVECTOR3 ButtonSize = m_pScene2d->GetSize();
	//当たり判定
	if (MousePos.x > ButtonPos.x - ButtonSize.x / 2
		&& MousePos.x  < ButtonPos.x + ButtonSize.x / 2
		&& MousePos.y > ButtonPos.y - ButtonSize.y / 2
		&& MousePos.y < ButtonPos.y + ButtonSize.y / 2)
	{
		//マウスオーバー処理
		MouseOver();
		//プッシュ処理
		Push();
		//当たったらボタン変換
		m_pScene2d->BindTexture(m_TextureData[BUTTON_STATE_PUSH].m_Texture);
		return true;
	}

	//当たってないときボタン
	m_pScene2d->BindTexture(m_TextureData[BUTTON_STATE_NORMAL].m_Texture);
	return false;
}
