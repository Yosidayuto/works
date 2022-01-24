//=============================================================================
//
// エフェクト処理 [effect.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "renderer.h"	
#include "manager.h"	
#include "effect.h"
//=============================================================================
//マクロ定義
//=============================================================================
#define EFFECT_LIFE (8)		//バレットの射程距離

//=============================================================================
//静的メンバー変数
//=============================================================================
TEXTURE_DATA CEffect::m_TextureData[EFFECT_TYPE_MAX] =
{ {NULL,"data/TEXTURE/Bullet.png"},
{ NULL,	"data/TEXTURE/Laser.png"} };

//=============================================================================
//コンストラクタ
//=============================================================================
CEffect::CEffect(int nPriorit):CScene2d(nPriorit)
{
	m_nLife = 0;
	//タイプ処理
	CScene::SetObjType(CScene::OBJ_TYPE_BULLET);
}

//=============================================================================
// テクスチャロード
//=============================================================================
HRESULT CEffect::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	for (int nCount = 0; nCount < EFFECT_TYPE_MAX; nCount++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, m_TextureData[nCount].m_cFileName, &m_TextureData[nCount].m_Texture);

	}
	return S_OK;
}

//=============================================================================
// テクスチャアンロード
//=============================================================================
void CEffect::Unload(void)
{
	for (int nCount = 0; nCount < EFFECT_TYPE_MAX; nCount++)
	{
		//テクスチャの破棄
		if (m_TextureData[nCount].m_Texture != NULL)
		{
			m_TextureData[nCount].m_Texture->Release();
			m_TextureData[nCount].m_Texture = NULL;
		}
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CEffect * CEffect::Create(D3DXVECTOR3 Pos, D3DXCOLOR col, D3DXVECTOR3 size, EFFECT_TYPE type)
{
	//メモリ確保
	CEffect *pEffect = NULL;
	pEffect = new CEffect;
	
	//NULLチェック
	if (pEffect != NULL)
	{
		//位置セット
		pEffect->SetPos(Pos);
		//サイズセット
		pEffect->SetSize(D3DXVECTOR3(size.x, size.y, 0.0f));
		//タイプセット
		pEffect->m_Type = type;
		//カラーセット
		pEffect->SetCol(col);
		//初期化処理
		pEffect->Init();
	}
	return pEffect;
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CEffect::Init(void)
{
	//射程距離
	m_nLife = EFFECT_LIFE;
	//テクスチャの設定
	BindTexture(m_TextureData[m_Type].m_Texture);
	//初期化処理
	CScene2d::Init();

	return S_OK;
}


//=============================================================================
// 更新処理
//=============================================================================
void CEffect::Update(void)
{
	//エフェクト処理
	Effect();
	//更新処理
	CScene2d::Update();
	//ライフ減少
	LifeDown();
}

//=============================================================================
//描画処理
//=============================================================================
void CEffect::Draw(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	/*レンダリングステート(加算合成処理)*/
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//描画処理
	CScene2d::Draw();

	/*レンダーステート*/
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


}

//=============================================================================
// エフェクト処理
//=============================================================================
void CEffect::Effect(void)
{
	//サイズ
	D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//カラー
	D3DXCOLOR col;

	switch (m_Type)
	{
	case EFFECT_TYPE_BULLET:
		//大きさの取得
		size = GetSize();
		//大きさの処理
		size -= D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		//ポリゴンの大きさを渡す
		SetSize(size);
		break;
	}
	//カラー取得
	col = GetCol();
	//カラー減少
	col = D3DXCOLOR(col.r - 0.05f, col.g - 0.05f, col.b - 0.05f, col.a - 0.05f);
	//カラーセット
	SetCol(col);

}

//=============================================================================
//描画処理
//=============================================================================
void CEffect::LifeDown(void)
{
	//ライフ減少
	m_nLife--;
	//エフェクトの終了処理
	if (m_nLife<=0)
	{
		Uninit();	//終了処理
	}

}
