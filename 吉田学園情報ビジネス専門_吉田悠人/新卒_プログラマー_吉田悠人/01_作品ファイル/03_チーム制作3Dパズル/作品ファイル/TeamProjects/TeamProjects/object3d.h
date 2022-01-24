//=============================================================================
//
// 3Dオブジェクト [object3d.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "object.h"

//=============================================================================
//前方宣言
//=============================================================================

//=============================================================================
//オブジェクトクラス
//=============================================================================
class CObject3D : public CObject
{
public:
    CObject3D(int nPriority = OBJTYPE_NONE);
    virtual ~CObject3D();
    virtual HRESULT Init(void);
    virtual void Uninit(void);
    virtual void Update(void);
    virtual void Draw(void);
  
	void SetPosition(D3DXVECTOR3 pos);
    void SetRotation(D3DXVECTOR3 rot);
    void SetScale(D3DXVECTOR3 scale);
    D3DXVECTOR3 GetPosition(void);
    D3DXVECTOR3 GetRotation(void);
    D3DXVECTOR3 GetScale(void);

private:
    D3DXVECTOR3 m_pos;      // 位置
    D3DXVECTOR3 m_rot;      // 回転情報
    D3DXVECTOR3 m_scale;    // サイズ
};

#endif
