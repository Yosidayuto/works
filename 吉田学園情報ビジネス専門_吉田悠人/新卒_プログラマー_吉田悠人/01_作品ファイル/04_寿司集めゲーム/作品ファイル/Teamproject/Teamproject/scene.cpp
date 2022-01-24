//=============================================================================
//
// シーン処理 [scene.cpp]
// Author : 林川紗梨夏
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "scene.h"
#include "renderer.h"

//=============================================================================
//静的メンバ変数宣言
//=============================================================================
CScene* CScene::m_pTop[PRIORITY_MAX] = {};
CScene* CScene::m_pCur[PRIORITY_MAX] = {};

//=============================================================================
//コンストラクタ
//=============================================================================
CScene::CScene(int nPriority)
{
	//初期化処理
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
//デストラクタ
//=============================================================================
CScene::~CScene()
{
}

//=============================================================================
//更新処理
//=============================================================================
void CScene::UpdateAll(void)
{
	CScene* pNext = nullptr;
	CScene* pNextBuff = nullptr;
	int ObjectCount = 0;
	//リストに含まれるオブジェクトを更新
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

	//死亡フラグ立ってるやつを消す
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
//描画処理
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
//全開放処理
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
//開放処理
//=============================================================================
void CScene::Release(void)
{
	//死亡フラグを立てる
	m_bDestroy = true;
}

//=============================================================================
//リスト消去＆自身も消去
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
//タイプセット
//=============================================================================
void CScene::SetObjType(OBJTYPE type)
{
	m_objType = type;
}

//=============================================================================
//取得関数
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
