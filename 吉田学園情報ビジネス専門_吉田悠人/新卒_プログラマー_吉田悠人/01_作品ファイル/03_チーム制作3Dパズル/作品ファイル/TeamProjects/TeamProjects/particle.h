//=============================================================================
//
// パーティクル処理 [particle.h]
// Author : 小熊 朗
// 更新日 : 2022/03/04
//
//=============================================================================
#ifndef PARTICLE_H_
#define PARTICLE_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "billboard.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_PARTICLE (400)
//=============================================================================
//パーティクルクラス定義
//=============================================================================
class CParticle:public CBillboard
{
public:
	typedef enum	//マップ種類
	{
		PARTICLE_TYPE_1 = 0,
		PARTICLE_TYPE_2,
		PARTICLE_TYPE_MAX
	}PARTICLE_TYPE;

	CParticle();		//コンストラクタ
	~CParticle();		//デストラクタ

	//クリエイト関数
	 void Sphere(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR col);
	 void Vacuum(D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR col);
	static CParticle *Cretae(D3DXVECTOR3 pos, D3DXVECTOR3 distPos, D3DXVECTOR3 size, D3DXVECTOR3 move,D3DXCOLOR col, PARTICLE_TYPE type);

	HRESULT Init(void);								//初期化関数
	void Update(void);								//更新関数
	void Uninit(void);								//終了関数
	void Draw(void);								//描画関数

private:
	const int m_nTexture = 70;				// テクスチャ番号
	D3DXVECTOR3 m_Playerpos;				// プレイヤーの位置
	D3DXVECTOR3 m_Childpos;					// 子供の位置
	D3DXVECTOR3 m_move;						// 移動量
	D3DXCOLOR	m_col;						// 色
	D3DXMATRIX	mtxWorld;					// ワールド計算用
	D3DXVECTOR3	m_Playerrot;				// プレイヤーの回転
	static CModel::MODELDATA m_modeldata;	// モデルデータ
};

#endif // !PARTICLE_H_
