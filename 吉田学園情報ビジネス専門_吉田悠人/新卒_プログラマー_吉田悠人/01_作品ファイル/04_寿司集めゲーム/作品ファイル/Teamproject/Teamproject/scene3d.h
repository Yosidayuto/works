//=============================================================================
//
// 3D�V�[���Ǘ����� [scene3d.h]
// Author : �ѐ�ї���
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CScene3d :public CScene
{
public:
	CScene3d(int nPriority = 3);
	virtual ~CScene3d();
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	void SetPos(D3DXVECTOR3 Pos);
	void SetRot(D3DXVECTOR3 Rot);
	void SetSize(D3DXVECTOR3 Size);
	D3DXVECTOR3 GetPos(void) { return m_Pos; };
	D3DXVECTOR3 GetRot(void) { return m_Rot; };
	D3DXVECTOR3 GetSize(void) { return m_Size; };
private:
	D3DXVECTOR3 m_Pos;			//���W
	D3DXVECTOR3 m_Rot;			//����
	D3DXVECTOR3 m_Size;			//�T�C�Y
};
#endif