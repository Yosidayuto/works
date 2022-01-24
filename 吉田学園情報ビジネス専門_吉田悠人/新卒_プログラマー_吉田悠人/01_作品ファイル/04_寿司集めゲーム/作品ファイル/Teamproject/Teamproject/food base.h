//=============================================================================
//
// �H�ו��x�[�X [food base.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _BAIT_H_
#define _BAIT_H_
//=============================================================================
// �w�b�_�[�t�@�C��
//=============================================================================
#include "model.h"
#include "billboard.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CFoodBase :public CBillboard
{
public:
	CFoodBase(int nPriority=3);
	~CFoodBase();
	typedef enum		//�t�[�h�^�C�v
	{
		TYPE_EBI,		//�G�r
		TYPE_EGG,		//��
		TYPE_IKURA,		//�C�N��
		TYPE_SALMON,	//�T�[����
		TYPE_TUNA,		//�}�O��
		TYPE_MAX		
	}FOOD_TYPE;

	void	Update(void);
		
	void		Collision(void);											// �����蔻��֐�
	void		SetPoint(int nPoint);										// �|�C���g�Z�b�^�[
	int			GetPoint(void) { return m_nPoint; }							// �|�C���g�Q�b�^�[
	void		SetFoodType(FOOD_TYPE FoodType) { m_FoodType = FoodType; }	// �t�[�h�^�C�v�Z�b�^�[
	FOOD_TYPE	GetFoodType(void) { return m_FoodType; }					// �t�[�h�^�C�v�Q�b�^�[
private:
	int			m_nPoint;		// �|�C���g���l
	FOOD_TYPE	m_FoodType;		// �t�[�h�^�C�v
};

#endif