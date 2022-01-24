//=============================================================================
//
// リソースマネージャー [reource manager.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "main.h"
#include "manager.h"
#include "model.h"

//=============================================================================
// クラス定義
//=============================================================================
class CResource
{
public:

	CResource();
	~CResource();
	
	HRESULT Init(void);
	void	Uninit(void);

	LPDIRECT3DTEXTURE9	TextureLoad(int nTexture);	// テクスチャロード
	CModel::MODELDATA	ModelLoad(int nModel);		// モデルロード

private:
	void	TextureUnLoad(void);					// テクスチャアンロード
	void	TextureFail(void);						// テクスチャ読み込みファイル
	void	ModelUnLoad(void);						// モデルアンロード
	void	XFail(void);							// Xファイル読み込みファイル

	char				m_pcTextureName[256];	// ファイルの名前
	int*				m_npTexture;			// テクスチャ番号
	int					m_nMaxTexture;			// テクスチャの総数
	LPDIRECT3DTEXTURE9*	m_pTexture;				// テクスチャへのポインタ
	int*				m_npModel;				// モデル番号
	int					m_nMaxModel;			// モデルの総数
	CModel::MODELDATA*	m_pModel;				// モデルへのポインタ

};
#endif
