//=============================================================================
//
// ホーミング処理 [homing.cpp]
// Author : 吉田悠人
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "homing.h"			
#include "manager.h"		
#include "renderer.h"		
#include "explosion.h"		
#include "sound.h"			
#include "effect.h"			
#include "boss base.h"
#include "enemy base.h"
#include <typeinfo.h>
//=============================================================================
//マクロ定義
//=============================================================================
#define HOMING_SIZE		(40)	//ホーミングの大きさ
#define HOMING_LIFE		(50)	//ホーミングの射程距離
#define HOMING_ATTACK	(1)		//ホーミングの攻撃力
#define HOMING_RANGE	(780)	//ホーミング範囲
#define HOMING_SPEED	(10.0f)	//ホーミングスピード

//=============================================================================
//静的メンバー変数
//=============================================================================
TEXTURE_DATA CHoming::m_TextureData = { NULL,"data/TEXTURE/Bullet.png" };

//=============================================================================
//コンストラクタ
//=============================================================================
CHoming::CHoming()
{
	//タイプ処理
	CScene::SetObjType(CScene::OBJ_TYPE_BULLET);
	m_nRange = HOMING_RANGE;
}

//=============================================================================
// テクスチャロード
//=============================================================================
HRESULT CHoming::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, m_TextureData.m_cFileName, &m_TextureData.m_Texture);
	return S_OK;
}

//=============================================================================
// テクスチャアンロード
//=============================================================================
void CHoming::Unload(void)
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
CHoming * CHoming::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	//メモリ確保
	CHoming *pHoming=NULL;
	pHoming = new CHoming;
	
	//NULLチェック
	if (pHoming != NULL)
	{
		//位置設定
		pHoming->SetPos(pos);
		//サイズ設定
		pHoming->SetSize(D3DXVECTOR3(HOMING_SIZE / 2.0f, HOMING_SIZE / 2.0f, 0.0f));
		//移動量設定
		pHoming->SetMove(move);
		//射程距離設定
		pHoming->SetLife(HOMING_LIFE);
		//初期化
		pHoming->Init();
	}

	return pHoming;
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CHoming::Init(void)
{
	//サウンド取得
	CSound *pSound = CManager::GetSound();
	//サウンド
	pSound->Play(CSound::LABEL_SE_LASER);
	//初期化処理
	CBulletBase::Init();
	//テクスチャの設定
	BindTexture(m_TextureData.m_Texture);

	return S_OK;
}

//=============================================================================
// 移動処理
//=============================================================================
void CHoming::Move(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//移動量取得
	D3DXVECTOR3 move = GetMove();
	//エフェクト生成
	CEffect::Create(pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(HOMING_SIZE / 2.0f, HOMING_SIZE / 2.0f, 0.0f), CEffect::EFFECT_TYPE_BULLET);
	//位置更新
	pos += move;
	//ポリゴンの位置を渡す
	SetPos(pos);
}

//=============================================================================
// バレット処理
//=============================================================================
void CHoming::Bullet(CScene * pObj)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//エネミーの当たり判定
	if (pObj->GetObjType() == OBJ_TYPE_ENEMY)
	{
		D3DXVECTOR3 EnemeyPos = ((CScene2d*)pObj)->GetPos();
		D3DXVECTOR3 EnemeySize = ((CScene2d*)pObj)->GetSize();

		//ターゲット捕捉
		LockOn(pos, EnemeyPos);

		//当たり判定
		if (EnemeyPos.x + EnemeySize.x / 2 > pos.x
			&&EnemeyPos.x - EnemeySize.x / 2 < pos.x
			&&EnemeyPos.y + EnemeySize.y / 2 > pos.y
			&&EnemeyPos.y - EnemeySize.y / 2 < pos.y)
		{
			//エクスプロージョン生成
			CExplosion::Create(pos);
			//エネミーダメージ処理
			((CEnemyBase*)pObj)->Damage(HOMING_ATTACK);
			//終了処理
			Uninit();
			return;
		}
	}
	//ボスの当たり判定処理
	if (pObj->GetObjType() == OBJ_TYPE_BOSS)
	{
		D3DXVECTOR3 BossPos = ((CScene2d*)pObj)->GetPos();
		D3DXVECTOR3 BossSize = ((CScene2d*)pObj)->GetSize();
		//当たり判定
		if (BossPos.x + BossSize.x / 2 > pos.x
			&&BossPos.x - BossSize.x / 2 < pos.x
			&&BossPos.y + BossSize.y / 2 > pos.y
			&&BossPos.y - BossSize.y / 2 < pos.y)
		{
			//エクスプロージョン生成
			CExplosion::Create(pos);
			//エネミーダメージ処理
			((CBossBase*)pObj)->Damage(HOMING_ATTACK);
			//バレット終了処理
			Uninit();
			return;
		}

	}

}

//=============================================================================
// ターゲット取得関数
//=============================================================================
void CHoming::LockOn(D3DXVECTOR3 pos, D3DXVECTOR3 EnemyPos)
{
	//ターゲットの距離を取得変数
	float	fDistance = 0.0f;
	int		nDistance = 0;

	//ターゲットの距離を取得
	fDistance = (pos.x - EnemyPos.x)*(pos.x - EnemyPos.x) + (pos.y - EnemyPos.y)*(pos.y - EnemyPos.y);
	
	//int型に収納
	nDistance = (int)(sqrt(fDistance));

	//ホーミング範囲に一番近いターゲット収納
	if (m_nRange>nDistance)
	{
		m_nRange = nDistance;
		TargetMove(pos, EnemyPos);
	}
}

//=============================================================================
// ターゲット方向の移動量取得関数
//=============================================================================
void CHoming::TargetMove(D3DXVECTOR3 pos, D3DXVECTOR3 EnemyPos)
{
	//移動量取得
	D3DXVECTOR3 move = GetMove();
	//ターゲットの方向取得変数
	float fAngle = 0.0f;

	fAngle = atan2f((-pos.x + EnemyPos.x), (-pos.y + EnemyPos.y));
	//移動量取得
	move.x = sinf(fAngle)*HOMING_SPEED;
	move.y = cosf(fAngle)*HOMING_SPEED;
	
	//移動量セット
	SetMove(move);

}
