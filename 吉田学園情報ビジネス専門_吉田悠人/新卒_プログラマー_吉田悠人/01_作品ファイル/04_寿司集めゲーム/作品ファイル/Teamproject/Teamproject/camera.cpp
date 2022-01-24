//===================================================================
//
//	カメラ処理 [camera.cpp]
//	Author:林川紗梨夏
//
//===================================================================

//======================================================
//インクルードファイル
//======================================================
#include "camera.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "mouse.h"
#include "keyboard.h"
#include "scene.h"
#include "player.h"

//======================================================
// マクロ定義
//======================================================
#define SCRIPT_PASS				("Data/TEXT/camera.txt")
#define CAMERA_INTERPOLATION	(0.2f)					//カメラ補間スピード
#define MAX_SCREEN				(4)						//最大画面分割数

#ifdef _DEBUG
#define CAMERA_SENSITIVITY (5)	// マウス感度
#define CAMERA_SPEED (10.0f)	// カメラスピード
#define CAMERA_ZOOM	(50.0f)		// カメラズーム量
#endif
//======================================================
// 静的メンバ変数の初期化
//======================================================
D3DXVECTOR2 CCamera::m_offset[MAX_PLAYER] =
{
	D3DXVECTOR2(0.0f, 0.0f),
	D3DXVECTOR2(SCREEN_WIDTH / 2.0f, 0.0f),
	D3DXVECTOR2(0.0f, SCREEN_HEIGHT / 2.0f),
	D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f),
};

//======================================================
//コンストラクタ
//======================================================
CCamera::CCamera()
{
	for (int nCoutn = 0; nCoutn < MAX_PLAYER; nCoutn++)
	{
		m_posV[nCoutn] = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
		m_posR[nCoutn] = m_posV[nCoutn] + D3DXVECTOR3(0.0f, 0.0f, 500.0f);
		m_pos[nCoutn] = m_posV[nCoutn];
	}
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(45.0f, 180.0f, 0.0f);
	m_fDistance = 100.0f;
	m_bIsFollowPlayer = false;
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fInterpolation = 0.0f;

#ifdef _DEBUG
	m_fMoveRot = 0.0f;
	m_bDebug = false;
#endif

}
//======================================================
//デストラクタ
//======================================================
CCamera::~CCamera()
{
}

//======================================================
//初期化処理
//======================================================
HRESULT CCamera::Init(void)
{
	for (int nCoutn = 0; nCoutn < MAX_PLAYER; nCoutn++)
	{
		//カメラの初期(位置・注意点・上方向)設定
		m_posV[nCoutn] = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
		m_posR[nCoutn] = m_posV[nCoutn] + D3DXVECTOR3(0.0f, 0.0f, 500.0f);

	}
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//カメラの向き設定
	m_rot = D3DXVECTOR3(89.0f, 180.0f, 0.0f);
	//マネージャーにカメラ情報を保存
	CManager::BindCamera(this);
	return S_OK;
}

//======================================================
//終了処理
//======================================================
void CCamera::Uninit(void)
{

}

//======================================================
//更新処理
//======================================================
void CCamera::Update(void)
{

	for (int nCoutn = 0; nCoutn < MAX_PLAYER; nCoutn++)
	{
		//移動の計算
		D3DXVECTOR3 RotateCenter = m_pos[nCoutn] + D3DXVECTOR3(sinf(D3DXToRadian(m_rot.y - 90)),
			50,
			cosf(D3DXToRadian(-m_rot.y - 90)));

		//カメラの移動処理
		m_posV[nCoutn] = RotateCenter +
			D3DXVECTOR3(sinf(D3DXToRadian(-m_rot.y)) * cosf(D3DXToRadian(m_rot.x)) * m_fDistance,
				sinf(D3DXToRadian(m_rot.x)) * m_fDistance,
				cosf(D3DXToRadian(-m_rot.y)) * cosf(D3DXToRadian(m_rot.x)) * m_fDistance);

		//注意点の移動処理
		m_posR[nCoutn] = RotateCenter;
	}
}

//======================================================
// カメラによる描画
//======================================================
void CCamera::SetCamera(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);
	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV[0], &m_posR[0], &m_vecU);
	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);
	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, CAMERA_VIEW_RANGE*2);
	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//======================================================
// カメラによる分割描画
//======================================================
void CCamera::SetCamera(int nCamera)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	
	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);
	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV[nCamera], &m_posR[nCamera], &m_vecU);
	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);
	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, CAMERA_VIEW_RANGE);
	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

}

//======================================================
// ビューポート設定
//======================================================
bool CCamera::SetUpViewport(int screen_id)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ビューポートパラメータ
	D3DVIEWPORT9 view_port;

	//画面のサイズ
	if (MAX_SCREEN >= 2)
	{
		m_WidowSize.Width = SCREEN_WIDTH / 2.0f;
	}

	if (MAX_SCREEN >= 3)
	{
		m_WidowSize.Height = SCREEN_HEIGHT / 2.0f;
	}


	// ビューポートの左上座標
	view_port.X = (DWORD)m_offset[screen_id].x;
	view_port.Y = (DWORD)m_offset[screen_id].y;

	// ビューポートの幅
	view_port.Width = (DWORD)m_WidowSize.Width;
	// ビューポートの高さ
	view_port.Height = (DWORD)m_WidowSize.Height;
	// ビューポート深度設定
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 1.0f;

	// ビューポート設定
	if (FAILED(pDevice->SetViewport(&view_port)))
	{
		return false;
	}

	return true;
}

//======================================================
// ビューポート(単体)設定
//======================================================
bool CCamera::SetUpViewport(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ビューポートパラメータ
	D3DVIEWPORT9 view_port;

	// 画面のサイズ
	m_WidowSize.Width = SCREEN_WIDTH;
	m_WidowSize.Height = SCREEN_HEIGHT;
	
	// ビューポートの左上座標
	view_port.X = (DWORD)0.0f;
	view_port.Y = (DWORD)0.0f;

	// ビューポートの幅
	view_port.Width = (DWORD)m_WidowSize.Width;
	// ビューポートの高さ
	view_port.Height = (DWORD)m_WidowSize.Height;
	// ビューポート深度設定
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 1.0f;

	// ビューポート設定
	if (FAILED(pDevice->SetViewport(&view_port)))
	{
		return false;
	}

	return true;
}

//======================================================
//向き取得
//======================================================
D3DXVECTOR3 CCamera::GetRot(void)
{
	return m_rot;
}

//======================================================
//向きのセット
//======================================================
void CCamera::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//======================================================
// 位置セッター
//======================================================
void CCamera::SetPos(int nCamera, D3DXVECTOR3 pos)
{
	m_pos[nCamera] = pos;
}

//======================================================
//カメラ情報のセット
//======================================================
void CCamera::SetCameraView(D3DXVECTOR3 posV, D3DXVECTOR3 posR, float fInterpolation)
{
	m_posVDest = posV;
	m_posRDest = posR;
	if (fInterpolation > 1.0f)
	{
		m_fInterpolation = 1.0f;//これ以上大きくなると変になるので制御
	}
	else
	{
		m_fInterpolation = fInterpolation;
	}
}

#ifdef _DEBUG
//=============================================================================
// 移動処理関数
//=============================================================================
void CCamera::Move(void)
{
	////キーボード入力の取得
	//CKeyboard* pInput = (CKeyboard*)CManager::GetInputKeyboard();
	////マウス入力取得
	//CMouse *pInputMouse = (CMouse*)CManager::GetInputMouse();
	////移動量
	//D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	////注視点までの距離
	//D3DXVECTOR3 distance = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////視点を動かす
	//if (m_bDebug == true)
	//{
	//	//向き
	//	m_rot.x += (pInputMouse->GetMouseMove().lY * (float)(0.01f * CAMERA_SENSITIVITY));
	//	m_rot.y -= (pInputMouse->GetMouseMove().lX * (float)(0.01f * CAMERA_SENSITIVITY));
	//	
	//	//注視点の距離を変える
	//	if (pInputMouse->GetMouseMove().lZ != 0)
	//	{
	//		//単位ベクトルに取得
	//		D3DXVec3Normalize(&distance, &(m_posR - m_posV));

	//		//ズームアウトの場合
	//		if (pInputMouse->GetMouseMove().lZ<0)
	//		{
	//			distance *= -1;
	//		}
	//	}

	//	//移動
	//	if (pInput->GetKeyPress(DIK_W))
	//	{
	//		//移動方向指定
	//		m_fMoveRot = -90.0f;
	//		//移動時の向き設定
	//		m_fMoveRot += m_rot.y;
	//		//移動量処理
	//		move += D3DXVECTOR3(cosf(D3DXToRadian(m_fMoveRot)), 0, sinf(D3DXToRadian(m_fMoveRot)));
	//	}

	//	if (pInput->GetKeyPress(DIK_S))
	//	{
	//		//移動方向指定
	//		m_fMoveRot = 90.0f;
	//		//移動時の向き設定
	//		m_fMoveRot += m_rot.y;
	//		//移動量処理
	//		move += D3DXVECTOR3(cosf(D3DXToRadian(m_fMoveRot)), 0, sinf(D3DXToRadian(m_fMoveRot)));
	//	}

	//	if (pInput->GetKeyPress(DIK_A))
	//	{
	//		//移動方向指定
	//		m_fMoveRot = 0.0f;
	//		//移動時の向き設定
	//		m_fMoveRot += m_rot.y;
	//		//移動量処理
	//		move += D3DXVECTOR3(cosf(D3DXToRadian(m_fMoveRot)), 0, sinf(D3DXToRadian(m_fMoveRot)));
	//	}

	//	if (pInput->GetKeyPress(DIK_D))
	//	{
	//		//移動方向指定
	//		m_fMoveRot = 180.0f;
	//		//移動時の向き設定
	//		m_fMoveRot += m_rot.y;
	//		//移動量処理
	//		move += D3DXVECTOR3(cosf(D3DXToRadian(m_fMoveRot)), 0, sinf(D3DXToRadian(m_fMoveRot)));
	//	}

	//	//速度処理
	//	move *= CAMERA_SPEED;
	//	//ズームの感度
	//	distance *= CAMERA_ZOOM;

	//	//移動処理
	//	m_pos += move;
	//	//ズーム処理
	//	m_pos += distance;

	//}

	////向きの限界値処理
	//if ((m_rot.x) >= 89
	//	|| (m_rot.x) <= -89)
	//{
	//	m_rot.x -= (pInputMouse->GetMouseMove().lY * (float)(0.01f * CAMERA_SENSITIVITY));
	//}
	//if (m_rot.y<0)
	//{
	//	m_rot.y += 360;
	//}
	//if (m_rot.y > 360)
	//{
	//	m_rot.y -= 360;
	//}

}
#endif
