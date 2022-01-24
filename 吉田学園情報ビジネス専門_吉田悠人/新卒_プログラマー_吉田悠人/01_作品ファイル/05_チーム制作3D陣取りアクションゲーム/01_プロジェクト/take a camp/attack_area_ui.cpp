//=============================================================================
//
// 攻撃範囲UIの処理 [attack_area_ui.cpp]
// Author : 増澤未来
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "attack_area_ui.h"
#include "resource_texture.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define LEVEL_CHANGE_COUNT (100)
#define SIZE	(D3DXVECTOR3(1260.0f,1944,0.0f)/5.5f)
#define COLOR	(D3DXCOLOR(1.0f,1.0f,1.0f,0.9f))
#define TEX_ANIM_MAX_U		(3)                       // 順位テクスチャ分割数*縦
#define FADE_MINUS_VALUE	(0.03f)					// フェード時減算値
#define FADE_ADD_VALUE		(FADE_MINUS_VALUE/2.0f) // フェード時減算値
//=============================================================================
// コンストラクタ
//=============================================================================
CAttackAreaUi::CAttackAreaUi() :CScene2d(OBJTYPE_UI_2)
{
	m_nLevel = 0;
	m_nCharaType = CResourceCharacter::CHARACTER_KNIGHT;
	m_bDraw = false;
	m_nCntLevel = 0;
	ZeroMemory(&m_apTex, sizeof(m_apTex));
    m_FadeMode = FADE_NONE;
}

//=============================================================================
// デストラクタ
//=============================================================================
CAttackAreaUi::~CAttackAreaUi()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CAttackAreaUi * CAttackAreaUi::Create(D3DXVECTOR3 pos)
{
	// メモリの確保
	CAttackAreaUi *pPointa;
	pPointa = new CAttackAreaUi;
	// 初期化
	pPointa->Init();

	// 各値の代入
	pPointa->SetPos(pos);

	return pPointa;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CAttackAreaUi::Init(void)
{
	// 初期化処理
	CScene2d::Init();

	// 初期化
	m_nLevel = 0;
	m_nCharaType = CResourceCharacter::CHARACTER_KNIGHT;
	m_bDraw = false;
	m_nCntLevel = 0;

	// 騎士
    m_apTex[CResourceCharacter::CHARACTER_KNIGHT] = CResourceTexture::GetTexture(CResourceTexture::TEXTURE_ATTACK_AREA_KNIGHT);
	// 槍
    m_apTex[CResourceCharacter::CHARACTER_LANCER] = CResourceTexture::GetTexture(CResourceTexture::TEXTURE_ATTACK_AREA_LANCER);
	// 魔法
    m_apTex[CResourceCharacter::CHARACTER_WIZARD] = CResourceTexture::GetTexture(CResourceTexture::TEXTURE_ATTACK_AREA_WIZARD);
	// 盗賊
    m_apTex[CResourceCharacter::CHARACTER_THIEF] = CResourceTexture::GetTexture(CResourceTexture::TEXTURE_ATTACK_AREA_THIEF);
	// 奇術師
    m_apTex[CResourceCharacter::CHARACTER_MAGICIAN] = CResourceTexture::GetTexture(CResourceTexture::TEXTURE_ATTACK_AREA_MAGICIAN);
	// 弓
    m_apTex[CResourceCharacter::CHARACTER_ARCHER] = CResourceTexture::GetTexture(CResourceTexture::TEXTURE_ATTACK_AREA_ARCHER);

    float fU = 1.0f / TEX_ANIM_MAX_U;

	//UV設定
    D3DXVECTOR2 uv[NUM_VERTEX];
    uv[0] = D3DXVECTOR2(fU*0.0f, 0.0f);
    uv[1] = D3DXVECTOR2(fU*0.0f + fU, 0.0f);
    uv[2] = D3DXVECTOR2(fU*0.0f, 1.0f);
    uv[3] = D3DXVECTOR2(fU*0.0f + fU, 1.0f);
    SetTextureUV(uv);

	SetSize(SIZE);
	SetColor(COLOR);

    m_FadeMode = FADE_NONE;
	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CAttackAreaUi::Update(void)
{
    if (m_FadeMode == FADE_NONE)
    {
        // カウントを進める
        m_nCntLevel++;
        if (m_nCntLevel > LEVEL_CHANGE_COUNT)
        {
            // カウントの初期化
            m_nCntLevel = 0;

            m_FadeMode = FADE_OUT;
           

            if (m_nCharaType == CResourceCharacter::CHARACTER_NONE) return;
        }
    }
    else
    {
        // フェードインアウトの処理
        Fade();
    }
}

//=============================================================================
// 描画処理
//=============================================================================
void CAttackAreaUi::Draw(void)
{
	// 描画処理
	if(m_bDraw) CScene2d::Draw();
}

//=============================================================================
// リセット
//=============================================================================
void CAttackAreaUi::Reset(void)
{
	// カウントの初期化
	m_nLevel = 0;
    m_nCntLevel = 0;

    SetColor(COLOR);
    m_FadeMode = FADE_NONE;

    // テクスチャの切り替え
    BindTexture(m_apTex[m_nCharaType]);

    // テクスチャアニメーション
    float fU = 1.0f / TEX_ANIM_MAX_U;
    D3DXVECTOR2 uv[NUM_VERTEX];
    uv[0] = D3DXVECTOR2(fU*m_nLevel, 0.0f);
    uv[1] = D3DXVECTOR2(fU*m_nLevel + fU, 0.0f);
    uv[2] = D3DXVECTOR2(fU*m_nLevel, 1.0f);
    uv[3] = D3DXVECTOR2(fU*m_nLevel + fU, 1.0f);
    SetTextureUV(uv);
}

void CAttackAreaUi::Fade(void)
{
    if (m_FadeMode == FADE_OUT)
    {
        // アルファ地の減算
        D3DXCOLOR col = GetColor();
        col.a -= FADE_MINUS_VALUE;
        SetColor(col);

        if (col.a < 0.0f)
        {
            // レベルを進める
            m_nLevel++;
            if (m_nLevel >= (MAX_ATTACK_LEVEL - 1))
            {
                m_nLevel = 0;
            }

            // テクスチャアニメーション
            float fU = 1.0f / TEX_ANIM_MAX_U;
            D3DXVECTOR2 uv[NUM_VERTEX];
            uv[0] = D3DXVECTOR2(fU*m_nLevel, 0.0f);
            uv[1] = D3DXVECTOR2(fU*m_nLevel + fU, 0.0f);
            uv[2] = D3DXVECTOR2(fU*m_nLevel, 1.0f);
            uv[3] = D3DXVECTOR2(fU*m_nLevel + fU, 1.0f);
            SetTextureUV(uv);

            m_FadeMode = FADE_IN;
        }
    }
    else if (m_FadeMode == FADE_IN)
    {
        // アルファ地の減算
        D3DXCOLOR col = GetColor();
        col.a += FADE_ADD_VALUE;
        SetColor(col);

        if (col.a > COLOR.a)
        {
            SetColor(COLOR);
            m_FadeMode = FADE_NONE;
        }
    }
}
