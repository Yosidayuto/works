//=============================================================================
//
// フェードベース処理 [fade base.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _FADE_BASE_H_
#define _FADE_BASE_H_

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "main.h"
#include "manager.h"
#include "game.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define FADE_RATE	(0.03f)

//=============================================================================
// フェードクラス
//=============================================================================
class CFade
{
public:
	typedef enum
	{
		FADE_NONE = 0,	// 何もない状態
		FADE_IN,		// フェードイン処理
		FADE_OUT,		// フェードアウト処理
		FADE_MAX
	}FADE;

	typedef enum
	{
		FADE_TYPE_MANAGER,
		FADE_TYPE_STAGE,
		FADE_TYPE_MAX
	}FADE_TYPE;


	CFade();						// コンストラクタ
	~CFade();						// デストラクタ
	static CFade *Create(void);	// 作成処理

	HRESULT Init(void);				// 初期化処理
	void	Uninit(void);			// 終了処理
	void	Update(void);			// 更新処理
	void	Draw(void);				// 描画処理
	void	Fadeout(void);			// 暗転処理
	void	SetBlackout(CManager::MODE mode);	//ブラックアウト処理
	void	SetWhiteout(CGame::MAP_TYPE mode);	//ホワイトアウト処理

	FADE    GetFade(void) { return m_fade; }	//フェードの処理情報を取得
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	D3DXVECTOR3		m_pos;					// 位置
	D3DXCOLOR		m_color;				// カラー
	FADE			m_fade;					// フェード
	CManager::MODE	m_ManagerMode;			// マネージャーモード
	CGame::MAP_TYPE m_StageMode;			// ステージモード
	FADE_TYPE		m_FadeType;				// フェードタイプ
};
#endif