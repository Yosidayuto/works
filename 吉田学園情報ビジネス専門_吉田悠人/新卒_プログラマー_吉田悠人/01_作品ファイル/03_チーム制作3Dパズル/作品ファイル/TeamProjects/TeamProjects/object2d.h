//=============================================================================
//
//	2Dポリゴン[object2d.h]
//	Author:吉田悠人
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "object.h"

//=============================================================================
// 前方宣言
//=============================================================================
typedef struct
{
	LPDIRECT3DTEXTURE9	m_pTexture;	// テクスチャへのポインタ
	char*				m_cFileName;// ファイルの名前
} TEXTURE_DATA;


//=============================================================================
// クラス定義
//=============================================================================
class CObject2D : public CObject
{
public:
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX
	}FADE_2D;

    CObject2D(int nPriority = OBJTYPE_NONE);	// コンストラクタ
    virtual ~CObject2D();			// デストラクタ
	
	static CObject2D*	Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const float frot,const LPDIRECT3DTEXTURE9 pTexture, const int nPriority);    // ポリゴン生成処理
	virtual HRESULT		Init(void);			// 初期化処理
    virtual void		Uninit(void);		// 終了処理
    virtual void		Update(void);		// 更新処理
    virtual void		Draw(void);			// 描画処理

    void SetPos(const D3DXVECTOR3 pos);		// 位置セット
    void SetRot(const float rot);			// 向きセット
    void SetSize(const D3DXVECTOR3 size);	// サイズセット
	void SetCol(const D3DCOLOR col);		// カラーセット
											   
	D3DXVECTOR3 GetPos(void);				// 位置ゲッター
	D3DXVECTOR3 GetSize(void);				// サイズゲッター
	D3DCOLOR    GetCol(void);
	float		GetRot(void);				// 向きゲッター

    void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	// テクスチャセット
    void SetTexPos(D3DXVECTOR2* pTexPos);			// テクスチャUVセット
	void Fade2d(void);
private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファへのポインタ
    LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャへのポインタ
    D3DXVECTOR3 m_pos;					// ポリゴンの位置
    D3DXVECTOR3 m_size;					// ポリゴンの大きさ
    D3DXCOLOR	m_col;					// ポリゴンのカラー
    float		m_fRot;					// ポリゴンの向き
	FADE_2D     m_fade;
};

#endif
