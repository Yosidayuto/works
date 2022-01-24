//=============================================================================
//
// スキルアローラインエフェクト 処理 [skill_arrow_line.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "skill_aroow_line.h"
//*****************************
//マクロ定義
//*****************************
#define ARROW_LINE_SIZE (D3DXVECTOR3(3.0f,3.0f,0.0f))
#define ARROW_LINE_LIFE (30)

//=============================================================================
//コンストラクタ
//=============================================================================
CSkillArrowLine::CSkillArrowLine(int nPliority)
{
	m_nTile = 0;
	m_bDeath = false;
}

//===================================
// デストラクタ
//===================================
CSkillArrowLine::~CSkillArrowLine()
{
}

//===================================
// 生成処理関数
//===================================
CSkillArrowLine * CSkillArrowLine::Create(const D3DXVECTOR3 pos, const float fAngle,const D3DXCOLOR col)
{
	//メモリ確保
	CSkillArrowLine* pSkillArrowLine = nullptr;
	pSkillArrowLine = new CSkillArrowLine;

	//NULLチェック
	if (pSkillArrowLine != nullptr)
	{
		//初期化処理
		pSkillArrowLine->Init();
		//位置設定
		pSkillArrowLine->SetPos(pos);
		//向き設定
		pSkillArrowLine->SetAngle(fAngle);
		//色設定
		pSkillArrowLine->SetColor(col);
	}

	return pSkillArrowLine;
}

//===================================
// 初期化処理
//===================================
HRESULT CSkillArrowLine::Init(void)
{
	//ビルボードの初期化処理
	CBillboard::Init();
	//サイズ設定
	SetSize(ARROW_LINE_SIZE);
	//ライフ設定
	m_nTile = ARROW_LINE_LIFE;
	return S_OK;
}


//===================================
// 更新処理
//===================================
void CSkillArrowLine::Update(void)
{
	D3DXVECTOR3 size = GetSize();
	D3DXCOLOR col = GetColor();
	col.a -= 0.02f;	
	size.x -= 0.01f;
	SetColor(col);
	SetSize(size);

	m_nTile--;

	//0より低くなったら
	if (m_nTile <= 0)
	{
		Uninit();
	}

}

//===================================
// 描画処理
//===================================
void CSkillArrowLine::Draw(void)
{
	//ビルボードの描画処理
	CBillboard::Draw();;
}

