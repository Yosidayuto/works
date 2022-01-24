//=============================================================================
//
// プレイヤー現在位置の処理[locationpoint.cpp]
// Author : 林川紗梨夏
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "locationpoint.h"
#include "resource manager.h"

//*****************************************************************************
// 静的メンバ変数初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CLocationPoint::CLocationPoint(int nPriority) : CScene2d(nPriority)
{
	m_nPatternAnim = 1;
	m_nCountAnim = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CLocationPoint::~CLocationPoint()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CLocationPoint * CLocationPoint::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size, int number)
{
	CLocationPoint *pLocationPoint = nullptr;

	pLocationPoint = new CLocationPoint;
	if (pLocationPoint != nullptr)
	{
		//リソース確保(リソースマネージャーから呼び出す)
		CResource* pResource = CManager::GetResource();
		LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pLocationPoint->m_nTexture);
		pLocationPoint->BindTexture(Texture);
		pLocationPoint->m_nPlayerNum = number;
		pLocationPoint->SetPos(Pos);
		pLocationPoint->SetSize(Size);
		pLocationPoint->Init();
	}
	return pLocationPoint;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLocationPoint::Init(void)
{
	SetObjType(CScene::OBJTYPE_NONE);

	CScene2d::Init();

	//テクスチャセット
	D3DXVECTOR2 Tex[NUM_VERTEX];
	Tex[0] = D3DXVECTOR2(m_nPlayerNum * 0.25f, 0.0f);
	Tex[1] = D3DXVECTOR2(m_nPlayerNum * 0.25f + 0.25f, 0.0f);
	Tex[2] = D3DXVECTOR2(m_nPlayerNum * 0.25f, 1.0f);
	Tex[3] = D3DXVECTOR2(m_nPlayerNum * 0.25f + 0.25f, 1.0f);
	SetTexture(Tex);
	//頂点カラーセット
	SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	return S_OK;
}


//=============================================================================
// 更新処理
//=============================================================================
void CLocationPoint::Update(void)
{
	CScene2d::Update();

	//テクスチャセット
	D3DXVECTOR2 Tex[NUM_VERTEX];
	Tex[0] = D3DXVECTOR2(m_nPlayerNum * 0.25f, 0.0f);
	Tex[1] = D3DXVECTOR2(m_nPlayerNum * 0.25f + 0.25f, 0.0f);
	Tex[2] = D3DXVECTOR2(m_nPlayerNum * 0.25f, 1.0f);
	Tex[3] = D3DXVECTOR2(m_nPlayerNum * 0.25f + 0.25f, 1.0f);
	SetTexture(Tex);

	//頂点カラーセット
	SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
}

