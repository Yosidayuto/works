//=============================================================================
//
// エフェクト用寿司処理 [effect sushi.h]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "effect sushi.h"
#include "resource manager.h"
#include "renderer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CEffectSushi::CEffectSushi(int nPriority):CScene2d(nPriority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CEffectSushi::~CEffectSushi()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CEffectSushi * CEffectSushi::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size, int nType)
{
	//メモリ確保
	CEffectSushi *pEffectSushi = nullptr;
	pEffectSushi = new CEffectSushi;

	//リソース確保(リソースマネージャーから呼び出す)
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 		Texture = pResource->TextureLoad(pEffectSushi->m_nEffectSushiTexture[nType]);

	//NULLチェック
	if (pEffectSushi != nullptr)
	{
		pEffectSushi->BindTexture(Texture);
		pEffectSushi->SetPos(Pos);
		pEffectSushi->SetSize(Size);
		pEffectSushi->Init();
	}
	return pEffectSushi;

}

//=============================================================================
// 描画処理関数
//=============================================================================
void CEffectSushi::Draw(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスにレンダラーのデバイスを代入
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//Zバッファを切る
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	//アルファテストを有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//アルファテスト基準値の設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	//アルファテストの比較方法の設定
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	
	//描画処理
	CScene2d::Draw();

	//アルファテストを無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//Zバッファをつける
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

}


