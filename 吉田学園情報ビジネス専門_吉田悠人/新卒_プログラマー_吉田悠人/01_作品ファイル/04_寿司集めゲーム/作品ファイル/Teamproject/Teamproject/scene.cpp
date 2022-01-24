//=============================================================================
//
// �V�[������ [scene.cpp]
// Author : �ѐ�ї���
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"
#include "renderer.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
CScene* CScene::m_pTop[PRIORITY_MAX] = {};
CScene* CScene::m_pCur[PRIORITY_MAX] = {};

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority)
{
	//����������
	m_bDestroy = false;
	m_nPriority = nPriority;

	if (m_pTop[nPriority] != NULL)
	{
		m_pCur[nPriority]->m_pNext = this;
	}
	else
	{
		m_pTop[nPriority] = this;
	}

	this->m_pPrev = m_pCur[nPriority];
	this->m_pNext = NULL;
	m_pCur[nPriority] = this;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CScene::~CScene()
{
}

//=============================================================================
//�X�V����
//=============================================================================
void CScene::UpdateAll(void)
{
	CScene* pNext = nullptr;
	CScene* pNextBuff = nullptr;
	int ObjectCount = 0;
	//���X�g�Ɋ܂܂��I�u�W�F�N�g���X�V
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (m_pTop[nCount] != nullptr)
		{
			pNext = m_pTop[nCount];
			while (pNext != NULL && !pNext->m_bDestroy)
			{
				pNextBuff = pNext->m_pNext;
				pNext->Update();
				pNext = pNextBuff;
				ObjectCount++;
			}
		}
	}

	//���S�t���O�����Ă�������
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (m_pTop[nCount] != nullptr)
		{
			pNext = m_pTop[nCount];
			while (pNext != nullptr)
			{
				pNextBuff = pNext->m_pNext;
				if (pNext->m_bDestroy == true)
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
void CScene::DrawAll(void)
{
	CScene* pNext = NULL;
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (m_pTop[nCount] != nullptr)
		{
			pNext = m_pTop[nCount];
			while (pNext != nullptr)
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
void CScene::ReleaseAll(void)
{
	CScene* pNext = nullptr;
	CScene* pNextBuff = nullptr;
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (m_pTop[nCount] != nullptr)
		{
			pNext = m_pTop[nCount];
			while (pNext != nullptr)
			{
				pNextBuff = pNext->m_pNext;
				pNext->Uninit();
				delete pNext;
				pNext = pNextBuff;
			}
		}
		m_pTop[nCount] = nullptr;
		m_pCur[nCount] = nullptr;
	}
}

//=============================================================================
//�J������
//=============================================================================
void CScene::Release(void)
{
	//���S�t���O�𗧂Ă�
	m_bDestroy = true;
}

//=============================================================================
//���X�g���������g������
//=============================================================================
void CScene::Death(void)
{
	if (this == m_pTop[m_nPriority])
	{
		m_pTop[m_nPriority] = m_pNext;
	}
	if (this == m_pCur[m_nPriority])
	{
		m_pCur[m_nPriority] = m_pPrev;
	}
	if (m_pNext != nullptr)
	{
		m_pNext->m_pPrev = m_pPrev;
	}
	if (m_pPrev != nullptr)
	{
		m_pPrev->m_pNext = m_pNext;
	}
	delete this;
}

//=============================================================================
//�^�C�v�Z�b�g
//=============================================================================
void CScene::SetObjType(OBJTYPE type)
{
	m_objType = type;
}

//=============================================================================
//�擾�֐�
//=============================================================================
CScene** CScene::GetTop(void)
{
	return m_pTop;
}

CScene* CScene::GetNext(void)
{
	return m_pNext;
}

CScene* CScene::GetPrev(void)
{
	return m_pPrev;
}

CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}
