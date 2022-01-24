//=============================================================================
//
// リソースマネージャー [reource manager.cpp]
// Author : 吉田悠人
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "renderer.h"
#include "resource manager.h"
#include <stdio.h>
#include "model.h"

#include "player.h"
#include "button.h"
#include "grass block.h"
#include "end button.h"
#include "restart button.h"
#include "start button.h"
#include "child.h"
#include "talk_base.h"
#include "red sand block.h"
#include "hole block.h"
#include "garbage block.h"
#include "building block.h"
#include "building break block.h"
#include "sand block.h"
#include "sprout block.h"
#include "seeds block.h"
#include "tutorial.h"
#include "press button ui.h"
#include "grass block.h"
#include "small tree.h"
#include "big tree.h"
#include "apple block.h"
#include "oranges block.h"
#include "grapes block.h"
#include "watermelon block.h"
#include "luggage block.h"
#include "sand block.h"
#include "watermelon block.h"
#include "title logo.h"
#include "particle.h"

#include "stage1.h"
#include "stage2.h"
#include "stage3.h"

#include "sea.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define TEXTURE_DATA ("Data/Text/TextureData.csv")
#define MODEL_DATA ("Data/Text/ModelData.csv")

//=============================================================================
// コンストラクタ
//=============================================================================
CResource::CResource()
{
	m_nMaxTexture	= 0;
	m_nMaxModel		= 0;
	m_npTexture		= NULL;
	m_npModel		= NULL;
	m_pTexture		= NULL;
	m_pModel		= NULL;
}
//=============================================================================
// デストラクタ
//=============================================================================
CResource::~CResource()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CResource::Init(void)
{
	//テクスチャロード
	TextureFail();
	//モデルファイルロード
	XFail();
	//海データロード
	CSea::Load();

	//マップ読み込み
	CStage1::Load();
	CStage2::Load();
	CStage3::Load();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CResource::Uninit(void)
{
	//テクスチャアンロード
	TextureUnLoad();
	//モデルアンロード
	ModelUnLoad();
	//海データアンロード
	CSea::Unload();

}

//=============================================================================
// テクスチャロード
//=============================================================================
LPDIRECT3DTEXTURE9 CResource::TextureLoad(int nTexture)
{
	for (int nCountTexture = 0; nCountTexture < m_nMaxTexture; nCountTexture++)
	{
		//テクスチャ番号が一致したら
		if (m_npTexture[nCountTexture] == nTexture)
		{
			return m_pTexture[nCountTexture];
		}
	}
	return NULL;
}

//=============================================================================
// テクスチャアンロード
//=============================================================================
void CResource::TextureUnLoad(void)
{
	for (int nTexture = 0; nTexture < m_nMaxTexture; nTexture++)
	{
		//テクスチャの破棄
		if (m_pTexture[nTexture] != NULL)
		{
			m_pTexture[nTexture]->Release();
			m_pTexture[nTexture] = NULL;
		}
	}
}

//=============================================================================
// テクスチャデータ読み込み
//=============================================================================
void CResource::TextureFail(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ファイルポインタ
	FILE*	pFile = NULL;
	//読み込み用データ
	char cFileString[258];
	char aData[256] = {};
	//行
	int nRow = 0;
	//初期化
	memset(cFileString, 0, sizeof(cFileString));

	//ファイル読み込み
	fopen_s(&pFile, TEXTURE_DATA, "r");

	if (pFile != NULL)
	{
		//総数読み込み
		fscanf_s(pFile, "MAX_DATA,%d", &m_nMaxTexture);
		
		//メモリ確保
		m_npTexture = new int [m_nMaxTexture];
		m_pTexture = new LPDIRECT3DTEXTURE9 [m_nMaxTexture];
		//初期化
		for (int nTexture = 0; nTexture < m_nMaxTexture; nTexture++)
		{
			m_npTexture[nTexture] = NULL;
			m_pTexture[nTexture] = NULL;
		}

		//行を読み飛ばし
		while (fgetc(pFile) != '\n');

		while (fscanf(pFile, "%d,%[^,],%s\n", &m_npTexture[nRow], m_pcTextureName, aData) != EOF)
		{
			// テクスチャの生成
			D3DXCreateTextureFromFile(pDevice,
				m_pcTextureName,
				&m_pTexture[nRow]);
			//行を進める
			nRow++;
		}
		fclose(pFile);				//ファイルを閉じる
	}

}

//=============================================================================
// モデルロード
//=============================================================================
CModel::MODELDATA CResource::ModelLoad(int nModel)
{
	for (int nCountModel = 0; nCountModel < m_nMaxModel; nCountModel++)
	{
		//テクスチャ番号が一致したら
		if (m_npModel[nCountModel] == nModel)
		{
			return m_pModel[nCountModel];
		}
	}
	return CModel::MODELDATA();
}

//=============================================================================
// モデルアンロード
//=============================================================================
void CResource::ModelUnLoad(void)
{
	for (int nCountModel = 0; nCountModel < m_nMaxModel; nCountModel++)
	{
		if (m_pModel[nCountModel].pBuffMat != NULL)
		{
			m_pModel[nCountModel].pBuffMat->Release();
		}

		if (m_pModel[nCountModel].pMesh != NULL)
		{
			m_pModel[nCountModel].pMesh->Release();
		}

		for (int nCountTex = 0; nCountTex < MAX_MATERIAL; nCountTex++)
		{
			if (m_pModel[nCountModel].pTexture[nCountTex] != NULL)
			{
				m_pModel[nCountModel].pTexture[nCountTex]->Release();
			}
		}

	}

}

//=============================================================================
// Xファイル読み込みファイル
//=============================================================================
void CResource::XFail(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//ファイルポインタ
	FILE*	pFile = NULL;
	//モデルテクスチャ用
	D3DXMATERIAL *pMat;
	//読み込み用データ
	char cFileString[258];
	char aData[256] = {};
	//行
	int nRow = 0;
	//初期化
	memset(cFileString, 0, sizeof(cFileString));

	//ファイル読み込み
	fopen_s(&pFile, MODEL_DATA, "r");

	if (pFile != NULL)
	{
		//総数読み込み
		fscanf_s(pFile, "MAX_DATA,%d", &m_nMaxModel);

		//メモリ確保
		m_npModel = new int[m_nMaxModel];
		m_pModel = new CModel::MODELDATA[m_nMaxModel];
		//初期化
		for (int nModel = 0; nModel < m_nMaxModel; nModel++)
		{
			m_npModel[nModel] = NULL;
			ZeroMemory(&m_pModel[nModel], sizeof(m_pModel[nModel]));
		}

		//行を読み飛ばし
		while (fgetc(pFile) != '\n');

		while (fscanf(pFile, "%d,%[^,],%s\n", &m_npModel[nRow], m_pcTextureName, aData) != EOF)
		{
			// モデルの生成
			D3DXLoadMeshFromX(m_pcTextureName,
				D3DXMESH_SYSTEMMEM, 
				pDevice,
				NULL,
				&m_pModel[nRow].pBuffMat,
				NULL, 
				&m_pModel[nRow].nNumMat,
				&m_pModel[nRow].pMesh);
			// モデルのテクスチャ処理
			if (m_pModel[nRow].pBuffMat != NULL)
			{
				pMat = (D3DXMATERIAL *)m_pModel[nRow].pBuffMat->GetBufferPointer();

				for (int nCountMat = 0; nCountMat < (int)m_pModel[nRow].nNumMat; nCountMat++)
				{
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCountMat].pTextureFilename,
						&m_pModel[nRow].pTexture[nCountMat]);
				}

			}

			//行を進める
			nRow++;
		}
		fclose(pFile);				//ファイルを閉じる
	}

}

