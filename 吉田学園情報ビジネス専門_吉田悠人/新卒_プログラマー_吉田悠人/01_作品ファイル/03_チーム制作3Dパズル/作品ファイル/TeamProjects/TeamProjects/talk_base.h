//=============================================================================
//
//	セリフ親クラス[talk_bass.h]
//	Author:吉田　悠人
//
//=============================================================================

// 二重インクルード防止
#ifndef _TALK_BASS_H_
#define _TALK_BASS_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "ui.h"

//=============================================================================
// クラス定義
//=============================================================================
class CTalkbase :public CUi
{
public:

	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX
	}TALK_FADE;

	CTalkbase(int nPriorit = PRIORITY_UI_0);	// コンストラクタ

	HRESULT		Init(void);				// 初期化処理
	void		Update(void);			// 更新処理

	virtual void Talk(void);			// トークを次に進める関数
	void		Blackout(void);			// フェードイン・アウトの処理

	void		SetAppear(int nAppear);			// 出現時間セッター
	int			GetAppear(void);				// 出現時間ゲッター
	void		SetFade(TALK_FADE FadeStatus);	// フェード状態セッター
	TALK_FADE	GetFade(void);					// フェード状態ゲッター
	bool		GetTalkEnd(void);				// 終了しているか

private:
	D3DXCOLOR		m_col;			// カラー
	bool			m_bTalkEnd;		// 終了しているか
	int				m_nAppear;		// 出現時間

protected:
	TALK_FADE					m_Fade;					// 文字の透過状況
	int							m_nTalkCount;			// 処理までのカウント

};
#endif
