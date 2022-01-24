//=============================================================================
//
// ボス演出のワーニング処理 [warning.cpp]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "renderer.h"
#include "manager.h"
#include "warning.h"
#include "sound.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define SIZE_X (800)	//X方向のサイズ
#define SIZE_Y (200)	//Y方向のサイズ

//=============================================================================
// 静的メンバー変数
//=============================================================================
CWarning::ANIME_DATA CWarning::WarningAnim =
{
	NULL,"data/TEXTURE/Warning.png",20,2,false,
};

//=============================================================================
//コンストラクタ
//=============================================================================
CWarning::CWarning(int nPriorit)
{
	//タイプ処理
	CScene::SetObjType(CScene::OBJ_TYPE_NONE);
	m_nCounterAnim	= 0;
	m_nPatternAnimX = 0;
	nStopCount		= 0;
}

//=============================================================================
//テクスチャ読み込み処理
//=============================================================================
HRESULT CWarning::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetObjects();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, WarningAnim.pTextName, &WarningAnim.pTexture);
	return S_OK;

}

//=============================================================================
//テクスチャ破棄処理
//=============================================================================
void CWarning::Unload(void)
{
	//テクスチャの破棄
	if (WarningAnim.pTexture != NULL)
	{
		WarningAnim.pTexture->Release();
		WarningAnim.pTexture = NULL;
	}

}

//=============================================================================
//生成処理
//=============================================================================
CWarning * CWarning::Create(D3DXVECTOR3 Pos)
{
	//メモリ確保
	CWarning *pWarning = NULL;
	pWarning = new CWarning;

	//NULLチェック
	if (pWarning != NULL)
	{
		//位置設定
		pWarning->SetPos(Pos);
		//サイズ設定
		pWarning->SetSize(D3DXVECTOR3(SIZE_X, SIZE_Y, 0.0f));
		//初期化処理
		pWarning->Init();
	}

	return pWarning;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CWarning::Init(void)
{
	//サウンドポインタ取得
	CSound *pSound = CManager::GetSound();	
	//サウンド再生
	pSound->Play(CSound::LABEL_SE_WARNING);

	//テクスチャ設定用変数
	D3DXVECTOR2 Texture[4];

	//初期化処理
	CScene2d::Init();
	//テクスチャアニメーション設定
	Texture[0] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount), 0.0f);
	Texture[1] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount) + (1.0f / (float)WarningAnim.MaxCount), 0.0f);
	Texture[2] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount), 1.0f);
	Texture[3] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount) + (1.0f / (float)WarningAnim.MaxCount), 1.0f);
	//テクスチャアニメーションセット
	TextureAnim(Texture);

	//テクスチャの設定
	BindTexture(WarningAnim.pTexture);

	return S_OK;
}


//=============================================================================
// 更新処理
//=============================================================================
void CWarning::Update(void)
{
	//アニメーション変数
	D3DXVECTOR2 Texture[4];
	//処理
	Texture[0] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount), 0);
	Texture[1] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount) + (1.0f / (float)WarningAnim.MaxCount), 0);
	Texture[2] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount), 1);
	Texture[3] = D3DXVECTOR2(m_nPatternAnimX*(1.0f / (float)WarningAnim.MaxCount) + (1.0f / (float)WarningAnim.MaxCount), 1);
	//テクスチャセット
	TextureAnim(Texture);
	//アニメーションカウント
	m_nCounterAnim++;
	if (m_nCounterAnim >= WarningAnim.nCountAnime)
	{
		//アニメーションの絵を次の絵に変える
		m_nCounterAnim = 0;
		
		if (m_nPatternAnimX !=14)
		{
			m_nPatternAnimX++;
		}
		else
		{
			nStopCount++;
			if (nStopCount >= 50)
			{
				m_nPatternAnimX++;
			}
		}
		if (m_nPatternAnimX == WarningAnim.MaxCount)
		{
			m_nPatternAnimX = 0;
			if (WarningAnim.bLoop == false)
			{
				Uninit();
			}
		}
	}

}

