//=============================================================================
//
// ���i���f�� [model sushi.h]
// Author : �ѐ�
//
//=============================================================================
#ifndef _SUSHI_MODEL_H_
#define _SUSHI_MODEL_H_

//=============================================================================
// �w�b�_�[�t�@�C��
//=============================================================================
#include "model.h"

//=============================================================================
//�N���X��`
//=============================================================================
class CSushiModel : public CModel
{
public:
	CSushiModel(int nPriority = 6);
	~CSushiModel();
	static CSushiModel* Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size, int nModel);	//��������
	void			Update(void);
private:
	D3DXVECTOR3 m_RandAddRot;
};
#endif // !_SUSHI_MODEL_H_


