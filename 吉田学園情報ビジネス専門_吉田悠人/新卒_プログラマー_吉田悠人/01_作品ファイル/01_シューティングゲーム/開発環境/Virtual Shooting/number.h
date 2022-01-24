//=============================================================================
//
// 数値処理 [number.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef  _NUMBER_H_
#define  _NUMBER_H_
//=============================================================================
//ヘッダーファイル
//=============================================================================
#include "main.h"
#include "scene.h"

//=============================================================================
// クラス定義
//=============================================================================
class CNumber
{
public:

	CNumber();		//コンストラクタ
	~CNumber();		//デストラクタ

	static CNumber*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//生成処理
	static HRESULT	Load(void);		//テクスチャ読み込み
	static void		Unload(void);	//テクスチャの破棄

	HRESULT Init(void);				//初期化処理
	void	Uninit(void);			//終了処理
	void	Update(void);			//更新処理
	void	Draw(void);				//描画処理
	void	SetNumber(int nNumber);
	void	ColChange(D3DXCOLOR col);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture;		//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuff;		//頂点バッファへのポインタ
	D3DXVECTOR3 pos;
	D3DXVECTOR3 size;
};
#endif