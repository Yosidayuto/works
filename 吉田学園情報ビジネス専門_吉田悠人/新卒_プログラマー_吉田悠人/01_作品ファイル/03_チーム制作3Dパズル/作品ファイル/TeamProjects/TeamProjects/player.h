//=============================================================================
//
// プレイヤー [player.h]
// Author : 
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "model.h"
#include "object3d.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CModel;
class CChild;

//=============================================================================
// クラス定義
//=============================================================================
class CPlayer : public CObject3D
{
public:

	// 移動パターン列挙
	typedef enum
	{
		STICKY_NONE = 0, // 通常移動
		STICKY_FRONT,    // くっついているものが側面にあり、そっちの方向に移動
		STICKY_DOWN,     // くっついているものが下面にある
		STICKY_UP		 // くっついているものが上面にある
	}MOVE_PATTERN;

	CPlayer();
	~CPlayer();
	static CPlayer*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	HRESULT Init(void);		//初期化処理
	void	Uninit(void);	//終了処理
	void	Update(void);	//更新処理
	void	Draw(void);		//描画処理

	void	Goal(void);		//ゴール処理
	static CPlayer* GetPlayer(void)	{ return m_pPlayer; }		// プレイヤー取得処理
	bool	IsActiveMove(void)		{ return m_bActiveMove; }	// 移動フラグ取得処理
	void	SetAction(bool bPlayer) { m_bPlayer = bPlayer; }	// プレイヤーの行動状態セッター
private:
	void Control(void);						// 操作処理
	void Move(void);						// 移動処理
	void Fall(void);						// 落下処理
	void Collision(void);					// 当たり判定処理
	bool CollisionChild(CObject* Object);	// 子供ブロックの当たり判定
	void MoveRange(void);					// 行動範囲設定処理
	void MoveRangeChild(void);				// 子供ブロックの行動範囲設定処理
	void ErrorStatus(void);					// エラー音の使用確認関数
	void MoveError(void);					// 行動不能時の処理
	void ExchangeWorldMtx(void);			// ワールド変換

	static CPlayer*	m_pPlayer;				// プレイヤーポインタ
	CModel*			m_model;				// モデルポインタ
	D3DXVECTOR3	 m_Move;					// 移動量
	D3DXMATRIX	 m_mtxRot;					// 回転行列
	int			 m_nMoveFrameCount;			// 移動フレーム数のカウント用
	int			 m_nFallFrameCount;			// 落下フレーム数のカウント用
	bool		 m_bPlayer;					// プレイヤーの制限判定
	bool		 m_bActiveMove;				// 移動中かの判定用
	bool		 m_bFallMove;				// 落下中かの判定用
	bool		 m_bError;					// エラー音用の使用判定
	CChild *	 m_pChild;					// 子供(くっつく面の処理)ポインタ
	MOVE_PATTERN m_movePattern;				// 移動のパターン
	const int	 m_nModel = 1;				// モデル番号

};
#endif