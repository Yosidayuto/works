//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	title.h
//	Author:高橋那伯志
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#include "scene.h"
#include "main.h"

#define MAX_TITLE_TEX 7

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//前方宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CScene2d;
class CCamera;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CTitle : public CScene
{
	typedef enum
	{
		TEX_TITLE = 0,
		TEX_MODE1,//30秒
		TEX_MODE2,//60秒
		TEX_1PLAYER,//1PMODE
		TEX_2PLAYER,//2PMODE
		TEX_3PLAYER,//3PMODE
		TEX_4PLAYER,//4PMODE
	} TITLE_TEX;
	typedef enum
	{
		PLAYER_NONE = 0,
		PLAYER_1,//1PMODE
		PLAYER_2,//2PMODE
		PLAYER_3,//3PMODE
		PLAYER_4,//4PMODE
	} PLAYER_SELECT;
public:
	CTitle();
	~CTitle();
	static CTitle *Create(void);
	HRESULT Init(void);
	void Update(void);
	void Draw(void);
	void Uninit(void);
private:
	void KeyControl(void);				//キーボード入力
	void JoyControl(void);				//コントローラー入力

	CScene2d* m_pTitle[MAX_TITLE_TEX];	//TEXポインタ
	static CCamera*	m_pCamera;			//カメラポインタ
	PLAYER_SELECT PlayerNum;
	int nPlayer;
	const int m_nTexture[MAX_TITLE_TEX] = { 60, 61, 62, 63, 64, 65 ,66 };		// テクスチャ番号
};