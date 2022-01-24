//=====================================================================
//
//	カメラ処理 [camera.h]
//	Author  林川紗梨夏
//
//=====================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
//======================================================
//マクロ定義
//======================================================
#define CAMERA_VIEW_RANGE (500.0f)
#define CAMERA_DISTANCE_FROM_PLAYER (100.0f)
#define CAMERA_DISTANCE_FROM_PLAYER_STAND (200.0f)
#define PLAYER_CAMERA_HEIGHT (20.0f) //プレイヤーの高さ

//======================================================
//クラス定義
//======================================================
class CCamera
{
public:
	CCamera();
	~CCamera();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);					// カメラによる描画
	void SetCamera(int nCamera);			// カメラによる分割描画

	bool SetUpViewport(int screen_id);		// ビューポート(複数)設定
	bool SetUpViewport(void);				// ビューポート(単体)設定

	D3DXVECTOR3 GetRot(void);
	void SetRot(D3DXVECTOR3 rot);
	void SetPos(int nCamera, D3DXVECTOR3 pos);
	//static void LoadScriptCamera(void);
	//void PlayerFlattery(void);		//プレイヤー追従

#ifdef _DEBUG
	void		Move(void);			// 移動処理
#endif
private:
	typedef struct 		//分割カメラ
	{
		float Width;	// 位置
		float Height;	// 注視点
	}WindowSize;

	WindowSize m_WidowSize;
	void SetCameraView(D3DXVECTOR3 posV, D3DXVECTOR3 posR, float fInterpolation);
	D3DXVECTOR3 m_posV[MAX_PLAYER];            // カメラの座標
	D3DXVECTOR3 m_posR[MAX_PLAYER];            // 注視点の座標
	D3DXVECTOR3 m_vecU;            // カメラの上方向
	D3DXMATRIX m_mtxProjection;    // プロジェクションマトリックス
	D3DXMATRIX m_mtxView;          // ビューマトリックス
	D3DXVECTOR3 m_RotateCenter;    // カメラの回転中心座標
	float m_fDistance;             // 視点-注意点の距離
	D3DXVECTOR3 m_pos[MAX_PLAYER];	// 位置
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_posVDest;         // カメラの座標(差)
	D3DXVECTOR3 m_posRDest;         // 注視点の座標(差)
	bool m_bIsFollowPlayer;			// プレイヤーに追従するか
	float m_fInterpolation;			// カメラ補間スピード
	static D3DXVECTOR2 m_offset[MAX_PLAYER];//画面の位置

#ifdef _DEBUG						   
	float		m_fMoveRot;			// 移動する向き
	bool		m_bDebug;			// デバック状態
#endif
};

#endif
