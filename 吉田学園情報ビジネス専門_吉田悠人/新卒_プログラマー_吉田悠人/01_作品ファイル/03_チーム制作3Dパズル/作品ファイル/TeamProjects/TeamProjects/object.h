//=============================================================================
//
// オブジェクト [object.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_
//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//随時追加
typedef enum			 // 描画優先度
{						 
	PRIORITY_BG_0 = 0,		// 背景
	PRIORITY_OBJECT_SEA,	// 海
	PRIORITY_OBJECT_PLAYER,	// 自機
	PRIORITY_OBJECT_CHILD,	// チャイルドブロック
	PRIORITY_OBJECT_ITEM,	// アイテム
	PRIORITY_OBJECT_TILE,	// タイルブロック
	PRIORITY_RESULT,		// リザルト
	PRIORITY_UI_1,			// UIテキストやUIアイコンなど
	PRIORITY_UI_3,			// ゲーム時のUI
	PRIORITY_UI_0,			// UI背景
	PRIORITY_MAX,
}PRIORITY;

//=============================================================================
//オブジェクトクラス
//=============================================================================
class CObject
{
public:

	//オブジェクトタイプ
    typedef enum
    {
		OBJTYPE_NONE = 0,
        OBJTYPE_PLAYER,
		OBJTYPE_ITEM,
		OBHTYPE_TILE,
        OBJTYPE_BLOCK,
		OBJTYPE_GOAL,
        OBJTYPE_MODEL,
        OBJTYPE_STAGE,
		OBJTYPE_MAX
    } OBJTYPE;

    CObject(int nPriority = PRIORITY_BG_0);		// コンストラクタ
	virtual ~CObject();				// デストラクタ

    virtual HRESULT Init(void)	= 0;	// 純粋仮想関数群
    virtual void	Uninit(void)  = 0;
    virtual void	Update(void)  = 0;
    virtual void	Draw(void)   = 0;

    static void		UpdateAll(void);	// 全シーン更新処理関数
	static void		DrawAll(void);		// 全シーン描画処理関数 
	static void		ReleaseAll(void);	// 全シーン終了処理関数

    void	SetObjType(OBJTYPE type);	// オブジェクトタイプセット
	OBJTYPE	GetObjType(void);			// オブジェクトタイプゲッター

	void	SetPriority(PRIORITY priority);	// プライオリティセット

    static CObject** GetTop(void);	// オブジェクトトップゲッター

    CObject*	GetNext(void);		// 次のオブジェクト取得
    CObject*	GetPrev(void);		// 前のオブジェクト取得


protected:
    void	Release(void);			//シーンの開放

private:

    void		Death(void);				// リスト削除後のシーンクラス終了処理
	void ReConnection(void);                // リスト構造から自身を消してつなぎなおす
	static CObject* m_pTop[PRIORITY_MAX];	// オブジェクトトップ
    static CObject* m_pCur[PRIORITY_MAX];	// オブジェクト
  
	CObject*	m_pPrev;					// 次のオブジェクトクラス
    CObject*	m_pNext;					// 前のオブジェクトクラス
    int			m_nPriority;				// 優先順位用変数
    bool		m_bDestroy;					// オブジェクト破棄スイッチ
    OBJTYPE		m_objType;					// オブジェクトタイプ
};

#endif
