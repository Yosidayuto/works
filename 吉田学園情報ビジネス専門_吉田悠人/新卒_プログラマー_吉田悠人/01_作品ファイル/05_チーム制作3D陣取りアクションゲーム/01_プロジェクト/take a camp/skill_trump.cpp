//=============================================================================
//
// スキルトランプエフェクト 処理 [skill_trump.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "skill_trump.h"
#include <time.h>
#include "resource_texture.h"

//*****************************
//マクロ定義
//*****************************
#define TRUMP_SPEED (0.5f)	//エフェクトのスピード

//=============================================================================
//コンストラクタ
//=============================================================================
CSkillTrump::CSkillTrump(int nPliority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_ColCount = 0;
	m_MoveAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bDeath = false;
}

//===================================
// デストラクタ
//===================================
CSkillTrump::~CSkillTrump()
{
}

//===================================
// 生成処理関数
//===================================
CSkillTrump * CSkillTrump::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 MoveAngle, const D3DXCOLOR col)
{
	CSkillTrump* pSkillTrump = nullptr;
	pSkillTrump = new CSkillTrump;

	//NULLチェック
	if (pSkillTrump != nullptr)
	{
		//移動角度設定
		pSkillTrump->m_MoveAngle = MoveAngle;

		//初期化処理
		pSkillTrump->Init();

		//位置設定
		pSkillTrump->SetPos(pos);
		//大きさ設定
		pSkillTrump->SetSize(size);
		//色設定
		pSkillTrump->SetColor(col);
	}

	return pSkillTrump;
}

//===================================
// 初期化処理
//===================================
HRESULT CSkillTrump::Init(void)
{
	//ビルボードの初期化処理
	CBillboard::Init();

	//テクスチャ設定
	BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_PARTICLE_TRUMP));

	//ランダムに角度を決める(マックス360度)
	float fAngle = (float)(rand() % 360);
	SetAngle(D3DXToRadian(fAngle));

	//回る方向を決める
	AnglePattern = (ANGLE_PATTERN)(rand() % MAX_ANGLE);

	//移動量設定	
	float fMoveX = TRUMP_SPEED*cosf(m_MoveAngle.z)*cosf(m_MoveAngle.y);
	float fMoveY = TRUMP_SPEED*sinf(m_MoveAngle.z)*2.0f;
	float fMoveZ = TRUMP_SPEED*cosf(m_MoveAngle.z)*-sinf(m_MoveAngle.y);
	m_move = D3DXVECTOR3(fMoveX, fMoveY, fMoveZ);

	return S_OK;
}

//===================================
// 更新処理
//===================================
void CSkillTrump::Update(void)
{
	//角度変更処理
	AngleChange();
	//位置変更処理
	PosChange();

	//死亡フラグが立っているか
	if (m_bDeath)
	{
		//終了処理
		Uninit();
	}
}


//===================================
// 向きの変化処理
//===================================
void CSkillTrump::AngleChange(void)
{
	//角度取得
	float fAngle = GetAngle();
	if (AnglePattern== RIGHT_ANGLE)
	{
		//少しずつ角度を変える
		fAngle--;
	}
	else if (AnglePattern == LEFT_ANGLE)
	{
		//少しずつ角度を変える
		fAngle++;
	}
	//角度セット
	SetAngle(fAngle);
}

//===================================
// 位置の変化処理
//===================================
void CSkillTrump::PosChange(void)
{
	SetPos(GetPos()+m_move);
	// 移動量の変異;
	m_move.y -= (2.0f - m_move.y)*0.035f;

	//一定の位置に来ると
	if (GetPos().y <= -5.0f)
	{
		//死亡フラグを立てる
		m_bDeath = true;
	}
}
