//=============================================================================
//
// ������ [floor.h]
// Author : �ѐ�ї���
//
//=============================================================================
#ifndef _SUSHI_BG_H_
#define _SUSHI_BG_H_

#include "scene3d.h"
#include "polygon3d.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURE_FLOOR		"Data/TEXTURE/FLOOR/bg001.png"

//=============================================================================
//�N���X��`
//=============================================================================
class CSushiBg : public CPolygon3d
{
public:
	CSushiBg(int nPriority = 3);
	~CSushiBg();

	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_BLOCK_001,
		TYPE_MAX,
	}TYPE;

	static CSushiBg * Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size);
	HRESULT			Init(void);
	void			Update(void);

private:
	int							m_nPatternAnim;			// �A�j���[�V�����p�^�[��
	int							m_nCountAnim;			// �A�j���[�V�����p�^�[��
	const int					m_nTexture = 80;			// �e�N�X�`���ԍ�
};
#endif


