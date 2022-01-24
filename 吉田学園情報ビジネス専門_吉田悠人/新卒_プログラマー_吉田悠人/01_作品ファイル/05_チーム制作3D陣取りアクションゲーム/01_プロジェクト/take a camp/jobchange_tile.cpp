//====================================================
//
// jobchange_tileクラスの処理[jobchange_tile.cpp]
// Author:伊藤陽梧
//
//====================================================

//====================================================
// インクルード
//====================================================
#include "jobchange_tile.h"
#include "scene3d.h"
#include "resource_texture.h"
#include "tutorial.h"
#include "collision.h"
#include "player.h"
#include "chara_select.h"
#include "fade.h"
#include "chara_select.h"
#include "skill_gauge.h"
#include "all_skill_gauge.h"
#include "attack.h"

//====================================================
// マクロ定義
//====================================================
#define TILE_COLOR	(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))

//====================================================
// コンストラクタ
//====================================================
CJobchangeTile::CJobchangeTile()
{
	m_pCrossPolygon = NULL;
	m_CharacterType = CResourceCharacter::CHARACTER_NONE;
}

//====================================================
// デストラクタ
//====================================================
CJobchangeTile::~CJobchangeTile()
{
}

//====================================================
// 生成するタイルごとに処理を分ける
//====================================================
void CJobchangeTile::CreateKnight(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	Create(pos, CResourceTexture::TEXTURE_SWORD_ICON, CResourceCharacter::CHARACTER_KNIGHT);
}
void CJobchangeTile::CreateLancer(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	Create(pos, CResourceTexture::TEXTURE_LANCE_ICON, CResourceCharacter::CHARACTER_LANCER);
}
void CJobchangeTile::CreateWizard(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	Create(pos, CResourceTexture::TEXTURE_MAGICSTICK_ICON, CResourceCharacter::CHARACTER_WIZARD);
}
void CJobchangeTile::CreateThief(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	Create(pos, CResourceTexture::TEXTURE_KNIFE_ICON, CResourceCharacter::CHARACTER_THIEF);
}
void CJobchangeTile::CreateMagician(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	Create(pos, CResourceTexture::TEXTURE_STICK_ICON, CResourceCharacter::CHARACTER_MAGICIAN);
}
void CJobchangeTile::CreateArcher(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	Create(pos, CResourceTexture::TEXTURE_ARROW_ICON, CResourceCharacter::CHARACTER_ARCHER);
}

//====================================================
// クラス生成
//====================================================
void CJobchangeTile::Create(D3DXVECTOR3 pos, CResourceTexture::TEXTURE_TYPE type, CResourceCharacter::CHARACTER_TYPE Char_type)
{
	// メモリの確保
	CJobchangeTile *pTile;
	pTile = new CJobchangeTile;

	// 初期化
	pTile->Init();

	// 各値の代入・セット
	pTile->SetPos(pos);
	pTile->SetPriority(OBJTYPE_TILE); // オブジェクトタイプ
	pTile->SetRide(true);			  // 載れないようにフラグを立てる
	pTile->m_CharacterType = Char_type;

	// ×マークの生成
	pTile->m_pCrossPolygon = CScene3d::Create(D3DXVECTOR3(pos.x, pos.y + (TILE_SIZE_Y / 2) + 1.0f, pos.z), D3DXVECTOR3(TILE_ONE_SIDE - 2, 0.0f, TILE_ONE_SIDE - 2));
	pTile->m_pCrossPolygon->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	pTile->m_pCrossPolygon->BindTexture(CResourceTexture::GetTexture(type));
	pTile->m_pCrossPolygon->SetPriority(OBJTYPE_MAP);
}

//====================================================
// 初期化処理
//====================================================
HRESULT CJobchangeTile::Init(void)
{
	// タイルの初期化
	if (FAILED(CTile::Init()))
	{
		return E_FAIL;
	}

	// タイルの色のセット
	SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CJobchangeTile::Uninit(void)
{
	// タイルの終了
	CTile::Uninit();
}

//====================================================
// 更新処理
//====================================================
void CJobchangeTile::Update(void)
{
	// タイルの更新
	CTile::Update();

	CTutorial * pTutorial = CManager::GetTutorial();
	if (pTutorial &&
		pTutorial->GetTutorialPhase() == CTutorial::PHASE_FINISH)
	{
		// タイルの色のセット
		SetColor(TILE_COLOR);
		m_pCrossPolygon->SetColor(TILE_COLOR);

		// プレイヤーのナンバー
		int nPlayerNum = 0;

		// このタイルの当たり判定
		CPlayer * pPlayer = (CPlayer*)GetTop(OBJTYPE_PLAYER);
		while (pPlayer != NULL)
		{
			// このタイルに載ったら指定の職種に変える
			if (CCollision::CollisionSphere(GetCollision(), pPlayer->GetCollision()))
			{
				// チャージしているタイルのキャンセル
				pPlayer->GetAttack()->CancelSwitch();

				// タイルに保持しているキャラタイプにセット
				pPlayer->SetCharacterType(m_CharacterType);

				// 攻撃範囲を変えるためキャラセレクトのキャラタイプを変える
				CCharaSelect::Entry_Data EntryData = CCharaSelect::GetEntryData(nPlayerNum);
				EntryData.charaType = m_CharacterType;
				CCharaSelect::SetEntryData(nPlayerNum, EntryData);

				// 攻撃の初期化
				pPlayer->InitCharacterData();

				// キャラクターのタイプごとにテクスチャを変える
				switch (m_CharacterType)
				{
				case CResourceCharacter::CHARACTER_TYPE::CHARACTER_KNIGHT:
					pPlayer->GetAllSkillgauge()->GetSkillgaugeIcon()->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_SWORD_ICON));
					break;

				case CResourceCharacter::CHARACTER_TYPE::CHARACTER_LANCER:
					pPlayer->GetAllSkillgauge()->GetSkillgaugeIcon()->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_LANCE_ICON));
					break;

				case CResourceCharacter::CHARACTER_TYPE::CHARACTER_WIZARD:
					pPlayer->GetAllSkillgauge()->GetSkillgaugeIcon()->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_MAGICSTICK_ICON));
					break;

				case CResourceCharacter::CHARACTER_TYPE::CHARACTER_THIEF:
					pPlayer->GetAllSkillgauge()->GetSkillgaugeIcon()->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_KNIFE_ICON));
					break;

				case CResourceCharacter::CHARACTER_TYPE::CHARACTER_MAGICIAN:
					pPlayer->GetAllSkillgauge()->GetSkillgaugeIcon()->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_STICK_ICON));
					break;

				case CResourceCharacter::CHARACTER_TYPE::CHARACTER_ARCHER:
					pPlayer->GetAllSkillgauge()->GetSkillgaugeIcon()->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_ARROW_ICON));
					break;

				default:
					break;
				}
			}
			pPlayer = (CPlayer*)pPlayer->GetNext();
			nPlayerNum++;
		}

		// チュートリアル中だったら
		CTutorial * pTutrial = CManager::GetTutorial();
		if (pTutrial)
		{
			// フェーズがすべて終了したとき
			if (pTutrial->GetTutorialPhase() == CTutorial::PHASE_FINISH)
			{
				// 載れるようにする
				SetRide(false);
			}
		}
	}
}