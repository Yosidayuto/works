//=============================================================================
//
// 3D�|���S���Ǘ����� [polygon3d.h]
// Author : �ѐ�ї���
//
//=============================================================================
#ifndef _POLYGON3D_H_
#define _POLYGON3D_H_

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
class CPolygon3d :public CScene3d
{
public:
	CPolygon3d(int nPriority = 3);
	~CPolygon3d();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetTexture(D3DXVECTOR2 aTex[NUM_VERTEX]);
	void SetColor(D3DXCOLOR Col);
	void SetScale(float fScale);
	D3DXCOLOR GetColor(void) { return m_Col; };
	float GetScale(void) { return m_fScale; };
private:
	D3DXMATRIX m_mtxWorld; //���[���h�}�g���N�X
	LPDIRECT3DTEXTURE9		m_pTexture;				//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR2				m_aTex[NUM_VERTEX];		//�e�N�X�`����UV���W
	D3DXCOLOR	 			m_Col;		//���_�J���[
	float					m_fScale;				//�k��
	float					m_fAngle;				//�p�x
	float					m_fLength;				//����
};
#endif