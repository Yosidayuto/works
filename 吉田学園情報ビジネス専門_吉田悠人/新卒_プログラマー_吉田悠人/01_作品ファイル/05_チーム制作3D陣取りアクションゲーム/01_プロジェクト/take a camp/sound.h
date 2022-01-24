//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 増澤 未来
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// クラス宣言
//*****************************************************************************

// サウンドクラス
class CSound
{
public:
	//============
	// 状態列挙
	//============
	typedef enum
	{
		// ゲーム本編のBGM
		LABEL_BGM_TITLE = 0,			// タイトルBGM
		LABEL_BGM_SELECT,				// キャラクターセレクトBGM
		LABEL_BGM_GAME,					// ゲームのBGM
		LABEL_BGM_GAME_LIMIT,			// ゲームの残り時間が少ないときのBGM
		LABEL_BGM_RESULT,				// リザルトのBGM
		// キャラのSE
		LABEL_SE_KENSI_ATTACK,			// 剣士の攻撃SE
		LABEL_SE_KENSI_FINALATTACK,		// 剣士の必殺SE
		LABEL_SE_YARI_ATTACK,			// 槍の攻撃SE
		LABEL_SE_YARI_FINALATTACK,		// 槍の必殺SE
		LABEL_SE_MAHOU_ATTACK,			// 魔法の攻撃SE
		LABEL_SE_MAHOU_FINALATTACK,		// 魔法の必殺SE
		LABEL_SE_YUMI_ATTACK,			// 弓の攻撃SE
		LABEL_SE_YUMI_FINALATTACK,		// 弓の必殺SE
		LABEL_SE_TOZOKU_ATTACK,			// 盗賊の攻撃SE
		LABEL_SE_TOZOKU_FINALATTACK,	// 盗賊の必殺SE
		LABEL_SE_KIJUTUSI_ATTACK,		// 奇術師の攻撃SE
		LABEL_SE_DEATH,					// 死んだ時のSE
		// ゲーム本編のSE
		LABEL_SE_BUTTON,				// ボタン押したときのSE
		LABEL_SE_WARP,					// ワープ時のSE
		LABEL_SE_PLAYERENTRY,			// プレイヤーエントリーSE
		LABEL_SE_ENTRY,					// エントリー時のSE
		LABEL_SE_ITEM,					// アイテム取得時のSE
		LABEL_SE_LIMIT,					// 残り時間表示時のSE
		LABEL_SE_FINISH,				// 終了時のSE
		// リザルトSE
		LABEL_SE_GAUGE,					// ゲージ上昇音
		LABEL_SE_RANKING,				// 順位決定音
		LABEL_SE_KAMIHUBUKI,			// 最後の紙吹雪SE
		SOUND_LABEL_MAX,				// サウンド最大数
	}LABEL;

	typedef enum
	{
		SOUND_LOOP_ON = -1,	//ループする
		SOUND_LOOP_OFF,		//ループしない
	}SOUND_LOOP;


	//============
	// メンバ関数
	//============
	CSound();
	~CSound();

	HRESULT Init(HWND hWnd);   // 初期化
	void Uninit(void);         // 終了
	HRESULT Play(LABEL label); // 再生
	void Stop(LABEL label);    // 停止
	void Stop(void);           // 再生中の音のすべて停止
private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	//============
	// 構造体定義
	//============
	// パラメータ
	typedef struct
	{
		char *pFilename; // ファイル名
		int nCntLoop;    // ループカウント
	} SOUNDPARAM;

	//============
	// メンバ変数
	//============
	static SOUNDPARAM m_aParam[SOUND_LABEL_MAX];             // パラメータ

	IXAudio2 *m_pXAudio2;                                    // XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;              // マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];   // ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];                    // オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];                     // オーディオデータサイズ
};
#endif