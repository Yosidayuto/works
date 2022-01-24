//=============================================================================
// サウンド処理 [sound.cpp]
//=============================================================================
#include "sound.h"
//----------------------------------
//静的メンバー変数
//----------------------------------
CSound::PARAM CSound::m_aParam[LABEL_MAX] =
{
	//BGM
	{ "data/BGM/Title.wav", 0 },	//タイトル
	{ "data/BGM/Load.wav", 0 },		//ロード
	{ "data/BGM/Select.wav", 0 },	//セレクト
	{ "data/BGM/Stage_1.wav", 0 },	//ステージ１
	{ "data/BGM/Stage_2.wav", 0 },	//ステージ２
	{ "data/BGM/Stage_3.wav", 0 },	//ステージ３
	{ "data/BGM/Boss1.wav", 0 },	//ボス１
	{ "data/BGM/Boss2.wav", 0 },	//ボス２
	{ "data/BGM/Boss3.wav", 0 },	//ボス３
	{ "data/BGM/Ranking.wav", 0 },	//ランキング
	//SE
	{ "data/SE/SE_Button.wav", 0 },	//クリック
	{ "data/SE/SE_Cancel.wav", 0 },	//キャンセル
	{ "data/SE/SE_Start.wav", 0 },	//スタート
	{ "data/SE/SE_Shots.wav", 0 },	//ショット
	{ "data/SE/SE_Laser.wav", 0 },	//レーザー
	{ "data/SE/SE_Homing.wav", 0 },	//ホーミング
	{ "data/SE/SE_Die.wav", 0 },	//死んだとき
	{ "data/SE/SE_Warning.wav", 0 },//ワーニング
	{ "data/SE/SE_Boss1.wav", 0 },	//死んだボス(1と3)
	{ "data/SE/SE_Boss2.wav", 0 },	//死んだボス(2)
	{ "data/SE/SE_Result.wav", 0 },	//リザルトファンファーレ
};

//---------------------------------
//コンストラクタ
//---------------------------------
CSound::CSound()
{
	//初期化処理
	m_pXAudio2 = NULL;
	m_pMasteringVoice = NULL;
	for (int nCountSound = 0; nCountSound < LABEL_MAX; nCountSound++)
	{
		m_apSourceVoice[nCountSound] = NULL;
		m_apDataAudio[nCountSound] = NULL;
		m_aSizeAudio[nCountSound] = NULL;

	}
	
}
//---------------------------------
//デストラクタ
//--------------------------------
CSound::~CSound()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSound::Init(HWND hWnd)
{
	// COMライブラリの初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2オブジェクトの作成
	if(FAILED(XAudio2Create(&m_pXAudio2, 0)))
	{
		MessageBox(hWnd, "XAudio2オブジェクトの作成に失敗！", "警告！", MB_ICONWARNING);

		// COMライブラリの終了処理
		CoUninitialize();

		return E_FAIL;
	}
	
	// マスターボイスの生成
	if(FAILED(m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice)))
	{
		MessageBox(hWnd, "マスターボイスの生成に失敗！", "警告！", MB_ICONWARNING);

		if(m_pXAudio2)
		{
			// XAudio2オブジェクトの開放
			m_pXAudio2->Release();
			m_pXAudio2 = NULL;
		}

		// COMライブラリの終了処理
		CoUninitialize();

		return E_FAIL;
	}

	// サウンドデータの初期化
	for(int nCntSound = 0; nCntSound < LABEL_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// バッファのクリア
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// サウンドデータファイルの生成
		hFile = CreateFile(m_aParam[nCntSound].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if(hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(1)", "警告！", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// ファイルポインタを先頭に移動
			MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(2)", "警告！", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
	
		// WAVEファイルのチェック
		if(FAILED(CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition)))
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		if(FAILED(ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition)))
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		if(dwFiletype != 'EVAW')
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(3)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
	
		// フォーマットチェック
		if(FAILED(CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition)))
		{
			MessageBox(hWnd, "フォーマットチェックに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		if(FAILED(ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition)))
		{
			MessageBox(hWnd, "フォーマットチェックに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// オーディオデータ読み込み
		if(FAILED(CheckChunk(hFile, 'atad', &m_aSizeAudio[nCntSound], &dwChunkPosition)))
		{
			MessageBox(hWnd, "オーディオデータ読み込みに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		m_apDataAudio[nCntSound] = (BYTE*)malloc(m_aSizeAudio[nCntSound]);
		if(FAILED(ReadChunkData(hFile, m_apDataAudio[nCntSound], m_aSizeAudio[nCntSound], dwChunkPosition)))
		{
			MessageBox(hWnd, "オーディオデータ読み込みに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
	
		// ソースボイスの生成
		if(FAILED(m_pXAudio2->CreateSourceVoice(&m_apSourceVoice[nCntSound], &(wfx.Format))))
		{
			MessageBox(hWnd, "ソースボイスの生成に失敗！", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// バッファの値設定
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = m_aSizeAudio[nCntSound];
		buffer.pAudioData = m_apDataAudio[nCntSound];
		buffer.Flags      = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount  = m_aParam[nCntSound].nCntLoop;

		// オーディオバッファの登録
		m_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);

		// ファイルをクローズ
		CloseHandle(hFile);
	}

	return S_OK;
}


//=============================================================================
// 終了処理
//=============================================================================
void CSound::Uninit(void) 
{
	// 一時停止
	for(int nCntSound = 0; nCntSound < LABEL_MAX; nCntSound++)
	{
		if(m_apSourceVoice[nCntSound])
		{
			// 一時停止
			m_apSourceVoice[nCntSound]->Stop(0);
	
			// ソースボイスの破棄
			m_apSourceVoice[nCntSound]->DestroyVoice();
			m_apSourceVoice[nCntSound] = NULL;
	
			// オーディオデータの開放
			free(m_apDataAudio[nCntSound]);
			m_apDataAudio[nCntSound] = NULL;
		}
	}
	
	// マスターボイスの破棄
	m_pMasteringVoice->DestroyVoice();
	m_pMasteringVoice = NULL;
	
	if(m_pXAudio2)
	{
		// XAudio2オブジェクトの開放
		m_pXAudio2->Release();
		m_pXAudio2 = NULL;
	}
	
	// COMライブラリの終了処理
	CoUninitialize();
}


//=============================================================================
// セグメント再生(再生中なら停止)
//=============================================================================
HRESULT CSound::Play(LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;
	// バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_aSizeAudio[label];
	buffer.pAudioData = m_apDataAudio[label];
	buffer.Flags      = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount  = m_aParam[label].nCntLoop;
	// 状態取得
	m_apSourceVoice[label]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		m_apSourceVoice[label]->Stop(0);
		// オーディオバッファの削除
		m_apSourceVoice[label]->FlushSourceBuffers();
	}
	// オーディオバッファの登録
	m_apSourceVoice[label]->SubmitSourceBuffer(&buffer);
	// 再生
	m_apSourceVoice[label]->Start(0);

	return S_OK;
}


//=============================================================================
// セグメント停止(ラベル指定)
//=============================================================================
void CSound::Stop(LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// 状態取得
	m_apSourceVoice[label]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		m_apSourceVoice[label]->Stop(0);

		// オーディオバッファの削除
		m_apSourceVoice[label]->FlushSourceBuffers();
	}
}


//=============================================================================
// セグメント停止(全て)
//=============================================================================
void CSound::Stop(void)
{
	// 一時停止
	for(int nCntSound = 0; nCntSound < LABEL_MAX; nCntSound++)
	{
		if(m_apSourceVoice[nCntSound])
		{
			// 一時停止
			m_apSourceVoice[nCntSound]->Stop(0);
		}
	}
}


//=============================================================================
// チャンクのチェック
//=============================================================================
HRESULT CSound::CheckChunk(HANDLE hFile, DWORD format, DWORD * pChunkSize, DWORD * pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;
	
	if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	while(hr == S_OK)
	{
		if(ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if(ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch(dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize  = dwChunkDataSize;
			dwChunkDataSize = 4;
			if(ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if(SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分移動
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if(dwChunkType == format)
		{
			*pChunkSize         = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if(dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}
	
	return S_OK;
}


//=============================================================================
// チャンクデータの読み込み
//=============================================================================
HRESULT CSound::ReadChunkData(HANDLE hFile, void * pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	
	if(SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if(ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	return S_OK;
}

