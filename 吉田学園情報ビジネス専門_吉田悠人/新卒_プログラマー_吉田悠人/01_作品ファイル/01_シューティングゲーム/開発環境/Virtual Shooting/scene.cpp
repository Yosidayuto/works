//=============================================================================
// ヘッダファイル
//=============================================================================
#include "scene.h"
#include <typeinfo.h>
#include "player.h"
#include "bullet.h"
#include "manager.h"
#include "inputmouse.h"
#include "inihkeyboard.h"

//=============================================================================
//静的メンバー変数宣言
//=============================================================================
CScene* CScene::m_pTop[PRIORITY_MAX] = {};
CScene* CScene::m_pCur[PRIORITY_MAX] = {};


//=============================================================================
//コンストラクト
//=============================================================================
CScene::CScene(int nPriority)
{
	//初期化処理
	m_bDestroy = false;
	//リスト構造に追加
	m_nPriority = nPriority;
	if (m_pTop[nPriority] != NULL)
	{
		m_pCur[nPriority]->m_pNext = this;
	}
	else
	{
		m_pTop[nPriority] = this;
	}
	this->m_pPrev		= m_pCur[nPriority];
	this->m_pNext		= NULL;
	m_pCur[nPriority]	= this;

}
//=============================================================================
//デストラクト
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
//更新処理
//=============================================================================
void CScene::UpdateAll(void)
{
	CScene* pNext = NULL;
	CScene* pNextBuff = NULL;
	int ObjectCount = 0;
	//リストに含まれるオブジェクトを更新
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		//NULLチェック
		if (m_pTop[nCount] != NULL)
		{
			pNext = m_pTop[nCount];
			//NULLチェック
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
		//NULLチェック
		if (m_pTop[nCount] != NULL)
		{
			pNext = m_pTop[nCount];
			//NULLチェック
			while (pNext != NULL)
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
		//NULLチェック
		if (m_pTop[nCount] != NULL)
		{
			pNext = m_pTop[nCount];
			while (pNext != NULL)
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
	CScene* pNext = NULL;
	CScene* pNextBuff = NULL;
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		//NULLチェック
		if (m_pTop[nCount] != NULL)
		{
			pNext = m_pTop[nCount];
			while (pNext != NULL)
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
//セットタイプ モード処理
//=============================================================================
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}
//=============================================================================
//タイプゲット処理
//=============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}

//=============================================================================
//オブジェクトトップゲッター
//=============================================================================
CScene** CScene::GetTop(void)
{
	return m_pTop;
}

//=============================================================================
// 次のオブジェクトゲッター
//=============================================================================
CScene* CScene::GetNext(void)
{
	return m_pNext;
}

//=============================================================================
// 前のオブジェクトゲッター
//=============================================================================
CScene* CScene::GetPrev(void)
{
	return m_pPrev;
}

//=============================================================================
//シーン破棄処理
//=============================================================================
void CScene::Release(void)
{
	//死亡フラグを立てる
	m_bDestroy = true;
}

//=============================================================================
//リストから消去して自身も消える処理
//=============================================================================
void CScene::Death(void)
{
	//消えるときの処理
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
	delete this;
}


