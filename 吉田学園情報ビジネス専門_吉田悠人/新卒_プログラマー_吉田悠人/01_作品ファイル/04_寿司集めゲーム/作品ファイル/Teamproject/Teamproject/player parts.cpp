//=============================================================================
//
//	�v���C���[�p�[�c[player parts.cpp]
//	Author:�g�c�I�l
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "player parts.h"
#include "resource manager.h"
#include "manager.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PARENT_DISTANCE (5.0f)	//�e�p�[�c�܂ł̋���
#define ROT_COUNT		(0.3f)	//�U������܂�

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayerParts::CPlayerParts(int nPriority):CBillboard(nPriority)
{
	m_pParent	= NULL;							//�e�p�[�c�̃|�C���^������
	m_Move		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ړ��ʏ�����
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayerParts::~CPlayerParts()
{

}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CPlayerParts::Update(void)
{
	//�ǔ�����
	Tracking();
	//��������
	Rot();

}

//=============================================================================
// �e�f�[�^�Z�b�^�[�����֐�
//=============================================================================
void CPlayerParts::SetParent(CScene3d* pParent)
{
	m_pParent = pParent;
}

//=============================================================================
// �ǔ������֐�
//=============================================================================
void CPlayerParts::Tracking(void)
{
	// �ʒu�擾
	D3DXVECTOR3	pos	= GetPos();			
	//�e�p�[�c�̈ʒu
	D3DXVECTOR3 PartsPos = m_pParent->GetPos();
	//�e�p�[�c�̌���
	D3DXVECTOR3 PartsRot = m_pParent->GetRot();
	//�ڕW�ʒu�v�Z
	m_Move = PartsPos + 
		D3DXVECTOR3((float)(cos(PartsRot.y - D3DXToRadian(90.0f))*PARENT_DISTANCE),
			0.0f,
			(float)(sin(PartsRot.y + D3DXToRadian(90.0f))*PARENT_DISTANCE));
	
	//�����擾
	D3DXVECTOR3 Diff = D3DXVECTOR3(m_Move.x - pos.x, 0.0f, m_Move.z - pos.z);
	//�ړ�����
	pos = D3DXVECTOR3(pos.x + (Diff.x*0.5f), 0.0f, pos.z + (Diff.z*0.5f));
	//�ʒu�Z�b�g
	SetPos(pos);

}

//=============================================================================
// ���������֐�
//=============================================================================
void CPlayerParts::Rot(void)
{
	//�p�x�̈ړ���
	float fRotMove = 0.0f;
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	//�����擾
	D3DXVECTOR3 rot = GetRot();
	//���������p�x
	fRotMove = atan2f((pos.x - m_Move.x), (pos.z - m_Move.z));
	//�����̊p�x
	float fDiff = ((D3DXToRadian(180.0f) - (fRotMove*-1.0f)) - (D3DXToRadian(180.0f) - (rot.y*-1.0f)))*-1.0f;
	//��]�����̊m�F(���v����true:�����v���false)
	bool bRotation = fRotMove>rot.y ? !(fRotMove - rot.y > D3DXToRadian(180.0f)) : rot.y - fRotMove  > D3DXToRadian(180.0f);

	//�����̏C��
	fDiff = (fDiff + (bRotation ? D3DXToRadian(-360.0f) : D3DXToRadian(360.0f)));
	fDiff = (float)(fmod(fDiff, D3DXToRadian(360.0f)));
	//��������
	rot.y = rot.y - (fDiff*ROT_COUNT);
	//�p�x�����ɒB������C��
	if (D3DXToDegree(rot.y) >= 360.0f
		|| D3DXToDegree(rot.y) <= -360.0f)
	{
		rot.y = 0.0f;
	}
	// �����ۑ�
	SetRot(rot);
}
