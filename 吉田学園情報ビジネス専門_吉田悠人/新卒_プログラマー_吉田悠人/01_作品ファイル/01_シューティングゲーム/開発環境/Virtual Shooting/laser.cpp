//=============================================================================
//
// レーザー処理 [laser.cpp]
// Author : 吉田悠人
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "laser.h"			
#include "manager.h"		
#include "renderer.h"		
#include "explosion.h"		
#include "sound.h"			
#include "effect.h"			
#include "enemy base.h"
#include "boss base.h"
#include <typeinfo.h>
//=============================================================================
//マクロ定義
//=============================================================================
#define LASER_X_SIZE	(10)	//レーザーの横大きさ
#define LASER_Y_SIZE	(100)	//レーザーの縦大きさ
#define LASER_LIFE		(1000)	//レーザーの射程距離
#define LASER_ATTACK	(1)		//レーザーの攻撃力
//=============================================================================
//静的メンバー変数
//=============================================================================
TEXTURE_DATA CLaser::m_TextureData = { NULL,"data/TEXTURE/Laser.png" };

//=============================================================================
//コンストラクタ
//=============================================================================
CLaser::CLaser()
{
	memset(m_bHit,false,sizeof(m_bHit));
	m_nHitCount = 0;
	//タイプ処理
	CScene::SetObjType(CScene::OBJ_TYPE_BULLET);
}


//=============================================================================
// テクスチャロード
//=============================================================================
HRESULT CLaser::Load(void)
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
void CLaser::Unload(void)
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
CLaser * CLaser::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	//メモリ確保
	CLaser *pLaser = NULL;
	pLaser = new CLaser;

	//NULLチェック
	if (pLaser != NULL)
	{
		//位置設定
		pLaser->SetPos(pos);
		//サイズ設定
		pLaser->SetSize(D3DXVECTOR3(LASER_X_SIZE / 2.0f, LASER_Y_SIZE / 2.0f, 0.0f));
		//移動量設定
		pLaser->SetMove(move);
		//射程距離設定
		pLaser->SetLife(LASER_LIFE);
		//初期化
		pLaser->Init();
	}

	return pLaser;
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CLaser::Init(void)
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
// 更新処理
//=============================================================================
void CLaser::Update(void)
{
	//初期化
	m_nHitCount = 0;
	CBulletBase::Update();
}


//=============================================================================
// 移動処理
//=============================================================================
void CLaser::Move(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//移動量取得
	D3DXVECTOR3 move = GetMove();
	//エフェクト生成
	CEffect::Create(pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(LASER_X_SIZE / 2.0f, LASER_Y_SIZE / 2.0f, 0.0f), CEffect::EFFECT_TYPE_LASER);
	//位置更新
	pos += move;
	//ポリゴンの位置を渡す
	SetPos(pos);
}

//=============================================================================
// バレット処理
//=============================================================================
void CLaser::Bullet(CScene * pObj)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	if (pObj->GetObjType() == OBJ_TYPE_ENEMY)
	{
		D3DXVECTOR3 EnemeyPos = ((CScene2d*)pObj)->GetPos();
		D3DXVECTOR3 EnemeySize = ((CScene2d*)pObj)->GetSize();
		//当たり判定
		if (EnemeyPos.x + EnemeySize.x / 2 > pos.x
			&&EnemeyPos.x - EnemeySize.x / 2 < pos.x
			&&EnemeyPos.y + EnemeySize.y / 2 > pos.y
			&&EnemeyPos.y - EnemeySize.y / 2 < pos.y
			&&m_bHit[m_nHitCount] != true)
		{
			//エクスプロージョン生成
			CExplosion::Create(pos);
			//エネミーダメージ処理
			((CEnemyBase*)pObj)->Damage(LASER_ATTACK);
			//当たった状態
			m_bHit[m_nHitCount] = true;
			return;
		}
		//エネミーカウント
		m_nHitCount++;
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
			&&BossPos.y - BossSize.y / 2 < pos.y
			&&m_bHit[m_nHitCount] != true)
		{
			//エクスプロージョン生成
			CExplosion::Create(pos);
			//エネミーダメージ処理
			((CBossBase*)pObj)->Damage(LASER_ATTACK);
			//当たった状態
			m_bHit[m_nHitCount] = true;
			return;
		}
		//エネミーカウント
		m_nHitCount++;

	}


}