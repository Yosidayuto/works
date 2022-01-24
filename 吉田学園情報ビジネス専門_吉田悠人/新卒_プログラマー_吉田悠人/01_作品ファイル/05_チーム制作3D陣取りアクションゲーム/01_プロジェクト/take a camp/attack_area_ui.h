//===================================================
//
// 攻撃範囲UIの処理 [attack_area_ui.h]
// Author : 増澤未来
//
//===================================================
#ifndef  _ATTACK_AREA_UI_H_
#define  _ATTACK_AREA_UI_H_

//===================================================
// インクルードファイル
//===================================================
#include "scene2d.h"
#include "resource_character.h"
#include "resource_attack.h"

//===================================================
// マクロ定義
//===================================================

//===================================================
// クラス宣言
//===================================================
class CAttackAreaUi : public CScene2d
{
public:

    //===============================================
    // 列挙
    //===============================================
    enum FadeMode
    {
        FADE_NONE = -1,
        FADE_IN,
        FADE_OUT,
    };

	//===============================================
	// メンバ関数
	//===============================================
	CAttackAreaUi();
	~CAttackAreaUi();

	static CAttackAreaUi *Create(D3DXVECTOR3 pos);    // 生成処理

	HRESULT Init(void);
	void Update(void);
	void Draw(void);

	void SetDrawFlag(bool bDraw) { m_bDraw = bDraw; }
	void SwitchDrawFlag(void) { m_bDraw ^= true; }
	void SetCharaType(CResourceCharacter::CHARACTER_TYPE type) { m_nCharaType = type; }

	void Reset(void);
private:
    // フェードインアウトの処理
    void Fade(void);

	//===============================================
	// メンバ変数宣言
	//===============================================
	int m_nLevel;
	CResourceCharacter::CHARACTER_TYPE m_nCharaType;
	bool m_bDraw;
	int m_nCntLevel;
	LPDIRECT3DTEXTURE9 m_apTex[CResourceCharacter::CHARACTER_MAX];
    FadeMode m_FadeMode;

};
#endif
