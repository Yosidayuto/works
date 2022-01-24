//=============================================================================
//
//	ボタンマネージャー[button manager.h]
//	Author:吉田　悠人
//
//=============================================================================

#ifndef _BUTTON_MANAGER_H_
#define _BUTTON_MANAGER_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "scene.h"
//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_BUTTON (6)
//=============================================================================
//前方宣言
//=============================================================================
class CButton;

typedef enum	//ボタンの種類
{
	BUTTON_TYPE_START = 0,	//スタート
	BUTTON_TYPE_LIFE,		//ライフ
	BUTTON_TYPE_SPEED,		//スピード
	BUTTON_TYPE_BUTTOL,		//バレット
	BUTTON_TYPE_LASER,		//レーザー
	BUTTON_TYPE_HOMING,		//ホーミング
	BUTTON_TYPE_MAX
}BUTTON_TYPE;
//=============================================================================
// クラス定義
//=============================================================================
class CButtonManager :public CScene
{
public:
	CButtonManager();	//コンストラクタ
	~CButtonManager();	//デストラクタ

	static HRESULT			Load(void);		
	static void				Unload(void);
	static CButtonManager*	Create(int nStage);

	HRESULT			Init(void);		// 初期化処理
	void			Uninit(void);	// 終了処理
	void			Update(void);	// 更新処理
	void			Draw(void);		// 描画処理
	void			SetStageNumber(int nStage);	//ステージ番号取得
	void			MouseOut(void);				// テロップの切替
private:
	CButton*		m_pButton[BUTTON_TYPE_MAX];	// ボタンポインタ
	int				m_nStageNumber;				// ステージナンバー
};
#endif
