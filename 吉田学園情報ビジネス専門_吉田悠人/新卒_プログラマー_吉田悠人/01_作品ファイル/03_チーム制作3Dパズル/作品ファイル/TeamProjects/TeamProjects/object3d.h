//=============================================================================
//
// 3D�I�u�W�F�N�g [object3d.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "object.h"

//=============================================================================
//�O���錾
//=============================================================================

//=============================================================================
//�I�u�W�F�N�g�N���X
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
    D3DXVECTOR3 m_pos;      // �ʒu
    D3DXVECTOR3 m_rot;      // ��]���
    D3DXVECTOR3 m_scale;    // �T�C�Y
};

#endif
