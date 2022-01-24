//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	title.h
//	Author:�����ߔ��u
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

#include "scene.h"
#include "main.h"

#define MAX_TITLE_TEX 7

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�O���錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CScene2d;
class CCamera;

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CTitle : public CScene
{
	typedef enum
	{
		TEX_TITLE = 0,
		TEX_MODE1,//30�b
		TEX_MODE2,//60�b
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
	void KeyControl(void);				//�L�[�{�[�h����
	void JoyControl(void);				//�R���g���[���[����

	CScene2d* m_pTitle[MAX_TITLE_TEX];	//TEX�|�C���^
	static CCamera*	m_pCamera;			//�J�����|�C���^
	PLAYER_SELECT PlayerNum;
	int nPlayer;
	const int m_nTexture[MAX_TITLE_TEX] = { 60, 61, 62, 63, 64, 65 ,66 };		// �e�N�X�`���ԍ�
};