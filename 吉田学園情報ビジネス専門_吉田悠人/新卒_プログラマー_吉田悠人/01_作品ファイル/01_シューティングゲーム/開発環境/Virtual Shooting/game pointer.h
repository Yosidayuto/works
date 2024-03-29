//=============================================================================
//
// ゲームのマウスポインター [game pointer.h]
// Author : 吉田悠人
//
//=============================================================================

#ifndef _GAME_POINTER_H_
#define _GAME_POINTER_H_

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "main.h"
#include "mouse pointer.h"
//=============================================================================
// クラス定義
//=============================================================================
class CGamePointer : public CPointer
{
public:

	CGamePointer();							// コンストラクタ
	static HRESULT			Load(void);		// テクスチャ読み込み
	static void				Unload(void);	// テクスチャ破棄
	static CGamePointer*	Create(void);	// 作成処理
	void	Update(void);					// 更新処理

private:
	static TEXTURE_DATA	m_TextureData;	//テクスチャデータ
};
#endif // !_POLYGON_H_
