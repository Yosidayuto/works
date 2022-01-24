//=============================================================================
//
// ホーミング弾処理 [homing.h]
// Author : 吉田悠人
//
//=============================================================================

#ifndef _HOMING_H_
#define _HOMING_H_
//=============================================================================
//インクルードファイル
//=============================================================================
#include"main.h"
#include"scene2d.h"
#include "bullet base.h"

//=============================================================================
// クラス定義
//=============================================================================
class CHoming :public CBulletBase
{
public:
	CHoming();						//コンストラクタ
	static HRESULT	Load(void);		//テクスチャ読み込み
	static void		Unload(void);	//テクスチャの破棄
	static CHoming* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);	//生成処理

	HRESULT Init(void);				// 初期化処理
	void	Move(void);				// 移動処理
	void	Bullet(CScene* pObj);	// バレット処理
	void	LockOn(D3DXVECTOR3 pos, D3DXVECTOR3 EnemyPos);		// ターゲット取得
	void	TargetMove(D3DXVECTOR3 pos, D3DXVECTOR3 EnemyPos);	// ターゲットに向かうためのmove取得
private:
	static TEXTURE_DATA	m_TextureData;		// テクスチャデータ
	int					m_nRange;			// ホーミング範囲保管変数
};
#endif