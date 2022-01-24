//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 吉田悠人
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "player.h"		
#include "player data.h"
#include "input.h"			
#include "inihkeyboard.h"	
#include "inputmouse.h"		
#include "manager.h"		
#include "bullet.h"			
#include "renderer.h"		
#include "sound.h"			
#include "life.h"			
#include "game.h"			
#include "laser.h"			
#include "homing.h"			
#include "fade.h"			
#include "explosion.h"		
//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_DAMAGE		(100)	//ダメージ状態の最大無敵時間
#define PLAYER_BULLET_TIME	(20)	//バレットのクールタイム
#define PLAYER_LASER_TIME	(30)	//レーザーのクールタイム
#define PLAYER_HOMING_TIME	(35)	//ホーミングのクールタイム

//=============================================================================
// 静的メンバー変数
//=============================================================================
TEXTURE_DATA CPlayer::m_TextureData = {NULL,"data/TEXTURE/Player.png" };
//=============================================================================
// コンストラクト
//=============================================================================
CPlayer::CPlayer(int nPriorit) :CScene2d(nPriorit)
{
	//タイプ処理
	CScene::SetObjType(CScene::OBJ_TYPE_PLAYER);	
	Stats		= STATS_MODE_NONE;
	m_nLife		= NULL;
	m_fSpeed	= NULL;
	memset(&m_Weapon, NULL, sizeof(m_Weapon));
	ZeroMemory(m_nAttackCount, sizeof(m_nAttackCount));
}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CPlayer::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, m_TextureData.m_cFileName, &m_TextureData.m_Texture);
	return S_OK;
}

//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CPlayer::Unload(void)
{
	//テクスチャの破棄
	if (m_TextureData.m_Texture != NULL)
	{
		m_TextureData.m_Texture->Release();
		m_TextureData.m_Texture = NULL;
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 Pos)
{
	//メモリ確保
	CPlayer *pPlayer = NULL;
	pPlayer = new CPlayer;

	//NULLチェック
	if (pPlayer != NULL)
	{
		//位置設定
		pPlayer->SetPos(Pos);
		//サイズ設定
		pPlayer->SetSize(D3DXVECTOR3(PLAYER_SIZE / 2.0f, PLAYER_SIZE / 2.0f, 0.0f));
		//ライフ設定
		pPlayer->SetLife(PLAYER_LIFE + CManager::GetPlayer()->GetLifeData());
		//スピード設定
		pPlayer->SetSpeed(PLAYER_SPEED + CManager::GetPlayer()->GetSpeedData());
		//ウェポン設定
		pPlayer->SetWeapon(CManager::GetPlayer()->GetWeaponData());
		//初期化処理
		pPlayer->Init();
	}

	return pPlayer;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPlayer::Init(void)
{
	//状態設定
	Stats = STATS_MODE_NORMAL;
	//初期化処理
	CScene2d::Init();
	//テクスチャの設定
	BindTexture(m_TextureData.m_Texture);
	//ライフ表記
	pLife = CLife::Create(D3DXVECTOR3(100, 100, 0.0f));
	if (pLife != NULL)
	{
		pLife->SetLife(m_nLife);
	}

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update(void)
{
	// マウス取得
	CInihMouse *pMouse	= CManager::GetMouse();			
	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	if (Stats!= STATS_MODE_NONE)
	{
		//攻撃処理
		Weapon();

		//移動処理
		Move();

		//アップデート処理
		CScene2d::Update();

		//状態管理
		StatasManage();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	if (Stats != STATS_MODE_NONE)
	{
		//描画処理
		CScene2d::Draw();
	}
}


//=============================================================================
// ダメージ処理
//=============================================================================
void CPlayer::Damage(int nDamage)
{
	if (Stats == STATS_MODE_NORMAL)
	{
		//ライフダメージ
		m_nLife -= nDamage;
		//ライフ表示処理
		pLife->DownLife(nDamage);
		//状態変換
		if (m_nLife > 0)
		{
			//ダメージ状態に移行
			Stats = STATS_MODE_DAMAGE;
		}
		else
		{
			//死亡状態に移行
			Stats = STATS_MODE_DEATH;
		}
	}

}

//=============================================================================
// セットライフ
//=============================================================================
void CPlayer::SetLife(int nLife)
{
	m_nLife = nLife;
}

//=============================================================================
// セットライフ
//=============================================================================
void CPlayer::SetSpeed(float fSpeed)
{
	m_fSpeed = fSpeed;
}

//=============================================================================
// セットウェポン
//=============================================================================
void CPlayer::SetWeapon(WEAPON_DATA wepon)
{
	m_Weapon = wepon;
}

//=============================================================================
// ライフゲッター
//=============================================================================
int CPlayer::GetLife(void)
{
	return m_nLife;
}

//=============================================================================
// スピードゲッター
//=============================================================================
float	CPlayer::GetSpeed(void)		
{
	return m_fSpeed;
}

//=============================================================================
// ウェポンゲッター
//=============================================================================
WEAPON_DATA CPlayer::GetWeapon(void)
{
	return m_Weapon;
}

//=============================================================================
//状態管理処理
//=============================================================================
void CPlayer::StatasManage(void)
{
	//ダメージ状態の無敵時間
	static int nDamageTime = 0;

	//状態
	switch (Stats)
	{
		//通常状態
	case STATS_MODE_NORMAL:
		break;
		//ダメージ処理
	case STATS_MODE_DAMAGE:
		
		//カウントダウン
		nDamageTime += 1;

		//ダメージカラー処理
		if (nDamageTime % 25)
		{
			SetCol(D3DXCOLOR(1.0f, 0.5f, 0.5f, 0.0f));
		}
		else
		{
			SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

		// ダメージカウントが一定になったら
		if (nDamageTime >= PLAYER_DAMAGE)
		{
			//カラーセット
			SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			//プレイヤー状態を通常状態に移行
			Stats = STATS_MODE_NORMAL;
			//ダメージ初期化
			nDamageTime = 0;
		}
		break;

	case STATS_MODE_DEATH:
		//サウンドクラス受け取り
		CSound *pSound = CManager::GetSound();
		//フェード取得	
		CFade *pFade = CManager::GetFade();

		//サウンドの再生
		pSound->Play(CSound::LABEL_SE_DIE);
		
		//エクスプロージョン生成
		CExplosion::Create(GetPos());

		//セレクト移動
		pFade->SetFade(GAME_MODE_SELECT);
		
		//終了処理
		CPlayer::Uninit();
		break;
	}
}

//=============================================================================
// 移動処理
//=============================================================================
void CPlayer::Move(void)
{
	// 位置取得
	D3DXVECTOR3 pos			= GetPos();
	// 移動量
	D3DXVECTOR3 Move		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// 範囲外処理用
	D3DXVECTOR3 MoveLimit	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// マウス取得
	CInihMouse *pMouse = CManager::GetMouse();

	//マウスの座標取得
	float fAngle = atan2f((-pos.x + pMouse->GetMousePos().x), (-pos.y + pMouse->GetMousePos().y));

	//位置情報の受け渡し
	Move.x = sinf(fAngle)*m_fSpeed;
	Move.y = cosf(fAngle)*m_fSpeed;

	//位置処理
	if (pos.x + 5 > pMouse->GetMousePos().x
		&&pos.x - 5 < pMouse->GetMousePos().x
		&&pos.y + 5 > pMouse->GetMousePos().y
		&&pos.y - 5 < pMouse->GetMousePos().y)
	{
	
	}
	else
	{
		//位置更新
		pos += Move;
	}

	//範囲外処理
	if (pos.x < 420 || pos.x > 1145)
	{
		MoveLimit.x = sinf(fAngle)*m_fSpeed;
	}
	if (pos.y < 25 || pos.y > 700)
	{
		MoveLimit.y = cosf(fAngle)*m_fSpeed;
	}

	//範囲外にいかないように
	pos -= MoveLimit;

	//座標更新
	SetPos(pos);
}


//=============================================================================
//プレイヤーの武器使用
//=============================================================================
void CPlayer::Weapon(void)
{
	// マウス取得
	CInihMouse *pMouse	= CManager::GetMouse();
	// 位置取得
	D3DXVECTOR3 pos		= GetPos();

	//左クリック処理
	if (pMouse->GetClick(CLICK_LEFT))
	{
		//攻撃までのカウント
		m_nAttackCount[CLICK_LEFT]++;

		//装備によって攻撃を変える
		switch (m_Weapon.Left)
		{
			//通常弾処理
		case WEAPONS_MODE_BUTTOL:
			if (m_nAttackCount[CLICK_LEFT] >= PLAYER_BULLET_TIME)
			{
				//バレット生成
				CBullet::Create(D3DXVECTOR3(pos.x - 20, pos.y, pos.z), D3DXVECTOR3(0, -20, 0.0f));
				//カウント初期化
				m_nAttackCount[CLICK_LEFT] = 0;
			}
			break;
			//レーザー処理
		case WEAPONS_MODE_LASER:
			if (m_nAttackCount[CLICK_LEFT] >= PLAYER_LASER_TIME)
			{
				//レーザー生成
				CLaser::Create(D3DXVECTOR3(pos.x - 20, pos.y, pos.z), D3DXVECTOR3(0, -17, 0.0f));
				//カウント初期化
				m_nAttackCount[CLICK_LEFT] = 0;
			}
			break;
			//ホーミング弾処理
		case WEAPONS_MODE_HOMING:
			if (m_nAttackCount[CLICK_LEFT] >= PLAYER_HOMING_TIME)
			{
				//ホーミング生成
				CHoming::Create(D3DXVECTOR3(pos.x - 20, pos.y, pos.z), D3DXVECTOR3(0, -17, 0.0f));
				//カウント初期化
				m_nAttackCount[CLICK_LEFT] = 0;
			}
			break;
		default:
			break;
		}
	}

	//右クリック処理
	if (pMouse->GetClick(CLICK_RIGHT))
	{
		//攻撃までのカウント
		m_nAttackCount[CLICK_RIGHT]++;

		switch (m_Weapon.Right)
		{
			//通常弾処理
		case WEAPONS_MODE_BUTTOL:
			if (m_nAttackCount[CLICK_RIGHT] >= PLAYER_BULLET_TIME)
			{
				//バレット生成
				CBullet::Create(D3DXVECTOR3(pos.x + 20, pos.y, pos.z), D3DXVECTOR3(0, -20, 0.0f));
				//カウント初期化
				m_nAttackCount[CLICK_RIGHT] = 0;
			}
			break;
			//レーザー処理
		case WEAPONS_MODE_LASER:
			if (m_nAttackCount[CLICK_RIGHT] >= PLAYER_LASER_TIME)
			{
				//レーザー生成
				CLaser::Create(D3DXVECTOR3(pos.x + 20, pos.y, pos.z), D3DXVECTOR3(0, -17, 0.0f));
				//カウント初期化
				m_nAttackCount[CLICK_RIGHT] = 0;
			}
			break;
			//ホーミング弾処理
		case WEAPONS_MODE_HOMING:
			if (m_nAttackCount[CLICK_RIGHT] >= PLAYER_HOMING_TIME)
			{
				//ホーミング生成
				CHoming::Create(D3DXVECTOR3(pos.x + 20, pos.y, pos.z), D3DXVECTOR3(0, -17, 0.0f));
				//カウント初期化
				m_nAttackCount[CLICK_RIGHT] = 0;
			}
			break;
		default:
			break;
		}
	}
}
