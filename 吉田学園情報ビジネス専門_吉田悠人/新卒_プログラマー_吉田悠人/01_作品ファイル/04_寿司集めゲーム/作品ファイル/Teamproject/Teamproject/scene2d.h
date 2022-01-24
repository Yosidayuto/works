//=============================================================================
//
// 2D�V�[���Ǘ����� [scene2d.h]
// Author : �ѐ�ї���
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

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
class CScene2d :public CScene
{
public:
	CScene2d(int nPriority = 3);
	~CScene2d();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetPos(D3DXVECTOR3 Pos);
	void SetSize(D3DXVECTOR3 Size);
	void SetRot(D3DXVECTOR3 Rot);
	void SetTexture(D3DXVECTOR2 aTex[NUM_VERTEX]);
	void SetColor(D3DXCOLOR Col);
	void SetScale(float fScale);
	D3DXCOLOR GetColor(void) { return m_Col; };
	D3DXVECTOR3 GetPos(void) { return m_Pos; };
	D3DXVECTOR3 GetSize(void) { return m_Size; };
	D3DXVECTOR3 GetRot(void) { return m_Rot; };
	float GetScale(void) { return m_fScale; };
private:
	LPDIRECT3DTEXTURE9		m_pTexture;				//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_Pos;					//���W
	D3DXVECTOR3				m_Size;					//�T�C�Y
	D3DXVECTOR3				m_Rot;					//����
	D3DXVECTOR2				m_aTex[NUM_VERTEX];		//�e�N�X�`����UV���W
	D3DXCOLOR	 			m_Col;		//���_�J���[
	float					m_fScale;				//�k��
	float					m_fAngle;				//�p�x
	float					m_fLength;				//����
};
#endif