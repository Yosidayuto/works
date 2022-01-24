//=============================================================================
//
// 制限時間の処理 [timer.h]
// Author : 齋藤大行
//
//=============================================================================
#ifndef _TIMER_H_
#define _TIMER_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "scene.h"

//================================================
// 前方宣言
//================================================
class CNumber;

//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_MINUTES_DIGIT 1	//分の桁数
#define MAX_SECONDS_DIGIT 2 //秒の桁数

#define MOOD1_SECONDS 00	//2分モード開始秒数
#define MOOD1_MINUTES 2		//2分モード開始分
		
#define MOOD2_SECONDS 30	//30秒モード開始秒数
#define MOOD2_MINUTES 00	//30秒モード開始分

// タイマーの位置とサイズ
#define TIMER_POS D3DXVECTOR3(SCREEN_WIDTH / 2 - 40.0f,50.0f,0.0f)
#define TIMER_SIZE D3DXVECTOR3(40.0f,50.0f,0.0f)
#define TIMER_POSBG D3DXVECTOR3(SCREEN_WIDTH / 2,50.0f,0.0f)
#define TIMERBG_SIZE D3DXVECTOR3(120.0f,50.0f,0.0f)

//=============================================================================
// クラス定義
//=============================================================================
class CTimer :public CScene
{
public:
	CTimer(int nPriority = 9);
	~CTimer();

	static CTimer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int Min,int Sec);
	HRESULT Init(void);
	void Update(void);
	void Uninit(void);
	void Draw(void);

	//ゲッター
	bool GetTimeUp(void) { return m_bTimeUp; }	//時間切れ所得関数
	//セッター
	void SetTimer(int Min, int Sec);	//制限時間の設定
	int GetTime(void);//時間取得
private:
	bool m_bTimeUp;
	CNumber *m_pMINUtes;						//分のポインター
	CNumber *m_pSexonds[MAX_SECONDS_DIGIT];		//秒のポインター
	int m_nSeconds;								//分カウント
	int m_nMinutes;								//秒カウント
	int m_nCountF;								//フレームカウント
	D3DXVECTOR3  m_Pos;							//位置
	D3DXVECTOR3  m_Size;						//大きさ
};


#endif