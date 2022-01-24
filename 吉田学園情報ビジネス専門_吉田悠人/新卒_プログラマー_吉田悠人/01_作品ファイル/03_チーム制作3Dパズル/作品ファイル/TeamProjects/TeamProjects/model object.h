//=============================================================================
//
//	オブジェクトモデル[model object.h]
//	Author:吉田悠人
//
//=============================================================================
#ifndef _MODEL_OBJECT_H_
#define _MODEL_OBJECT_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "model.h"

//=============================================================================
//クラス定義
//=============================================================================
class CModelObject : public CModel
{
public:

	CModelObject();
	virtual ~CModelObject();
	static CModelObject* Create(MODELDATA Data,CObject* pParentObject, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

private:
	MODELDATA m_ModelData;

};
#endif
