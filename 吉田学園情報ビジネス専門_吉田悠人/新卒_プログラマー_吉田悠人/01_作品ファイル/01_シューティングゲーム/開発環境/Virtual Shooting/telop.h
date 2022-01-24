//=============================================================================
//
//	テロップ[telop.h]
//	Author:吉田　悠人
//
//=============================================================================
#ifndef _TELOP_BER_H_
#define _TELOP_BER_H_
//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define TELOP_X_SIZE (70)	//表示されるテロップのサイズ調整用
#define TELOP_Y_SIZE (20)	//表示されるテロップのサイズ調整用

//=============================================================================
// 前方宣言
//=============================================================================
class CTexture;
typedef enum	//テロップの種類
{
	TELOP_TYPE_TUTORIAL = 0,// チュートリアル
	TELOP_TYPE_LIFEUP,		// ライフアップ
	TELOP_TYPE_SPEEDUP,		// スピードアップ
	TELOP_TYPE_BUTTOL,		// バレット
	TELOP_TYPE_LASER,		// レーザー
	TELOP_TYPE_HOMING,		// ホーミング
	TELOP_TYPE_MAX
}TELOP_TYPE;

//=============================================================================
// クラス定義
//=============================================================================
class CTelop :public CScene2d
{
public:
	CTelop(int nPriorit = PRIORITY_UI_0);						//コンストラクタ

	static HRESULT		Load(void);		//テクスチャ読み込み
	static void			Unload(void);	//テクスチャの破棄
	static CTelop*		Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//生成処理

	HRESULT				Init(void);		//初期化処理

	TELOP_TYPE			GetTelopType(void);				// テロップタイプ取得
	void				TypeChange(TELOP_TYPE Type);	// テロップの切替　

private:
	static void			TelopLoad(void);	// テロップロード
	static void			TelopUnload(void);	// テロップアンロード

	static TEXTURE_DATA	m_TextureData;	// テクスチャデータ
	CScene2d*			m_pTelop;		// テロップ用のポインタ
	TELOP_TYPE			m_TelopType;	// テロップのタイプ
};
#endif