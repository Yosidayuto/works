//=============================================================================
//
//	�z�[�~���O�A�C�R��[homing icon.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _HOMING_ICON_H_
#define _HOMING_ICON_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CHomingIcon :public CScene2d
{
public:
	CHomingIcon();	//�R���X�g���N�^

	static HRESULT			Load(void);
	static void				Unload(void);
	static CHomingIcon*		Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	static TEXTURE_DATA	m_TextureData;	// �e�N�X�`���f�[�^
};
#endif
