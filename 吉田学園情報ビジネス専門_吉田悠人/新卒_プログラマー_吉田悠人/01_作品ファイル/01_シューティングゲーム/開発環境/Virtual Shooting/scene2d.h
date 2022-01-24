//=============================================================================
//
// 2Dシーン [scene2d.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include"main.h"	//メインヘッダー
#include"scene.h"	//シーンファイル
//=============================================================================
// 前方宣言
//=============================================================================
typedef struct
{
	LPDIRECT3DTEXTURE9	m_Texture;	// テクスチャへのポインタ
	char*				m_cFileName;// ファイルの名前
} TEXTURE_DATA;

//=============================================================================
//クラス定義
//=============================================================================
class CScene2d :public CScene
{
public:
	
	CScene2d(int nPriorit = 3);					// コンストラクタ
	virtual ~CScene2d();						// デストラクタ
	static CScene2d*	Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const float frot, const LPDIRECT3DTEXTURE9 pTexture, const int nPriority);    // ポリゴン生成処理
	virtual HRESULT Init(void);					// 初期化処理
	virtual void	Uninit(void);				// 終了処理
	virtual void	Update(void);				// 更新処理
	virtual void	Draw(void);					// 描画処理
	

	void	SetPos(D3DXVECTOR3 pos); 	//位置設置
	void	SetRot(float frot);			//向き設定
	void	SetSize(D3DXVECTOR3 size);	//サイズセット
	void	SetCol(D3DXCOLOR col);		//カラーセット

	D3DXVECTOR3 GetPos(void);			//位置取得
	D3DXVECTOR3 GetSize(void);			//サイズ取得
	float		GetRot(void);			//向き取得
	D3DXCOLOR	GetCol(void);			//カラー取得

	void	BindTexture(LPDIRECT3DTEXTURE9 pTexture);	//テクスチャの読み込み処理
	void	TextureAnim(D3DXVECTOR2 *Texture);			//テクスチャアニメーション
private:
	LPDIRECT3DTEXTURE9		m_Texture;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;			// ポリゴンの位置
	D3DXVECTOR3				m_size;			// ポリゴンの大きさ
	D3DCOLOR				m_col;			// ポリゴンのカラー
	float					m_fRot;			// ポリゴンの向き
};
#endif
