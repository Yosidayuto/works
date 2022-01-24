//=============================================================================
//
// フィールド端のポリゴン（マスクするがわ）の処理 [MapEdgeMask.cpp]
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
#include "MapEdgeMaskOut.h"
#include "MapEdgeOverlay.h"
#include "resource manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CMapEdgeMaskOut::CMapEdgeMaskOut(int nPriority) : CPolygon3d(nPriority)
{
	m_nPatternAnim = 0;
	m_nCountAnim = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CMapEdgeMaskOut::~CMapEdgeMaskOut()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CMapEdgeMaskOut * CMapEdgeMaskOut::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	CMapEdgeMaskOut *pFloor;

	pFloor = new CMapEdgeMaskOut;
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
HRESULT CMapEdgeMaskOut::Init(void)
{
	//リソース確保
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(m_nTexture);

	SetObjType(CScene::OBJTYPE_NONE);

	CPolygon3d::Init();

	//テクスチャセット
	D3DXVECTOR2 Tex[NUM_VERTEX];
	Tex[0] = D3DXVECTOR2(0.0f, 0.0f);
	Tex[1] = D3DXVECTOR2(1.0f, 0.0f);
	Tex[2] = D3DXVECTOR2(0.0f, 1.0f);
	Tex[3] = D3DXVECTOR2(1.0f, 1.0f);
	SetTexture(Tex);

	SetRot(D3DXVECTOR3(D3DXToRadian(-90.0f), D3DXToRadian(0.0f), D3DXToRadian(90.0f)));
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	BindTexture(Texture);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMapEdgeMaskOut::Uninit(void)
{
	CPolygon3d::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMapEdgeMaskOut::Update(void)
{
	CPolygon3d::Update();
	//テクスチャセット
	D3DXVECTOR2 Tex[NUM_VERTEX];
	Tex[0] = D3DXVECTOR2(0.0f, 0.0f);
	Tex[1] = D3DXVECTOR2(1.0f, 0.0f);
	Tex[2] = D3DXVECTOR2(0.0f, 1.0f);
	Tex[3] = D3DXVECTOR2(1.0f, 1.0f);
	SetTexture(Tex);
}

//=============================================================================
// 描画処理
//=============================================================================
void CMapEdgeMaskOut::Draw(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスにレンダラーのデバイスを代入
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//アルファテストの設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)0x00000001);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	//深度テストの設定(必ず不合格にする)
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);
	//ステンシルテストを有効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	//ステンシルバッファへ書き込む参照値設定
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);

	//ステンシルバッファに書き込む条件
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	// ステンシルテストのテスト設定
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_REPLACE);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
	CPolygon3d::Draw();

	//ステンシルテストを無効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}