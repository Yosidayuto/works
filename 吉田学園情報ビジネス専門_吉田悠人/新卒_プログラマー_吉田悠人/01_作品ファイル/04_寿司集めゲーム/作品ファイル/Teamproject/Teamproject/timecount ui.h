//=============================================================================
//
// 制限時間通知の処理 [timecount ui.h]
// Author : 林川紗梨夏
//
//=============================================================================
#ifndef _TIME_COUNT_UI_H_
#define _TIME_COUNT_UI_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene2d.h"


//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTimecountUi : public CScene2d
{
public:
	CTimecountUi(int nPriority = 8);
	~CTimecountUi();
	static CTimecountUi *Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size);
	static CTimecountUi *Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Move, D3DXVECTOR3 Size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	D3DXVECTOR3				m_move;			//移動量
	int                     m_nPatternAnim;	//アニメーションパターン
	int                     m_nCountAnim;	//アニメーションパターン
	int                     m_nTexture = 58;//テクスチャ番号
};
#endif // !_MAP_H_


