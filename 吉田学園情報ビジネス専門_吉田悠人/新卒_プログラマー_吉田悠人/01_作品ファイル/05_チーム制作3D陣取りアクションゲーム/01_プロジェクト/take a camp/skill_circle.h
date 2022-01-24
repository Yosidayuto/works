//=============================================================================
//

// スキルサークル [skill_circle.h]
// Author : 齋藤大行
//
//=============================================================================

//二重インクルード防止
#ifndef _SKILL_CIRCLE_
#define _SKILL_CIRCLE_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene.h"
#include "base_Cylinder.h"

//*****************************
//マクロ定義
//*****************************
#define NORMAL_SKIIL_HIGHROT (1.0f)
#define NORMAL_SKIIL_ROWROT (1.7f)

#define NORMAL_SKIIL_SIZE (D3DXVECTOR3(8.5f,6.5f,8.5f))
#define NORMAL_SKIIL_POS (D3DXVECTOR3(0.0f,0.0f,0.0f))
#define NORMAL_SKIIL_COL (D3DXCOLOR(0.0f,0.0f,0.0f))
#define NORMAL_SKIIL_SIZESHIFT D3DXVECTOR3(1.5f, 0.0f, 1.5f)

#define EXPLOSION_SKIIL_POSSHIFT D3DXVECTOR3(0.0f, 6.0f, 0.0f)
#define EXPLOSION_SKIIL_SHADOW_POSSHIFT D3DXVECTOR3(0.0f, 0.0f, 0.0f)
#define EXPLOSION_SKIIL_SIZESHIFT D3DXVECTOR3(2.5f, 2.5f, 2.5f)
#define EXPLOSION_SKIIL_MOVE D3DXVECTOR3(0.0f, 0.0f, 0.0f)
#define EXPLOSION_SKIIL_POS	 D3DXVECTOR3(0.0f,0.0f,0.0f)
#define EXPLOSION_SKIIL_SIZE D3DXVECTOR3(7.5f,4.5f,7.5f)
#define EXPLOSION_SKIIL_CENTER_SIZE D3DXVECTOR3(4.0f,0.0f,4.0f)
#define EXPLOSION_SKIIL_CENTER_SIZESHIFT D3DXVECTOR3(0.0f,3.0f,0.0f)
#define EXPLOSION_SKIIL_IMPACT_SIZE	D3DXVECTOR3(5.0f,0.0f,5.0f)
#define EXPLOSION_SKIIL_IMPACT_SIZESHIFT D3DXVECTOR3(0.0f,4.5f,0.0f)
#define EXPLOSION_SKIIL_METEOR_IMPACT_SIZE	D3DXVECTOR3(4.0f,0.0f,4.0f)
#define EXPLOSION_SKIIL_METEOR_IMPACT_SIZESHIFT D3DXVECTOR3(0.0f,3.0f,0.0f)
#define EXPLOSION_SKIIL_METEOR_IMPACT_POS D3DXVECTOR3(0.0f,25.0f,0.0f)
#define EXPLOSION_SKIIL_METEOR_IMPACT_UV1 (1.0f)
#define EXPLOSION_SKIIL_METEOR_IMPACT_UV2 (0.0f)

#define SLASH_SKIIL_POSSHIFT D3DXVECTOR3(0.0f, 6.0f, 0.0f)
#define SLASH_SKIIL_MOVE D3DXVECTOR3(0.0f, 0.0f, 0.0f)

#define THUKI_SKIIL_POSSHIFT D3DXVECTOR3(0.0f, 6.0f, 0.0f)
#define THUKI_SKIIL_MOVE D3DXVECTOR3(0.0f, 0.0f, 0.0f)

#define EXPLOSION_SKIIL_HIGHROT (3.5f)
#define EXPLOSION_SKIIL_ROWROT (0.5f)
#define EXPLOSION_SKIIL_CENTER_HIGHROT (1.0f)
#define EXPLOSION_SKIIL_CENTER_ROWROT (1.0f)
#define EXPLOSION_SKIIL_IMPACT_HIGHROT (2.0f)
#define EXPLOSION_SKIIL_IMPACT_ROWROT (0.5f)


//*****************************
// 前方宣言
//*****************************
class CPlayer;

//=============================================================================
// クラス定義
//=============================================================================
class CSkill_circle : public Cbase_Cylinder
{
public:
	//============
	//メンバ関数
	//============
	CSkill_circle(int nPliority = OBJTYPE_PARTICLE);
	~CSkill_circle();



	//============
	// 状態列挙
	//============
	// エフェクトタイプ列挙
	
	typedef enum
	{
		EFFECTTYPE_SKIIL = 0,
		EFFECTTYPE_SKIILMINI,
		EFFECTTYPE_METEOR,
		EFFECTTYPE_METEOR_CENTER,
		EFFECTTYPE_METEOR_IMPACT,
		EFFECTTYPE_IMPACT,
		EFFECTTYPE_MAX
	}EFFECTTYPE;

	// static

	static CSkill_circle *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col , const int nlife ,const EFFECTTYPE type, CPlayer * pPlayer); // クラス生成

	virtual HRESULT Init(void); // 初期化
	virtual void Uninit(void);  // 終了
	virtual void Update(void);  // 更新
	virtual	void Draw(void);    // 描画
	
	LPDIRECT3DTEXTURE9 GetTexture(int nIndex) { return m_apTexture[nIndex]; }
	bool GetEffectTrigger(void) {return m_bEffectTrigger;}
	void		SetPlayer(CPlayer* pPlayer) { m_pPlayer = pPlayer; }
	CPlayer*	GetPlayer(void) { return m_pPlayer; }
private:
	//============
	// メンバ変数
	//============
	CPlayer *		m_pPlayer;												// プレイヤークラス
	LPDIRECT3DTEXTURE9		m_apTexture[EFFECTTYPE_MAX];	    // テクスチャへのポインタ
	D3DXVECTOR3			    m_pos;	 	    // 位置
	D3DXVECTOR3			    m_move;	 	    // 移動量
	D3DXVECTOR3			    m_rot;	 	    // 向き
	D3DXVECTOR3	            m_size;		    // 大きさ
	int                     m_nLife;	    // 寿命
	float		            m_fRotAngle;    // 回転角度
	float		            m_fFadeout;	    // フェードアウト　
	bool		            m_bFadeoutFlag; // フェードアウトのフラグ
	bool					m_bAddMode;     // 加算合成
	bool					m_bEffectTrigger;	// エフェクト発生トリガー
	D3DXCOLOR	            m_col;		    // 色
	D3DXMATRIX				m_mtxWorld;     // ワールドマトリックス
	EFFECTTYPE				m_type;			// エフェクトのタイプ

};

#endif
