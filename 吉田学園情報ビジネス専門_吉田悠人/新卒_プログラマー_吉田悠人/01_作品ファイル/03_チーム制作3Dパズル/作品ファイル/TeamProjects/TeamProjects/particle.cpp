//=============================================================================
//
// パーティクル処理 [particle.cpp]
// Author : 小熊 朗
// 更新日 : 2022/03/04
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "particle.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define VECTORPOS_INIT (D3DXVECTOR3(0.0f, 0.0f, 0.0f))		//初期位置
#define ACTUALSLOW (100)									//パーティクルの速度
#define PLAYER_DIRECTIONPOS (0.1f)							//プレイヤーの向く位置
#define ANGLE_RADIAN (D3DXToRadian((float)(rand() % 360)))	//ラジアンの角度
#define ALPHA_VALUE_DECREASE (0.0001f)						//アルファ値の減少値

//=============================================================================
//静的メンバ変数宣言
//=============================================================================
CModel::MODELDATA	CParticle::m_modeldata = {};
//=============================================================================
//コンストラクタ
//=============================================================================
CParticle::CParticle()
{
	m_Playerpos = VECTORPOS_INIT;
	m_Childpos = VECTORPOS_INIT;
	m_move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//=============================================================================
//デストラクタ
//=============================================================================
CParticle::~CParticle()
{

}

//=============================================================================
//クリエイト関数
//=============================================================================
CParticle* CParticle::Cretae(D3DXVECTOR3 pos, D3DXVECTOR3 distPos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR col, PARTICLE_TYPE type)
{
	CParticle *pParticle = NULL;	//メモリ確保

	if (pParticle == NULL)
	{
		pParticle = new CParticle;
		pParticle->m_Playerpos = distPos;
		pParticle->m_Childpos = pos;
		if (type == PARTICLE_TYPE_1)
		{
			pParticle->Vacuum(size, move, col);
		}
		if (type == PARTICLE_TYPE_2)
		{
			pParticle->Sphere(pos, size, move, col);
		}
		pParticle->Init();
	}
	return pParticle;
}

//=============================================================================
//球体パーティクルの関数
//=============================================================================
void CParticle::Sphere(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR col)
{
	//リソース確保
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(m_nTexture);

	//パーティクルの移動角度
	D3DXVECTOR3 actualMove = VECTORPOS_INIT;
	D3DXVECTOR3 CretaePos = VECTORPOS_INIT;

	//パーティクル分繰り返す
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		if (rand() % 2 == 0)
		{
			//角度計算
			float fAngle = ANGLE_RADIAN;
			//慣性角度
			actualMove.x = ((float)cos(nCnt)*(float)cos(fAngle))*move.x;
			actualMove.y = ((float)sin(fAngle))*move.y;
			actualMove.z = ((float)sin(nCnt)*(float)cos(fAngle))*move.z;
			//真上
			//発生位置
			CretaePos.x = ((float)cos(fAngle) * (float)cos(nCnt)) + pos.x;
			CretaePos.y = ((float)sin(fAngle)) + pos.y*-1;//正の数に直す
			CretaePos.z = ((float)sin(fAngle) * (float)cos(nCnt)) + pos.z;
		}
		SetPosition(CretaePos);	//位置情報を格納
		SetSize(size);			//大きさを格納
		SetColor(col);			//色情報を格納
		m_move = actualMove;//移動量を代入
		BindTexture(Texture);//テクスチャ情報を格納
	}
}

//=============================================================================
//吸引演出の関数
//=============================================================================
void CParticle::Vacuum(D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXCOLOR col)
{
	//リソース確保
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(m_nTexture);

	D3DXVECTOR3 CretaePos = VECTORPOS_INIT;
	// 距離の計算
	float fDitanse = sqrtf(powf(m_Playerpos.x - m_Childpos.x, 2) +
						   powf(m_Playerpos.y - m_Childpos.y, 2) +
						   powf(m_Playerpos.z - m_Childpos.z, 2));
	//角度
	float fAngle = ANGLE_RADIAN;
	//半径
	float fCircleRadius = 25.0f;
	//プレイヤーとチャイルドの距離
	D3DXVECTOR3 CreatedsitPos = m_Playerpos - m_Childpos;
	D3DXVec3Normalize(&CreatedsitPos, &CreatedsitPos);

	//プレイヤーの向く位置が変わった場合
	if (CreatedsitPos.x > PLAYER_DIRECTIONPOS || CreatedsitPos.x < -PLAYER_DIRECTIONPOS)
	{
		CretaePos = m_Childpos + D3DXVECTOR3(0.0f, fCircleRadius * sinf(fAngle), fCircleRadius * cosf(fAngle));
	}
	if (CreatedsitPos.y > PLAYER_DIRECTIONPOS ||CreatedsitPos.y < -PLAYER_DIRECTIONPOS)
	{
		CretaePos = m_Childpos + D3DXVECTOR3(fCircleRadius * sinf(fAngle), 0.0f, fCircleRadius * cosf(fAngle));
	}
	if (CreatedsitPos.z > PLAYER_DIRECTIONPOS || CreatedsitPos.z < -PLAYER_DIRECTIONPOS)
	{
		CretaePos = m_Childpos + D3DXVECTOR3(fCircleRadius * sinf(fAngle), fCircleRadius * cosf(fAngle), 0.0f);
	}

	//移動量
	D3DXVECTOR3 actualMove = (CretaePos / ACTUALSLOW - m_Playerpos / ACTUALSLOW) * -move.x;

	SetPosition(CretaePos);	//位置情報を格納
	SetSize(size);			//大きさを格納
	SetColor(col);			//色情報を格納
	m_move = actualMove ;//移動量を代入
	BindTexture(Texture);//テクスチャ情報を格納
}

//=============================================================================
//初期化関数
//=============================================================================
HRESULT CParticle::Init()
{

	//ビルボードの初期化
	CBillboard::Init();

	return S_OK;
}

//=============================================================================
//更新関数
//=============================================================================
void CParticle::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();	//位置情報を取得
	D3DXVECTOR3 size = GetSize();		//サイズ情報を取得
	D3DXCOLOR m_col = GetColor();		//カラー情報を取得
	m_col.a -= 0.01f;					//アルファ値を減らす

	m_col.a -= ALPHA_VALUE_DECREASE;	//アルファ値を減らす

	pos += m_move;		//移動量をプラスする

	//情報を格納（反映）
	SetPosition(pos);		//位置
	SetSize(size);			//大きさ
	SetColor(m_col);		//色

	CBillboard::Update();	
	//終了処理
	if (m_col.a < 0)
	{
		Uninit();
	}
}

//=============================================================================
//終了関数
//=============================================================================
void CParticle::Uninit(void)
{
	CBillboard::Uninit();
}

//=============================================================================
//描画関数
//=============================================================================
void CParticle::Draw(void)
{
	CBillboard::Draw();
}

