//=============================================================================
//
// エネミーバレット処理 [enemy bullet.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "enemy bullet.h"			
#include "manager.h"		
#include "renderer.h"		
#include "explosion.h"		
#include "player.h"
#include "sound.h"			
#include "effect.h"			
//=============================================================================
//マクロ定義
//=============================================================================
#define BULLET_SIZE 40		//バレットの大きさ
#define BULLET_LIFE 1000	//バレットの射程距離
//=============================================================================
//静的メンバー変数
//=============================================================================
TEXTURE_DATA CEnemyBullet::m_TextureData = { NULL,"data/TEXTURE/Bullet.png" };

//=============================================================================
//コンストラクタ
//=============================================================================
CEnemyBullet::CEnemyBullet()
{
	//タイプ処理
	CScene::SetObjType(CScene::OBJ_TYPE_BULLET);
}

//=============================================================================
// テクスチャロード
//=============================================================================
HRESULT CEnemyBullet::Load(void)
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
void CEnemyBullet::Unload(void)
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
CEnemyBullet * CEnemyBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	//メモリ確保
	CEnemyBullet *pEnemyBullet = NULL;
	pEnemyBullet = new CEnemyBullet;

	//NULLチェック
	if (pEnemyBullet != NULL)
	{
		//位置設定
		pEnemyBullet->SetPos(pos);
		//サイズ設定
		pEnemyBullet->SetSize(D3DXVECTOR3(BULLET_SIZE / 2.0f, BULLET_SIZE / 2.0f, 0.0f));
		//移動量設定
		pEnemyBullet->SetMove(move);
		//射程距離設定
		pEnemyBullet->SetLife(BULLET_LIFE);
		//初期化
		pEnemyBullet->Init();

	}
	return pEnemyBullet;
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CEnemyBullet::Init(void)
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
void CEnemyBullet::Move(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//移動量取得
	D3DXVECTOR3 move = GetMove();

	//位置更新
	pos += move;
	//ポリゴンの位置を渡す
	SetPos(pos);
}

//=============================================================================
// バレット処理
//=============================================================================
void CEnemyBullet::Bullet(CScene * pObj)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();

	if (pObj->GetObjType() == OBJ_TYPE_PLAYER)
	{
		D3DXVECTOR3 PlayerPos = ((CScene2d*)pObj)->GetPos();
		D3DXVECTOR3 PlayerSize = ((CScene2d*)pObj)->GetSize();
		//当たり判定
		if (PlayerPos.x + PlayerSize.x / 2 > pos.x
			&&PlayerPos.x - PlayerSize.x / 2 < pos.x
			&&PlayerPos.y + PlayerSize.y / 2 > pos.y
			&&PlayerPos.y - PlayerSize.y / 2 < pos.y)
		{
			//エネミーダメージ処理
			((CPlayer*)pObj)->Damage(1);
			//バレット終了処理
			Uninit();
			return;
		}
	}
}



