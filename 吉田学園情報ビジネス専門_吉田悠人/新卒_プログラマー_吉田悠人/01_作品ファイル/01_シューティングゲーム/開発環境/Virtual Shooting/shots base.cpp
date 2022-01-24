//=============================================================================
//
// ショット ベース処理 [shots base.cpp]
// Author : 吉田悠人
//
//=============================================================================
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "shots base.h"
#include "scene.h"
#include "scene2d.h"

//=============================================================================
// コンストラクト
//=============================================================================
CShotsBase::CShotsBase()
{
	memset(m_rot, NULL, sizeof(m_rot));	//移動量
	memset(m_pos, NULL, sizeof(m_pos));	//位置
	m_bShotsEnd = false;
}

//=============================================================================
// デストラクト
//=============================================================================
CShotsBase::~CShotsBase()
{
}

//=============================================================================
// 更新処理
//=============================================================================
void CShotsBase::Update(void)
{
	Shots();
}

//=============================================================================
// 撃つ向き処理（向きをm_rotに代入）
//=============================================================================
void CShotsBase::Tracking(float fSpeed)
{
	//シーン取得用
	CScene* pTop[PRIORITY_MAX] = {};
	//次チェックするシーンポインタ
	CScene* pNext = NULL;

	//topのアドレスを取得
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		pTop[nCount] = *(CScene::GetTop() + nCount);
	}
	//プレイヤーの方向
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (pTop[nCount] != NULL)
		{
			pNext = pTop[nCount];
			//その描画優先度のオブジェクトがなくなるまでループ
			while (pNext != NULL)
			{
				//オブジェクトのタイプがプレイヤーなら
				if (pNext->GetObjType() == CScene::OBJ_TYPE_PLAYER)
				{
					D3DXVECTOR3 Playerpos = ((CScene2d*)pNext)->GetPos();
					float fAngle = atan2f((-m_pos.x + Playerpos.x), (-m_pos.y + Playerpos.y));
					m_rot.x = sinf(fAngle)*fSpeed;
					m_rot.y = cosf(fAngle)*fSpeed;
					return;
				}
				//次のオブジェクトのポインタを更新
				pNext = pNext->GetNext();
			}
		}
	}
}

//=============================================================================
// 撃つ向き処理(角度だけを返す)
//=============================================================================
float CShotsBase::Tracking(void)
{
	//シーン取得用
	CScene* pTop[PRIORITY_MAX] = {};
	//次チェックするシーンポインタ
	CScene* pNext = NULL;

	//topのアドレスを取得
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		pTop[nCount] = *(CScene::GetTop() + nCount);
	}
	//プレイヤーの方向
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (pTop[nCount] != NULL)
		{
			pNext = pTop[nCount];
			//その描画優先度のオブジェクトがなくなるまでループ
			while (pNext != NULL)
			{
				//オブジェクトのタイプがプレイヤーなら
				if (pNext->GetObjType() == CScene::OBJ_TYPE_PLAYER)
				{
					D3DXVECTOR3 Playerpos = ((CScene2d*)pNext)->GetPos();
					float fAngle = atan2f((-m_pos.x + Playerpos.x), (-m_pos.y + Playerpos.y));
					return fAngle;
				}
				//次のオブジェクトのポインタを更新
				pNext = pNext->GetNext();
			}
		}
	}
	return 0.0f;
}

//=============================================================================
// ランダムな向き取得処理
//=============================================================================
void CShotsBase::Random(float fSpeed)
{
	D3DXVECTOR3 rot = D3DXVECTOR3(0, 0, 0);;
	//シーン取得用
	CScene* pTop[PRIORITY_MAX] = {};
	//次チェックするシーンポインタ
	CScene* pNext = NULL;

	//topのアドレスを取得
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		pTop[nCount] = *(CScene::GetTop() + nCount);
	}
	//プレイヤーの方向
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (pTop[nCount] != NULL)
		{
			pNext = pTop[nCount];
			//その描画優先度のオブジェクトがなくなるまでループ
			while (pNext != NULL)
			{
				//オブジェクトのタイプがプレイヤーなら
				if (pNext->GetObjType() == CScene::OBJ_TYPE_PLAYER)
				{
					D3DXVECTOR3 Playerpos = ((CScene2d*)pNext)->GetPos();
					float fRandom = (float)(rand() % 1500 + 1);
					float fAngle = atan2f((-m_pos.x + Playerpos.x), (-m_pos.y + Playerpos.y)) + (float)fRandom / 1000.0f - 0.75f;

					m_rot.x = sinf(fAngle)*fSpeed;
					m_rot.y = cosf(fAngle)*fSpeed;

					return;
				}
				//次のオブジェクトのポインタを更新
				pNext = pNext->GetNext();
			}
		}
	}
}

//=============================================================================
// 向きセッター
//=============================================================================
void CShotsBase::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// 向きゲッター
//=============================================================================
D3DXVECTOR3 CShotsBase::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// 位置セッター
//=============================================================================
void CShotsBase::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// 位置ゲッター
//=============================================================================
D3DXVECTOR3 CShotsBase::GetPos(void)
{
	return m_pos;
}
//=============================================================================
// 撃ち終わったかのセッター
//=============================================================================
void CShotsBase::SetShotsEnd(bool bShots)
{
	m_bShotsEnd = bShots;
}

//=============================================================================
// 撃ち終わったかのゲッター
//=============================================================================
bool CShotsBase::GetShotsEnd(void)
{
	return m_bShotsEnd;
}
