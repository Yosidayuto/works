//=============================================================================
//
// バレットベース処理 [bullet base.h]
// Author : 吉田悠人
//
//=============================================================================

#ifndef _BULLET_BASE_H_
#define _BULLET_BASE_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include"main.h"
#include"scene2d.h"

//=============================================================================
// クラス定義
//=============================================================================
class CBulletBase :public CScene2d
{
public:
	CBulletBase(int nPriorit = PRIORITY_OBJECT_1);	//コンストラクタ

	static HRESULT		Load(void);		//テクスチャ読み込み
	static void			Unload(void);	//テクスチャの破棄

	void	Update(void);					// 更新処理
	void	ObjeSearch(void);				// オブジェクトサーチ
	bool	Range(void);					// 射程距離
	virtual void Move(void) = 0;			// 移動処理
	virtual void Bullet(CScene* pObj) = 0;	// バレット

	void		SetMove(D3DXVECTOR3 move);	// 移動量セッター
	D3DXVECTOR3	GetMove(void);				// 移動量ゲッター
	void		SetLife(int nLife);			// ライフセッター
	int			GetLife(void);				// ライフゲッター
private:
	D3DXVECTOR3			m_move;				// 移動量
	int					m_nLife;			// 弾の射程距離

};
#endif