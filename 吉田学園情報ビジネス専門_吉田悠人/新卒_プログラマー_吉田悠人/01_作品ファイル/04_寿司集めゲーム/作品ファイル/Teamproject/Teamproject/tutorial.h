//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	tutorial.h
//	Author:高橋那伯志
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#include "scene.h"
#include "main.h"

#define MAX_TUTORIAL_TEX 1

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//前方宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CScene2d;
class CCamera;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CTutorial : public CScene
{
	typedef enum
	{
		TEX_TUTORIAL = 0,
	} TUTORIAL_TEX;

public:
	CTutorial();
	~CTutorial();
	static CTutorial *Create(void);
	HRESULT Init(void);
	void Update(void);
	void Draw(void);
	void Uninit(void);
private:
	CScene2d* m_pTutorial[MAX_TUTORIAL_TEX];	//TEXポインタ

	static CCamera*	m_pCamera;			//カメラポインタ

	const int m_nTexture[MAX_TUTORIAL_TEX] = { 70 };		// テクスチャ番号
};