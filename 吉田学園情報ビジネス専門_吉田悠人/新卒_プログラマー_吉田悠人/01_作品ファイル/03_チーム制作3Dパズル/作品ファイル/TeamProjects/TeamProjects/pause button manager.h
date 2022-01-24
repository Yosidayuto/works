//=============================================================================
//
//  ポーズボタンマネージャー[pause button manager.h]
//	Author:吉田　悠人
//
//=============================================================================

#ifndef _PAUSE_BUTTON_MANAGER_H_
#define _PAUSE_BUTTON_MANAGER_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "object.h"
//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_BUTTON (2)
//=============================================================================
//前方宣言
//=============================================================================
class CButton;

typedef enum	//ボタンの種類
{
	BUTTON_TYPE_START = 0,	//再開
	BUTTON_TYPE_RESTART,	//リスタート
	BUTTON_TYPE_END,		//終了
	BUTTON_TYPE_MAX
}BUTTON_TYPE;
//=============================================================================
// クラス定義
//=============================================================================
class CPauseButtonManager :public CObject
{
public:
	CPauseButtonManager();	//コンストラクタ
	~CPauseButtonManager();	//デストラクタ

	static CPauseButtonManager*	Create(void);

	HRESULT			Init(void);		// 初期化処理
	void			Uninit(void);	// 終了処理
	void			Update(void);	// 更新処理
	void			Draw(void);		// 描画処理
	void			Select(void);	// 選択処理
	void			Over(void);		// 選択したボタンの処理
private:
	CButton*		m_pButton[BUTTON_TYPE_MAX];	// ボタンポインタ
	int				m_nButtonSelect;			// 選択しているボタン
	bool			m_bStick;					// スティック
};
#endif
