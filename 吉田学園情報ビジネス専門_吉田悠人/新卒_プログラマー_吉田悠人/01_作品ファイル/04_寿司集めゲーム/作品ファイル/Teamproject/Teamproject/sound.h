//=============================================================================
//
// サウンド [sound.h]
// Author : 林川紗梨夏
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <xaudio2.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CSound
{
public:
	typedef enum
	{
		LABEL_NONE = -1,
		//SE
		LABEL_SE_DASH,
		LABEL_SE_DEATH,
		LABEL_SE_GETITEM,
		LABEL_SE_GETSUSHI,
		LABEL_SE_HITPLAYER,
		LABEL_SE_COUNTDOWN,
		LABEL_SE_PIPI,
		//BGM
		LABEL_BGM_TITLE,
		LABEL_BGM_GAME,
		LABEL_BGM_OLADING,
		LABEL_BGM_RESULT,
		LABEL_MAX
	} LABEL;
	CSound();
	~CSound();
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(LABEL label);
	void StopSound(LABEL label);
	void StopSound(void);
private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} PARAM;
	IXAudio2 *m_pXAudio2;									// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;				// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[LABEL_MAX];	// ソースボイス
	BYTE *m_apDataAudio[LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[LABEL_MAX];					// オーディオデータサイズ
	static PARAM m_aParam[LABEL_MAX];
};
#endif