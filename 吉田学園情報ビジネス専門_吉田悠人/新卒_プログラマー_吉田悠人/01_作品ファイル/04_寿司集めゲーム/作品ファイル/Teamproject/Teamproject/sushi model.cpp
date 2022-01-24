//=============================================================================
//
//	���i���f��[model sushi.cpp]
//	Author:�ѐ�
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "sushi model.h"
#include "resource manager.h"

#define MOVE_SPEED (5)
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSushiModel::CSushiModel(int nPriority) :CModel(nPriority)
{
	m_RandAddRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSushiModel::~CSushiModel()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CSushiModel * CSushiModel::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size, int nModel)
{
	//�������m��
	CSushiModel* pWinnerPlayer = nullptr;
	pWinnerPlayer = new CSushiModel;
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	MODELDATA Model = pResource->ModelLoad(20 + nModel);

	//NULL�`�F�b�N
	if (pWinnerPlayer != nullptr)
	{
		//�ʒu�ݒ�
		pWinnerPlayer->SetPos(Pos);
		//�����ݒ�
		pWinnerPlayer->SetRot(Rot);
		//�J���[�ݒ�
		pWinnerPlayer->SetSize(Size);
		//���f���f�[�^�ݒ�
		pWinnerPlayer->SetModelData(Model);
		float nRandRotX = float(rand() % 100) / 10000;
		float nRandRotY = float(rand() % 100) / 10000;
		float nRandRotZ = float(rand() % 100) / 10000;
		pWinnerPlayer->m_RandAddRot = D3DXVECTOR3(nRandRotX, nRandRotY, nRandRotZ);
		//����������
		pWinnerPlayer->Init();
	}

	return pWinnerPlayer;
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CSushiModel::Update(void)
{
	SetRot(GetRot() + m_RandAddRot);

	SetPos(D3DXVECTOR3(GetPos().x, GetPos().y, GetPos().z - MOVE_SPEED));

	//��ʊO�ɏo�Ă��邩
	if (GetPos().z <= -500)
	{
		//��ʊO�ɂ��鎞�ɏ���
		Uninit();
	}
}
