//=============================================================================
//
//�@�~���G�t�F�N�g���� [effect_cylinder.h]
// Author : �ѐ�ї���
//
//=============================================================================
#ifndef _EFFECT_CYLINDER_H_
#define _EFFECT_CYLINDER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene3d.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CEffectCylinder :public CScene3d
{
public:
	CEffectCylinder(int nPriority = 3);
	~CEffectCylinder();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetColor(D3DXCOLOR Col);
	D3DXCOLOR GetColor(void) { return m_Col; };
private:
	D3DXMATRIX m_mtxWorld; //���[���h�}�g���N�X
	LPDIRECT3DTEXTURE9		m_pTexture;				//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;//�C���f�b�N�X�o�b�t�@�|�C���^
	D3DXCOLOR	 			m_Col;		//���_�J���[
};
#endif