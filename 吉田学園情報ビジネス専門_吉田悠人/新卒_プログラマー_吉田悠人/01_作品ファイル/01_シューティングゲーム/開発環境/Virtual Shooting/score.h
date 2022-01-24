//=============================================================================
//
// スコア処理 [score.h]
// Author : 吉田 悠人
//
//=============================================================================

#ifndef  _SCORE_H_
#define  _SCORE_H_
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_SCORE (8)//スコアパネルの最大数

//=============================================================================
//前方宣言
//=============================================================================
class CUi;
class CNumber;
class CScoreBar;
//=============================================================================
// クラス定義
//=============================================================================
class CScore :public CScene
{
public:
	CScore(int nPriorit = PRIORITY_UI_3);	//コンストラクタ
	~CScore();								//デストラクタ

	static CScore*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,bool UI, PRIORITY priority = PRIORITY_UI_3);	//生成処理


	HRESULT Init(void);		// 初期化処理
	void	Uninit(void);	// 終了処理
	void	Update(void);	// 更新処理
	void	Draw(void);		// 描画処理

	void	SetScore(int nScore);		// スコアセット処理
	void	ColChange(D3DXCOLOR col);	// カラー変更処理
	void	AddScore(int nValue);		// スコア加算処理
	int		GetScore(void);				// スコアゲッター

private:
	bool						UiSwitch;				// 背景をつけるか
	CScoreBar*					m_pScoreBar;			// 背景
	CNumber						*m_apNumber[MAX_SCORE];	// ナンバークラス
	int							m_nScore;				// スコア
	D3DXVECTOR3					m_pos;					// 位置
	D3DXVECTOR3					m_size;					// サイズ
};
#endif