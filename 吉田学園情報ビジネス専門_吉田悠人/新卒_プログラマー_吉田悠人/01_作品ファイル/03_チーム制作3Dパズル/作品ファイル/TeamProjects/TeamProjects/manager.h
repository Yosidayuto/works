//=============================================================================
//
// マネージャー処理 [manager.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
//=============================================================================
//前方宣言
//=============================================================================
class CRenderer;
class CFade;
class CInput;
class CSound;
class CCamera;
class CTitle;
class CGame;
class CPause;
class CResource;
//=============================================================================
//クラス定義
//=============================================================================
class CManager
{
public:

	typedef enum //モードタイプ
	{
		MODE_TITLE = 0,		// タイトル
		MODE_GAME,			// ゲーム
		MODE_MAX
	} MODE;

	CManager();     //コンストラクタ
	~CManager();    //デストラクタ

	HRESULT Init(HWND hWnd, bool bWindow, HINSTANCE hInstance);	// 初期化関数
	void	Uninit(void);										// 終了関数
	void	Update(void);										// 更新関数
	void	Draw(void);											// 描画関数
	
	static CRenderer*	GetRenderer(void);			// レンダラゲッター
	static CResource*	GetResource(void);			// リソースゲッター
	static CInput*		GetInputKey(void);			// キーボード取得
	static CInput*		GetInputMou(void);			// マウス取得
	static CInput*		GetInputController(void);	// コントローラー取得
	static CCamera*		GetCamera(void);			// カメラ取得
	static CFade*		GetFadeout(void) { return m_pFade; }// フェードの取得
	static CSound*		GetSound(void);						//サウンドの取得
	static CPause*		GetPause(void) { return m_pPause; }	// ポーズの取得
	static void SetMode(MODE mode);					// モード切替
	static MODE GetMode(void);						// モード取得

	static void BindCamera(CCamera* pCamera);		// カメラ設定
	
	void		PauseStart(void);					// ポーズスタート

private:

    static CRenderer*	m_pRenderer;		// レンダラのポインタ
    static MODE			m_mode;				// モードの変数
	static CInput*		m_pInputKey;		// キーボードのポインタ
	static CInput*		m_pInputMou;		// マウスのポインタ
	static CInput*		m_pInputController;	// コントローラーのポインタ
	static CCamera*		m_pCamera;			// カメラのポインタ
	static CFade*		m_pFade;			// フェードポインタ
	static CSound*		m_pSound;			// サウンドのポインタ
	static CTitle*		m_pTitle;			// タイトルのポインタ
	static CGame*		m_pGame;			// ゲームのポインタ
	static CPause*		m_pPause;			// ポーズポインタ
	static CResource*	m_Resource;			// リソースマネージャーポインタ
	
};

#endif
