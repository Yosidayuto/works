//=============================================================================
//
// チャイルド [child.h]
// Author : 増澤 未来
//
//=============================================================================
#ifndef _CHILD_H_
#define _CHILD_H_
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "model.h"
#include "object3d.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// 前方宣言
//=============================================================================
class CModel;

//=============================================================================
// クラス定義
//=============================================================================
class CChild : public CObject3D
{
public:
	CChild();
	~CChild();
	static HRESULT	Load(void);
	static void		Unload(void);
	static CChild*	Create(CModel* modelPearent ,D3DXVECTOR3 rot, D3DXVECTOR3 size = D3DXVECTOR3(1.0f, 1.0f, 1.0f));//引数:親モデル,回転,サイズ
	HRESULT Init(void);   // 初期化処理
	void	Uninit(void); // 終了処理
	void	Update(void); // 更新処理
	void	Draw(void);   // 描画処理

	//void FadeTalk(void);

	CModel* GetModel(void) { return m_model; }	 // モデルの取得
	bool GetIsActive(void) { return m_bActive; } // 有効フラグの取得処理

private:
	void CollisionItem(void);				// アイテムとのくっつき判定
	
	CModel* m_modelPearent;                 // 親モデル
	CModel* m_model;		                // モデルポインタ
	bool m_bActive;                         // 有効フラグ
	static CModel::MODELDATA m_modeldata;	// モデルデータ
	bool m_bFlag;
};
#endif