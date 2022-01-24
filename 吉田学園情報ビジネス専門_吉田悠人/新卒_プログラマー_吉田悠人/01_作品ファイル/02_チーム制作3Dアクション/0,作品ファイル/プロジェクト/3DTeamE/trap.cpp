//=============================================================================
//
// トラップ処理 [trap.cpp]
// Author : 吉田悠人
//
//=============================================================================


//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "trap.h"
#include "explosion.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "sound.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CTrap::CTrap()
{
	m_Startpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Endpos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_pTexture = NULL;
	SetObjType(OBJTYPE_NONE);
}

//=============================================================================
// 生成処理関数
//=============================================================================
CTrap * CTrap::Create(D3DXVECTOR3 Startpos, D3DXVECTOR3 Endpos)
{
	//メモリ確保
	CTrap* pTrap = NULL;
	pTrap = new CTrap;

	//メモリ確保がされたか
	if (pTrap!=NULL)
	{
		//トラップの線のスタート位置取得
		pTrap->m_Startpos = Startpos;
		//トラップの線の終了位置取得
		pTrap->m_Endpos = Endpos;
		//位置設定（スタート位置と終了位置で計算）
		pTrap->SetPosition((Startpos + Endpos) / 2);
		//向き設定（スタート位置と終了位置で計算）
		pTrap->SetRotation(D3DXVECTOR3(90.0f, D3DXToDegree(atan2f((Startpos.x - Endpos.x), (Startpos.z - Endpos.z))), 0.0f));
		//サイズ設定（スタート位置と終了位置で計算）
		pTrap->SetSize(D3DXVECTOR3(1.0f, sqrtf(((Startpos.x - Endpos.x)*(Startpos.x - Endpos.x)) + ((Startpos.z - Endpos.z)*(Startpos.z - Endpos.z))), 1.0f));
		//カラー設定
		for (int nMesh = 0; nMesh < MESH_Y_BLOCK + 1; nMesh++)
		{
			pTrap->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f - (nMesh*0.1f)), nMesh);
		}
		//初期化処理
		pTrap->Init();
	}
	return pTrap;
}

//=============================================================================
// 更新関数
//=============================================================================
void CTrap::Update(void)
{
	//リスト取得用
	CObject* pTop[PRIORITY_MAX] = {};
	CObject* pNext = NULL;
	//サウンドの取得
	CSound* pSound = CManager::GetSound();   

	//リストトップ取得
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		pTop[nCount] = *(CObject::GetTop() + nCount);
	}

	//距離
	float fDistanve;

	//リストの優先順に読み込み
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		//NULLチェック
		if (pTop[nCount] != NULL)
		{
			//保存
			pNext = pTop[nCount];
			while (pNext != NULL)
			{
				//オブジェクトタイプチェック
				if (pNext->GetObjType() == OBJTYPE_MODEL)
				{
					//NULLチェック
					if (((CModel *)pNext)->GetParentObject() != NULL)
					{
						//オブジェクトがプレイヤーか
						if (((CModel*)pNext)->GetParentObject()->GetObjType() == OBJTYPE_PLAYER)
						{
							//プレイヤーが触れたか
							if (Search(((CModel*)pNext)->GetModelData(), fDistanve) == TRUE)
							{
								if (GetSize().y>fDistanve)
								{
									//爆破
									CExplosion::Create(D3DXVECTOR3(CManager::GetPlayer()->GetPos().x, CManager::GetPlayer()->GetPos().y + 30, CManager::GetPlayer()->GetPos().z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100, 100, 100));

									//プレイヤーダメージ
									CManager::GetPlayer()->AddLife(-45);

									//終了処理
									Uninit();
								}
							}
						}
					}
				}
				//次の対象を読み込む
				pNext = pNext->GetNext();
			}
		}
	}
	//更新処理
	CMeshCylinder::Update();
}


//=============================================================================
// 感知関数
//=============================================================================
BOOL CTrap::Search(CModel::MODELDATA modeldata, float &fDistanve)
{
	BOOL bSearch = FALSE;			//反応しているか
	D3DXMATRIX mtxWorld;
	D3DXMATRIX InversedWorldMatrix;	//逆列用マトリックス
	D3DXVECTOR3 TransformedPos, NormalizedVec, TranceformedVec;

	//単位ベクトルに変換
	D3DXVec3Normalize(&NormalizedVec, &(m_Endpos - m_Startpos));
	//逆行列生成
	D3DXMatrixInverse(&InversedWorldMatrix, NULL, &modeldata.mtxWorld);
	//逆行列で変換
	D3DXVec3TransformCoord(&TransformedPos, &m_Startpos, &InversedWorldMatrix);
	D3DXVec3TransformNormal(&TranceformedVec, &NormalizedVec, &InversedWorldMatrix);
	//当たり判定を確認
	D3DXIntersect(modeldata.pMesh, &TransformedPos, &TranceformedVec, &bSearch, NULL, NULL, NULL, &fDistanve, NULL, NULL);
	return bSearch;

}


