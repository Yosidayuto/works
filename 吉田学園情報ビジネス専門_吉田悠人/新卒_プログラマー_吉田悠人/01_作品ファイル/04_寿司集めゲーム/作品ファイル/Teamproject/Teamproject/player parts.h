//=============================================================================
//
// �v���C���[�p�[�c [player parts.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _PLAYER_PARTS_H_
#define _PLAYER_PARTS_H_

//=============================================================================
// �w�b�_�[�t�@�C��
//=============================================================================
#include "scene3d.h"
#include "billboard.h"
#include "food base.h"

//=============================================================================
//�N���X��`
//=============================================================================
class CPlayerParts : public CBillboard
{
public:
	CPlayerParts(int nPriority = 3);
	~CPlayerParts();
	void Update(void);
	void SetParent(CScene3d* pParent);											// �e�f�[�^�Z�b�^�[
	CFoodBase::FOOD_TYPE GetType(void) { return m_Type; };						//�^�C�v�Q�b�^�[
	void				 SetType(CFoodBase::FOOD_TYPE Type) { m_Type = Type; };	//�^�C�v�Z�b�^�[
private: 
	void Tracking(void);		// �ǔ�����
	void Rot(void);				// ��������

	CFoodBase::FOOD_TYPE m_Type;	// �p�[�c�̃^�C�v
	CScene3d* 	m_pParent;			// �e�p�[�c�̃|�C���^
	D3DXVECTOR3 m_Move;				// �ړ���
	const int	m_nModel = 1;		// �e�N�X�`���ԍ�
};
#endif // !_BLOCK_H_


