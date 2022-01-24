//=============================================================================
//
// ����UI���� [weapons_ui.h]
// Author : �g�c�@�I�l
//
//=============================================================================
#ifndef _WEAPONS_UI_H_
#define _WEAPONS_UI_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "object2d.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define WEAPONS_UI_AR_TEXTURE 	"Data/Texture/AR_UI.png"	// �ǂݍ��ޗp��AR����e�N�X�`��
#define WEAPONS_UI_HG_TEXTURE	"Data/Texture/HG_UI.png"	// �ǂݍ��ޗp��HG����e�N�X�`��
#define WEAPONS_TEXTURE_MAX 2								// �e�N�X�`����
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CWeapons_ui :public CObject2D
{
public:
	CWeapons_ui();
	static HRESULT Load(void);
	static void Unload(void);
	static CWeapons_ui * Create(void);
	void Update(void);

	void Gleams(void);	//���鏈���֐�
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[WEAPONS_TEXTURE_MAX];		// �e�N�X�`���ւ̃|�C���^
	static char *m_cFileName[WEAPONS_TEXTURE_MAX];					// �t�@�C���̖��O

	int nCountCol;		//���܂Ō��邩�J�E���g�ϐ�
};
#endif