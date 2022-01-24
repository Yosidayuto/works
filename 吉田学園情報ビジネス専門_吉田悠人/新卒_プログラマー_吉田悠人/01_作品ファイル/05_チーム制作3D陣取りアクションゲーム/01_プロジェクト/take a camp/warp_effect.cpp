//=============================================================================
//
// ワープエフェクト [warp_effect.cpp]
// Author : 吉田 悠人
//
//=============================================================================

//*****************************
// インクルード
//*****************************
#include "warp_effect.h"
#include "glitter_effect.h"
#include <time.h>
//******************************
// マクロ定義
//******************************
#define EFFECT_RANGE (D3DXVECTOR3(10.0f,10.0f,10.0f))
#define EFFECT_SPEED (12.0f)

//******************************
// コンストラクタ
//******************************
CWarpEffect::CWarpEffect()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_GoalPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	nCreateCount = 0;
}

//******************************
// デストラクタ
//******************************
CWarpEffect::~CWarpEffect()
{

}

//******************************
// クラス生成
//******************************
void CWarpEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 GoalPos, D3DXCOLOR col)
{
	//メモリ確保
	CWarpEffect* pWarpEffect = nullptr;
	pWarpEffect = new CWarpEffect;

	//NULLチェック
	if (pWarpEffect != nullptr)
	{

		//位置設定
		pWarpEffect->m_pos = pos;
		//目的地設定
		pWarpEffect->m_GoalPos = GoalPos;
		//色設定
		pWarpEffect->m_col = col;
		//初期化処理
		pWarpEffect->Init();

	}
}

//******************************
// 初期化処理
//******************************
HRESULT CWarpEffect::Init(void)
{
	//ランダム関数の初期化
	srand((unsigned int)time(NULL));

	//移動量を計算
	D3DXVec3Normalize(&m_move, &(m_GoalPos - m_pos));
	m_move = m_move * EFFECT_SPEED;

	//カウント生成
	nCreateCount = rand() % 1;

	return S_OK;
}

//******************************
// 終了処理
//******************************
void CWarpEffect::Uninit(void)
{
	//オブジェクトの破棄
	Release();
}

//******************************
// 更新処理
//******************************
void CWarpEffect::Update(void)
{
	//位置更新
	m_pos = m_pos + m_move;

	//エフェクトの生成
	CreateEffect();

	//目的地についたか
	if (pow(m_pos.x - m_GoalPos.x, 2) +
		pow(m_pos.y - m_GoalPos.y, 2) + 
		pow(m_pos.z - m_GoalPos.z, 2) <= pow(5 + 5, 2))
	{
		//終了処理
		Uninit();
	}
}

//******************************
// 描画処理
//******************************
void CWarpEffect::Draw(void)
{
}

//******************************
// エフェクト生成処理
//******************************
void CWarpEffect::CreateEffect(void)
{
	nCreateCount--;

	if (nCreateCount<0)
	{

		int nXpos, nZpos;
		nXpos = (rand() % (int)(EFFECT_RANGE.x*2.0f))-(int)EFFECT_RANGE.x;
		nZpos = (rand() % (int)(EFFECT_RANGE.z*2.0f))-(int)EFFECT_RANGE.z;

		CGlitter::Create(D3DXVECTOR3(m_pos.x + nXpos, m_pos.y+15.0f, m_pos.z + nZpos), 40, m_col);

		nCreateCount = rand() % 2;
	}
}
