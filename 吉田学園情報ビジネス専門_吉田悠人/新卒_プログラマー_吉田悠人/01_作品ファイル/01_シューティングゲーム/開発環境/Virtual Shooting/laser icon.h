//=============================================================================
//
//	���[�U�[�A�C�R��[laser icon.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _LASER_ICON_H_
#define _LASER_ICON_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CLaserIcon :public CScene2d
{
public:
	CLaserIcon();	//�R���X�g���N�^

	static HRESULT		Load(void);
	static void			Unload(void);
	static CLaserIcon*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	static TEXTURE_DATA	m_TextureData;	// �e�N�X�`���f�[�^
};
#endif
