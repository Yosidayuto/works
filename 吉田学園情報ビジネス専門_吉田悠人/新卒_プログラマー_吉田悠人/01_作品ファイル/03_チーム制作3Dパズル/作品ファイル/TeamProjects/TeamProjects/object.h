//=============================================================================
//
// �I�u�W�F�N�g [object.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_
//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//�����ǉ�
typedef enum			 // �`��D��x
{						 
	PRIORITY_BG_0 = 0,		// �w�i
	PRIORITY_OBJECT_SEA,	// �C
	PRIORITY_OBJECT_PLAYER,	// ���@
	PRIORITY_OBJECT_CHILD,	// �`���C���h�u���b�N
	PRIORITY_OBJECT_ITEM,	// �A�C�e��
	PRIORITY_OBJECT_TILE,	// �^�C���u���b�N
	PRIORITY_RESULT,		// ���U���g
	PRIORITY_UI_1,			// UI�e�L�X�g��UI�A�C�R���Ȃ�
	PRIORITY_UI_3,			// �Q�[������UI
	PRIORITY_UI_0,			// UI�w�i
	PRIORITY_MAX,
}PRIORITY;

//=============================================================================
//�I�u�W�F�N�g�N���X
//=============================================================================
class CObject
{
public:

	//�I�u�W�F�N�g�^�C�v
    typedef enum
    {
		OBJTYPE_NONE = 0,
        OBJTYPE_PLAYER,
		OBJTYPE_ITEM,
		OBHTYPE_TILE,
        OBJTYPE_BLOCK,
		OBJTYPE_GOAL,
        OBJTYPE_MODEL,
        OBJTYPE_STAGE,
		OBJTYPE_MAX
    } OBJTYPE;

    CObject(int nPriority = PRIORITY_BG_0);		// �R���X�g���N�^
	virtual ~CObject();				// �f�X�g���N�^

    virtual HRESULT Init(void)	= 0;	// �������z�֐��Q
    virtual void	Uninit(void)  = 0;
    virtual void	Update(void)  = 0;
    virtual void	Draw(void)   = 0;

    static void		UpdateAll(void);	// �S�V�[���X�V�����֐�
	static void		DrawAll(void);		// �S�V�[���`�揈���֐� 
	static void		ReleaseAll(void);	// �S�V�[���I�������֐�

    void	SetObjType(OBJTYPE type);	// �I�u�W�F�N�g�^�C�v�Z�b�g
	OBJTYPE	GetObjType(void);			// �I�u�W�F�N�g�^�C�v�Q�b�^�[

	void	SetPriority(PRIORITY priority);	// �v���C�I���e�B�Z�b�g

    static CObject** GetTop(void);	// �I�u�W�F�N�g�g�b�v�Q�b�^�[

    CObject*	GetNext(void);		// ���̃I�u�W�F�N�g�擾
    CObject*	GetPrev(void);		// �O�̃I�u�W�F�N�g�擾


protected:
    void	Release(void);			//�V�[���̊J��

private:

    void		Death(void);				// ���X�g�폜��̃V�[���N���X�I������
	void ReConnection(void);                // ���X�g�\�����玩�g�������ĂȂ��Ȃ���
	static CObject* m_pTop[PRIORITY_MAX];	// �I�u�W�F�N�g�g�b�v
    static CObject* m_pCur[PRIORITY_MAX];	// �I�u�W�F�N�g
  
	CObject*	m_pPrev;					// ���̃I�u�W�F�N�g�N���X
    CObject*	m_pNext;					// �O�̃I�u�W�F�N�g�N���X
    int			m_nPriority;				// �D�揇�ʗp�ϐ�
    bool		m_bDestroy;					// �I�u�W�F�N�g�j���X�C�b�`
    OBJTYPE		m_objType;					// �I�u�W�F�N�g�^�C�v
};

#endif
