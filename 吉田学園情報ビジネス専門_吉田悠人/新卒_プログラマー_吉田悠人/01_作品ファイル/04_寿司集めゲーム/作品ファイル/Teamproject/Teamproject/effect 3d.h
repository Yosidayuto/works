//=============================================================================
//
// エフェクト処理 [effect.h]
// Author : 林川紗梨夏
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "billboard.h"
#include "player.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_EFFECT	"Data/TEXTURE/EFFECT/effect.png"
//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CEffect : public CBillboard
{
public:
	CEffect(int nPriority = 7);
	~CEffect();
	static CEffect *Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Move, D3DXVECTOR3 Size, D3DXCOLOR col, int nLife,int TexNum);
	static CEffect *Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Move, D3DXVECTOR3 Size, D3DXCOLOR col, int nLife, int TexNum,CPlayer * pPlayer);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetLife(int nLife);
private:
	static LPDIRECT3DTEXTURE9   m_apTexture;
	D3DXVECTOR3					m_Move;
	int							m_nLife;
	CPlayer *                   m_pPlayer;
};
#endif