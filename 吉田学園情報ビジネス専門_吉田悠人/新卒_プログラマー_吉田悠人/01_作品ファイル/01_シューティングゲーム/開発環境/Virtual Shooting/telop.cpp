//=============================================================================
//
//	テロップ[telop.h]
//	Author:吉田　悠人
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "telop.h"
#include "scene2d.h"
#include "manager.h"
#include "renderer.h"
#include "telop tutorial.h"
#include "telop life.h"
#include "telop speed.h"
#include "telop bullet.h"
#include "telop laser.h"
#include "telop homing.h"

//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CTelop::m_TextureData = {NULL,"data/TEXTURE/Telop.png" };

//=============================================================================
// コンストラクト
//=============================================================================
CTelop::CTelop(int nPriorit) :CScene2d(nPriorit)
{
	//タイプ処理
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);
	m_pTelop = NULL;
	m_TelopType = TELOP_TYPE_TUTORIAL;
}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CTelop::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, 
		m_TextureData.m_cFileName, 
		&m_TextureData.m_Texture);
	//テロップロード
	TelopLoad();
	return S_OK;
}

//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CTelop::Unload(void)
{
	//テクスチャの破棄
	if (m_TextureData.m_Texture != NULL)
	{
		m_TextureData.m_Texture->Release();
		m_TextureData.m_Texture = NULL;
	}
	//テロップアンロード
	TelopUnload();
}

//=============================================================================
//生成処理
//=============================================================================
CTelop * CTelop::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	CTelop *pTelopBer = NULL;
	pTelopBer = new CTelop;
	
	//NULLチェック
	if (pTelopBer != NULL)
	{
		//位置
		pTelopBer->SetPos(D3DXVECTOR3(SCREEN_WIDTH - 425, 25, 0.0f));
		//サイズ
		pTelopBer->SetSize(D3DXVECTOR3(850, 50, 0.0f));
		//テクスチャ設定
		pTelopBer->BindTexture(m_TextureData.m_Texture);
		//初期化処理
		pTelopBer->Init();

	}
	return pTelopBer;
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CTelop::Init(void)
{
	//初期化処理
	CScene2d::Init();
	//テロップ生成
	m_pTelop = CTelopTutorial::Create(GetPos(), GetSize());
	return S_OK;
}

//=============================================================================
// テロップ切替処理
//=============================================================================
TELOP_TYPE CTelop::GetTelopType(void)
{
	return m_TelopType;
}

//=============================================================================
// テロップ切替処理
//=============================================================================
void CTelop::TypeChange(TELOP_TYPE Type)
{
	//現在のテロップ終了処理
	if (m_pTelop!=NULL)
	{
		m_pTelop->Uninit();
		m_pTelop = NULL;
	}

	//タイプ変更
	m_TelopType = Type;

	//テロップ生成
	switch (m_TelopType)
	{
	case TELOP_TYPE_TUTORIAL:
		m_pTelop = CTelopTutorial::Create(GetPos(), GetSize());
		break;
	case TELOP_TYPE_LIFEUP:
		m_pTelop = CTelopLife::Create(GetPos(),GetSize());
		break;
	case TELOP_TYPE_SPEEDUP:
		m_pTelop = CTelopSpeed::Create(GetPos(), GetSize());
		break;
	case TELOP_TYPE_BUTTOL:
		m_pTelop = CTelopBullet::Create(GetPos(), GetSize());
		break;
	case TELOP_TYPE_LASER:
		m_pTelop = CTelopLaser::Create(GetPos(), GetSize());
		break;
	case TELOP_TYPE_HOMING:
		m_pTelop = CTelopHoming::Create(GetPos(), GetSize());
		break;
	}
}
//=============================================================================
// テロップロード処理
//=============================================================================
void CTelop::TelopLoad(void)
{
	CTelopTutorial::Load();
	CTelopLife::Load();
	CTelopSpeed::Load();
	CTelopBullet::Load();
	CTelopLaser::Load();
	CTelopHoming::Load();
}

//=============================================================================
// テロップアンロード処理
//=============================================================================
void CTelop::TelopUnload(void)
{
	CTelopTutorial::Unload();
	CTelopLife::Unload();
	CTelopSpeed::Unload();
	CTelopBullet::Unload();
	CTelopLaser::Unload();
	CTelopHoming::Unload();
}
