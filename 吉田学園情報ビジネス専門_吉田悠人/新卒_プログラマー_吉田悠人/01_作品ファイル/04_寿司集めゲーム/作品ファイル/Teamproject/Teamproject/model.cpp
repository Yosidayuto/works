//=============================================================================
//
//	���f���f�[�^����[model.cpp]
//	Author:�g�c�I�l
//
//=============================================================================

//=============================================================================
// �w�b�_�[�t�@�C��
//=============================================================================
#include "model.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CModel::CModel(int nPriority):CScene3d(nPriority)
{
    //���f���f�[�^�̏�����
    ZeroMemory(&m_ModelData, sizeof(m_ModelData));
	SetObjType(OBJTYPE_MODEL);
	m_fAlphaValue = 1.0f;	//�J���[
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CModel::~CModel()
{

}


//=============================================================================
//�`�揈��
//=============================================================================
void CModel::Draw(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
    D3DMATERIAL9 matDef;
    D3DXMATERIAL* pMat;
	
	//�s��v�Z�p
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;
	//���[���h�ϊ��s��̏�����
	D3DXMatrixIdentity(&m_ModelData.mtxWorld);

	//�g��k���s��̐����ƌv�Z
	D3DXMatrixScaling(&mtxScale, GetSize().x, GetSize().y, GetSize().z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxScale);

	//��]�s��̐����ƌv�Z
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxRot);

	//���s�ړ��s��̐����ƌv�Z
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxTrans);

	//�v�Z���ʂ�K�p
	pDevice->SetTransform(D3DTS_WORLD, &m_ModelData.mtxWorld);


    //�}�e���A�����̎擾
    pDevice->GetMaterial(&matDef);

    if(m_ModelData.pBuffMat != NULL)
    {
        pMat = (D3DXMATERIAL*)m_ModelData.pBuffMat->GetBufferPointer();
    }

    //�}�e���A�����̐ݒ�ƃ}�e���A�����Ƃɕ`��
    for(int nCntMat = 0; nCntMat < (int)m_ModelData.nNumMat; nCntMat++)
    {
		//�A���t�@�l�ݒ�
		pMat[nCntMat].MatD3D.Diffuse.a = m_fAlphaValue;
		//�}�e���A���̐ݒ�
        pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		// �e�N�X�`��
        pDevice->SetTexture(0, m_ModelData.pTexture[nCntMat]);
		//���f���p�[�c�̕`��
        m_ModelData.pMesh->DrawSubset(nCntMat);
    }

    //�}�e���A�����̃��Z�b�g
    pDevice->SetMaterial(&matDef);
}

//=============================================================================
// ���f���f�[�^�Q�b�^�[
//=============================================================================
CModel::MODELDATA CModel::GetModelData(void)
{
    return m_ModelData;
}

//=============================================================================
// ���f���f�[�^�Z�b�^�[
//=============================================================================
void CModel::SetModelData(MODELDATA Model)
{
	m_ModelData = Model;
}

//=============================================================================
// ���f���J���[�Q�b�^�[
//=============================================================================
float CModel::GetAlphaValue(void)
{
	return m_fAlphaValue;
}

//=============================================================================
// ���f���J���[�Z�b�^�[
//=============================================================================
void CModel::SetAlphaValue(float fAlphaValue)
{
	m_fAlphaValue = fAlphaValue;
}
