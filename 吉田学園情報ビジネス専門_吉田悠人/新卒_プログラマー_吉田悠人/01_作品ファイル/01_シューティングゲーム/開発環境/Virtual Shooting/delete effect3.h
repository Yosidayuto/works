//=============================================================================
//
// �{�X�f���[�g�G�t�F�N�g3���� [delete effect3.h]
// Author : �g�c�I�l
//
//=============================================================================

#ifndef _DELETE_EFFECT_3_H_
#define _DELETE_EFFECT_3_H_
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"
#include "boss effect base.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CDeleteEffect3 :public CBossEffectBase
{
public:
	CDeleteEffect3();						// �R���X�g���N�^

	static HRESULT			Load(void);		// �e�N�X�`���ǂݍ���
	static void				Unload(void);	// �e�N�X�`���̔j��
	static CDeleteEffect3*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ��������

private:
	static TEXTURE_DATA		m_TextureData;	// �e�N�X�`���f�[�^

};
#endif