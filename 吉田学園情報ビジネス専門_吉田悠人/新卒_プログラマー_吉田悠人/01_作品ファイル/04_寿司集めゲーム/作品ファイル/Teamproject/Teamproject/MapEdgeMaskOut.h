//=============================================================================
//
// �}�b�v�[�|���S���i�}�b�v�O�̃}�X�N���j���� [MapEdgeMaskOut.h]
// Author : �ѐ�ї���
//
//=============================================================================
#ifndef _MAP_EDGE_MASK_OUT_H_
#define _MAP_EDGE_MASK_OUT_H_

#include "scene3d.h"
#include "polygon3d.h"
//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
//�N���X��`
//=============================================================================
class CMapEdgeMaskOut : public CPolygon3d
{
public:
	CMapEdgeMaskOut(int nPriority = 3);
	~CMapEdgeMaskOut();

	static CMapEdgeMaskOut * Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	int							m_nPatternAnim;			// �A�j���[�V�����p�^�[��
	int							m_nCountAnim;			// �A�j���[�V�����p�^�[��
	const int					m_nTexture = 32;			// �e�N�X�`���ԍ�
};
#endif 


