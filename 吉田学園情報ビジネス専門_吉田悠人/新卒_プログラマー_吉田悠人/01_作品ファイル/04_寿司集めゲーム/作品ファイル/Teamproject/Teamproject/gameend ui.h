//=============================================================================
//
// 制限時間通知の処理 [gameend ui.h]
// Author : 林川紗梨夏
//
//=============================================================================
#ifndef _GAME_END_UI_H_
#define _GAME_END_UI_H_

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
class CGameEndUi : public CScene2d
{
public:
	CGameEndUi(int nPriority = 8);
	~CGameEndUi();
	static CGameEndUi *Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size);
	static CGameEndUi *Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Move, D3DXVECTOR3 Size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	D3DXVECTOR3				m_move;			//移動量
	int                     m_nPatternAnim;	//アニメーションパターン
	int                     m_nCountAnim;	//アニメーションパターン
	int                     m_nTexture = 59;//テクスチャ番号
};
#endif // !_MAP_H_


