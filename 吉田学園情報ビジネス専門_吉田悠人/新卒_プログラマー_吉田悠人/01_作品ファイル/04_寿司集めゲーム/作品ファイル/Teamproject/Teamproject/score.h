//=============================================================================
//
// スコア処理 [score.h]
// Author : 林川紗梨夏
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "number.h"
#include "scene2d.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_DIGITS (5) //最大桁数
#define SCORE_SIZE_WIDTH (60.0f)
#define SCORE_SIZE_HEIGHT (100.0f)
#define SCORE_POS (D3DXVECTOR3(SCREEN_WIDTH / 2 + SCORE_SIZE_WIDTH,80.0f,0.0f))
#define SCORE_SIZE (D3DXVECTOR3(50.0f,80.0f,0.0f))
//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CScore : public CScene
{
public:

	CScore(int nPriority = 8);
	~CScore();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScore * Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size);
	void SetScore(int nScore);
	void AddScore(int nValue);
	int GetScore(void) { return m_nScore; }

private:
	CNumber                           *m_apNumber[MAX_DIGITS];//ナンバー（最大桁数分）
	D3DXVECTOR3                        m_Pos;
	D3DXVECTOR3                        m_Size;
	int                                m_nScore; //スコアの数値
};
#endif // !_SCORE_H_
