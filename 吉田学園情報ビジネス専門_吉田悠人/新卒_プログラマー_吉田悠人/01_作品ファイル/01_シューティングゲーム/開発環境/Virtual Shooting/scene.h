//=============================================================================
//
// シーン処理 [scene.h]
// Author : 吉田悠人
//
//=============================================================================

#ifndef _SCENE_H_
#define _SCENE_H_

#include"main.h"
//=============================================================================
// マクロ定義
//=============================================================================
typedef enum				// 描画優先度
{
	PRIORITY_BG_0 = 0,	// 背景
	PRIORITY_OBJECT_0,	// 自機やエネミー
	PRIORITY_OBJECT_1,	// バレットやエフェクト
	PRIORITY_UI_0,		// UI背景
	PRIORITY_UI_1,		// UIテキストやUIアイコンなど
	PRIORITY_SCENE,		// 特殊な演出や他の表示より上に来る
	PRIORITY_UI_3,		// ゲーム時のUI
	PRIORITY_RESULT,	// リザルト
	PRIORITY_MAX,
}PRIORITY;

//=============================================================================
// クラス定義
//=============================================================================
class CScene
{
public:
	typedef enum				// ポリゴン種類
	{							   
		OBJ_TYPE_NONE = 0,		   
		OBJ_TYPE_PLAYER,		// プレイヤー
		OBJ_TYPE_BULLET,		// バレット
		OBJ_TYPE_ENEMY,			// エネミー
		OBJ_TYPE_BOSS,			// ボス
		LABEL_MAX,
	}OBJTYPE;


	CScene(int nPriorit = 3);			// コンストラクタ
	virtual ~CScene();					// デストラクタ

	virtual	HRESULT Init(void)		= 0;// 純粋仮想関数群
	virtual	void	Uninit(void)	= 0;
	virtual void	Draw(void)		= 0;
	virtual void	Update(void)	= 0;

	static void		UpdateAll(void);	// 全シーン更新処理関数
	static void		DrawAll(void);		// 全シーン描画処理関数 
	static void		ReleaseAll(void);	// 全シーン終了処理関数
	
	void			SetObjType(OBJTYPE Type);	// オブジェクトタイプセット
	OBJTYPE			GetObjType(void);			// オブジェクトタイプゲッター

	static CScene** GetTop(void);				// オブジェクトトップゲッター

	CScene*			GetNext(void);				// 次のオブジェクト取得
	CScene*			GetPrev(void);				// 前のオブジェクト取得


protected:
	void Release(void);						// シーンの開放
private:
	void	Death(void);					// リスト削除後のシーンクラス終了処理
	
	static CScene* m_pTop[PRIORITY_MAX];	// オブジェクトトップ
	static CScene* m_pCur[PRIORITY_MAX];	// オブジェクト
	CScene*		m_pPrev;					// 次のオブジェクトクラス
	CScene*		m_pNext;					// 前のオブジェクトクラス
	int			m_nPriority;				// 優先順位用変数
	bool		m_bDestroy;					// オブジェクト破棄スイッチ
	OBJTYPE		m_objType;					// オブジェクトタイプ
};
#endif