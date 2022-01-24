////////////////////////////////////////////////////
//
//    playerクラスの処理[player.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "player.h"
#include "manager.h"
#include "keyboard.h"
#include "joypad.h"
#include "collision.h"
#include "act_range.h"
#include "color_manager.h"
#include "attack.h"
#include "motion.h"
#include "color_tile.h"
#include "chara_select.h"
#include "kill_count.h"
#include "particle.h"
#include "all_skill_gauge.h"
#include "tutorial.h"
#include "sound.h"

//*****************************
// マクロ定義
//*****************************
#define MOVE_DIST				(TILE_ONE_SIDE)					// 移動距離
#define COLLISION_RADIUS		(18.0f)							// 当たり判定の大きさ
#define MODL_COLOR				(D3DXCOLOR(0.3f,0.3f,0.3f,1.0f))// モデルカラー
#define MODEL_SIZE				(D3DXVECTOR3(1.4f,1.4f,1.4f))	// モデルサイズ
#define RESPAWN_MAX_COUNT		(60*2)							// リスポーンまでの最大カウント
#define INVINCIBLE_COUNT		(60*2)							// 無敵時間
#define ROTDEST_PREVIOUS		(0.0f)							// 前方向き
#define ROTDEST_AFTER 			(180.0f)						// 後方向き
#define ROTDEST_LEFT			(270.0f)						// 左向き
#define ROTDEST_RIGHT			(90.0f)							// 右向き
#define ROT_SPEED				(0.3f)							// 回転速度
#define ROT_FACING_01			(180)							// 回転の基準
#define ROT_FACING_02			(360)							// 回転向き
#define DASH_FRAME				(60*5)							// ダッシュ時有効フレーム数
#define ATTCK_ROT_INPUT			(15)							// 攻撃方向受付するフレーム数
#define SKILL_ROT_INPUT			(35)							// 必殺技の方向受付フレーム数
#define FALL_OVER				(60*0.2)						// 倒れるフレーム数
#define FALL_OVER_KEEP			(FALL_OVER+60*2)				// 倒れた後にどれだけ維持するか

//*****************************
// 静的メンバ変数宣言
//*****************************
int CPlayer::m_anControllKey[MAX_PLAYER][CPlayer::KEY_MAX] =
{
	{ DIK_W,DIK_S,DIK_A,DIK_D,DIK_E,DIK_Q },
	{ DIK_UP,DIK_DOWN,DIK_LEFT,DIK_RIGHT,DIK_NUMPAD1,DIK_RSHIFT },
	{ DIK_U,DIK_J,DIK_H,DIK_K,DIK_I,DIK_Y },
	{ DIK_NUMPAD8,DIK_NUMPAD5,DIK_NUMPAD4,DIK_NUMPAD6,DIK_NUMPAD9,DIK_NUMPAD7 }
};

//******************************
// コンストラクタ
//******************************
CPlayer::CPlayer()
{
	m_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_ReverseCount = 0;
	m_nRespawnCount = 0;
	m_nPlayerNumber = 0;
	m_nInvincibleCount = 0;
	m_nControllNum = 0;
	m_bMove = false;
	m_bOldMove = false;
	m_bInvincible = false;
	m_PlayerState = PLAYER_STATE_NORMAL;
	m_pCollision = NULL;
	m_nColor = 0;
	m_pActRange = NULL;
	memset(&m_AttackData, 0, sizeof(m_AttackData));
	memset(&MoveData, 0, sizeof(MoveData));
	memset(&m_RespawnPos, 0, sizeof(D3DXVECTOR3));
	m_pAttack = NULL;
	m_ItemState = ITEM_STATE_NONE;	// アイテム用ステート
	m_nDashCnt = 1;					// 速度アップカウント
	m_bController = false;
	m_bUpdate = false;
	m_pKillCount = NULL;
	m_nChargeTilelevel = 0;
	m_nFallOverCout = 0;
}

//******************************
// デストラクタ
//******************************
CPlayer::~CPlayer()
{
}

//******************************
// クラス生成
//******************************
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPlayerNumber)
{
	// メモリの確保
	CPlayer *pPlayer;
	pPlayer = new CPlayer;

	// initで使うから先に代入
	pPlayer->m_nPlayerNumber = nPlayerNumber;

	// オブジェクトタイプ
	pPlayer->SetPriority(OBJTYPE_PLAYER);

	// 初期化
	pPlayer->Init();

	// 各値の代入・セット
	pPlayer->SetPos(pos);
	pPlayer->SetRot(rot);
	pPlayer->m_RespawnPos = pos;

	// 必殺用クラス生成
	//pPlayer->m_pAttack = CAttackFinalknight::Create(pPlayer);

	//移動範囲クラスの生成
	pPlayer->m_pActRange = CActRange::Create(pPlayer);

	return pPlayer;
}

//******************************
// プレイヤーの取得処理*プレイヤー番号参照
//******************************
CPlayer * CPlayer::GetPlayerByPlayerNumber(int nPlayerNum)
{
	CPlayer*pPlayer = (CPlayer*)GetTop(OBJTYPE_PLAYER);

	while (pPlayer != NULL)
	{
		if (pPlayer->GetPlayerNumber() == nPlayerNum)
		{
			return pPlayer;
		}
		pPlayer = (CPlayer*)pPlayer->GetNext();
	}

	return pPlayer;
}

//******************************
// 初期化処理
//******************************
HRESULT CPlayer::Init(void)
{
	// キャラタイプのセット
	SetCharacterType(CCharaSelect::GetEntryData(m_nPlayerNumber).charaType);
	// キャラデータの初期化
	InitCharacterData();

	if (FAILED(CPlayerModel::Init()))
	{
		return E_FAIL;
	}

	// モデルのサイズの設定
	SetSize(MODEL_SIZE);

	// 移動フラグの初期化
	m_bMove = true;
	// 無敵フラグの初期化
	m_bInvincible = false;
	// 更新フラグの初期化
	m_bUpdate = false;
	//プレイヤーステータス初期化
	m_PlayerState = PLAYER_STATE_NORMAL;
	//色設定
	m_color = MODL_COLOR;
	// エントリーデータの取得
	CCharaSelect::Entry_Data entryData = CCharaSelect::GetEntryData(m_nPlayerNumber);
	// コントロール番号
	m_nControllNum = entryData.nControllNum;
	m_bController = entryData.bController;
	// カラー番号の取得
	m_nColor = entryData.nColorNum;
	CColorManager::GetColorManager()->SetUsePlayerNum(m_nPlayerNumber, m_nColor);
	//リムライトカラーの設定
	SetRimColor(GET_COLORMANAGER->GetIconColor(m_nColor));
	//テクスチャカラーの設定
	SetTexColor(GET_COLORMANAGER->GetIconColor(m_nColor));
	// キルカウント用のクラス
	m_pKillCount = CKillCount::Create(m_nPlayerNumber);
	// スキルゲージの生成
	m_pAllSkillgauge = CAllskillgauge::Create(m_nColor);

	//// プレイヤーの頭上に出すスコア生成
	//CNumberArray::Create(0, GetPos(), D3DXVECTOR3(10.0f, 10.0f, 0.0f), GET_COLORMANAGER->GetIconColor(m_nColor), m_nColor);
	
	//向きの移動量
	m_rotDest = D3DXVECTOR3(0.0f, D3DXToRadian(0.0f), 0.0f);

	// アイテムステート
	m_ItemState = ITEM_STATE_NONE;
	
	//移動速度の取得
	MoveData.m_nMoveFrame = MoveData.m_nMoveFrameInitialData;
	//速度アップカウント
	m_nDashCnt = 0;		
	return S_OK;
}

//******************************
// キャラデータの初期化
//******************************
void CPlayer::InitCharacterData(void)
{
	CResourceCharacter::CharacterData charaData = CResourceCharacter::GetResourceCharacter()->GetCharacterData(GetCharacterType());
	// キャラデータの反映
	MoveData.m_nMoveFrameData = charaData.nMoveFrame;				// 移動時フレーム数
	MoveData.m_nMoveFrameDataDash = charaData.nMoveFrameDash;		// 移動時フレーム数*ダッシュ時
	MoveData.m_nMoveFrameInitialData = charaData.nMoveFrameInitial;	// 初動時の移動フレーム数
	MoveData.m_nMoveCountData = charaData.nMoveCount;				// 加速までの回数

	// 既存の攻撃の破棄
	if (m_pAttack != NULL)
	{
		m_pAttack->OutList();
		m_pAttack->ReleaseAttakcArea();
		m_pAttack->Uninit();
		delete m_pAttack;
		m_pAttack = NULL;
	}

	//攻撃用クラス生成(今後職業ごとに攻撃タイプを変える)
	m_pAttack = CAttackBased::Create(this, CCharaSelect::GetEntryData(m_nPlayerNumber).charaType);
}

//******************************
// 終了処理
//******************************
void CPlayer::Uninit(void)
{
	//当たり判定の終了処理
	if (m_pCollision != NULL)
	{
		m_pCollision->OutList();
		m_pCollision->Uninit();
		delete m_pCollision;
		m_pCollision = NULL;
	}

	CPlayerModel::Uninit();

	// スキルゲージの終了処理
	if (m_pAllSkillgauge)
	{
		delete m_pAllSkillgauge;
		m_pAllSkillgauge = nullptr;
	}
}

//******************************
// 更新処理
//******************************
void CPlayer::Update(void)
{
	if (!m_bUpdate)
	{
		//プレイヤーのモデルパーツ更新処理
		CPlayerModel::Update();
		return;
	}

	// ステート管理
	ManageState();

	//移動状況
	m_bOldMove = m_bMove;

	//死亡している以外の時移動計算処理
	if (m_PlayerState != PLAYER_STATE_DEATH&&m_PlayerState != PLAYER_STATE_RESPAWN) Move();
	//当たり判定の位置更新処理
	if (m_pCollision != NULL) m_pCollision->SetPos(D3DXVECTOR3(GetPos().x, GetPos().y + COLLISION_RADIUS / 2, GetPos().z));
	//無敵処理
	Invincible();
	// 向きの管理
	ManageRot();

	// アイテムステートの管理
	ManageItemState();

	//プレイヤーモデルの更新
	CPlayerModel::Update();

#ifdef _DEBUG
	// キーボードの取得
	if (m_nPlayerNumber == 0)
	{
		CInputKeyboard * pKey = CManager::GetKeyboard();
		if (pKey->GetKeyPress(DIK_1))
		{
			Death();
		}
		if (pKey->GetKeyPress(DIK_2))
		{
			m_pAttack->AttackSwitch();
		}
		if (pKey->GetKeyPress(DIK_3))
		{
			m_pAttack->AttackSwitch();
		}
	}
#endif // _DEBUG

}

//******************************
// 描画処理
//******************************
void CPlayer::Draw(void)
{
	// 色の設定
	for (int nCntParts = 0; nCntParts < GetPartsNum(); nCntParts++)
	{
		for (int nCntMat = 0; nCntMat < (int)GetModelData()[nCntParts].nNumMat; nCntMat++)
		{
			D3DXMATERIAL* mat = (D3DXMATERIAL*)GetModelData()[nCntParts].pBuffMat->GetBufferPointer();
			mat[nCntMat].MatD3D.Ambient .a = m_color.a;
			mat[nCntMat].MatD3D.Diffuse .a = m_color.a;
			mat[nCntMat].MatD3D.Specular.a = m_color.a;
			mat[nCntMat].MatD3D.Emissive.a = m_color.a;
		}
	}

	CPlayerModel::Draw();
}

//******************************
// 死亡処理
// Author:吉田 悠人
//******************************
void CPlayer::Death(void)
{
	// サウンド情報の取得
	CSound *pSound = CManager::GetSound();

	if (!m_bInvincible)
	{
		//死亡状態に移行
		SetState(PLAYER_STATE_DEATH);

		// SE再生
		pSound->Play(CSound::LABEL_SE_DEATH);

		//当たり判定を消す
		if (m_pCollision != NULL)
		{
			m_pCollision->OutList();
			m_pCollision->Uninit();
			delete m_pCollision;
			m_pCollision = NULL;
		}

		//行動クラスに死亡状態になったフラグを送る
		m_pActRange->SetDeath(true);
		//攻撃状態の初期化
		m_pAttack->SetState(CAttackBased::ATTACK_STATE_NORMAL);
	}

}

//******************************
// 移動処理
// Author:吉田 悠人
//******************************
void CPlayer::Move(void)
{
	if (!m_bMove)
	{
		// 座標の取得
		D3DXVECTOR3 pos = GetPos();

		//移動計算
		pos += (MoveData.m_Move - pos) / (float)(MoveData.m_nMoveFrame - MoveData.m_nMoveFrameCount);

		//位置設定
		SetPos(pos);

		//カウントアップ
		MoveData.m_nMoveFrameCount++;

		//カウントが一定に達する
		if (MoveData.m_nMoveFrameCount >= MoveData.m_nMoveFrame)
		{
			
			// 初動加速処理
			if (MoveData.m_nMoveCount<MoveData.m_nMoveCountData
				&&m_ItemState != ITEM_STATE_DASH)
			{

				MoveData.m_nMoveFrame += (MoveData.m_nMoveFrameData - MoveData.m_nMoveFrame) / (MoveData.m_nMoveCountData - MoveData.m_nMoveCount);
				MoveData.m_nMoveCount++;
			}
			//カウント初期化
			MoveData.m_nMoveFrameCount = 0;
			//移動できるように
			m_bMove = true;

			//フラグの状態を伝える
			m_pActRange->SetMove(m_bMove);
		}
	}
}

//******************************
// 攻撃時の向き処理
// Author:吉田 悠人
//******************************
void CPlayer::AttackRot(void)
{
	// キーボードとジョイパッドの取得
	CInputKeyboard * pKey = CManager::GetKeyboard();
	CInputJoypad* pJoypad = CManager::GetJoypad();

	// スティックの座標
	D3DXVECTOR2 StickPos = pJoypad->GetStickState(pJoypad->PAD_LEFT_STICK, m_nControllNum);

	if (!m_bController && pKey->GetKeyPress(m_anControllKey[m_nControllNum][KEY_PROGRESS])
		|| m_bController && ((StickPos.y > 0.0f && StickPos.x < STICK_DECISION_RANGE && StickPos.x > -STICK_DECISION_RANGE)
			
			|| pJoypad->GetButtonState(XINPUT_GAMEPAD_DPAD_UP, CInputJoypad::BUTTON_PRESS, m_nControllNum)))
	{
		m_rotDest.y = D3DXToRadian(ROTDEST_PREVIOUS);
	}
	else if (!m_bController && pKey->GetKeyPress(m_anControllKey[m_nControllNum][KEY_RECESSION])
		|| m_bController && ((StickPos.y < 0.0f && StickPos.x < STICK_DECISION_RANGE && StickPos.x > -STICK_DECISION_RANGE)
			
			|| pJoypad->GetButtonState(XINPUT_GAMEPAD_DPAD_DOWN, CInputJoypad::BUTTON_PRESS, m_nControllNum)))
	{
		m_rotDest.y = D3DXToRadian(ROTDEST_AFTER);
	}
	else if (!m_bController && pKey->GetKeyPress(m_anControllKey[m_nControllNum][KEY_LEFT])
		|| m_bController && ((StickPos.x < 0.0f && StickPos.y < STICK_DECISION_RANGE && StickPos.y > -STICK_DECISION_RANGE)
	
			|| pJoypad->GetButtonState(XINPUT_GAMEPAD_DPAD_LEFT, CInputJoypad::BUTTON_PRESS, m_nControllNum)))
	{
		m_rotDest.y = D3DXToRadian(ROTDEST_LEFT);
	}
	else if (!m_bController && pKey->GetKeyPress(m_anControllKey[m_nControllNum][KEY_RIGHT])
		|| m_bController && ((StickPos.x > 0.0f && StickPos.y < STICK_DECISION_RANGE && StickPos.y > -STICK_DECISION_RANGE)
		
			|| pJoypad->GetButtonState(XINPUT_GAMEPAD_DPAD_RIGHT, CInputJoypad::BUTTON_PRESS, m_nControllNum)))
	{
		m_rotDest.y = D3DXToRadian(ROTDEST_RIGHT);
	}


	while (m_rotDest.y - GetRot().y > D3DXToRadian(ROT_FACING_01))
	{
		m_rotDest.y -= D3DXToRadian(ROT_FACING_02);
	}

	while (m_rotDest.y - GetRot().y < D3DXToRadian(-ROT_FACING_01))
	{
		m_rotDest.y += D3DXToRadian(ROT_FACING_02);
	}


	if (D3DXToDegree(GetRot().y) + 1 >= D3DXToDegree(m_rotDest.y)
		&& D3DXToDegree(GetRot().y) - 1 <= D3DXToDegree(m_rotDest.y))
	{
		m_AttackData.m_bAttackRot = false;
	}
	else
	{
		m_AttackData.m_bAttackRot = true;
	}
}

//******************************
// 操作移動処理
// Author:吉田 悠人
//******************************
void CPlayer::ControlMove(void)
{
	if (m_bMove&&!m_AttackData.m_bAttack)
	{
		// キーボードとジョイパッドの取得
		CInputKeyboard * pKey = CManager::GetKeyboard();
		CInputJoypad* pJoypad = CManager::GetJoypad();

		// スティックの座標
		D3DXVECTOR2 StickPos = pJoypad->GetStickState(pJoypad->PAD_LEFT_STICK, m_nControllNum);

		// 移動値
		auto MoveValue = [&](D3DXVECTOR3 move, D3DXVECTOR2 actMove, float fRotDistY)
		{
			//プレイヤーの移動方向取得変数
			D3DXVECTOR2 ActMove;
			
			//プレイヤーの加速度を初期化
			if (m_bOldMove&&m_ItemState != ITEM_STATE_DASH)
			{
				MoveData.m_nMoveFrame = MoveData.m_nMoveFrameInitialData;
				MoveData.m_nMoveCount = 0;
			}

			//操作逆転状態じゃない時
			if (m_ItemState != ITEM_STATE_REVERSE)
			{

				ActMove = actMove;
				if (m_pActRange->ActMove(((int)ActMove.x), ((int)ActMove.y)))
				{
					MoveData.m_Move = move + GetPos();
					m_bMove = false;
					m_rotDest.y = fRotDistY;
				}
			}
			//操作逆転状態の時
			else
			{
				ActMove = -actMove;
				if (m_pActRange->ActMove(((int)ActMove.x), ((int)ActMove.y)))
				{
					MoveData.m_Move = -move + GetPos();
					m_bMove = false;
					m_rotDest.y = fRotDistY - D3DXToRadian(180);
				}
			}

		};

		if (!m_bController && pKey->GetKeyPress(m_anControllKey[m_nControllNum][KEY_PROGRESS])
			|| m_bController && ((StickPos.y > 0.0f && StickPos.x < STICK_DECISION_RANGE && StickPos.x > -STICK_DECISION_RANGE)
		
				|| pJoypad->GetButtonState(XINPUT_GAMEPAD_DPAD_UP, CInputJoypad::BUTTON_PRESS, m_nControllNum)))
		{
			MoveValue(D3DXVECTOR3(0.0f, 0.0f, -MOVE_DIST), D3DXVECTOR2(0, -1), D3DXToRadian(ROTDEST_PREVIOUS));
		}
		else if (!m_bController && pKey->GetKeyPress(m_anControllKey[m_nControllNum][KEY_RECESSION])
			|| m_bController && ((StickPos.y < 0.0f && StickPos.x < STICK_DECISION_RANGE && StickPos.x > -STICK_DECISION_RANGE)

				|| pJoypad->GetButtonState(XINPUT_GAMEPAD_DPAD_DOWN, CInputJoypad::BUTTON_PRESS, m_nControllNum)))
		{
			MoveValue(D3DXVECTOR3(0.0f, 0.0f, MOVE_DIST), D3DXVECTOR2(0, 1), D3DXToRadian(ROTDEST_AFTER));
		}
		else if (!m_bController && pKey->GetKeyPress(m_anControllKey[m_nControllNum][KEY_LEFT])
			|| m_bController && ((StickPos.x < 0.0f && StickPos.y < STICK_DECISION_RANGE && StickPos.y > -STICK_DECISION_RANGE)
		
				|| pJoypad->GetButtonState(XINPUT_GAMEPAD_DPAD_LEFT, CInputJoypad::BUTTON_PRESS, m_nControllNum)))
		{
			MoveValue(D3DXVECTOR3(MOVE_DIST, 0.0f, 0.0f), D3DXVECTOR2(-1, 0), D3DXToRadian(ROTDEST_LEFT));
		}
		else if (!m_bController && pKey->GetKeyPress(m_anControllKey[m_nControllNum][KEY_RIGHT])
			|| m_bController && ((StickPos.x > 0.0f && StickPos.y < STICK_DECISION_RANGE && StickPos.y > -STICK_DECISION_RANGE)

				|| pJoypad->GetButtonState(XINPUT_GAMEPAD_DPAD_RIGHT, CInputJoypad::BUTTON_PRESS, m_nControllNum)))
		{
			MoveValue(D3DXVECTOR3(-MOVE_DIST, 0.0f, 0.0f), D3DXVECTOR2(1, 0), D3DXToRadian(ROTDEST_RIGHT));
		}
		m_pActRange->SetMove(m_bMove);
	}
}


//******************************
// 向きの管理処理
// Author：佐藤颯紀
//******************************
void CPlayer::ManageRot(void)
{
	// 向きの取得
	D3DXVECTOR3 rot = GetRot();

	while (m_rotDest.y - rot.y > D3DXToRadian(ROT_FACING_01))
	{
		m_rotDest.y -= D3DXToRadian(ROT_FACING_02);
	}

	while (m_rotDest.y - rot.y < D3DXToRadian(-ROT_FACING_01))
	{
		m_rotDest.y += D3DXToRadian(ROT_FACING_02);
	}

	// 目標の向きに変える
	rot += (m_rotDest - rot)*ROT_SPEED;

	// 向き設定
	SetRot(rot);
}


//******************************
// 攻撃処理
// Author:吉田悠人・佐藤颯紀
//******************************
void CPlayer::Attack(void)
{
	// キーボードとジョイパッドの取得
	CInputKeyboard * pKey = CManager::GetKeyboard();
	CInputJoypad* pJoypad = CManager::GetJoypad();
	CColorTile*pHitTile = CColorTile::GetHitColorTile(GetPos());
	D3DXVECTOR3 rot = GetRot();

	// 攻撃ボタンを押したらチャージ
	if (!m_bController && pKey->GetKeyPress(m_anControllKey[m_nControllNum][KEY_BULLET])

		|| m_bController &&pJoypad->GetButtonState(XINPUT_GAMEPAD_X, CInputJoypad::BUTTON_PRESS, m_nControllNum))
	{	
		if (pHitTile != NULL)
		{
			m_nChargeTilelevel = pHitTile->GetStepNum();
		}
		//攻撃チャージを開始
		m_pAttack->ChargeFlag();
		
	}
				
	//チャージ状態か
	if (m_pAttack->GetState() == CAttackBased::ATTACK_STATE_CHARGE)
	{
		// 離したら攻撃がでるように
		if (!m_bController && pKey->GetKeyRelease(m_anControllKey[m_nControllNum][KEY_BULLET])
		
			|| m_bController && pJoypad->GetButtonState(XINPUT_GAMEPAD_X, CInputJoypad::BUTTON_RELEASE, m_nControllNum))
		{
			//攻撃フラグを立てる
			m_AttackData.m_bAttack = true;
		}
	}

	//攻撃フラグが立っているか＆移動フラグが立っていない状態か&ステートが通常状態か
	if (m_AttackData.m_bAttack&&m_bMove&&m_PlayerState == PLAYER_STATE_NORMAL)
	{
		//カウントアップ
		m_AttackData.m_nAttackRotCount++;
		//攻撃方向指定
		AttackRot();

		//一定のカウントかフラグが立っているか
		if (m_AttackData.m_nAttackRotCount>= ATTCK_ROT_INPUT
			|| m_AttackData.m_bAttackRot)
		{
			//フラグを回収
			m_AttackData.m_bAttackRot = false;
			//カウント初期化
			m_AttackData.m_nAttackRotCount = 0;
			//フラグを回収
			m_AttackData.m_bAttack = false;
			//攻撃スイッチ処理
			m_pAttack->AttackSwitch();
			//アニメーション処理
			GetMotion(CResourceCharacter::MOTION_ATTACK)->SetActiveMotion(true);


		}
	}
}

//******************************
// 必殺処理
// Author：佐藤颯紀
//******************************
void CPlayer::AttackFinal(void)
{
	// キーボードとジョイパッドの取得
	CInputKeyboard * pKey = CManager::GetKeyboard();
	CInputJoypad* pJoypad = CManager::GetJoypad();
	CColorTile*pHitTile = CColorTile::GetHitColorTile(GetPos());

	// アタックタイプが通常状態なら
	if (m_AttackData.m_bFinalAttack)
	{
		// 攻撃ボタンを押したら
		if (!m_bController && pKey->GetKeyPress(m_anControllKey[m_nControllNum][KEY_ATTCK_FINAL])

			|| m_bController &&pJoypad->GetButtonState(XINPUT_GAMEPAD_Y, CInputJoypad::BUTTON_PRESS, m_nControllNum))
		{
	
			if (pHitTile != NULL)
			{
				m_nChargeTilelevel = pHitTile->GetStepNum();
			}
			m_pAttack->AttackFinalFlag();

		}
	}

	// 攻撃状態じゃないなら
	if (m_pAttack->GetState() == CAttackBased::ATTACK_STATE_FINALATTACKWAITING)
	{
		// 離したら弾がでるように
		if (!m_bController && pKey->GetKeyRelease(m_anControllKey[m_nControllNum][KEY_ATTCK_FINAL])
	
			|| m_bController && pJoypad->GetButtonState(XINPUT_GAMEPAD_Y, CInputJoypad::BUTTON_RELEASE, m_nControllNum))
		{
			m_AttackData.m_bAttack = true;
		}
	}


	//攻撃フラグが立っているか＆移動フラグが立っていない状態か&ステートが通常状態か
	if (m_AttackData.m_bAttack&&m_bMove&&m_PlayerState == PLAYER_STATE_NORMAL)
	{
		//カウントアップ
		m_AttackData.m_nAttackRotCount++;
		//攻撃方向指定
		AttackRot();

		//攻撃時に方向を変更したら
		if (m_AttackData.m_bAttackRot)
		{
			//フレーム数が一定に達したら
			if (m_AttackData.m_nAttackRotCount >= SKILL_ROT_INPUT)
			{
				//フラグを回収
				m_AttackData.m_bAttackRot = false;
				//カウント初期化
				m_AttackData.m_nAttackRotCount = 0;
				//フラグを回収
				m_AttackData.m_bAttack = false;
				//攻撃スイッチ処理
				m_pAttack->AttackFinalSwitch();
				//アニメーション処理
				GetMotion(CResourceCharacter::MOTION_ATTACK)->SetActiveMotion(true);
			}
		}
		else if (m_AttackData.m_nAttackRotCount >= ATTCK_ROT_INPUT)
		{
			//フラグを回収
			m_AttackData.m_bAttackRot = false;
			//カウント初期化
			m_AttackData.m_nAttackRotCount = 0;
			//フラグを回収
			m_AttackData.m_bAttack = false;
			//攻撃スイッチ処理
			m_pAttack->AttackFinalSwitch();
			//アニメーション処理
			GetMotion(CResourceCharacter::MOTION_ATTACK)->SetActiveMotion(true);
		}
	}
}

//******************************
// 無敵状態セッター処理
// Author:吉田悠人
//******************************
void CPlayer::SetInvincible(bool bInvincible)
{
	//初期化
	m_nInvincibleCount = 0;
	m_color.a = 1.0f;
	m_bInvincible = bInvincible;
}

//******************************
// 死亡時の倒れる処理
// Author:吉田悠人
//******************************
void CPlayer::DeathFallOver(void)
{
	//フレームカウント
	m_nFallOverCout++;

	//フレームが一定の数値に達していなければ
	if (m_nFallOverCout < FALL_OVER)
	{
		//プレイヤーを倒れさす
		m_rotDest.z += (D3DXToRadian(80) - m_rotDest.z) / (float)(FALL_OVER - m_nFallOverCout);
	}
	else if(m_nFallOverCout > FALL_OVER+60)
	{
		//5の倍数でカラーを変更（点滅するように）
		if ((m_nFallOverCout % 5) == 0)
		{
			//点滅
			if (m_color.a <= 0.0f)
			{
				m_color.a = 1.0f;
			}
			else
			{
				m_color.a = 0.0f;
			}
		}
	}


	//フレームが一定に達したていたら
	if (m_nFallOverCout >= FALL_OVER_KEEP)
	{
		//カウントの初期化
		m_nFallOverCout = 0;
		//角度を戻す
		m_rotDest.z = 0;
		//透明にする
		m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		//リスポーン待機状態に移行
		SetState(PLAYER_STATE_RESPAWN);
	}


}

//******************************
// リスポーン処理
// Author:吉田悠人
//******************************
void CPlayer::Respawn(void)
{
	//プレイヤーステートが死亡状態の時
	if (m_PlayerState == PLAYER_STATE_RESPAWN)
	{
		//カウントアップ
		m_nRespawnCount++;
		//カウントが一定までに達したとき
		if (m_nRespawnCount >= RESPAWN_MAX_COUNT)
		{
			//通常状態に移行
			SetState(PLAYER_STATE_NORMAL);
			//位置セット
			SetPos(m_RespawnPos);
			//移動量セット
			m_bMove = true;
			//行動クラスに通常状態になったフラグを送る
			m_pActRange->SetDeath(false);
			//行動クラスに位置設定をするように送る
			m_pActRange->PlayerPos();
			//移動フラグ
			m_bMove = true;
			//無敵処理
			m_bInvincible = true;
			//カウント初期化
			m_nRespawnCount = 0;
		}
	}
}

//******************************
// 無敵処理
// Author:吉田悠人
//******************************
void CPlayer::Invincible(void)
{
	//無敵フラグが立っているか
	if (m_bInvincible)
	{
		//無敵カウントアップ
		m_nInvincibleCount++;
		//5の倍数でカラーを変更（点滅するように）
		if ((m_nInvincibleCount % 5) == 0)
		{
			//点滅
			if (m_color.a <= 0.0f)
			{
				m_color.a = 1.0f;
			}
			else
			{
				m_color.a = 0.0f;
			}
		}
		//カウントが一定になったら
		if (m_nInvincibleCount >= INVINCIBLE_COUNT)
		{
			SetInvincible(false);
		}
	}
}

//******************************
// ステート管理
// Author:吉田悠人
//******************************
void CPlayer::ManageState(void)
{
	//ステートごとの処理
	switch (m_PlayerState)
	{
	case PLAYER_STATE_NORMAL:	//通常状態

		//攻撃可否フラグが立っているか
		if (m_pAttack->GetState() != CAttackBased::ATTACK_STATE_ATTACK
			&& m_pAttack->GetState() != CAttackBased::ATTACK_STATE_FINALATTACK
			&& TutorialControll(CTutorial::PHASE_PAINT))
		{
			// 移動処理
			ControlMove();
			//ジョイパットの取得
			CInputJoypad* pJoypad = CManager::GetJoypad();

			//攻撃キャンセル
			if (m_bController && pJoypad->GetButtonState(XINPUT_GAMEPAD_RIGHT_SHOULDER, CInputJoypad::BUTTON_PRESS, m_nControllNum))
			{
				m_pAttack->CancelSwitch();
			}
			//攻撃をチャージしていないとき
			if (m_pAttack->GetState() != CAttackBased::ATTACK_STATE_CHARGE
				&& TutorialControll(CTutorial::PHASE_FINALATTACK))
			{
				// 必殺の処理
				AttackFinal();
			}
			//必殺技を使っていないとき
			if (m_pAttack->GetState() != CAttackBased::ATTACK_STATE_FINALATTACKWAITING
				&& TutorialControll(CTutorial::PHASE_ATTACK))
			{
				// 攻撃処理
				Attack();
			}
		}
		// 当たり判定の位置
		if (m_pCollision == NULL)
		{
			m_pCollision = CCollision::CreateSphere(D3DXVECTOR3(GetPos().x, GetPos().y + COLLISION_RADIUS / 2, GetPos().z), COLLISION_RADIUS / 2);
		}

		break;
	case PLAYER_STATE_STOP:
		//攻撃可否フラグが立っているか
		if (m_pAttack->GetState() != CAttackBased::ATTACK_STATE_ATTACK
			&& m_pAttack->GetState() != CAttackBased::ATTACK_STATE_FINALATTACK)
		{
			//ジョイパットの取得
			CInputJoypad* pJoypad = CManager::GetJoypad();

			//攻撃キャンセル
			if (m_bController && pJoypad->GetButtonState(XINPUT_GAMEPAD_RIGHT_SHOULDER, CInputJoypad::BUTTON_PRESS, m_nControllNum))
			{
				m_pAttack->CancelSwitch();
			}
			//攻撃をチャージしていないとき
			if (m_pAttack->GetState() != CAttackBased::ATTACK_STATE_CHARGE)
			{
				// 必殺の処理
				AttackFinal();
			}
			//必殺技を使っていないとき
			if (m_pAttack->GetState() != CAttackBased::ATTACK_STATE_FINALATTACKWAITING)
			{
				// 攻撃処理
				Attack();
			}
		}
		break;
	case PLAYER_STATE_DEATH:	//死亡状態
		DeathFallOver();	//倒れこむ処理
		break;
	case PLAYER_STATE_RESPAWN:	//リスポーン待機状態
		Respawn();			//リスポーン処理
		break;

	}
}

//******************************
// アイテムステートの管理
// Author:吉田悠人
//******************************
void CPlayer::ManageItemState(void)
{
	switch (m_ItemState)
	{
	case ITEM_STATE_NONE:
		break;
	case ITEM_STATE_DASH:

		//ダッシュタイムをカウント
		m_nDashCnt++;

		//速度を設定
		MoveData.m_nMoveFrame = (int)(MoveData.m_nMoveFrameDataDash);

		//効果を切る
		if (m_nDashCnt % DASH_FRAME == 0)
		{
			MoveData.m_nMoveCount = 0;
			m_nDashCnt = 0;
			MoveData.m_nMoveFrame = MoveData.m_nMoveFrameData;
			m_ItemState = ITEM_STATE_NONE;
		}
		break;
	case ITEM_STATE_REVERSE:
		m_ReverseCount++;
		//効果を切る
		if (m_ReverseCount % 180 == 0)
		{
			m_ReverseCount = 0;
			m_ItemState = ITEM_STATE_NONE;
		}

		//ランダムでエフェクトを生成
		if (m_ReverseCount % 15 == 0)
		{
			D3DXVECTOR3 pos = GetPos();
			pos.y += 10.0f;
			CParticle::Create(pos, D3DXVECTOR3((float)(rand() % 16 - 8) / 100.0f, 0.25f, (float)(rand() % 16 - 8) / 100.0f), D3DXVECTOR3(7.0f, 7.0f, 7.0f), 500, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECT_DEFAULT_FADE_OUT_RATE, GetRotDest().y , this, CParticle::PARTICLE_GURUGURU)->SetAddRotValue(1.2f);
		}
		break;
	}
}

//==========================================================
// チュートリアル時のフェーズによって操作を制限する処理
// nTutorialphase：制限したい行動のフェーズ
// Author:伊藤陽梧
//==========================================================
bool CPlayer::TutorialControll(int nTutorialphase)
{
	CTutorial* pTutorial = CManager::GetTutorial();
	if (pTutorial)
	{
		// チュートリアルの段階が同じだったら真を返す
		if (pTutorial->GetTutorialPhase() == nTutorialphase)
		{
			return true;
		}
		// 移動は常にするためフェーズに入ったら常時真を返す
		else if (CTutorial::PHASE_PAINT >= nTutorialphase)
		{
			return true;
		}
		// チュートリアルのフェーズが完了したら常に真を返す
		else if (CTutorial::PHASE_FINISH == pTutorial->GetTutorialPhase())
		{
			return true;
		}
	}
	else
	{
		// チュートリアルのポインタないなら真
		// ゲーム中のエラー回避のため
		return true;
	}

	return false;
}

