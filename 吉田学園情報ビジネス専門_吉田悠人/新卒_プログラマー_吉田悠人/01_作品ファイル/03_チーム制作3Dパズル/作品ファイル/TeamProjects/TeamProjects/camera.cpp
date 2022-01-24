//=============================================================================
//
//	カメラ処理[camera.cpp]
//	Author:吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "camera.h"
#include "input.h"
#include "inputmouse.h"
#include "inputkeyboard.h"
#include "main.h"
#include "manager.h"
#include "object.h"
#include "renderer.h"
#include "sound.h"
//=============================================================================
//マクロ定義
//=============================================================================
#define PLAYER_DISTANCE (200.0f)	//カメラと注視点の距離

//=============================================================================
//コンストラクタ
//=============================================================================
CCamera::CCamera()
{
	ZeroMemory(&m_mtxProjection,sizeof(m_mtxProjection));//プロジェクションマトリックス
	ZeroMemory(&m_mtxView, sizeof(m_mtxView));//ビューマトリックス
}

//=============================================================================
//デストラクタ
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CCamera::Init(D3DXVECTOR3 posR)
{
	//カメラの初期(位置・注意点・上方向)設定
	m_posV = D3DXVECTOR3(posR);
	m_posR = m_posV + D3DXVECTOR3(0.0f, 600.0f, 750.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//カメラの向き設定
	m_rot = D3DXVECTOR3(60.0f, 0.0f, 0.0f);
	//カメラの位置
	m_pos = m_posV;

	//視点-注意点の距離の計算
	m_fDistance = (float)sqrt(
		pow(m_posV.x - m_posR.x, 2.0f) + pow(m_posV.z - m_posR.z, 2.0f));

	//マウスの感度の設定
	m_nSensitivity = CAMERA_SENSITIVITY;
	//カメラのスピード設定
	m_fSpeed = CAMERA_SPEED;

	//マネージャーにカメラ情報を保存
	CManager::BindCamera(this);

	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CCamera::Uninit(void)
{

}

//=============================================================================
//更新処理
//=============================================================================
void CCamera::Update(void)
{
	Move();

	//移動の計算
	D3DXVECTOR3 RotateCenter =m_pos + D3DXVECTOR3(sinf(D3DXToRadian(m_rot.y - 90)),
											 50,
											 cosf(D3DXToRadian(-m_rot.y - 90)));
	
	//カメラの移動処理
	m_posV = RotateCenter +
		D3DXVECTOR3(sinf(D3DXToRadian(-m_rot.y)) * cosf(D3DXToRadian(m_rot.x))*m_fDistance,
			sinf(D3DXToRadian(m_rot.x))*m_fDistance,
			cosf(D3DXToRadian(-m_rot.y)) * cosf(D3DXToRadian(m_rot.x))*m_fDistance);

	//注意点の移動処理
	m_posR = RotateCenter;

}

//=============================================================================
//カメラによる描画
//=============================================================================
void CCamera::SetCamera(void)
{		
	//デバイスへのポインタ
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice(); 
  
    //ビューマトリックスの初期化
    D3DXMatrixIdentity(&m_mtxView);
    //ビューマトリックスの作成
    D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);
    //ビューマトリックスの設定
    pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
    //プロジェクションマトリックスの初期化
    D3DXMatrixIdentity(&m_mtxProjection);
    //プロジェクションマトリックスの作成
    D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, CAMERA_VIEW_RANGE);
    //プロジェクションマトリックスの設定
    pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//=============================================================================
// 注視点ゲッター
//=============================================================================
D3DXVECTOR3 CCamera::GetPosR(void)
{
    //注視点を距離分の長さに補正して出力
    D3DXVECTOR3 vec;
    D3DXVec3Normalize(&vec, &(m_posR - m_posV));
    vec = vec * m_fDistance + m_posV;
    return vec;
}

//=============================================================================
// 移動処理関数
//=============================================================================
void CCamera::Move(void)
{
#ifdef _DEBUG

	//キーボード入力の取得
	CInputKeyboard* pInput = (CInputKeyboard*)CManager::GetInputKey();

	//マウス入力取得
	CInputMouse *pInputMouse = (CInputMouse*)CManager::GetInputMou();
	//移動量
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//視点を動かす
	if (pInputMouse->GetClick(1))
	{
		//向き
		m_rot.x += (pInputMouse->GetMousePos().lY * (float)(0.01f * m_nSensitivity));
		m_rot.y -= (pInputMouse->GetMousePos().lX * (float)(0.01f * m_nSensitivity));

		//移動
		if (pInput->GetKeyPress(DIK_UP))
		{
			//単位ベクトルに取得
			D3DXVec3Normalize(&move, &(m_posR - m_posV));
		}
		if (pInput->GetKeyPress(DIK_DOWN))
		{
			//単位ベクトルに取得
			D3DXVec3Normalize(&move, &(m_posR - m_posV));
			move *= -1;
		}
		if (pInput->GetKeyPress(DIK_LEFT))
		{
			//移動方向指定w
			m_moveRot = 0.0f;
			//移動時の向き設定
			m_moveRot += m_rot.y;
			//移動量処理
			move += D3DXVECTOR3(cosf(D3DXToRadian(m_moveRot)), 0, sinf(D3DXToRadian(m_moveRot)));
		}
		if (pInput->GetKeyPress(DIK_RIGHT))
		{
			//移動方向指定
			m_moveRot = 180.0f;
			//移動時の向き設定
			m_moveRot += m_rot.y;
			//移動量処理
			move += D3DXVECTOR3(cosf(D3DXToRadian(m_moveRot)), 0, sinf(D3DXToRadian(m_moveRot)));
		}
		//速度処理
		move *= m_fSpeed;
		//移動処理
		m_pos += move;
	}


	//向きの限界値処理
	if ((m_rot.x) >= 89
		|| (m_rot.x) <= -89)
	{
		m_rot.x -= (pInputMouse->GetMousePos().lY * (float)(0.01f * m_nSensitivity));
	}
	if (m_rot.y<0)
	{
		m_rot.y += 360;
	}
	if (m_rot.y > 360)
	{
		m_rot.y -= 360;
	}

#endif

}

//=============================================================================
// タイトルでの動き処理関数
//=============================================================================
void CCamera::TitleMove(void)
{
	//カメラのY軸を少しずつ動かす
	m_rot.y+=0.2f;
}

//=============================================================================
// カメラ位置設定関数
//=============================================================================
void CCamera::SetPos(D3DXVECTOR3 pos)
{
	//カメラの初期(位置・注意点・上方向)設定
	m_posV = D3DXVECTOR3(pos);
	m_posR = m_posV + D3DXVECTOR3(0.0f, 600.0f, 750.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//カメラの位置
	m_pos = m_posV;

	//視点-注意点の距離の計算
	m_fDistance = (float)sqrt(
		pow(m_posV.x - m_posR.x, 2.0f) + pow(m_posV.z - m_posR.z, 2.0f));


}

