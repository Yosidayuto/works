//=============================================================================
//
// アイテムベース [item.cpp]
// Author : 齋藤大行
//
//=============================================================================

//=============================================================================
// ヘッダーファイル
//=============================================================================
#include "item.h"
#include "timer.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "number.h"
#include "scene.h"

//=============================================================================
// マクロ定義
//=============================================================================



//=============================================================================
//静的メンバー変数宣言
//=============================================================================


//=============================================================================
// コンストラクタ
//=============================================================================
CTimer::CTimer(int nPriority) : CScene(nPriority)
{
	m_nCountF = 0;
	m_nMinutes = 0;
	m_nSeconds = 0;
	m_bTimeUp = false;

	for (int nCnt = 0; nCnt < MAX_SECONDS_DIGIT; nCnt++)
	{
		m_pSexonds[nCnt] = NULL;
	}

	m_pMINUtes = NULL;

	m_bTimeUp = false;
}


//=============================================================================
// デストラクタ
//=============================================================================
CTimer::~CTimer()
{
}


//=============================================================================
// 生成処理関数
//=============================================================================
CTimer * CTimer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int Min, int Sec)
{
	//インスタンス生成
	CTimer *pTimer;
	
	//メモリ確保
	pTimer = new CTimer;
	
	//時間設定
	pTimer->SetTimer(Min, Sec);

	//場所設定
	pTimer->m_Pos = pos;

	//大きさ設定
	pTimer->m_Size = size;

	//初期化処理
	pTimer->Init();

	return pTimer;
}


//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CTimer::Init(void)
{
	//分の生成
	m_pMINUtes = CNumber::Create(m_Pos, m_Size.x, m_Size.y);
	
	//秒の生成
	for (int nCnt = 0;  nCnt < MAX_SECONDS_DIGIT;  nCnt++)
	{
		m_pSexonds[nCnt] = CNumber::Create(D3DXVECTOR3(m_Pos.x + (nCnt * m_Size.x) + 40.0f, m_Pos.y, 0.0f), m_Size.x, m_Size.y);
	}
	
	
	return S_OK;
}


//=============================================================================
// 更新処理関数
//=============================================================================
void CTimer::Update(void)
{
	
	//if(ゲーム中の場合)

	//フレームのカウント
	m_nCountF++;

	if (m_nCountF == 30)
	{
		//フレームのカウントをリセット
		m_nCountF = 0;
		//秒のカウントを下げる
		m_nSeconds--;
	}

	//描画0以下になったら
	if (m_nSeconds <= -1)
	{
		//分のカウントが1以上の時
		if (m_nMinutes >= 1)
		{
			// 秒のカウントを59に戻す
			m_nSeconds = 59;

			// 分のカウントを下げる
			m_nMinutes--;
		}
	}
	//タイムアップ　
	if (m_pMINUtes && m_nSeconds <= -1)
	{
		m_nCountF = 0;
		m_nMinutes = 0;
		m_nSeconds = 0;

		//タイムアップのフラグ
		m_bTimeUp = true;

		//ゲーム終了処理
		//ゲーム中なら
		//ゲームモードをおわりにする
	}


	// 数字の変更
	int nRadix = 10;

	for (int nCnt = 0; nCnt < MAX_SECONDS_DIGIT; nCnt++)
	{
		int nAnswer = m_nSeconds % (int)pow(nRadix, MAX_SECONDS_DIGIT - nCnt) / (int)pow(nRadix, MAX_SECONDS_DIGIT - nCnt - 1);

		m_pSexonds[nCnt]->SetNumber(nAnswer);
	}

	//タイマー分の数字設定
	m_pMINUtes->SetNumber(m_nMinutes);

}


//=============================================================================
// 終了処理関数
//=============================================================================
void CTimer::Uninit(void)
{
	//秒の破棄
	for (int nCnt = 0; nCnt < MAX_SECONDS_DIGIT; nCnt++)
	{
		if (m_pSexonds[nCnt] != NULL)
		{
			m_pSexonds[nCnt]->Uninit();
			delete 	m_pSexonds[nCnt];
			m_pSexonds[nCnt] = NULL;
		}
	}

	//分の破棄
	if (m_pMINUtes != NULL)
	{
		m_pMINUtes->Uninit();
		delete 	m_pMINUtes;
		m_pMINUtes = NULL;
	}

	//オブジェクトの破棄
	Release();
}


//=============================================================================
// 描画処理
//=============================================================================
void CTimer::Draw(void)
{

	//秒の描画
	for (int nCnt = 0; nCnt < MAX_SECONDS_DIGIT; nCnt++)
	{
		m_pSexonds[nCnt]->Draw();
	}

	//分の描画
	m_pMINUtes->Draw();

}


//=============================================================================
// 時間設定処理
//=============================================================================
void CTimer::SetTimer(int Min, int Sec)
{
	m_nMinutes = Min;
	m_nSeconds = Sec;
}

//=============================================================================
// 現在時間取得（フレーム）
//=============================================================================
int CTimer::GetTime(void)
{
	int nTime = (m_nMinutes * 60 * 30) + (m_nSeconds * 30);
	return nTime;//フレームで返す
}
