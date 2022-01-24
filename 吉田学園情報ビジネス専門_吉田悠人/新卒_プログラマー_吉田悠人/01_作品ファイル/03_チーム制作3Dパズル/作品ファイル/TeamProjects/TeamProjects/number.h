//=============================================================================
//
// ナンバー [number.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef  _NUMBER_H_
#define  _NUMBER_H_
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "main.h"
#include "object.h"

//=============================================================================
// クラス定義
//=============================================================================
class CNumber
{
public:

	CNumber();		// コンストラクタ
	~CNumber();		// デストラクタ

	static CNumber*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 生成処理
	static HRESULT	Load(void);			// テクスチャ読み込み
	static void		Unload(void);		// テクスチャの破棄

	HRESULT Init(void);					// 初期化処理
	void	Uninit(void);				// 終了処理
	void	Update(void);				// 更新処理
	void	Draw(void);					// 描画処理
										   
	void	SetNumber(int nNumber);		// 表示数値設定
	void	SetPos(D3DXVECTOR3 pos);	// 位置セッター
	void	SetSize(D3DXVECTOR3 size);	// サイズセッター
	void	ColChange(D3DXCOLOR col);	// カラーチェンジ

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;		// テクスチャへのポインタ
	static char*				m_cFileName;	// ファイル名
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;		// 頂点バッファへのポインタ
	D3DXVECTOR3					m_pos;			// 位置
	D3DXVECTOR3					m_size;			// サイズ
};




#endif