//=============================================================================
//
//	�o���b�g�A�C�R��[bullet icon.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _BULLET_ICON_H_
#define _BULLET_ICON_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CBulletIcon :public CScene2d
{
public:
	CBulletIcon();	//�R���X�g���N�^

	static HRESULT			Load(void);
	static void				Unload(void);
	static CBulletIcon*		Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	static TEXTURE_DATA	m_TextureData;	// �e�N�X�`���f�[�^
};
#endif
