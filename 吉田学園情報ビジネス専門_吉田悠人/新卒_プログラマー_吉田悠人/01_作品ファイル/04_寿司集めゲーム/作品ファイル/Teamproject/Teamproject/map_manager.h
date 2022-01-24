//=============================================================================
//
// マップ管理 [map_manager.h]
// Author : 林川紗梨夏
//
//=============================================================================
#ifndef _MAP_MANAGER_H_
#define _MAP_MANAGER_H_
//=============================================================================
// ヘッダーファイル
//=============================================================================
#include "food base.h"
#include "item.h"
#include "game.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CLocationPoint;
class CMapEdgeMask;
class CFieldManager;

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************

class CMapManager : public CScene
{
public:
	CMapManager(int nPriority = 8);
	~CMapManager();

	static CMapManager *Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	float GetMapSize(void) { return m_MapSize.x; };
private:
	void SushiSpawn(void);				// 寿司のランダム生成処理関数
	void ItemSpawn(void);				// アイテムのランダム生成処理関数

	D3DXVECTOR3 m_originPos;						//マップの原点（ここを{0,0}とする）
	CLocationPoint * m_pLocationPoint[MAX_PLAYER];	//現在位置
	D3DXVECTOR3 m_MapSize;							//mapのサイズ
	CMapEdgeMask * m_pMapEdgeMask;					//マスクポインタ
	CFieldManager * m_pFieldManager;				//フィールドポインタ
	int m_nShrinkCount;								//収縮した回数
	bool m_bShirnk;									//収縮中か

	int			m_nSushiSpawn;						// 寿司のスポーンする時間
	int			m_nSpawnSushiCount;					// 寿司のスポーンする時間までのカウント
	static int	m_nSpawnItemCount[CGame::GAMESTATE_MAX];		// アイテムのスポーンする時間までのカウント

	static int	m_nItemProb[CItem::ITEM_MAX];		// どのアイテムが出てくるかの確率
	static int	m_nMaxItemProb;						// アイテムの最大確率
	static int	m_nSushiProb[CFoodBase::TYPE_MAX];	// どの寿司が出てくるかの確率
	static int	m_nMaxSushiProb;					// 寿司の最大確率
	CGame::GAME_STATE m_GameState;					// ゲームの状態

};
#endif // !_MAP_MANAGER_H_


