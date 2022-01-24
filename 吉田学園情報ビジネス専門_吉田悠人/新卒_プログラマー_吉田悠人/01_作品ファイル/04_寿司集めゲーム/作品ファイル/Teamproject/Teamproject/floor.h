//=============================================================================
//
// ������ [floor.h]
// Author : �ѐ�ї���
//
//=============================================================================
#ifndef _FLOOR_H_
#define _FLOOR_H_

#include "scene3d.h"
#include "polygon3d.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURE_FLOOR		"Data/TEXTURE/FLOOR/bg001.png"

//=============================================================================
//�N���X��`
//=============================================================================
class CFloor : public CPolygon3d
{
public:
	CFloor(int nPriority = 3);
	~CFloor();

	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_BLOCK_001,
		TYPE_MAX,
	}TYPE;

	static CFloor * Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size);
	HRESULT			Init(void);

private:
	int							m_nPatternAnim;			// �A�j���[�V�����p�^�[��
	int							m_nCountAnim;			// �A�j���[�V�����p�^�[��
	const int					m_nTexture = 1;			// �e�N�X�`���ԍ�
};
#endif


