//=============================================================================
//
//	カメラ処理[camera.h]
//	Author:吉田悠人
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define CAMERA_VIEW_RANGE (1000000.0f)
#define CAMERA_SENSITIVITY (3)		//初期マウス感度
#define CAMERA_SPEED (10.0f)			//初期カメラスピード

//=============================================================================
//クラス定義
//=============================================================================
class CCamera
{
public:
    CCamera();					// コンストラクタ
    ~CCamera();					// デストラクタ
    HRESULT Init(D3DXVECTOR3 posR);						// 初期化関数

    void Uninit(void);			// 終了関数
    void Update(void);			// 更新関数

    void		SetCamera(void);	// カメラの見ているものを描画
    D3DXVECTOR3 GetPosR(void);		// 注視点ゲッター
	void		Move(void);			// 移動処理
	void		TitleMove(void);	// タイトルでの動き

	void		SetPos(D3DXVECTOR3 pos);	//カメラ位置設定

	D3DXMATRIX GetViewMtx(void) { return m_mtxView; }
	D3DXMATRIX GetProjectionMtx(void) { return m_mtxProjection; }
private:
    D3DXVECTOR3 m_posV;				//カメラの座標
    D3DXVECTOR3 m_posR;				//注視点の座標
    D3DXVECTOR3 m_vecU;				//カメラの上方向
    float		m_fDistance;		//視点-注意点の距離
    D3DXVECTOR3 m_rot;				//向き
	D3DXVECTOR3 m_pos;				//位置
	float		m_moveRot;			//移動する向き

	int			m_nSensitivity;		//マウスの感度
	float		m_fSpeed;			//カメラスピード
	
	D3DXMATRIX	m_mtxProjection;//プロジェクションマトリックス
	D3DXMATRIX	m_mtxView;//ビューマトリックス
};

#endif
