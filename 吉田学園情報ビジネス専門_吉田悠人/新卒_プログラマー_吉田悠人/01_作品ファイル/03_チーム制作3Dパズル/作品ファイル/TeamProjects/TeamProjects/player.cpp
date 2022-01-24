//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "player.h"
#include "resource manager.h"
#include "inputcontroller.h"
#include "inputkeyboard.h"
#include "renderer.h"
#include "model.h"
#include "child.h"
#include "particle.h"
#include "sound.h"
#include "tile block base.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_HEIGHT	(25.0f)                             // プレイヤーの高さ
#define PLAYER_SPEED	(5)							        // プレイヤーのスピード
#define PLAYERL_RANGE	(25.0f)								// プレイヤーの当たり判定の広さ
#define MOVE_FRAME      (20.0f)                             // 一回の移動のフレーム数
#define MOVE_DISTANCE   (50.0f / (MOVE_FRAME+1))            // 一回の移動の距離
#define ADD_ROT_VALU    (D3DXToRadian(90)/MOVE_FRAME)       // 回転量
#define MOVE_Y_VALU     ((sqrtf(powf(50.0f , 2.0f) + powf(50.0f, 2.0f)) / 2) - PLAYER_HEIGHT)	// 移動量Y
#define MOVE_Y_VALU2    ((sqrtf(powf(100.0f , 2.0f) + powf(50.0f, 2.0f)) / 2) - PLAYER_HEIGHT)	// 移動量Y) // 移動量Y
#define MOVE_JOYPAD_EFFECT_FRAME 13    // 移動時コントローラーが振動するポイント

//=============================================================================
// 静的メンバ変数初期化
//=============================================================================
CPlayer*CPlayer::m_pPlayer = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer()
{
	
	//モデルデータの初期化
	SetObjType(OBJTYPE_PLAYER);

	m_model				= NULL;
	m_Move				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);        // 移動量の初期化
	m_nMoveFrameCount	= 0;                                    // 移動フレーム数のカウント用
	m_nFallFrameCount	= 0;									// 落下フレーム数のカウント用
	m_bPlayer			= false;								// プレイヤーの行動制限
	m_bActiveMove		= false;                                // 移動中かの判定用
	m_bFallMove			= false;								// 落下中かの判定用
	m_bError			= false;								// エラー音の判定用
	D3DXMatrixRotationYawPitchRoll(&m_mtxRot, 0.0f, 0.0f, 0.0f);// 回転行列
	m_pChild			= NULL;                                 // くっついているオブジェクト
	m_movePattern		= STICKY_NONE;							// 移動パターン

}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{
	m_pPlayer = NULL;
}


//=============================================================================
// 生成関数
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//メモリ確保
	if (m_pPlayer == NULL)
	{
		m_pPlayer = new CPlayer;

		//NULLチェック
		if (m_pPlayer != NULL)
		{
			//位置設定
			m_pPlayer->SetPosition(D3DXVECTOR3(pos.x, pos.y + PLAYER_HEIGHT, pos.z));
			//向き設定
			m_pPlayer->SetRotation(rot);
			//カラー設定
			m_pPlayer->SetScale(size);
			//初期化処理
			m_pPlayer->Init();
		}
	}
	return m_pPlayer;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CPlayer::Init(void)
{
	//リソース確保
	CResource* pResource = CManager::GetResource();
	CModel::MODELDATA Model = pResource->ModelLoad(m_nModel);
	//ワールド変換行列の初期化
	D3DXMatrixIdentity(&Model.mtxWorld);
	// モデル生成
	m_model = new CModel;
	if (m_model != NULL)
	{
		m_model->SetPosition(GetPosition());
		m_model->SetRotation(GetRotation());
		m_model->SetScale(GetScale());
		m_model->SetModelData(Model);
		m_model->Init();
	}
	SetPriority(PRIORITY_OBJECT_PLAYER);
	m_model->SetPriority(PRIORITY_OBJECT_PLAYER);
	m_bPlayer = true;

	////////////////////
	m_pChild = CChild::Create(m_model, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	////////////////////
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CPlayer::Uninit(void)
{
	//NULLチェック
	if (m_model != NULL)
	{
		m_model->Uninit();
	}

	Release();
}

//=============================================================================
// 更新関数
//=============================================================================
void CPlayer::Update(void)
{
	//行動制限がかかっていないとき
	if (m_bPlayer == false)
	{
		// 操作処理
		Control();
		// 落下処理
		Fall();
		// 移動処理
		Move();
		//モデルの位置セット
		m_model->SetPosition(GetPosition());
	}

	// チャイルドのワールド座標取得
	CModel::MODELDATA modelData = m_pChild->GetModel()->GetModelData();
	D3DXVECTOR3 childPos = D3DXVECTOR3(modelData.mtxWorld._41, modelData.mtxWorld._42, modelData.mtxWorld._43);
	//パーティクルの生成
	if (rand() % 3 == 0 && 0 < childPos.y&&m_pChild->GetIsActive() == false)
	{
		CParticle *pParticle = CParticle::Cretae(childPos, m_model->GetPosition(), D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CParticle::PARTICLE_TYPE_1);
	}

	// ワールド行列計算変換
	ExchangeWorldMtx();
}

//=============================================================================
// 描画関数
//=============================================================================
void CPlayer::Draw(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DMATERIAL9 matDef;	//現在のマテリアル保持用
	D3DXMATERIAL*pMat;	//マテリアルデータへのポインタ

	CModel::MODELDATA modelData = m_model->GetModelData();
	
	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &modelData.mtxWorld);

	//現在のマテリアルを取得する
	pDevice->GetMaterial(&matDef);

	if (modelData.pBuffMat != NULL)
	{
		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)modelData.pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)modelData.nNumMat; nCntMat++)
		{
			//マテリアルのアンビエントにディフューズカラーを設定
			pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			// テクスチャ
			pDevice->SetTexture(0, modelData.pTexture[nCntMat]);
			//モデルパーツの描画
			modelData.pMesh->DrawSubset(nCntMat);
		}
	}


}


//******************************
// キー操作処理
//******************************
void CPlayer::Control(void)
{
	if (!m_bActiveMove&&!m_bFallMove)
	{// 移動中じゃないとき+落下中じゃないとき
	  //キーボード入力の取得
		CInputKeyboard* pKeyInput = (CInputKeyboard*)CManager::GetInputKey();
		
		// コントローラー十字キーの値の取得
		CInputJoyStick* pJoyInput = (CInputJoyStick*)CManager::GetInputController();
		WORD joyCross = CROSS_KEY_NEUTRAL;
		if (pJoyInput != NULL) joyCross = (WORD)pJoyInput->GetJoyStick().rgdwPOV[0];

		//エラー音の切替関数
		ErrorStatus();

		if (pKeyInput->GetKeyPress(DIK_W)|| joyCross == CROSS_KEY_UP)
		{
			// 回転行列の設定
			D3DXMatrixRotationYawPitchRoll(&m_mtxRot, 0.0f, -ADD_ROT_VALU, 0.0f);
			// 移動量の設定
			m_Move = D3DXVECTOR3(0.0f, 0.0f, -MOVE_DISTANCE);

			// カウントの初期化
			m_nMoveFrameCount = 0;
			// 移動中フラグをtrue
			m_bActiveMove = true;

		}
		if (pKeyInput->GetKeyPress(DIK_S) || joyCross == CROSS_KEY_DOWN)
		{
			// 回転行列の設定
			D3DXMatrixRotationYawPitchRoll(&m_mtxRot, 0.0f, ADD_ROT_VALU, 0.0f);

			// 移動量の設定
			m_Move = D3DXVECTOR3(0.0f, 0.0f, MOVE_DISTANCE);

			// カウントの初期化
			m_nMoveFrameCount = 0;
			// 移動中フラグをtrue
			m_bActiveMove = true;
		}
		if (pKeyInput->GetKeyPress(DIK_A) || joyCross == CROSS_KEY_LEFT)
		{
			// 回転行列の設定
			D3DXMatrixRotationYawPitchRoll(&m_mtxRot, 0.0f, 0.0f, -ADD_ROT_VALU);

			// 移動量の設定
			m_Move = D3DXVECTOR3(MOVE_DISTANCE, 0.0f, 0.0f);

			// カウントの初期化
			m_nMoveFrameCount = 0;

			// 移動中フラグをtrue
			m_bActiveMove = true;
		}
		if (pKeyInput->GetKeyPress(DIK_D) || joyCross == CROSS_KEY_RIGHT)
		{
			// 回転行列の設定
			D3DXMatrixRotationYawPitchRoll(&m_mtxRot, 0.0f, 0.0f, ADD_ROT_VALU);

			// 移動量の設定
			m_Move = D3DXVECTOR3(-MOVE_DISTANCE, 0.0f, 0.0f);

			// カウントの初期化
			m_nMoveFrameCount = 0;

			// 移動中フラグをtrue
			m_bActiveMove = true;
		}

		if (m_bActiveMove)
		{
			if (m_pChild->GetIsActive())
			{
				// くっついているオブジェクトのワールド座標の取得
				D3DXVECTOR3 childVec = D3DXVECTOR3(m_pChild->GetModel()->GetModelData().mtxWorld._41, m_pChild->GetModel()->GetModelData().mtxWorld._42, m_pChild->GetModel()->GetModelData().mtxWorld._43);

				if (childVec.y - GetPosition().y <= -0.001)
				{// 移動パターンの設定
					m_movePattern = STICKY_DOWN;
				}
				else if (childVec.y - GetPosition().y >= 0.001)
				{
					m_movePattern = STICKY_UP;
				}
				else
				{
					childVec.y = GetPosition().y;

					if (D3DXVec3Length(&(childVec - GetPosition())) > 10.0f)
					{

						// プレイヤーからオブジェクトへの方向ベクトル
						childVec = childVec - GetPosition();
						childVec.y = 0.0f;
						// 正規化
						D3DXVec3Normalize(&childVec, &childVec);

						// 移動方向のベクトル
						D3DXVECTOR3 moveVec = m_Move;
						moveVec.y = 0.0f;
						// 正規化
						D3DXVec3Normalize(&moveVec, &moveVec);

						if (D3DXVec3Length(&(childVec - moveVec)) < 0.001f)
						{// 移動パターンの設定
							m_movePattern = STICKY_FRONT;
						}
						else
						{// 移動パターンの設定
							m_movePattern = STICKY_NONE;
						}
					}
					else
					{// 移動パターンの設定
						m_movePattern = STICKY_NONE;
					}
				}
			}
			else
			{
				m_movePattern = STICKY_NONE;
			}

			//当たり判定
			Collision();
			//行動範囲
			MoveRange();
			//子供ブロックの行動範囲
			MoveRangeChild();
		}
	}
}

//******************************
// 移動処理
//******************************
void CPlayer::Move(void)
{
	if (m_bActiveMove)
	{// 移動中の処理

		// 位置の取得
		D3DXVECTOR3 pos = GetPosition();
		switch (m_movePattern)
		{
		case STICKY_NONE:
			// 高さの調整
			pos.y = ((sinf((D3DXToRadian(180.0f) / MOVE_FRAME)*m_nMoveFrameCount))*MOVE_Y_VALU) + PLAYER_HEIGHT;
			//位置セット
			pos += m_Move;
			break;
		
		case STICKY_FRONT:
			// 高さの調整
			pos.y = ((sinf((D3DXToRadian(90.0f) / MOVE_FRAME)*m_nMoveFrameCount)) * (PLAYER_HEIGHT * 3)) + (PLAYER_HEIGHT - ((m_nMoveFrameCount / MOVE_FRAME) * PLAYER_HEIGHT));
			//位置セット
			pos += m_Move * 2.0f;
			break;

		case STICKY_DOWN:
			// 高さの調整
			pos.y = ((sinf(((D3DXToRadian(90.0f) / MOVE_FRAME)*m_nMoveFrameCount) + D3DXToRadian(90.0f))) * (PLAYER_HEIGHT * 3)) + (0 + ((m_nMoveFrameCount / MOVE_FRAME) * PLAYER_HEIGHT));
			//位置セット
			pos += m_Move * 2.0f;
			break;

		case STICKY_UP:
			// 高さの調整
			pos.y = ((sinf((D3DXToRadian(180.0f) / MOVE_FRAME)*m_nMoveFrameCount))*MOVE_Y_VALU) + PLAYER_HEIGHT;
			//位置セット
			pos += m_Move;
			break;
		default:
			break;
		}


		//位置セット
		SetPosition(pos);

		// カウントを進めて一定数で
		m_nMoveFrameCount++;

		// コントローラーの振動処理
		if (m_nMoveFrameCount == MOVE_JOYPAD_EFFECT_FRAME)
		{
			// コントローラー十字キーの値の取得
			CInputJoyStick* pJoyInput = (CInputJoyStick*)CManager::GetInputController();
			pJoyInput->SetVibration(1);
		}

		if (m_nMoveFrameCount > MOVE_FRAME)
		{
			// 移動量の初期化
			m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			// 回転行列の初期化
			D3DXMatrixRotationYawPitchRoll(&m_mtxRot, 0.0f, 0.0f, 0.0f);

			// カウントの初期化
			m_nMoveFrameCount = 0;
			// 移動中カウントをfalse
			m_bActiveMove = false;
			return;
		}
	}
}

//******************************
// 落下処理
//******************************
void CPlayer::Fall(void)
{
	//移動をしていない
	if (!m_bActiveMove)
	{
		//落下している
		if (m_bFallMove)
		{//落下中の処理
			//位置の取得
			D3DXVECTOR3 pos = GetPosition();
			
			//位置計算
			pos.y = pos.y + (PLAYER_HEIGHT - pos.y) / (MOVE_FRAME- m_nFallFrameCount);
			//位置セット
			SetPosition(pos);
			//落下フレーム加算
			m_nFallFrameCount++;
			
			if (m_nFallFrameCount>=MOVE_FRAME)
			{
				//カウント初期化
				m_nFallFrameCount = 0;
				//落下中カウントをfalse
				m_bFallMove = false;
			}
		}

	}
}

//******************************
// 当たり判定処理
//******************************
void CPlayer::Collision(void)
{
	//オブジェクト取得用
	CObject* pTop[PRIORITY_MAX] = {};
	//次チェックするオブジェクトのポインタ
	CObject* pNext = NULL;
	//次の移動先
	D3DXVECTOR3 NextPos;
	if (m_movePattern != STICKY_DOWN)
	{
		NextPos = GetPosition() + ((m_Move*(MOVE_FRAME + 1)) / 2.0f);
	}
	else
	{
		NextPos = GetPosition() + ((m_Move*(MOVE_FRAME + 1)) * 2.0f);
		NextPos.y -= (PLAYER_HEIGHT * 2.0f);
	}

	//topのアドレスを取得
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		pTop[nCount] = *(CObject::GetTop() + nCount);
	}

	//オブジェクト探査
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (pTop[nCount] != NULL)
		{
			pNext = pTop[nCount];
			//その描画優先度のオブジェクトがなくなるまでループ
			while (pNext != NULL)
			{			
				//子供ブロックの当たり判定
				if (CollisionChild(pNext))
				{
					//行動不能処理
					MoveError();
					return;
				}

				//オブジェクトのタイプがアイテムなら
				if (pNext->GetObjType() == OBJTYPE_ITEM)
				{
					//アイテムブロックの位置取得
					D3DXVECTOR3 ItemPos = ((CObject3D*)pNext)->GetPosition();

					//当たり判定(誤差を消すために+-１)
					if (NextPos.x + PLAYERL_RANGE + 1 > ItemPos.x
						&&NextPos.x - PLAYERL_RANGE - 1 < ItemPos.x
						&&NextPos.y + PLAYERL_RANGE + 1 > ItemPos.y
						&&NextPos.y - PLAYERL_RANGE - 1 < ItemPos.y
						&&NextPos.z + PLAYERL_RANGE + 1 > ItemPos.z
						&&NextPos.z - PLAYERL_RANGE - 1 < ItemPos.z)
					{
						//行動不能処理
						MoveError();
						return;
					}
				}
				//オブジェクトのタイプがブロックなら
				else if (pNext->GetObjType() == OBJTYPE_BLOCK)
				{
					//障害ブロックの位置取得
					D3DXVECTOR3 ObjPos = ((CObject3D*)pNext)->GetPosition();

					//当たり判定(誤差を消すために+-１)
					if (NextPos.x + PLAYERL_RANGE + 1 > ObjPos.x
						&&NextPos.x - PLAYERL_RANGE - 1 < ObjPos.x
						&&NextPos.y + PLAYERL_RANGE + 1 > ObjPos.y
						&&NextPos.y - PLAYERL_RANGE - 1 < ObjPos.y
						&&NextPos.z + PLAYERL_RANGE + 1 > ObjPos.z
						&&NextPos.z - PLAYERL_RANGE - 1 < ObjPos.z)
					{
						//行動不能処理
						MoveError();
						return;
					}

				}
			
				//次のオブジェクトのポインタを更新
				pNext = pNext->GetNext();
			}
		}
	}
}

//******************************
// 子供ブロックの当たり判定
//******************************
bool CPlayer::CollisionChild(CObject * Object)
{	
	if (m_pChild->GetIsActive())
	{
		//子供ブロックの位置取得
		CModel::MODELDATA modelData = m_pChild->GetModel()->GetModelData();
		D3DXVECTOR3 pos = D3DXVECTOR3(modelData.mtxWorld._41, modelData.mtxWorld._42, modelData.mtxWorld._43);

		//次の移動先
		D3DXVECTOR3 NextPos;
		if (m_movePattern != STICKY_UP)
		{
			NextPos = pos + ((m_Move*(MOVE_FRAME + 1)) / 2);
		}
		else
		{
			NextPos = pos + ((m_Move*(MOVE_FRAME + 1)) * 2);
			NextPos.y -= (PLAYER_HEIGHT * 2);
		}

		//オブジェクトのタイプがアイテムなら
		if (Object->GetObjType() == OBJTYPE_ITEM)
		{
			//アイテムブロックの位置取得
			D3DXVECTOR3 ItemPos = ((CObject3D*)Object)->GetPosition();

			//当たり判定(誤差を消すために+-１)
			if (NextPos.x + PLAYERL_RANGE + 1 > ItemPos.x
				&&NextPos.x - PLAYERL_RANGE - 1 < ItemPos.x
				&&NextPos.y + PLAYERL_RANGE + 1 > ItemPos.y
				&&NextPos.y - PLAYERL_RANGE - 1 < ItemPos.y
				&&NextPos.z + PLAYERL_RANGE + 1 > ItemPos.z
				&&NextPos.z - PLAYERL_RANGE - 1 < ItemPos.z)
			{
				return true;
			}
		}
		//オブジェクトのタイプがブロックなら
		else if (Object->GetObjType() == OBJTYPE_BLOCK)
		{
			//障害ブロックの位置取得
			D3DXVECTOR3 ObjPos = ((CObject3D*)Object)->GetPosition();

			//当たり判定(誤差を消すために+-１)
			if (NextPos.x + PLAYERL_RANGE + 1 > ObjPos.x
				&&NextPos.x - PLAYERL_RANGE - 1 < ObjPos.x
				&&NextPos.y + PLAYERL_RANGE + 1 > ObjPos.y
				&&NextPos.y - PLAYERL_RANGE - 1 < ObjPos.y
				&&NextPos.z + PLAYERL_RANGE + 1 > ObjPos.z
				&&NextPos.z - PLAYERL_RANGE - 1 < ObjPos.z)
			{
				return true;
			}

		}
	}

	return false;
}

//******************************
// 行動範囲処理関数
//******************************
void CPlayer::MoveRange(void)
{
	//次の移動先
	D3DXVECTOR3 NextPos;
	//状況に応じて
	if (m_movePattern != STICKY_DOWN)
	{
		NextPos = GetPosition() + ((m_Move*(MOVE_FRAME + 1)));
		NextPos.y = NextPos.y - (TILE_HEIGHT + PLAYER_HEIGHT);
	}
	else
	{
		NextPos = GetPosition() + ((m_Move*(MOVE_FRAME + 1.0f))*2);
		NextPos.y -= ((PLAYER_HEIGHT * 2) + (TILE_HEIGHT + PLAYER_HEIGHT));
	}

	//タイルのポインタ取得
	CTileBlockBase * pTile = (CTileBlockBase*)(GetTop()[PRIORITY_OBJECT_TILE]);

	while (pTile != NULL)
	{		
		// アイテムの座標の取得
		D3DXVECTOR3 TilePos = pTile->GetPosition();
	
		//当たり判定
		if (NextPos.x + PLAYERL_RANGE > TilePos.x
			&&NextPos.x - PLAYERL_RANGE < TilePos.x
			&&NextPos.y + PLAYERL_RANGE > TilePos.y
			&&NextPos.y - PLAYERL_RANGE < TilePos.y
			&&NextPos.z + PLAYERL_RANGE > TilePos.z
			&&NextPos.z - PLAYERL_RANGE < TilePos.z)
		{
			return;
		}
		pTile = (CTileBlockBase*)(pTile->GetNext());
	}

	//行動不能処理
	MoveError();
}

//******************************
// 子供ブロックの行動範囲設定処理
//******************************
void CPlayer::MoveRangeChild(void)
{
	if (m_pChild->GetIsActive())
	{		
		//子供ブロックの位置取得
		CModel::MODELDATA modelData = m_pChild->GetModel()->GetModelData();
		D3DXVECTOR3 pos = D3DXVECTOR3(modelData.mtxWorld._41, modelData.mtxWorld._42, modelData.mtxWorld._43);

		//次の移動先
		D3DXVECTOR3 NextPos;
		if (m_movePattern != STICKY_UP)
		{
			NextPos = pos + ((m_Move*(MOVE_FRAME + 1)));
			NextPos.y -= (TILE_HEIGHT + PLAYER_HEIGHT);

		}
		else
		{

			NextPos = pos + ((m_Move*(MOVE_FRAME + 1))*2);
			NextPos.y -= ((PLAYER_HEIGHT * 2) + (TILE_HEIGHT + PLAYER_HEIGHT));
		}

		//タイルのポインタ取得
		CTileBlockBase * pTile = (CTileBlockBase*)(GetTop()[PRIORITY_OBJECT_TILE]);

		while (pTile != NULL)
		{
			// アイテムの座標の取得
			D3DXVECTOR3 TilePos = pTile->GetPosition();

			//当たり判定
			if (NextPos.x + PLAYERL_RANGE > TilePos.x
				&&NextPos.x - PLAYERL_RANGE < TilePos.x
				&&NextPos.y + PLAYERL_RANGE > TilePos.y
				&&NextPos.y - PLAYERL_RANGE < TilePos.y
				&&NextPos.z + PLAYERL_RANGE > TilePos.z
				&&NextPos.z - PLAYERL_RANGE < TilePos.z)
			{
				return;
			}
			pTile = (CTileBlockBase*)(pTile->GetNext());
		}

		//行動不能処理
		MoveError();
	}
}

//******************************
// エラー音の使用確認関数
//******************************
void CPlayer::ErrorStatus(void)
{
	//キーボード入力の取得
	CInputKeyboard* pKeyInput = (CInputKeyboard*)CManager::GetInputKey();
	// コントローラー十字キーの値の取得
	CInputJoyStick* pJoyInput = (CInputJoyStick*)CManager::GetInputController();
	WORD joyCross = CROSS_KEY_NEUTRAL;
	if (pJoyInput != NULL)
	{ 
		if (pJoyInput->GetPushCross(CROSS_KEY_UP)
			|| pJoyInput->GetPushCross(CROSS_KEY_RIGHT)
			|| pJoyInput->GetPushCross(CROSS_KEY_DOWN)
			|| pJoyInput->GetPushCross(CROSS_KEY_LEFT))
		{
			m_bError = false;
		}
		
	}

	if (pKeyInput->GetKeyTrigger(DIK_W)
		|| pKeyInput->GetKeyTrigger(DIK_A)
		|| pKeyInput->GetKeyTrigger(DIK_S)
		|| pKeyInput->GetKeyTrigger(DIK_D))
	{
		m_bError = false;
	}
}

//******************************
// 行動不能時の処理関数
//******************************
void CPlayer::MoveError(void)
{
	//エラーオン用の処理
	if (m_bError == false)
	{
		//BGMの再生
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_ERROR);
		//SEフラグオン
		m_bError = true;
	}
	// 回転行列の初期化
	D3DXMatrixRotationYawPitchRoll(&m_mtxRot, 0.0f, 0.0f, 0.0f);
	//移動量を初期化
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// 移動中カウントをfalse
	m_bActiveMove = false;
}

//******************************
// ワールド変換
//******************************
void CPlayer::ExchangeWorldMtx(void)
{

	D3DXMATRIX mtxTrans, mtxScail;

	CModel::MODELDATA modelData = m_model->GetModelData();

	// 位置の初期化
	modelData.mtxWorld._41 = 0.0f;
	modelData.mtxWorld._42 = 0.0f;
	modelData.mtxWorld._43 = 0.0f;

	//サイズを反映
	D3DXMatrixScaling(&mtxScail, m_model->GetScale().x, m_model->GetScale().y, m_model->GetScale().z);
	D3DXMatrixMultiply(&modelData.mtxWorld, &modelData.mtxWorld, &mtxScail);

	//向きを反映
	D3DXMatrixMultiply(&modelData.mtxWorld, &modelData.mtxWorld, &m_mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_model->GetPosition().x, m_model->GetPosition().y, m_model->GetPosition().z);
	D3DXMatrixMultiply(&modelData.mtxWorld, &modelData.mtxWorld, &mtxTrans);

	// セット
	m_model->SetModelData(modelData);
}

//******************************
// ゴール処理関数
//******************************
void CPlayer::Goal(void)
{
	//アイテムがくっついているか
	if (m_pChild->GetIsActive())
	{
		// 位置の取得
		D3DXVECTOR3 pos = GetPosition();
		//終了処理
		m_pChild->Uninit();
		//生成処理
		m_pChild = CChild::Create(m_model, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		
		if (m_movePattern == STICKY_FRONT)
		{
			//フレーム数の初期化
			m_nFallFrameCount = 0;

			//落下判定
			m_bFallMove = true;
		}


		//BGMの再生
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_REACHED);
	}
}