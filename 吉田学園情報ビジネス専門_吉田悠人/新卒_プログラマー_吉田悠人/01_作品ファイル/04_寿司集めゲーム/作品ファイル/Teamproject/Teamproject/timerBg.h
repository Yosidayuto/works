//=============================================================================
//
// �������Ԕw�i�̏��� [timerBg.h]
// Author : �V����s
//
//=============================================================================
#ifndef _CTIMERBG_
#define _CTIMERBG_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "billboard.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"
//================================================
// �O���錾
//================================================


//=============================================================================
//�}�N����`
//=============================================================================


class CtimerBg :public CScene2d
{
public:
	CtimerBg(int nPriority = 8);
	~CtimerBg();

	static CtimerBg *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR Col);
	void Update(void);
	void Uninit(void);
	void Draw(void);


private:

	int							m_Alpha;		//�����x
	bool						m_bUse;			//�g�����g��Ȃ���
	const int					m_nTexture = 23;// �e�N�X�`���ԍ�


};


#endif 