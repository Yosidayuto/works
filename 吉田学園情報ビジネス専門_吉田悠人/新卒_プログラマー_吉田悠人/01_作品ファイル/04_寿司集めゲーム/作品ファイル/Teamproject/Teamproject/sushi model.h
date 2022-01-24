//=============================================================================
//
// 寿司モデル [model sushi.h]
// Author : 林川
//
//=============================================================================
#ifndef _SUSHI_MODEL_H_
#define _SUSHI_MODEL_H_

//=============================================================================
// ヘッダーファイル
//=============================================================================
#include "model.h"

//=============================================================================
//クラス定義
//=============================================================================
class CSushiModel : public CModel
{
public:
	CSushiModel(int nPriority = 6);
	~CSushiModel();
	static CSushiModel* Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size, int nModel);	//生成処理
	void			Update(void);
private:
	D3DXVECTOR3 m_RandAddRot;
};
#endif // !_SUSHI_MODEL_H_


