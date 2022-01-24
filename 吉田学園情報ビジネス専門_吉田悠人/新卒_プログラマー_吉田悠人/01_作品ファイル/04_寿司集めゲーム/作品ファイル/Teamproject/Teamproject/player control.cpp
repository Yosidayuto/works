//=============================================================================
//
//	プレイヤー操作 [player control.cpp]
//	Author:吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "manager.h"
#include "player control.h"
#include "player.h"
#include "joystick.h"
#include "keyboard.h"
#include "player parts.h"
#include "score.h"
#include <time.h>
#include "sound.h"
#include "respawn count.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_SIZE				(7.0f)		// プレイヤーの当たり判定のサイズ
#define PLAYER_DEATH			(30*10)		// プレイヤーが死亡時間
#define NPC_AVOID				(50.0f)		// NPCのプレイヤー回避条件
#define NPC_ITEM				(200.0f)	// NPCのアイテム優先条件
#define NPC_SUSHI				(1000.0f)	// NPCの寿司優先条件
#define NPC_MAX_RANDOM_ROT		(100)		// ランダムに向く方向
#define NPC_MAX_RANDOM			(50)		// ランダムに向く際の最大カウント
#define NPC_MAX_TARGET_COUNT	(60*10)		// ターゲットカウントの最大数
#define NPC_AVOID_BARRIER		(100)		// バリアをよける距離

//*****************************************************************************
// 静的メンバ変数初期化
//*****************************************************************************
D3DXVECTOR3 CPlayerControl::m_RespawnCountPos[MAX_PLAYER]=
{
	D3DXVECTOR3(340.0f, 150.0f, 0.0f),
	D3DXVECTOR3(1050.0f, 150.0f, 0.0f),
	D3DXVECTOR3(340.0f, 505.0f, -50.0f),
	D3DXVECTOR3(1050.0f, 505.0f, -50.0f)

};
D3DXVECTOR3 CPlayerControl::m_PlayerPos[MAX_PLAYER] =
{
	D3DXVECTOR3(-50.0f, 0.0f, 0.0f),
	D3DXVECTOR3(50.0f, 0.0f, 0.0f),
	D3DXVECTOR3(-50.0f, 0.0f, -50.0f),
	D3DXVECTOR3(50.0f, 0.0f, -50.0f)
};
//=============================================================================
// コンストラクタ
//=============================================================================
CPlayerControl::CPlayerControl(int nPriority)
{
	for (int nPlayer = 0; nPlayer<MAX_PLAYER; nPlayer++)
	{
		m_pPlayer[nPlayer] = nullptr;
		m_nRespawn[nPlayer] = PLAYER_DEATH;
		m_pRespawnCount[nPlayer] = NULL;
	}
	m_bRespawn = true;

	for (int nNpc = 0; nNpc < MAX_NPC; nNpc++)
	{
		m_NpcData[nNpc] = { D3DXVECTOR3(0.0f,0.0f,0.0f),NPC_MAX_RANDOM ,NPC_MAX_TARGET_COUNT,false,nullptr,nullptr };
	}
	m_nNumberPlayer = 1;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayerControl::~CPlayerControl()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CPlayerControl * CPlayerControl::Create()
{
	//メモリ確保
	CPlayerControl *pPlayerControl = nullptr;
	pPlayerControl = new CPlayerControl;

	if (pPlayerControl != nullptr)
	{
		pPlayerControl->Init();
	}
	return pPlayerControl;

}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CPlayerControl::Init(void)
{
	//プレイヤー生成
	for (int nPlayer = 0; nPlayer < MAX_PLAYER; nPlayer++)
	{
		m_pPlayer[nPlayer] = CPlayer::Create(m_PlayerPos[nPlayer], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), m_nPlayerModel[nPlayer]);
	}

	//プレイヤー人数取得
	m_nNumberPlayer = CManager::GetPlayerNumber();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CPlayerControl::Uninit(void)
{
	Release();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CPlayerControl::Update(void)
{
	for (int nPlayer = 0; nPlayer<MAX_PLAYER; nPlayer++)
	{
		//NULLチェック
		if (m_pPlayer[nPlayer] != nullptr)
		{
			//プレイヤーの人数
			if (nPlayer < m_nNumberPlayer)
			{
				//プレイヤー、一人ひとりの操作管理
				PlayerControl(nPlayer);

				if (m_nNumberPlayer == 1)
				{
					PlayerKeyControl();
				}
			}
			else
			{
				//NPCとして管理
				NpcControl(nPlayer);
			}
			//プレイヤー同士の当たり判定
			PlayerHit(nPlayer);
			//プレイヤーのダメージ判定
			DamageHit(nPlayer);
			//リスポーン処理
			RespawnControl(nPlayer);
			//スコア管理
			PlayerScore(nPlayer);
		}
	}

}

//=============================================================================
// 描画処理関数
//=============================================================================
void CPlayerControl::Draw(void)
{
}

//=============================================================================
// プレイヤー人数セッター処理関数
//=============================================================================
void CPlayerControl::SetNumberPlayer(int nNumber)
{
	m_nNumberPlayer = nNumber;
}

//=============================================================================
// リスポーンスイッチセッター処理関数
//=============================================================================
void CPlayerControl::SetRespawn(bool Respawn)
{
	m_bRespawn = Respawn;
}

//=============================================================================
// プレイヤーのリスポーン処理関数
//=============================================================================
void CPlayerControl::RespawnControl(int nPlayer)
{
	//プレイヤーの状態が死んでいる状態なのか+リスポーンのスイッチが入っているか
	if (m_pPlayer[nPlayer]->GetStats() == CPlayer::PLAYER_STATS_RESPAWN&&m_bRespawn == true)
	{
		//カウントのUI
		if (m_pRespawnCount[nPlayer] == NULL)
		{
			m_pRespawnCount[nPlayer] = CRespawnCount::Create(m_RespawnCountPos[nPlayer], D3DXVECTOR3(60.0f, 120.0f, 0.0f));
			m_pRespawnCount[nPlayer]->SetControl(m_nRespawn[nPlayer]/30);
		}
		//リスポーンカウント
		m_nRespawn[nPlayer]--;
		m_pRespawnCount[nPlayer]->SetControl(m_nRespawn[nPlayer]/30);

		//リスポーンカウントが一定に達したら
		if (m_nRespawn[nPlayer] <= 0)
		{
			//中心地
			D3DXVECTOR3 centre = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//(ココの数値を範囲制限の円の中心を取得)
			//ランダム角度
			srand((unsigned int)time(NULL));					//ランダム関数の初期化
			float fAngle = (float)(rand() % 360 + 1);			//ランダムで角度を決める
			//ランダムな距離
			srand((unsigned int)time(NULL));					//ランダム関数の初期化
			int nDistance = rand() % (int)((m_fMapSize / 2) - 50);		//ランダムな距離を取得(マップのサイズ内に入るように)
			//ランダムリスポーン位置
			D3DXVECTOR3 random = centre + D3DXVECTOR3((float)(nDistance*cos(fAngle)), 0.0f, (float)(nDistance*sin(fAngle)));

			//リスポーン処理
			m_pPlayer[nPlayer]->Respawn(random);
			//リスポーンカウントの初期化
			m_nRespawn[nPlayer] = PLAYER_DEATH;

			//リスポーンカウントUIの処理
			if (m_pRespawnCount[nPlayer] != NULL)
			{
				m_pRespawnCount[nPlayer]->Uninit();
				m_pRespawnCount[nPlayer] = NULL;
			}
		}
	}
}

//=============================================================================
// 他のプレイヤーの当たった際のダメージ処理
//=============================================================================
void CPlayerControl::DamageHit(int nPlayer)
{
	//NULLチェック
	if (m_pPlayer[nPlayer] != nullptr)
	{
		for (int nPlayerCount = 0; nPlayerCount < MAX_PLAYER; nPlayerCount++)
		{
			if (m_pPlayer[nPlayerCount] != nullptr
				&& nPlayer != nPlayerCount)
			{
				//プレイヤーの位置
				D3DXVECTOR3 PlayerPos = m_pPlayer[nPlayer]->GetPos();
				//あてられたプレイヤーのパーツ数
				int nPlayerParts = m_pPlayer[nPlayerCount]->GetPartsCount();

				for (int nPartsCount = 0; nPartsCount<nPlayerParts; nPartsCount++)
				{
					//パーツの位置
					D3DXVECTOR3 PartsPos = m_pPlayer[nPlayerCount]->GetParts(nPartsCount)->GetPos();

					//プレイヤーとパーツの距離を計算
					float RangeX = PlayerPos.x - PartsPos.x;
					float RangeZ = PlayerPos.z - PartsPos.z;
					float Range = (float)(sqrt(RangeX * RangeX + RangeZ * RangeZ));

					//範囲に入っているか
					if (Range <= PLAYER_SIZE + PLAYER_SIZE)
					{
						//プレイヤーの処理
						m_pPlayer[nPlayer]->DamageHit();
						return;
					}
				}

			}
		}
	}
}

//=============================================================================
//プレイヤーの同士のヒット処理関数
//=============================================================================
void CPlayerControl::PlayerHit(int nPlayer)
{
	//NULLチェック
	if (m_pPlayer[nPlayer] != nullptr)
	{
		if (m_pPlayer[nPlayer]->GetStats() == CPlayer::PLAYER_STATS_NORMAL)
		{
			//一度処理をした部分を省くために+1
			int nPlayerCount = nPlayer + 1;
			//プレイヤー同士の処理
			for (nPlayerCount; nPlayerCount < MAX_PLAYER; nPlayerCount++)
			{
				//プレイヤーのポインタのNULLチェック
				if (m_pPlayer[nPlayerCount] != nullptr)
				{
					//相手プレイヤーの状態チェック
					if (m_pPlayer[nPlayerCount]->GetStats() == CPlayer::PLAYER_STATS_NORMAL)
					{
						//プレイヤーの位置
						D3DXVECTOR3 PlayerPos = m_pPlayer[nPlayer]->GetPos();
						//あてられたプレイヤーの位置
						D3DXVECTOR3 HitPlayerPos = m_pPlayer[nPlayerCount]->GetPos();
						//プレイヤー同士の距離を計算
						float RangeX = PlayerPos.x - HitPlayerPos.x;
						float RangeZ = PlayerPos.z - HitPlayerPos.z;
						float Range = (float)(sqrt(RangeX * RangeX + RangeZ * RangeZ));

						//プレイヤーが近くにいるか
						if (Range <= PLAYER_SIZE + PLAYER_SIZE)
						{
							//プレイヤー同士の判定
							m_pPlayer[nPlayer]->Repel(m_pPlayer[nPlayerCount]);
							m_pPlayer[nPlayerCount]->Repel(m_pPlayer[nPlayer]);
							return;
						}
					}
				}
			}
		}
	}
}

//=============================================================================
// プレイヤー操作処理関数
//=============================================================================
void CPlayerControl::PlayerControl(int nPlayer)
{
	// コントローラーの取得
	CJoystick* pJoystick = CManager::GetInputJoystick();
	//入力先
	D3DXVECTOR3 Joystic = D3DXVECTOR3((float)pJoystick->GetJoyStick(nPlayer).lX, (float)-pJoystick->GetJoyStick(nPlayer).lY, 0.0f);
	// プレイヤーの操作 
	m_pPlayer[nPlayer]->RotControl(Joystic);
	//プレイヤーの加速操作
	if (pJoystick->GetJoystickPress(JS_A, nPlayer))
	{
		//パーツ数が0以上
		if (m_pPlayer[nPlayer]->GetPartsCount()>0)
		{
			m_pPlayer[nPlayer]->Dash(true);
		}
		else
		{
			m_pPlayer[nPlayer]->Dash(false);
		}
	}
	else
	{
		m_pPlayer[nPlayer]->Dash(false);
	}
}

//=============================================================================
// プレイヤー操作(キーボード)関数
//=============================================================================
void CPlayerControl::PlayerKeyControl(void)
{
	//キーボードの取得
	CKeyboard* pKeyBoard = CManager::GetInputKeyboard();
	//入力先
	D3DXVECTOR3 Key = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	//キー入力取得
	if (pKeyBoard->GetKeyPress(DIK_UP))Key.y += 1.0f;
	if (pKeyBoard->GetKeyPress(DIK_LEFT)) Key.x -= 1.0f;
	if (pKeyBoard->GetKeyPress(DIK_RIGHT)) Key.x += 1.0f;
	if (pKeyBoard->GetKeyPress(DIK_DOWN))Key.y -= 1.0f;

	// プレイヤーの操作 
	m_pPlayer[0]->RotControl(Key);
	
	//プレイヤーの加速操作
	if (pKeyBoard->GetKeyPress(DIK_Z))
	{
		//パーツ数が0以上
		if (m_pPlayer[0]->GetPartsCount()>0)
		{
			m_pPlayer[0]->Dash(true);
		}
		else
		{
			m_pPlayer[0]->Dash(false);
		}
	}
	else
	{
		m_pPlayer[0]->Dash(false);
	}
}

//=============================================================================
// プレイヤーのスコア処理関数
//=============================================================================
void CPlayerControl::PlayerScore(int nPlayer)
{
	//スコアポインタ取得
	CScore* pScore = CManager::GetScore(nPlayer);
	
	//スコアセット
	pScore->SetScore(m_pPlayer[nPlayer]->GetPartsCount());
	
}

//=============================================================================
// NPC操作関数
//=============================================================================
void CPlayerControl::NpcControl(int nNpc)
{
	//近くにあるものを見て条件にあう行動を決める(重要度が高いほど後に処理)
	SushiProcessCriteria(nNpc);		// 寿司の距離を測る
	ItemProcessCriteria(nNpc);		// アイテムの距離を測る
	PlayerProcessCriteria(nNpc);	// プレイヤーの距離を測る
	NpcRandomProbability(nNpc);		// たまにランダムに行動
	TargetSwitching(nNpc);			// 移動時の停滞対策
	NpcRandomCount(nNpc);			// ランダム移動処理
	AvoidBarrier(nNpc);				// バリア除け処理

	//それを引数に入れて渡す
	m_pPlayer[nNpc]->RotControl(m_NpcData[nNpc - 1].m_TargetRot);
}

//=============================================================================
// NPCとプレイヤーの関係処理関数
//=============================================================================
void CPlayerControl::PlayerProcessCriteria(int nNpc)
{
	//NULLチェック
	if (m_pPlayer[nNpc] != nullptr)
	{
		//NPCの位置
		D3DXVECTOR3 NPCPos = m_pPlayer[nNpc]->GetPos();
		//距離の記録用変数
		float fDistance = NPC_AVOID;

		for (int nPlayerCount = 0; nPlayerCount < MAX_PLAYER; nPlayerCount++)
		{
			if (m_pPlayer[nPlayerCount] != nullptr
				&& nNpc != nPlayerCount)
			{
				//相手プレイヤーの位置
				D3DXVECTOR3 PlayerPos = m_pPlayer[nPlayerCount]->GetPos();
				//NPCとプレイヤーの距離を計算
				float RangeX = PlayerPos.x - NPCPos.x;
				float RangeZ = PlayerPos.z - NPCPos.z;
				float Range = (float)(sqrt(RangeX * RangeX + RangeZ * RangeZ));

				//距離が一定以上近いか
				if (NPC_AVOID>Range)
				{
					//現在記録している距離より近いか
					if (fDistance>Range)
					{
						//近い場合記録する
						fDistance = Range;
						//向きの記録
						m_NpcData[nNpc - 1].m_TargetRot = D3DXVECTOR3(-RangeX, -RangeZ, 0.0f);
						//現在のターゲットを取得
						m_NpcData[nNpc - 1].m_pTarget = m_pPlayer[nPlayerCount];
					}
				}
			}
		}
	}
}

//=============================================================================
// NPCとアイテムの関係処理関数
//=============================================================================
void CPlayerControl::ItemProcessCriteria(int nNpc)
{
	//NULLチェック
	if (m_pPlayer[nNpc] != nullptr)
	{
		//シーン取得用
		CScene* pTop[PRIORITY_MAX] = {};
		//次チェックするシーンのポインタ
		CScene* pNext = NULL;
		//NPCの位置
		D3DXVECTOR3 NPCPos = m_pPlayer[nNpc]->GetPos();
		//距離の記録用変数
		float fDistance = NPC_ITEM;

		//topのアドレスを取得
		for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
		{
			pTop[nCount] = *(CScene::GetTop() + nCount);
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
					if (pNext->GetObjType() == CScene::OBJTYPE_ITEM)
					{
						//アイテムの位置取得
						D3DXVECTOR3 ItemPos = ((CPlayer*)pNext)->GetPos();
						//NPCとアイテムの距離を計算
						float RangeX = ItemPos.x - NPCPos.x;
						float RangeZ = ItemPos.z - NPCPos.z;
						float Range = (float)(sqrt(RangeX * RangeX + RangeZ * RangeZ));

						//特定の距離より近いか
						if (NPC_ITEM > Range)
						{
							//現在記録している距離より近いか
							if (fDistance > Range)
							{
								//近い場合記録する
								fDistance = Range;
								//向きの記録
								m_NpcData[nNpc - 1].m_TargetRot = D3DXVECTOR3(RangeX, RangeZ, 0.0f);
								//現在のターゲットを取得
								m_NpcData[nNpc - 1].m_pTarget = pNext;
							}
						}
					}
					//次のオブジェクトのポインタを更新
					pNext = pNext->GetNext();
				}
			}
		}
	}
}

//=============================================================================
// NPCと寿司の関係処理関数
//=============================================================================
void CPlayerControl::SushiProcessCriteria(int nNpc)
{
	//NULLチェック
	if (m_pPlayer[nNpc] != nullptr)
	{
		//シーン取得用
		CScene* pTop[PRIORITY_MAX] = {};
		//次チェックするシーンのポインタ
		CScene* pNext = NULL;
		//NPCの位置
		D3DXVECTOR3 NPCPos = m_pPlayer[nNpc]->GetPos();
		//距離の記録用変数
		float fDistance = NPC_SUSHI;

		//topのアドレスを取得
		for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
		{
			pTop[nCount] = *(CScene::GetTop() + nCount);
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
					if (pNext->GetObjType() == CScene::OBJTYPE_SUSHI)
					{
						//寿司の位置取得
						D3DXVECTOR3 SushiPos = ((CPlayer*)pNext)->GetPos();
						//NPCと寿司の距離を計算
						float RangeX = SushiPos.x - NPCPos.x;
						float RangeZ = SushiPos.z - NPCPos.z;
						float Range = (float)(sqrt(RangeX * RangeX + RangeZ * RangeZ));

						//一定の距離より近いか
						if (NPC_SUSHI>Range)
						{
							//現在記録している距離より近いか
							if (fDistance>Range)
							{
								//近い場合記録する
								fDistance = Range;
								//向きの記録
								m_NpcData[nNpc - 1].m_TargetRot = D3DXVECTOR3(RangeX, RangeZ, 0.0f);
								//現在のターゲットを取得
								m_NpcData[nNpc - 1].m_pTarget = pNext;
							}
						}
					}
					//次のオブジェクトのポインタを更新
					pNext = pNext->GetNext();
				}
			}
		}
	}
}

//=============================================================================
// 確率で向きをランダムに変更処理関数
//=============================================================================
void CPlayerControl::NpcRandomProbability(int nNpc)
{
	//ランダム関数の初期化
	srand((unsigned int)time(NULL));
	//ランダムに動く用の確率
	int nRandom = (rand() % NPC_MAX_RANDOM);
	//数値が10以下になった時
	if (nRandom <= 10)
	{
		//ランダムに向き変更
		NpcRandomControl(nNpc);
	}
}

//=============================================================================
// ランダム向き移動関数
//=============================================================================
void CPlayerControl::NpcRandomControl(int nNpc)
{
	//ランダム関数の初期化
	srand((unsigned int)time(NULL));

	//Xの数値
	float fXRandom = (float)((rand() % NPC_MAX_RANDOM_ROT) - NPC_MAX_RANDOM_ROT/2);
	//Yの数値
	float fYRandom = (float)((rand() % NPC_MAX_RANDOM_ROT) - NPC_MAX_RANDOM_ROT/2);
	//ランダムに設定
	m_NpcData[nNpc - 1].m_TargetRot = D3DXVECTOR3(fXRandom, fYRandom, 0.0f);

}

//=============================================================================
// ターゲット切替関数
//=============================================================================
void CPlayerControl::TargetSwitching(int nNpc)
{
	//ターゲットが変わっていないか
	if (m_NpcData[nNpc - 1].m_pTarget == m_NpcData[nNpc - 1].m_pOldTarget)
	{
		//変わっていないとカウントダウン
		m_NpcData[nNpc - 1].m_nTargetCount--;
	}

	//変わった際の処理
	else
	{
		//ターゲットを更新
		m_NpcData[nNpc - 1].m_pOldTarget = m_NpcData[nNpc - 1].m_pTarget;
		//カウントダウンの初期化
		m_NpcData[nNpc - 1].m_nTargetCount = NPC_MAX_TARGET_COUNT;
	}

	//カウントダウンが0いかになったら
	if (m_NpcData[nNpc - 1].m_nTargetCount <= 0)
	{
		m_NpcData[nNpc - 1].m_bRandomControl = true;
		m_NpcData[nNpc - 1].m_nTargetCount = NPC_MAX_TARGET_COUNT;
	}
}

//=============================================================================
// ランダム向き移動(長時間)処理関数
//=============================================================================
void CPlayerControl::NpcRandomCount(int nNpc)
{
	//ランダム移動のスイッチが入っているか
	if (m_NpcData[nNpc - 1].m_bRandomControl == true)
	{
		//カウントダウン
		m_NpcData[nNpc - 1].m_nRandomCount--;

		//ランダム移動
		NpcRandomControl(nNpc);

		//カウントが0になったら
		if (m_NpcData[nNpc - 1].m_nRandomCount <= 0)
		{
			//カウントを初期化
			m_NpcData[nNpc - 1].m_nRandomCount = NPC_MAX_RANDOM;
			//スイッチを切る
			m_NpcData[nNpc - 1].m_bRandomControl = false;
			return;
		}
	}
}

//=============================================================================
// バリアを避ける処理関数
//=============================================================================
void CPlayerControl::AvoidBarrier(int nNpc)
{
	//エリアの中心取得
	D3DXVECTOR3 centre = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//(ココの数値を範囲制限の円の中心を取得)
	//エリアの半径
	float fRadius = (m_fMapSize / 2) - NPC_AVOID_BARRIER;									//(ココの数値を範囲制限の円の半径を取得)

	//NPCの位置
	D3DXVECTOR3 NpcPos = m_pPlayer[nNpc]->GetPos();
	//NPCとバリアからの距離
	float RangeX = NpcPos.x - centre.x;
	float RangeZ = NpcPos.z - centre.z;
	float Range = (float)(sqrt(RangeX * RangeX + RangeZ * RangeZ));

	if (Range >= PLAYER_SIZE + (fRadius))
	{
		//向きの記録
		m_NpcData[nNpc - 1].m_TargetRot = D3DXVECTOR3(-RangeX, -RangeZ, 0.0f);
	}
}
