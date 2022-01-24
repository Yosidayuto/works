//=============================================================================
//
// �G�t�F�N�g�p���i���� [effect sushi.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _EFFECT_SUSHI_H_
#define _EFFECT_SUSHI_H_

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "scene2d.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CEffectSushi : public CScene2d
{
public:
	typedef enum		//�t�[�h�^�C�v
	{
		TYPE_EBI = 0,	// �G�r
		TYPE_EGG,		// ��
		TYPE_IKURA,		// �C�N��
		TYPE_SALMON,	// �T�[����
		TYPE_TUNA,		// �}�O��
		TYPE_MAX
	}FOOD_TYPE;

	CEffectSushi(int nPriority = 0);
	~CEffectSushi();

	static CEffectSushi *Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size, int nType);
	void				 Draw(void);
private:
	const int	m_nEffectSushiTexture[TYPE_MAX] = {10,11,12,13,14};	//�e�N�X�`���ԍ�
};
#endif // !_EFFECT_SUSHI_H_
