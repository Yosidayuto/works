//=============================================================================
//
//	背景[bg.h]
//	Author:吉田　悠人
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "bg.h"
#include "scene2d.h"
//=============================================================================
// コンストラクタ
//=============================================================================
CBgc::CBgc(int nPriorit):CScene2d(nPriorit)
{
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
}

//=============================================================================
// スクロールY方向関数
//=============================================================================
void CBgc::ScrollY(float fScroll)
{
	D3DXVECTOR2 Texture[4];
	Texture[0] = D3DXVECTOR2(0.0f, ((float)-m_nPatternAnim * fScroll)*(1.0f / 1.0f));
	Texture[1] = D3DXVECTOR2(1.0f, ((float)-m_nPatternAnim * fScroll)*(1.0f / 1.0f));
	Texture[2] = D3DXVECTOR2(0.0f, ((float)-m_nPatternAnim * fScroll)*(1.0f / 1.0f) + (1.0f / 1.0f));
	Texture[3] = D3DXVECTOR2(1.0f, ((float)-m_nPatternAnim * fScroll)*(1.0f / 1.0f) + (1.0f / 1.0f));
	
	//アニメーションカウント
	m_nCounterAnim++;
	if (m_nCounterAnim % 2)
	{
		//アニメーションの絵を次の絵に変える
		m_nPatternAnim++;

		m_nCounterAnim = 0;
		if (m_nPatternAnim >= (1.0f/ fScroll))
		{
			m_nPatternAnim = 0;
		}
	}
	TextureAnim(Texture);
}

//=============================================================================
// スクロールX方向関数
//=============================================================================
void CBgc::ScrollX(float fScroll)
{
	D3DXVECTOR2 Texture[4];
	Texture[0] = D3DXVECTOR2(0.0f, ((float)-m_nPatternAnim * fScroll)*(1.0f / 1.0f));
	Texture[1] = D3DXVECTOR2(1.0f, ((float)-m_nPatternAnim * fScroll)*(1.0f / 1.0f));
	Texture[2] = D3DXVECTOR2(0.0f, ((float)-m_nPatternAnim * fScroll)*(1.0f / 1.0f) + (1.0f / 1.0f));
	Texture[3] = D3DXVECTOR2(1.0f, ((float)-m_nPatternAnim * fScroll)*(1.0f / 1.0f) + (1.0f / 1.0f));

	//アニメーションカウント
	m_nCounterAnim++;
	if (m_nCounterAnim % 2)
	{
		//アニメーションの絵を次の絵に変える
		m_nPatternAnim++;

		m_nCounterAnim = 0;
		if (m_nPatternAnim >= (1.0f / fScroll))
		{
			m_nPatternAnim = 0;
		}
	}
	TextureAnim(Texture);

}
