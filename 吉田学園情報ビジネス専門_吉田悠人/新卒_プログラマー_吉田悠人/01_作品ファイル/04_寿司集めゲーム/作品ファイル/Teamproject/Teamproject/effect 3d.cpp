//=============================================================================
//
// エフェクト処理 [effect.h]
// Author : 林川紗梨夏
//
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "effect 3d.h"
#include "resource manager.h"
//****************************************************************************************************
//静的メンバ変数宣言
//****************************************************************************************************
LPDIRECT3DTEXTURE9 CEffect::m_apTexture = nullptr;
//****************************************************************************************************
// コンストラクタ
//****************************************************************************************************
CEffect::CEffect(int nPriority) : CBillboard(nPriority)
{
	m_nLife = 0;
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pPlayer = nullptr;
}
//****************************************************************************************************
// デストラクタ
//****************************************************************************************************
CEffect::~CEffect()
{
}

//****************************************************************************************************
// 生成関数
//****************************************************************************************************
CEffect * CEffect::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Move, D3DXVECTOR3 Size, D3DXCOLOR col, int nLife, int TexNum)
{
	CEffect *pEffect = nullptr;

	pEffect = new CEffect;
	if (pEffect != nullptr)
	{
		//リソース確保(リソースマネージャーから呼び出す)
		CResource* pResource = CManager::GetResource();
		LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(TexNum);
		pEffect->BindTexture(Texture);
		pEffect->SetPos(Pos);
		pEffect->SetSize(Size);
		pEffect->SetColor(col);
		pEffect->m_Move = Move;
		pEffect->m_nLife = nLife;
		pEffect->Init();
	}

	return pEffect;
}

CEffect * CEffect::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Move, D3DXVECTOR3 Size, D3DXCOLOR col, int nLife, int TexNum, CPlayer * pPlayer)
{
	CEffect *pEffect = nullptr;

	pEffect = new CEffect;
	if (pEffect != nullptr)
	{
		//リソース確保(リソースマネージャーから呼び出す)
		CResource* pResource = CManager::GetResource();
		LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(TexNum);
		pEffect->BindTexture(Texture);
		pEffect->SetPos(Pos);
		pEffect->SetSize(Size);
		pEffect->SetColor(col);
		pEffect->m_Move = Move;
		pEffect->m_nLife = nLife;
		pEffect->m_pPlayer = pPlayer;
		pEffect->Init();
	}

	return pEffect;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CEffect::Init(void)
{
	// 初期化
	CBillboard::Init();

	return S_OK;
}
//=============================================================================
// 破棄
//=============================================================================
void CEffect::Uninit(void)
{
	// 終了
	CBillboard::Uninit();
}
//=============================================================================
// 更新
//=============================================================================
void CEffect::Update(void)
{
	// どんどん小さくどんどん透明に
	SetSize(GetSize() - D3DXVECTOR3(GetSize().x / m_nLife, GetSize().y / m_nLife, GetSize().z / m_nLife));
	SetColor(D3DXCOLOR(GetColor().r, GetColor().g, GetColor().b, GetColor().a - (1.0f / m_nLife)));

	m_nLife--;
	

	//一定時間で破棄
	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}
	if (m_pPlayer != nullptr)
	{
		//位置更新
		SetPos(D3DXVECTOR3(m_pPlayer->GetPos().x, GetPos().y, m_pPlayer->GetPos().z) + m_Move);
	}
	else
	{
		//位置更新
		SetPos(GetPos() + m_Move);
	}

	// 更新
	CBillboard::Update();
}
//=============================================================================
// 描画処理
//=============================================================================
void CEffect::Draw(void)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//加算合成
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	// 描画
	CBillboard::Draw();
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

void CEffect::SetLife(int nLife)
{
	m_nLife = nLife;
}
