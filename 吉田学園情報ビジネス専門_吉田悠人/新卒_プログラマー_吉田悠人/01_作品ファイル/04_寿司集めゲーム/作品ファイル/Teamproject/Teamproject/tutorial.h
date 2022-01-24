//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	tutorial.h
//	Author:�����ߔ��u
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

#include "scene.h"
#include "main.h"

#define MAX_TUTORIAL_TEX 1

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�O���錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CScene2d;
class CCamera;

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
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
	CScene2d* m_pTutorial[MAX_TUTORIAL_TEX];	//TEX�|�C���^

	static CCamera*	m_pCamera;			//�J�����|�C���^

	const int m_nTexture[MAX_TUTORIAL_TEX] = { 70 };		// �e�N�X�`���ԍ�
};