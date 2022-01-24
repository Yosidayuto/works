//=============================================================================
//
// フィールド管理 [fieldmanager.h]
// Author : 林川紗梨夏
//
//=============================================================================
#ifndef _FIELD_MANAGER_H_
#define _FIELD_MANAGER_H_

#include "food base.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CLocationPoint;
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************

class CFieldManager : public CScene
{
public:
	CFieldManager(int nPriority = 8);
	~CFieldManager();

	static CFieldManager *Create(D3DXVECTOR3 Pos,D3DXVECTOR3 Size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetSize(D3DXVECTOR3 Size);
private:

	void EdgeCollision(void);
	D3DXVECTOR3 m_size;
	D3DXVECTOR3 m_originsize;

};
#endif // !_MAP_MANAGER_H_


