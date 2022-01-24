//=============================================================================
//
// �}�b�v�[�|���S���i�}�X�N���j���� [MapEdgeMask.h]
// Author : �ѐ�ї���
//
//=============================================================================
#ifndef _MAP_EDGE_MASK_H_
#define _MAP_EDGE_MASK_H_

#include "scene3d.h"
#include "polygon3d.h"
//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
//�N���X��`
//=============================================================================
class CMapEdgeMask : public CPolygon3d
{
public:
	CMapEdgeMask(int nPriority = 3);
	~CMapEdgeMask();

	static CMapEdgeMask * Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	int							m_nPatternAnim;			// �A�j���[�V�����p�^�[��
	int							m_nCountAnim;			// �A�j���[�V�����p�^�[��
	const int					m_nTexture = 30;			// �e�N�X�`���ԍ�
};
#endif 


