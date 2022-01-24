//=============================================================================
//
// プレイヤーの番号UI [player number.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _PLAYER_NUMBER_H_
#define _PLAYER_NUMBER_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// クラス定義
//=============================================================================
class CPlayerNumber :public CScene2d
{
public:
	CPlayerNumber();
	~CPlayerNumber();

	static CPlayerNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumber);

private:
	const int nPlayerNumberTexture[MAX_PLAYER] = { 52,53,54,55 };		//テクスチャ番号
};

#endif