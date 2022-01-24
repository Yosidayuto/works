//=============================================================================
// サウンド処理 [sound.h]
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンドクラス
//*****************************************************************************
class CSound
{
public:
	CSound();
	~CSound();
	// サウンドファイル
	typedef enum
	{
		//BGM
		LABEL_BGM_TITLE = 0,	//タイトル
		LABEL_BGM_LOAD,			//ロード
		LABEL_BGM_SELECT,		//セレクト
		LABEL_BGM_STAGE_1,		//ステージ１
		LABEL_BGM_STAGE_2,		//ステージ２
		LABEL_BGM_STAGE_3,		//ステージ３
		LABEL_BGM_BOSS_1,		//ボス１
		LABEL_BGM_BOSS_2,		//ボス２
		LABEL_BGM_BOSS_3,		//ボス３
		LABEL_BGM_RANKING,		//ランキング
		//SE
		LABEL_SE_CLICK,			//クリック
		LABEL_SE_CANCEL,		//キャンセル
		LABEL_SE_START,			//スタート
		LABEL_SE_SHOTS,			//ショット
		LABEL_SE_LASER,			//レーザー
		LABEL_SE_HOMING,		//ホーミング
		LABEL_SE_DIE,			//死んだとき（まだ）
		LABEL_SE_WARNING,		//ワーニング
		LABEL_SE_BOSS_DIE_1,	//死んだボス(1と3)
		LABEL_SE_BOSS_DIE_2,	//死んだボス(2)
		LABEL_SE_RESULT,		//リザルトファンファーレ
		LABEL_MAX,
	}LABEL;


	HRESULT	Init(HWND hWnd);			//初期化処理
	void	Uninit(void);				//終了処理
	HRESULT Play(LABEL label);			//スタート処理
	void	Stop(LABEL label);			//ストップ処理（１つだけ）
	void	Stop(void);					//ストップ処理（全部）
private:
	//関数
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	//変数
	IXAudio2				*m_pXAudio2;					// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice	*m_pMasteringVoice;				// マスターボイス
	IXAudio2SourceVoice		*m_apSourceVoice[LABEL_MAX];	// ソースボイス
	BYTE					*m_apDataAudio[LABEL_MAX];		// オーディオデータ
	DWORD					m_aSizeAudio[LABEL_MAX];		// オーディオデータサイズ
		
	// 各音素材のパラメータ
	typedef struct
	{
		char	*pFilename;	// ファイル名
		int		nCntLoop;	// ループカウント
	}PARAM;

	static PARAM m_aParam[LABEL_MAX];
};
#endif
