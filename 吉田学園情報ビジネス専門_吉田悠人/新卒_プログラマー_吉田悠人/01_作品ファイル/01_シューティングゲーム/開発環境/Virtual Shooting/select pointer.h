//=============================================================================
//
// �Z���N�g�̃}�E�X�|�C���^�[ [select pointer.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _SELECT_POINTER_H_
#define _SELECT_POINTER_H_
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "main.h"
#include "mouse pointer.h"
//=============================================================================
// �N���X��`
//=============================================================================
class CSelectPointer : public CPointer
{
public:
	CSelectPointer();						// �R���X�g���N�^
	static HRESULT			Load(void);		// �e�N�X�`���ǂݍ���
	static void				Unload(void);	// �e�N�X�`���j��
	static CSelectPointer*	Create(void);	// �쐬����
	void	Update(void);					// �X�V����
private:
	static TEXTURE_DATA	m_TextureData;	//�e�N�X�`���f�[�^
};
#endif // !_POLYGON_H_
