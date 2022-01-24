//=============================================================================
//
// スキルアローエフェクト 処理 [skill_arrow.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "resource_texture.h"
#include "skill_arrow.h"
#include "skill_aroow_line.h"
#include "tile.h"
//******************************
// マクロ定義
//******************************
#define ARROW_SIZE	(D3DXVECTOR3(3.0f,4.0f,0.0f))	// エフェクトのサイズ
#define ARROW_SPPED (10.0f)							// エフェクトスピード

//=============================================================================
//コンストラクタ
//=============================================================================
CSkillArrow::CSkillArrow(int nPliority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bDeath = false;
	m_nTile = 0;
}

//===================================
// デストラクタ
//===================================
CSkillArrow::~CSkillArrow()
{
}

//===================================
// 生成処理関数
//===================================
CSkillArrow * CSkillArrow::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const float fAngle, int nTile, const D3DXCOLOR col )
{
	CSkillArrow* pSkillArrow = nullptr;
	pSkillArrow = new CSkillArrow;
	
	//NULLチェック
	if (pSkillArrow != nullptr)
	{
		//初期化処理
		pSkillArrow->Init();
		//位置設定
		pSkillArrow->SetPos(pos);
		pSkillArrow->m_StartPos = pos;
		//向き設定
		pSkillArrow->SetAngle(fAngle);
		//カラー設定
		pSkillArrow->SetColor(col);
		//ライフ設定
		pSkillArrow->m_nTile = nTile;
		//移動量設定
		pSkillArrow->m_move = move;
	}

	return pSkillArrow;
}

//===================================
// 初期化処理
//===================================
HRESULT CSkillArrow::Init(void)
{
	//ビルボードの初期化処理
	CBillboard::Init();
	//サイズ設定
	SetSize(ARROW_SIZE);
	return S_OK;
}

//===================================
// 更新処理
//===================================
void CSkillArrow::Update(void)
{
	CSkillArrowLine::Create(GetPos(), GetAngle(),GetColor());

	PosChange();
	//移動した距離を求める
	D3DXVECTOR3 move = GetPos() - m_StartPos;
	//ベクトルの大きさの取得
	float fdistance = hypotf(move.x, move.z);

	//どれだけ移動したか
	if ((int)fdistance>m_nTile * TILE_ONE_SIDE)
	{
		//ライフの初期化
		m_nTile = 0;
		//終了処理
		Uninit();
	}

	//死亡フラグが立っているか
	if (m_bDeath)
	{
		//終了処理
		Uninit();
	}

}

//===================================
// 位置の変化処理
//===================================
void CSkillArrow::PosChange(void)
{
	D3DXVECTOR3 pos = GetPos();
	//位置変更
	SetPos(pos + m_move);
}
