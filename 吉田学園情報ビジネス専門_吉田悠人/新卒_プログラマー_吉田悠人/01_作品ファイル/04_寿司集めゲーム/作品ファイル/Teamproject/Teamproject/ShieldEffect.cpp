//=============================================================================
//
// シールドエフェクトの処理 [ShieldEffect.cpp]
// Author : 齋藤大行
//
//=============================================================================

//=============================================================================
// ヘッダーファイル
//=============================================================================
#include "ShieldEffect.h"
#include "resource manager.h"
#include "player.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CShieldEffect::CShieldEffect(int nPriority) :CBillboard(nPriority)
{
	SetObjType(CScene::OBJTYPE_NONE);	//タイプ設定
}

//=============================================================================
// デストラクタ
//=============================================================================
CShieldEffect::~CShieldEffect()
{
}

//=============================================================================
// 生成関数
//=============================================================================
CShieldEffect * CShieldEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR Col, CPlayer* pPlayer)
{
	// メモリ確保
	CShieldEffect *pShieldEffect = NULL;
	pShieldEffect = new CShieldEffect;

	//リソースデータ取得
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pShieldEffect->m_nTexture);

	//NULLチェック
	if (pShieldEffect != NULL)
	{
		pShieldEffect->SetPos(pos);				// 位置設定
		pShieldEffect->SetSize(size);			// サイズ設定
		pShieldEffect->SetColor(Col);			// カラー設定
		pShieldEffect->BindTexture(Texture);	// テクスチャ設定
		pShieldEffect->m_pPlayer = pPlayer;		// プレイヤーポインタ取得
		pShieldEffect->Init();					// 初期化処理
	}

	return pShieldEffect;
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CShieldEffect::Update(void)
{
	//プレイヤーの位置取得
	D3DXVECTOR3 pos = m_pPlayer->GetPos();
	//プレイヤーの位置に合わせてセット
	SetPos(D3DXVECTOR3(pos.x, pos.y + 13.0f, pos.z));

	//プレイヤーの状況に合わせて消失
	if (m_pPlayer->GetShield() == false)
	{
		CShieldEffect::Uninit();
	}
}
