//=============================================================================
//
// ワープ床ヘッダー [warp_tile.h]
// Author : 吉田 悠人
//
//=============================================================================

//二重インクルード防止
#ifndef _WARP_TILE_H_
#define _WARP_TILE_H_

//*****************************
// インクルード
//*****************************
#include "tile.h"
#include "map.h"
#include <vector>
//*****************************
//前方宣言
//*****************************
class CModel;
class CPlayer;
class CScene3d;
//*****************************
//マクロ定義
//*****************************

//*****************************
// クラス定義
//*****************************
class CWarpTile : public CTile
{
public:
	//*****************************
	// 列挙
	//*****************************
	// ステート
	typedef enum
	{
		WARP_TILE_NORMAL = 0,	//通常状態
		WARP_TILE_WARP,			//ワープ状態
		WARP_TILE_WARP_AFTER,	//ワープ先の状態
	}WARP_TILE_STATE;

	//識別用タイプ
	typedef enum
	{
		WARP_TILE_TYPE_NONE = -1,//なし
		WARP_TILE_TYPE_1,		//タイプ1
		WARP_TILE_TYPE_2,		//タイプ2
		WARP_TILE_TYPE_3,		//タイプ3
		WARP_TILE_TYPE_4,		//タイプ4
		WARP_TILE_TYPE_5,		//タイプ5
		WARP_TILE_TYPE_6,		//タイプ6
		WARP_TILE_TYPE_MAX
	}WARP_TILE_TYPE;

	//*****************************
	//メンバ関数
	//*****************************
	CWarpTile();
	~CWarpTile();

	static void Create_1(D3DXVECTOR3 pos, D3DXCOLOR col);	//生成処理（識別番号1）
	static void Create_2(D3DXVECTOR3 pos, D3DXCOLOR col);	//生成処理（識別番号2）
	static void Create_3(D3DXVECTOR3 pos, D3DXCOLOR col);	//生成処理（識別番号3）
	static void Create_4(D3DXVECTOR3 pos, D3DXCOLOR col);	//生成処理（識別番号4）
	static void Create_5(D3DXVECTOR3 pos, D3DXCOLOR col);	//生成処理（識別番号5）
	static void Create_6(D3DXVECTOR3 pos, D3DXCOLOR col);	//生成処理（識別番号6）

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:
	void HitPlayerAction(CPlayer*pPlayer);			// プレイヤーが乗っているか
	void HitPlayerActionRelease(CPlayer*pPlayer);	// プレイヤーが降りたか
	D3DXVECTOR3 RandTileSelect(void);				// 他のワープ先をランダムで取得
	//*****************************
	// メンバ変数
	//*****************************
	int				m_nLyncTile;								// つながっているタイル
	int				m_nPlayerCount[MAX_PLAYER];					// 行動できるまでのカウント
	WARP_TILE_STATE m_WarpState[MAX_PLAYER];					// 状態変数
	WARP_TILE_TYPE	m_WarpType;									// ワープ床の識別用変数
	static std::vector<std::vector<CWarpTile*>> m_pWarpTile;	// ワープ床のポインタ動的配列
	static int m_nTotalWarpTile;								// 総数
	CScene3d*	m_Texture;										// テクスチャ用のポリゴン

};

#endif