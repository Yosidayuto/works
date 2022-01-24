//=============================================================================
//
//	カウントUI[ui count.h]
//	Author:吉田　悠人
//
//=============================================================================
#ifndef _UI_COUNT_H_
#define _UI_COUNT_H_
//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "scene.h"
#include "manager.h"
#include "number.h"

//=============================================================================
// クラス定義
//=============================================================================
class CUiCount :public CScene
{
public:

	CUiCount(int nPriorit = PRIORITY_UI_1);			//コンストラクタ
	~CUiCount();						//デストラクタ
	static CUiCount*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, PRIORITY priority = PRIORITY_UI_1);
	HRESULT			Init(void);				//初期化処理
	void			Uninit(void);			//終了処理
	void			Update(void);			//更新処理
	void			Draw(void);				//描画処理
	void			SetCount(int nCount);	//カウントセッター
	void			SetCol(D3DXCOLOR col);	//カラーセッター
private:
	CNumber*		m_apNumber;
	int				m_nCount;

	D3DXVECTOR3		m_pos;
	D3DXVECTOR3		m_size;

};
#endif