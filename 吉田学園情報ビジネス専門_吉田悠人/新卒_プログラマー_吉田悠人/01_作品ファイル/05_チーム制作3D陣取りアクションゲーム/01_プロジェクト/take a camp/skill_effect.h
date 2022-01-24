//=============================================================================
//
// スキルエフェクト定義 [skill_effect.h]
// Author : 齋藤大行
//
//=============================================================================


//二重インクルード防止
#ifndef _SKILL_EFFECT_
#define _SKILL_EFFECT_

//=============================================================================
// インクルードファイル
//=============================================================================

#include "main.h"
#include "scene.h"
#include "base_Cylinder.h"
#include "skill_circle.h"
//*****************************
//マクロ定義
//*****************************

#define THIEF_EFFECT_POS D3DXVECTOR3(0.0f, 6.0f, 0.0f)
#define THIEF_EFFECT_SIZE D3DXVECTOR3(15.0f, 15.0f, 0.0f)

#define WIZARD_EFFECT_POS D3DXVECTOR3(0.0f, 6.0f, 0.0f)
#define WIZARD_EFFECT_SIZE D3DXVECTOR3(7.5f, 4.5f, 7.5f)

#define KNIGHT_EFFECT_POS D3DXVECTOR3(0.0f, 6.0f, 0.0f)
#define KNIGHT_EFFECT_SIZE D3DXVECTOR3(4.5f,4.5f,4.5f)

#define LANCER_EFFECT_POS D3DXVECTOR3(0.0f, 12.0f, 0.0f)
#define LANCER_EFFECT_SIZE D3DXVECTOR3(10.0f,22.6f,0.0f)

#define KNIGHT_EFFECT_LIFE (50)
#define ARCHER_EFFECT_LIFE (50)
#define WIZARD_EFFECT_LIFE (500)
#define LANCER_EFFECT_LIFE (50)
#define MAGICIAN_EFFECT_LIFE (50)
#define THIER_EFFECT_LIFE (50)

//*****************************
// 前方宣言
//*****************************
class CPlayer;

//=============================================================================
// クラス定義
//=============================================================================
class CSkill_effect 
{
public:
	//============
	//メンバ関数
	//============
	CSkill_effect();
	~CSkill_effect();



	//============
	// 状態列挙
	//============
	// スキルタイプ列挙

	typedef enum
	{
		SKILLTYPE_KNIGHT = 0,
		SKILLTYPE_ARCHER,
		SKILLTYPE_WIZARD,
		SKILLTYPE_WIZARD_FINALATTACK,
		SKILLTYPE_LANCER,
		SKILLTYPE_MAGICIAN,
		SKILLTYPE_THIER,
		SKILLTYPE_MAX
	}SKILLTYPE;

	// static
	static void Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col1 ,const D3DXCOLOR col2 ,const D3DXCOLOR col3,const int nlife, const SKILLTYPE type, CPlayer * pPlayer); // クラス生成


private:
	//============
	// メンバ変数
	//============
	D3DXVECTOR3			    m_pos;	 	    // 位置
	D3DXVECTOR3			    m_move;	 	    // 移動量
	D3DXVECTOR3			    m_rot;	 	    // 向き
	D3DXVECTOR3	            m_size;		    // 大きさ
	int                     m_nTile;	    // 寿命
	float		            m_fRotAngle;    // 回転角度
	float		            m_fFadeout;	    // フェードアウト　
	bool		            m_bFadeoutFlag; // フェードアウトのフラグ
	bool					m_bAddMode;     // 加算合成
	D3DXCOLOR	            m_col;		    // 色
	D3DXMATRIX				m_mtxWorld;     // ワールドマトリックス
	SKILLTYPE				m_type;			// エフェクトのタイプ
};

#endif
