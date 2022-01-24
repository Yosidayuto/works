//=============================================================================
//
// フィールド端のポリゴン（エリア外がわ）の処理 [MapEdgeOverlay.cpp]
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
#include "polygon3d.h"
#include "MapEdgeOverlay.h"
#include "resource manager.h"
#include "MapEdgeMask.h"

#define MAX_SCROLL (10) // スクロールカウント最大
#define MAX_SCROLL_SPEED (0.001f)//スクロールのスピード
//=============================================================================
// コンストラクタ
//=============================================================================
CMapEdgeOverlay::CMapEdgeOverlay(int nPriority) : CPolygon3d(nPriority)
{
	m_nPatternAnim = 0;
	m_nCountAnim = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CMapEdgeOverlay::~CMapEdgeOverlay()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CMapEdgeOverlay * CMapEdgeOverlay::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	CMapEdgeOverlay *pFloor;

	pFloor = new CMapEdgeOverlay;
	if (pFloor != NULL)
	{
		pFloor->SetPos(Pos);
		pFloor->SetSize(Size);
		pFloor->Init();
	}

	return pFloor;
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMapEdgeOverlay::Init(void)
{
	//リソース確保
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(m_nTexture);

	SetObjType(CScene::OBJTYPE_NONE);
	CPolygon3d::Init();
	
	//テクスチャセット
	D3DXVECTOR2 Tex[NUM_VERTEX];
	Tex[0] = D3DXVECTOR2(m_nCountAnim * 0.001f, m_nCountAnim * 0.001f);
	Tex[1] = D3DXVECTOR2(m_nCountAnim * 0.001f + 0.001f, m_nCountAnim * 0.001f);
	Tex[2] = D3DXVECTOR2(m_nCountAnim * 0.001f, m_nCountAnim * 0.001f + 0.001f);
	Tex[3] = D3DXVECTOR2(m_nCountAnim * 0.001f + 0.001f, m_nCountAnim * 0.001f + 0.001f);
	SetTexture(Tex);

	SetRot(D3DXVECTOR3(D3DXToRadian(-90.0f), D3DXToRadian(90.0f), D3DXToRadian(-90.0f)));
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	BindTexture(Texture);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMapEdgeOverlay::Uninit(void)
{
	CPolygon3d::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMapEdgeOverlay::Update(void)
{
	m_nCountAnim++;
	if (float(m_nCountAnim * MAX_SCROLL_SPEED) > 1.0f)
	{
		m_nCountAnim = 0;
	}

	CPolygon3d::Update();
	//テクスチャセット
	D3DXVECTOR2 Tex[NUM_VERTEX];
	Tex[0] = D3DXVECTOR2(m_nCountAnim * MAX_SCROLL_SPEED, m_nCountAnim * MAX_SCROLL_SPEED);
	Tex[1] = D3DXVECTOR2(5.0f + m_nCountAnim * MAX_SCROLL_SPEED, m_nCountAnim * MAX_SCROLL_SPEED);
	Tex[2] = D3DXVECTOR2(m_nCountAnim * MAX_SCROLL_SPEED, 5.0f + m_nCountAnim * MAX_SCROLL_SPEED);
	Tex[3] = D3DXVECTOR2(5.0f + m_nCountAnim * MAX_SCROLL_SPEED, 5.0f + m_nCountAnim * MAX_SCROLL_SPEED);
	SetTexture(Tex);
}

//=============================================================================
// 描画処理
//=============================================================================
void CMapEdgeOverlay::Draw(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスにレンダラーのデバイスを代入
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//ステンシルテストを有効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	//深度テストの設定
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//ステンシル参照値の設定
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);
	//ステンシルマスクの設定
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_GREATER);
	//ステンシルテストのテスト設定
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
	CPolygon3d::Draw();
	//ステンシルテストを無効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	
}