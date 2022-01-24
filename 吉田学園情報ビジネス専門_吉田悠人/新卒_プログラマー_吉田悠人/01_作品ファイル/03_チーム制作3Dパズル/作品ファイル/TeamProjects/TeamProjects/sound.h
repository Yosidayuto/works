//=============================================================================
//
// 音 [sound.h]
// Author : 吉田悠人
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
// クラス定義
//*****************************************************************************
class CSound
{
public:
	//*****************************************************************************
	// サウンドファイル
	//*****************************************************************************
	typedef enum
	{
		SOUND_LABEL_BGM_TITLE = 0,		//タイトルBGM
		SOUND_LABEL_BGM_STAGE_1,		//ステージ１BGM
		SOUND_LABEL_BGM_STAGE_2,		//ステージ２BGM
		SOUND_LABEL_BGM_STAGE_3,		//ステージ３BGM
		SOUND_LABEL_BGM_DECISION,		//決定音
		SOUND_LABEL_BGM_MESSAGE,		//セリフが出るとき
		SOUND_LABEL_BGM_TUTORIAL,		//チュートリアルが出るとき
		SOUND_LABEL_BGM_REACHED,		//オブジェクトが指定の位置に置かれたとき
		SOUND_LABEL_BGM_SHOW_POSE,		//ポーズ表示音
		SOUND_LABEL_BGM_CHOICE,			//ポーズ選択音
		SOUND_LABEL_BGM_ERROR,			//エラー音
		SOUND_LABEL_MAX
	} SOUND_LABEL;

	CSound();
	~CSound();
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	//*****************************************************************************
	// パラメータ構造体定義
	//*****************************************************************************
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} PARAM;
	IXAudio2 *m_pXAudio2;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;			// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ
	static PARAM m_aParam[SOUND_LABEL_MAX];
};
#endif