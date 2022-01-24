//=============================================================================
//
// マネージャー処理 [manager.h]
// Author : 吉田悠人
//
//=============================================================================

#ifndef _MANAGER_H_
#define _MANAGER_H_
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "main.h"
#include "scene.h"
#include "game.h"

//=============================================================================
//前方宣言
//=============================================================================
class CRenderer;
class CInihKeyboard;
class CInihMouse;
class CSound;
class CScene;
class CFade;
class CGame;
class CSelect;
class CPlayerData;
class CTitle;
class CTutorial;
class CLoad;

typedef enum	//ゲームモード
{
	GAME_MODE_NONE = 0,
	GAME_MODE_LOAD,			//ロード
	GAME_MODE_TITLE,		//タイトル
	GAME_MODE_TUTORIAL,		//チュートリアル
	GAME_MODE_SELECT,		//セレクト
	GAME_MODE_STAGE,		//ステージ
	GAME_MODE_CLEAR,		//クリア
	GAME_MODE_MAX,
}GAME_MODE;

//=============================================================================
// クラス定義
//=============================================================================
class CManager
{
public:
	CManager();		//コンストラクタ
	~CManager();	//デストラクタ

	HRESULT Init(HINSTANCE hInstance,HWND hWnd, bool bWindow);	// 初期化処理
	void	Uninit(void);										// 終了処理
	void	Update(void);										// 更新処理
	void	Draw(void);											// 描画処理

	static void SetMode(GAME_MODE mode);						// ゲームモードセット
	static void	SetScore(int nScore) { m_nScore = nScore; };	// スコアセッター
	static void SetPlayer(CPlayerData* Player);					// プレイヤーセッター

	static int				GetScore(void);		//スコア取得
	static CPlayerData*		GetPlayer(void);	//プレイヤー取得

	static CRenderer		*GetRenderer(void);	// レンダリング取得
	static CInihKeyboard	*GetKeyboard(void);	// キーボード取得
	static CInihMouse		*GetMouse(void);	// マウス取得
	static CSound			*GetSound(void);	// サウンド取得
	static CFade			*GetFade(void);		// フェードアウト取得
private:
	void LoadFile(void);						// ファイルロード関数
	void UnLoadFile(void);						// ファイルアンロード関数

	static CRenderer		*m_pRenderer;	// レンダリングクラス
	static CInihKeyboard	*m_pInput;		// インプット（キーボード）クラス
	static CInihMouse		*m_pInihMouse;	// インプット（マウス）クラス
	static CSound			*m_pSound;		// サウンドクラス
	static CScene			*m_pScene;		// シーンクラス
	static CFade			*m_pFade;		// フェイドアウトクラス

	static CPlayerData*		m_pPlayerData;	// プレイヤークラスクラス
	static int				m_nScore;		// スコア保存先
	static CGame*			m_pGame;		// ゲームポインタ

	static CSelect*			m_pSelect;		// セレクト処理
	static GAME_MODE		m_Mode;			// ゲームモード
	static CTitle*			m_pTitle;		// タイトルポインタ
	static CTutorial*		m_pTutorial;	// チュートリアルポインタ
	static CLoad*			m_pLoad;		// ロード画面
};

#endif