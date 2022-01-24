//=============================================================================
//
//	ウェポンマネージャー[weapon manager.h]
//	Author:吉田　悠人
//
//=============================================================================

#ifndef _WEAPON_MANAGER_H_
#define _WEAPON_MANAGER_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "scene.h"
#include "player.h"
//=============================================================================
//前方宣言
//=============================================================================
class CWeaponUi;

//=============================================================================
// クラス定義
//=============================================================================
class CWeaponManager:public CScene
{
public:
	CWeaponManager();	//コンストラクタ
	~CWeaponManager();	//デストラクタ

	static HRESULT			Load(void);
	static void				Unload(void);
	static CWeaponManager*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	HRESULT			Init(void);		// 初期化処理
	void			Uninit(void);	// 終了処理
	void			Update(void);	// 更新処理
	void			Draw(void);		// 描画処理
private:
	CWeaponUi*		m_pWeaponUi[MAX_WEAPON];	// ウェポンUIポインタ
	D3DXVECTOR3		m_pos;						// 位置
	D3DXVECTOR3		m_size;						// サイズ
};
#endif
