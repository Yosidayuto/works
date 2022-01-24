//=============================================================================
//
// バレット処理 [bullet.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "bullet.h"			
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
#define BULLET_SIZE		(20)	//バレットの大きさ
#define BULLET_LIFE		(1000)	//バレットの射程距離
#define BULLET_DAMAGE	(1)		//バレットのダメージ	
//=============================================================================
//静的メンバー変数
//=============================================================================
TEXTURE_DATA CBullet::m_TextureData = { NULL,"data/TEXTURE/Bullet.png" };

//=============================================================================
//コンストラクタ
//=============================================================================
CBullet::CBullet()
{
	//タイプ処理
	CScene::SetObjType(CScene::OBJ_TYPE_BULLET);
}

//=============================================================================
// テクスチャロード
//=============================================================================
HRESULT CBullet::Load(void)
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
void CBullet::Unload(void)
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
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	//メモリ確保
	CBullet *pBullet = NULL;
	pBullet = new CBullet;

	//NULLチェック
	if (pBullet != NULL)
	{
		//位置設定
		pBullet->SetPos(pos);
		//サイズ設定
		pBullet->SetSize(D3DXVECTOR3(BULLET_SIZE / 2.0f, BULLET_SIZE / 2.0f, 0.0f));
		//移動量設定
		pBullet->SetMove(move);
		//射程距離設定
		pBullet->SetLife(BULLET_LIFE);
		//初期化
		pBullet->Init();

		return pBullet;
	}
	return NULL;
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CBullet::Init(void)
{
	//サウンド取得
	CSound *pSound = CManager::GetSound();	
	//サウンド
	pSound->Play(CSound::LABEL_SE_SHOTS);	
	//初期化処理
	CBulletBase::Init();
	//テクスチャの設定
	BindTexture(m_TextureData.m_Texture);

	return S_OK;
}

//=============================================================================
// 移動処理
//=============================================================================
void CBullet::Move(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//移動量取得
	D3DXVECTOR3 move = GetMove();
	//エフェクト生成
	CEffect::Create(pos, D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),D3DXVECTOR3(BULLET_SIZE/2.0f, BULLET_SIZE/2.0f,0.0f), CEffect::EFFECT_TYPE_BULLET);
	//位置更新
	pos += move;
	//ポリゴンの位置を渡す
	SetPos(pos);
}

//=============================================================================
// バレット処理
//=============================================================================
void CBullet::Bullet(CScene * pObj)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();

	//エネミーの当たり判定処理
	if (pObj->GetObjType() == OBJ_TYPE_ENEMY)
	{
		D3DXVECTOR3 EnemeyPos = ((CScene2d*)pObj)->GetPos();
		D3DXVECTOR3 EnemeySize = ((CScene2d*)pObj)->GetSize();
		//当たり判定
		if (EnemeyPos.x + EnemeySize.x / 2 > pos.x
			&&EnemeyPos.x - EnemeySize.x / 2 < pos.x
			&&EnemeyPos.y + EnemeySize.y / 2 > pos.y
			&&EnemeyPos.y - EnemeySize.y / 2 < pos.y)
		{
			//エクスプロージョン生成
			CExplosion::Create(pos);
			//エネミーダメージ処理
			((CEnemyBase*)pObj)->Damage(BULLET_DAMAGE);
			//バレット終了処理
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
			((CBossBase*)pObj)->Damage(BULLET_DAMAGE);
			//バレット終了処理
			Uninit();
			return;
		}

	}
}



