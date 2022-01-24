//=============================================================================
//
// エフェクト用寿司処理 [effect sushi.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _EFFECT_SUSHI_H_
#define _EFFECT_SUSHI_H_

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "scene2d.h"

//=============================================================================
// クラス定義
//=============================================================================
class CEffectSushi : public CScene2d
{
public:
	typedef enum		//フードタイプ
	{
		TYPE_EBI = 0,	// エビ
		TYPE_EGG,		// 卵
		TYPE_IKURA,		// イクラ
		TYPE_SALMON,	// サーモン
		TYPE_TUNA,		// マグロ
		TYPE_MAX
	}FOOD_TYPE;

	CEffectSushi(int nPriority = 0);
	~CEffectSushi();

	static CEffectSushi *Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size, int nType);
	void				 Draw(void);
private:
	const int	m_nEffectSushiTexture[TYPE_MAX] = {10,11,12,13,14};	//テクスチャ番号
};
#endif // !_EFFECT_SUSHI_H_
