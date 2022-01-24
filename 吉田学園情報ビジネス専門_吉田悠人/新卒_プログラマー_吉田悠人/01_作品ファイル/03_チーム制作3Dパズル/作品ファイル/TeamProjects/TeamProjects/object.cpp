//=============================================================================
//
// �I�u�W�F�N�g [object.cpp]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"
#include "object2d.h"
#include "renderer.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
CObject* CObject::m_pTop[PRIORITY_MAX] = {};
CObject* CObject::m_pCur[PRIORITY_MAX] = {};

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CObject::CObject(int nPriority)
{
    //����������
    m_bDestroy       = false;
    //���X�g�\���ɒǉ�
    m_nPriority = nPriority;
    if(m_pTop[nPriority] != NULL)
    {
        m_pCur[nPriority]->m_pNext = this;
    }
    else
    {
        m_pTop[nPriority] = this;
    }
    this->m_pPrev     = m_pCur[nPriority];
    this->m_pNext     = NULL;
    m_pCur[nPriority] = this;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CObject::~CObject()
{
}

//=============================================================================
//�X�V����
//=============================================================================
void CObject::UpdateAll(void)
{
    CObject* pNext     = NULL;
    CObject* pNextBuff = NULL;
    int ObjectCount    = 0;
    //���X�g�Ɋ܂܂��I�u�W�F�N�g���X�V
    for(int nCount = 0; nCount < PRIORITY_MAX; nCount++)
    {
		//NULL�`�F�b�N
        if(m_pTop[nCount] != NULL)
        {
            pNext = m_pTop[nCount];
			//NULL�`�F�b�N
            while(pNext != NULL && !pNext->m_bDestroy)
            {
                pNextBuff = pNext->m_pNext;
                pNext->Update();
                pNext = pNextBuff;
                ObjectCount++;
            }
        }
    }

    //���S�t���O�����Ă����E��
    for(int nCount = 0; nCount < PRIORITY_MAX; nCount++)
    {
		//NULL�`�F�b�N
        if(m_pTop[nCount] != NULL)
        {
            pNext = m_pTop[nCount];
			//NULL�`�F�b�N
            while(pNext != NULL)
            {
                pNextBuff = pNext->m_pNext;
                if(pNext->m_bDestroy == true)
                {
                    pNext->Death();
                }
                pNext = pNextBuff;
            }
        }
    }
}

//=============================================================================
//�`�揈��
//=============================================================================
void CObject::DrawAll(void)
{
    CObject* pNext = NULL;
    for(int nCount = 0; nCount < PRIORITY_MAX; nCount++)
    {
		//NULL�`�F�b�N
        if(m_pTop[nCount] != NULL)
        {
            pNext = m_pTop[nCount];
            while(pNext != NULL)
            {
                pNext->Draw();
                pNext = pNext->m_pNext;
            }
        }
    }
}

//=============================================================================
//�S�J������
//=============================================================================
void CObject::ReleaseAll(void)
{
    CObject* pNext     = NULL;
    CObject* pNextBuff = NULL;
    for(int nCount = 0; nCount < PRIORITY_MAX; nCount++)
    {
		//NULL�`�F�b�N
        if(m_pTop[nCount] != NULL)
        {
            pNext = m_pTop[nCount];
            while(pNext != NULL)
            {
                pNextBuff = pNext->m_pNext;
                pNext->Uninit();
                delete pNext;
                pNext = pNextBuff;
            }
        }
        m_pTop[nCount] = NULL;
        m_pCur[nCount] = NULL;
    }
}

//=============================================================================
//�J������
//=============================================================================
void CObject::Release(void)
{
    //���S�t���O�𗧂Ă�
    m_bDestroy = true;
}

//=============================================================================
//���X�g����������Ď��g�������鏈��
//=============================================================================
void CObject::Death(void)
{
    //������Ƃ��̏���
    if(this == m_pTop[m_nPriority])
    {
        m_pTop[m_nPriority] = m_pNext;
    }
    if(this == m_pCur[m_nPriority])
    {
        m_pCur[m_nPriority] = m_pPrev;
    }
    if(m_pNext != NULL)
    {
        m_pNext->m_pPrev = m_pPrev;
    }
    if(m_pPrev != NULL)
    {
        m_pPrev->m_pNext = m_pNext;
    }
    delete this;
}

void CObject::ReConnection(void)
{
	if (this == m_pTop[m_nPriority])
	{
		m_pTop[m_nPriority] = m_pNext;
	}
	if (this == m_pCur[m_nPriority])
	{
		m_pCur[m_nPriority] = m_pPrev;
	}
	if (m_pNext != NULL)
	{
		m_pNext->m_pPrev = m_pPrev;
	}
	if (m_pPrev != NULL)
	{
		m_pPrev->m_pNext = m_pNext;
	}
}

//=============================================================================
//�Z�b�^�[�֐�
//=============================================================================
void CObject::SetObjType(OBJTYPE type)
{
	// �I�u�W�F�N�g�^�C�v�̐ݒ�
    m_objType = type;
}


//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�Q�b�^�[�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CObject** CObject::GetTop(void)
{
    return m_pTop;
}

CObject* CObject::GetNext(void)
{
    return m_pNext;
}

CObject* CObject::GetPrev(void)
{
    return m_pPrev;
}

//=============================================================================
//�^�C�v�Q�b�g����
//=============================================================================
CObject::OBJTYPE CObject::GetObjType(void)
{
    return m_objType;
}

void CObject::SetPriority(PRIORITY priority)
{
	ReConnection();

	// �v���C�I���e�B�̐ݒ�
	m_nPriority = priority;

	if (m_pTop[m_nPriority] != NULL)
	{
		m_pCur[m_nPriority]->m_pNext = this;
	}
	else
	{
		m_pTop[m_nPriority] = this;
	}

	this->m_pPrev = m_pCur[m_nPriority];
	this->m_pNext = NULL;
	m_pCur[m_nPriority] = this;
}

