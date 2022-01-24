//=============================================================================
//
//	2D�|���S��[object2d.h]
//	Author:�g�c�I�l
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "object.h"

//=============================================================================
// �O���錾
//=============================================================================
typedef struct
{
	LPDIRECT3DTEXTURE9	m_pTexture;	// �e�N�X�`���ւ̃|�C���^
	char*				m_cFileName;// �t�@�C���̖��O
} TEXTURE_DATA;


//=============================================================================
// �N���X��`
//=============================================================================
class CObject2D : public CObject
{
public:
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX
	}FADE_2D;

    CObject2D(int nPriority = OBJTYPE_NONE);	// �R���X�g���N�^
    virtual ~CObject2D();			// �f�X�g���N�^
	
	static CObject2D*	Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const float frot,const LPDIRECT3DTEXTURE9 pTexture, const int nPriority);    // �|���S����������
	virtual HRESULT		Init(void);			// ����������
    virtual void		Uninit(void);		// �I������
    virtual void		Update(void);		// �X�V����
    virtual void		Draw(void);			// �`�揈��

    void SetPos(const D3DXVECTOR3 pos);		// �ʒu�Z�b�g
    void SetRot(const float rot);			// �����Z�b�g
    void SetSize(const D3DXVECTOR3 size);	// �T�C�Y�Z�b�g
	void SetCol(const D3DCOLOR col);		// �J���[�Z�b�g
											   
	D3DXVECTOR3 GetPos(void);				// �ʒu�Q�b�^�[
	D3DXVECTOR3 GetSize(void);				// �T�C�Y�Q�b�^�[
	D3DCOLOR    GetCol(void);
	float		GetRot(void);				// �����Q�b�^�[

    void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	// �e�N�X�`���Z�b�g
    void SetTexPos(D3DXVECTOR2* pTexPos);			// �e�N�X�`��UV�Z�b�g
	void Fade2d(void);
private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
    LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���ւ̃|�C���^
    D3DXVECTOR3 m_pos;					// �|���S���̈ʒu
    D3DXVECTOR3 m_size;					// �|���S���̑傫��
    D3DXCOLOR	m_col;					// �|���S���̃J���[
    float		m_fRot;					// �|���S���̌���
	FADE_2D     m_fade;
};

#endif
