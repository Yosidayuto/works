//=============================================================================
//
// 円筒エフェクト処理 [effect_cylinder.cpp]
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
#include "Effect powerup.h"
#include "player.h"
#include "resource manager.h"
#include "effect 3d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COLOR (D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f))
#define CIRCLE_SIZE (D3DXVECTOR3(30.0f,30.0f,30.0f))
#define ARROW_SIZE (D3DXVECTOR3(10.0f,10.0f,10.0f))
#define COLOR_VALUE (20)//ランダム色の範囲（大きくなればなるほど色の種類が多くなる
#define POS_VALUE (20)
//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CEffectPowerUP::CEffectPowerUP(int nPriority): CScene3d(nPriority)
{
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pPlayer = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CEffectPowerUP::~CEffectPowerUP()
{
}

CEffectPowerUP * CEffectPowerUP::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size, CPlayer * pPlayer)
{
	CEffectPowerUP * pEffectPowerUP;
	pEffectPowerUP = new CEffectPowerUP;
	if (pEffectPowerUP != NULL)
	{
		pEffectPowerUP->m_pPlayer = pPlayer;
		pEffectPowerUP->SetPos(Pos);
		pEffectPowerUP->SetSize(Size);
		pEffectPowerUP->Init();
	}
	return pEffectPowerUP;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CEffectPowerUP::Init(void)
{

	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CEffectPowerUP::Uninit(void)
{
	Release();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CEffectPowerUP::Update(void)
{
	
	m_nTime++;
	//プレイヤーの位置取得
	D3DXVECTOR3 pos = m_pPlayer->GetPos();
	//プレイヤーの位置に合わせてセット
	SetPos(D3DXVECTOR3(pos.x, pos.y + 30.0f, pos.z));

	//円形エフェクト
	if (m_nTime % 10 == 0)
	{
		CEffect::Create(GetPos(), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CIRCLE_SIZE, COLOR, 80, 56,m_pPlayer);
	}
	//矢印エフェクト
	if (m_nTime % 15 == 0)
	{
		srand(m_nTime);
		float r, g, b;
		r = float(rand() % COLOR_VALUE) / float(COLOR_VALUE);
		g = float(rand() % COLOR_VALUE) / float(COLOR_VALUE);
		b = float(rand() % COLOR_VALUE) / float(COLOR_VALUE);
		float x, z;
		x = float(rand() % POS_VALUE) + float(-POS_VALUE /2);
		z = float(rand() % POS_VALUE) + float(-POS_VALUE / 2);
		CEffect::Create(D3DXVECTOR3(GetPos().x + x, GetPos().y  + 5.0f , GetPos().z + z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ARROW_SIZE, D3DXCOLOR(r, g, b, 1.0f), 40, 57);
	}
	//矢印エフェクト
	if (m_nTime % 17 == 0)
	{
		srand(m_nTime);
		float r, g, b;
		r = float(rand() % COLOR_VALUE) / float(COLOR_VALUE);
		g = float(rand() % COLOR_VALUE) / float(COLOR_VALUE);
		b = float(rand() % COLOR_VALUE) / float(COLOR_VALUE);
		float x, z;
		x = float(rand() % POS_VALUE) + float(-POS_VALUE / 2);
		z = float(rand() % POS_VALUE) + float(-POS_VALUE / 2);
		CEffect::Create(D3DXVECTOR3(GetPos().x + x, GetPos().y + 5.0f, GetPos().z + z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ARROW_SIZE, D3DXCOLOR(r, g, b, 1.0f), 30, 57);
	}

	//プレイヤーの状況に合わせて消失
	if (m_pPlayer->GetScoreUp() == false)
	{
		Uninit();
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CEffectPowerUP::Draw(void)
{
}