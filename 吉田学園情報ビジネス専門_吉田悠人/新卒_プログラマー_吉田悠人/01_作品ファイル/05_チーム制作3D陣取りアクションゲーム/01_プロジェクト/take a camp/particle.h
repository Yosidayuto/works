//=============================================================================
//
// particleヘッダ [particle.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//*****************************
// インクルード
//*****************************
#include "main.h"
#include "billboard.h"

//*****************************
//マクロ定義
//*****************************
#define EFFECT_DEFAULT_FADE_OUT_RATE 0.006f                               // フェードアウト割合
#define TEXTURE_ANIMA_PATTERN (20)

#define TEXTURE_ANIMA_LATE (1)
#define TEXTURE_ANIMA_THUKI_LATE (2)
#define TEXTURE_ANIMA_CREATE_POINT (8)
#define EFFECT_NUM_MAX (10)
#define EFFECT_MAX (8)


//*****************************
// 前方宣言
//*****************************
class CPlayer;


//*****************************
// クラス定義
//*****************************

// パーティクルクラス
class CParticle : public CBillboard
{
public:
	//============
	// 状態列挙
	//============
	// パーティクルタイプ
	typedef enum
	{
		PARTICLE_SQUARE = 0, // 四角
		PARTICLE_TEARS,   // 涙
		PARTICLE_SHOOT,  // ゆみの起動
		PARTICLE_METEOR, // 爆発
		PARTICLE_METEOR_SHADOW, // 爆発の影
		PARTICLE_GURUGURU,
		PARTICLE_SLASH,
		PARTICLE_THUKI,
		PARTICLE_MAX,     // タイプの最大数
	}PARTICLE_TYPE;

	//============
	//メンバ関数
	//============
	CParticle();
	~CParticle();

	// static
	static CParticle *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXVECTOR3 size, const int nLife,
		const D3DXCOLOR col,const float fadeout, const float fAngle, CPlayer * pPlayer, const PARTICLE_TYPE type = PARTICLE_SQUARE); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新

	// 移動量の取得・セット
	D3DXVECTOR3 GetMove(void) { return m_move; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void SetAddRotValue(float fAdd) { m_fRotAngle = fAdd; }
	//プレイヤーのポインタ所得・セット
	void		SetPlayer(CPlayer* pPlayer) { m_pPlayer = pPlayer; }
	CPlayer*	GetPlayer(void) { return m_pPlayer; }
private:
	//============
	// メンバ変数
	//============
	LPDIRECT3DTEXTURE9 m_apTexture[PARTICLE_MAX]; // テクスチャ
	D3DXVECTOR3   m_move;	 	  // 移動量
	D3DXVECTOR3	  m_rot;		  // 向き
	D3DXVECTOR3	  m_posOld;		  // 初期位置


	CPlayer*	  m_pPlayer;	  // プレイヤーのポインタ
	int           m_nLife;        //寿命
	int			  m_nPattern;	  //アニメーションのパターン
	int			  m_nEffectId;	  //エフェクトのiD
	static int    m_nEffectIdAII; //エフェクトの総数
	int			  m_nAnimation;   //アニメーションの時間カウント
	float		  m_fRotAngle;	  // 回転角度
	
	float		  m_fFadeout;	  // フェードアウト　
	bool		  m_bFadeoutFlag; // フェードアウトのフラグ
	bool          m_bAnimation;	  // アニメーションしていいか
	PARTICLE_TYPE m_type;		  // パーティクルの種類
};

#endif