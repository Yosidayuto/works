//====================================================
//
// jobchange_tileヘッダ [jobchange_tile.h]
// Author : 伊藤陽梧
//
//====================================================

//二重インクルード防止
#ifndef _JOBCHANGE_TILE_H_
#define _JOBCHANGE_TILE_H_

//====================================================
// インクルード
//====================================================
#include "tile.h"
#include "resource_texture.h"
#include "resource_character.h"

//====================================================
//前方宣言
//====================================================
class CScene3d;

//====================================================
// クラス定義
//====================================================

// ダミータイルクラス
class CJobchangeTile : public CTile
{
public:
	//============
	// メンバ関数
	//===========
	CJobchangeTile();
	~CJobchangeTile();

	// 生成するタイルごとの処理
	static void CreateKnight(D3DXVECTOR3 pos, D3DXCOLOR col = TILE_DEFAULT_COLOR);
	static void CreateLancer(D3DXVECTOR3 pos, D3DXCOLOR col = TILE_DEFAULT_COLOR);
	static void CreateWizard(D3DXVECTOR3 pos, D3DXCOLOR col = TILE_DEFAULT_COLOR);
	static void CreateThief(D3DXVECTOR3 pos, D3DXCOLOR col = TILE_DEFAULT_COLOR);
	static void CreateMagician(D3DXVECTOR3 pos, D3DXCOLOR col = TILE_DEFAULT_COLOR);
	static void CreateArcher(D3DXVECTOR3 pos, D3DXCOLOR col = TILE_DEFAULT_COLOR);

	// クラス生成
	static void Create(D3DXVECTOR3 pos, CResourceTexture::TEXTURE_TYPE Tex_type, CResourceCharacter::CHARACTER_TYPE Char_type);

	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
private:

	//============
	// メンバ変数
	//===========
	CScene3d *m_pCrossPolygon;	// マーク
	CResourceCharacter::CHARACTER_TYPE m_CharacterType;
};

#endif