////////////////////////////////////////////////////
//
//    particleクラスの処理[particle.cpp]
//    Author:齋藤大行
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "particle.h"
#include "manager.h"
#include "renderer.h"
#include "resource_texture.h"
#include "skill_effect.h" 
#include "player.h"
//*****************************
// マクロ定義
//*****************************

//******************************
// 静的メンバ変数宣言
//*****************************

//******************************
// コンストラクタ
//******************************
CParticle::CParticle()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_type = PARTICLE_SQUARE;
	m_bFadeoutFlag = true;
	m_fRotAngle = 0.0f;

	m_fFadeout = 0.0f; 
	m_nPattern = 0;
	m_nAnimation = 0;
	m_pPlayer = NULL;
	m_nEffectId = 0;
}

//******************************
// デストラクタ
//******************************
CParticle::~CParticle()
{
}


//*****************************
// 静的メンバ変数宣言
//*****************************


//******************************
// クリエイト
//******************************
CParticle * CParticle::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXVECTOR3 size, const int nLife, const D3DXCOLOR col,const float fadeout, const float fAngle, CPlayer * pPlayer, const PARTICLE_TYPE type)
{
	// メモリの確保
	CParticle *pParticle;
	pParticle = new CParticle;

	// タイプの設定
	pParticle->m_type = type;
	//プレイヤーのポインタ設定
	pParticle->SetPlayer(pPlayer);				
	// 初期化
	pParticle->Init();

	// 各値の代入・セット

	pParticle->m_move = move;                // 移動量
	pParticle->SetSize(size);                // サイズ
	pParticle->m_nLife = nLife;				 // 寿命
	pParticle->SetColor(col);					 // 代入
	pParticle->m_fFadeout = fadeout;		 // フェードアウト
	pParticle->m_fRotAngle = 0.0f;           // 回転角度

	//pParticle->SetAngle((float)(rand() % 360));       // 回転角度をランダム
	pParticle->SetAddMode(false);             // 加算合成
	

	switch (type)
	{
	case PARTICLE_SQUARE:
		pParticle->SetAngle((float)(rand() % 360));       // 回転角度をランダム

		break;

	case PARTICLE_TEARS:
		break;

	case PARTICLE_SHOOT:
		break;

	case PARTICLE_METEOR:
		pParticle->SetAddMode(true); 
	
		break;
	case PARTICLE_METEOR_SHADOW:
		pParticle->SetAddMode(false);
		break;

	case PARTICLE_GURUGURU:
		pParticle->SetAngle((float)(rand() % 360));       // 回転角度をランダム
		break;

	case PARTICLE_SLASH:
		pParticle->SetPos (pos);					      // 初期位置代入
		pParticle->SetAngle((float)(rand() % 360));       // 回転角度をランダム
		pParticle->SetTextureManualUV(TEXTURE_ANIMA_PATTERN, pParticle->m_nPattern);
		break;
		
	case PARTICLE_THUKI:
		pParticle->SetPos(pos);					      // 初期位置代入
		
		pParticle->SetAngle(fAngle);
		pParticle->SetTextureManualUV(TEXTURE_ANIMA_PATTERN, pParticle->m_nPattern);
		break;
		
	default:
		break;
	}
	
	return pParticle;
}

//******************************
// 初期化処理
//******************************
HRESULT CParticle::Init(void)
{

	

	if (FAILED(CBillboard::Init()))
	{
		return E_FAIL;
	}

	m_apTexture[PARTICLE_SQUARE] = CResourceTexture::GetTexture(CResourceTexture::TEXTURE_PARTICLE_SQUARE);
	m_apTexture[PARTICLE_TEARS] = CResourceTexture::GetTexture(CResourceTexture::TEXTURE_PARTICLE_SKILL);
	m_apTexture[PARTICLE_SHOOT] = CResourceTexture::GetTexture(CResourceTexture::TEXTURE_PARTICLE_SHOOT);
	m_apTexture[PARTICLE_METEOR] = CResourceTexture::GetTexture(CResourceTexture::TEXTURE_PARTICLE_METEOR);
	m_apTexture[PARTICLE_METEOR_SHADOW] = CResourceTexture::GetTexture(CResourceTexture::TEXTURE_PARTICLE_METEOR_SHADOW);
	m_apTexture[PARTICLE_GURUGURU] = CResourceTexture::GetTexture(CResourceTexture::TEXTURE_PARTICLE_GURUGURU);
	m_apTexture[PARTICLE_SLASH] = CResourceTexture::GetTexture(CResourceTexture::TEXTURE_PARTICLE_SLASH);
	m_apTexture[PARTICLE_THUKI] = CResourceTexture::GetTexture(CResourceTexture::TEXTURE_PARTICLE_THUKI);
	// テクスチャ割り当て
	BindTexture(m_apTexture[m_type]);

	SetPriority(OBJTYPE_PARTICLE);
	return S_OK;
}

//******************************
// 終了処理
//******************************
void CParticle::Uninit(void)
{
	CBillboard::Uninit();
}

//******************************
// 更新処理
//******************************
void CParticle::Update(void)
{
	CPlayer *pPlayer = GetPlayer();
	D3DXVECTOR3 rot = pPlayer->GetRotDest();
	
	// 移動
	SetPos(GetPos() + m_move);
	m_nAnimation++;

	switch (m_type)
	{
	case PARTICLE_SQUARE:
	{
		D3DXCOLOR col = GetColor();
		col.a -= m_fFadeout;
		SetColor(col);
	}
		break;

	case PARTICLE_TEARS:
		break;

	case PARTICLE_SHOOT:
		break;

	case PARTICLE_METEOR:
	{
		D3DXCOLOR col = GetColor();
		col.a -= m_fFadeout;
		SetColor(col);
	}
		break;

	case PARTICLE_METEOR_SHADOW:
		break;

	case PARTICLE_GURUGURU:
	{
		D3DXCOLOR col = GetColor();
		col.a -= m_fFadeout;
		SetColor(col);
		SetAngle(GetAngle() + m_fRotAngle);
	}
		break;

	case PARTICLE_SLASH:
		if (m_nAnimation >= TEXTURE_ANIMA_LATE)
		{
			SetTextureManualUV(TEXTURE_ANIMA_PATTERN, m_nPattern);
			m_nPattern++;
			m_nAnimation = 0;

			if (m_nEffectId <= EFFECT_MAX)
			{
				if (m_nPattern == TEXTURE_ANIMA_CREATE_POINT)
				{
					CParticle * pPar = CParticle::Create(GetPos(), SLASH_SKIIL_MOVE, GetSize(), m_nLife, GetColor(), 0.05f, D3DXToDegree(pPlayer->GetRotDest().y), pPlayer, CParticle::PARTICLE_SLASH);
					pPar->m_nEffectId = m_nEffectId + 1;
					SetPos(D3DXVECTOR3(GetPos().x + (float)(rand() % 14 - 7), GetPos().y, GetPos().z + (float)(rand() % 14 - 7)));
				}
			}
			if (m_nPattern >= TEXTURE_ANIMA_PATTERN)
			{
				m_bFadeoutFlag = false;
			}
		}
		break;

	case PARTICLE_THUKI:	
			SetPos(GetPos());
		if (m_nAnimation >= TEXTURE_ANIMA_THUKI_LATE)
		{
			SetTextureManualUV(TEXTURE_ANIMA_PATTERN, m_nPattern);
			m_nPattern++;
			m_nAnimation = 0;
		
			if (m_nPattern >= TEXTURE_ANIMA_PATTERN)
			{
				m_bFadeoutFlag = false;
			}

		}
		break;

	default:
		break;
	}

	if (GetColor().a <= 0)
	{
		m_bFadeoutFlag = false;
	}

	if (!m_bFadeoutFlag)
	{
		Uninit();
	}

}
