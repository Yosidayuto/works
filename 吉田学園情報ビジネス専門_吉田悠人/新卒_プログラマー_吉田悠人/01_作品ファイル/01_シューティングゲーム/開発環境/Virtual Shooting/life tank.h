//=============================================================================
//
//	���C�t�^���N[life tank.h]
//	Author:�g�c�@�I�l
//
//=============================================================================

#ifndef _LIFE_ICON_H_
#define _LIFE_ICON_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CLifeTank :public CScene2d
{
public:
	CLifeTank(int nPriorit = PRIORITY_UI_3);	//�R���X�g���N�^

	static HRESULT		Load(void);
	static void			Unload(void);
	static CLifeTank*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT				Init(void);		// ����������

private:
	static TEXTURE_DATA	m_TextureData;	// �e�N�X�`���f�[�^
};
#endif
