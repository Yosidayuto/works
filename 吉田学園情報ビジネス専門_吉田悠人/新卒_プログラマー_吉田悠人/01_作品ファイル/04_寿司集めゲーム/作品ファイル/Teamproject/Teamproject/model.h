//=============================================================================
//
//	���f���f�[�^����[model.h]
//	Author:�g�c�I�l
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "scene3d.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_MATERIAL (20)
//=============================================================================
//�N���X��`
//=============================================================================
class CModel : public CScene3d
{
public:

	typedef struct
	{
		LPD3DXBUFFER pBuffMat;                        // �}�e���A�����ւ̃|�C���^
		DWORD nNumMat;                                // �}�e���A�����̐�
		LPD3DXMESH pMesh;                             // ���b�V�����ւ̃|�C���^
		LPDIRECT3DTEXTURE9 pTexture[MAX_MATERIAL];    // �e�N�X�`���ւ̃|�C���^
		D3DXMATRIX mtxWorld;                          // ���[���h���
	} MODELDATA;

	CModel(int nPriority = 3);
	virtual ~CModel();
    virtual void	Draw(void);
    
	MODELDATA	GetModelData(void);					// ���f���f�[�^�Q�b�^�[
	void		SetModelData(MODELDATA Model);		// ���f���f�[�^�Z�b�^�[
	float		GetAlphaValue(void);				// ���f���J���[�Q�b�^�[
	void		SetAlphaValue(float fAlphaValue);	// ���f���J���[�Z�b�^�[

private:
    MODELDATA	m_ModelData;		// ���f���f�[�^
	float		m_fAlphaValue;		// �A���t�@�l
};
#endif
