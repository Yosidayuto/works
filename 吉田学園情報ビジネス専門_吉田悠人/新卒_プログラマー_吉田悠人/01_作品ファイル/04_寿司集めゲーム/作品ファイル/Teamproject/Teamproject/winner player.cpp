//=============================================================================
//
//	���҃v���C���[[winner player.cpp]
//	Author:�g�c�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "winner player.h"
#include "resource manager.h"
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWinnerPlayer::CWinnerPlayer(int nPriority) :CModel(nPriority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CWinnerPlayer::~CWinnerPlayer()
{

}

//=============================================================================
// ���������֐�
//=============================================================================
CWinnerPlayer * CWinnerPlayer::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size, int nModel)
{
	//�������m��
	CWinnerPlayer* pWinnerPlayer = nullptr;
	pWinnerPlayer = new CWinnerPlayer;
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	MODELDATA Model = pResource->ModelLoad(nModel);

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
		//����������
		pWinnerPlayer->Init();
	}

	return pWinnerPlayer;
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CWinnerPlayer::Update(void)
{

}
