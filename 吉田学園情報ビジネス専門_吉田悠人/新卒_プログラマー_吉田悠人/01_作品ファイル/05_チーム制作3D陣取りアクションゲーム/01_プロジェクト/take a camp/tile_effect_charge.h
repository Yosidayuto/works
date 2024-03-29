//=============================================================================
//
// tile_effect_chargewb_ [tile_effect_charge.h]
// Author : ΰV ’
//
//=============================================================================

//ρdCN[hh~
#ifndef _TILE_EFFECT_CHARGE_H_
#define _TILE_EFFECT_CHARGE_H_

//*****************************
//CN[h
//*****************************
#include "tile_effect.h"

//*****************************
//OϋιΎ
//*****************************
class CScene3d;

//*****************************
//NXθ`
//*****************************

//UΝΝΜΒ»
class CTileEffectCharge : public CTileEffect
{
public:
	// oΦ
	CTileEffectCharge();
	~CTileEffectCharge();
	static CTileEffectCharge *Create(void);
	HRESULT Init(void);
	void Update(void);
	void Uninit(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos);
private:
	CScene3d* m_pPolygon;
};


#endif