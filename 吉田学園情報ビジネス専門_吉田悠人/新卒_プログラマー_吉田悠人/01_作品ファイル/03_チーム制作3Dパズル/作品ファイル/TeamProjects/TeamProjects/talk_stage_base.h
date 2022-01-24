//=============================================================================
//
//	トーク処理ベース [talk_stage_base.h]
//	Author : 吉田 悠人
//
//=============================================================================

//二重インクルード防止
#ifndef _TALK_STAGE_BASE_H_
#define _TALK_STAGE_BASE_H_

//====================================
//インクルード
//====================================
#include "main.h"
#include "object.h"

//====================================
// クラス定義
//====================================
class CTalkStageBese :public CObject
{
public:
	CTalkStageBese(int nPriorit = PRIORITY_UI_0);
	virtual HRESULT Init(void);
	virtual void	Uninit(void);
	virtual void	Update(void);
	virtual void	Draw(void);

	void		SetPos(D3DXVECTOR3 pos);	//位置セッター
	D3DXVECTOR3	GetPos(void);				//位置ゲッター
	void		SetSize(D3DXVECTOR3 size);	//サイズセッター
	D3DXVECTOR3	Getsize(void);				//サイズゲッター

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
};
#endif // !_UI_H_
