//=============================================================================
//
//	�X�R�A�w�i[score bar.h]
//	Author:�g�c�@�I�l
//
//=============================================================================
#ifndef _SCORE_BAR_H_
#define _SCORE_BAR_H_
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CScoreBar :public CScene2d
{
public:
	CScoreBar(int nPriorit= PRIORITY_SCENE);	//�R���X�g���N�^

	static HRESULT			Load(void);
	static void				Unload(void);
	static CScoreBar*		Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	static TEXTURE_DATA	m_TextureData;	// �e�N�X�`���f�[�^
};
#endif
