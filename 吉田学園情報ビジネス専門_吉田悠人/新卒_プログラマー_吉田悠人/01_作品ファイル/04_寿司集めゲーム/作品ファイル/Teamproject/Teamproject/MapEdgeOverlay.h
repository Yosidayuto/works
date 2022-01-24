//=============================================================================
//
// �}�b�v�[�|���S���i�G���A�O���j���� [MapEdgeOverlay.h]
// Author : �ѐ�ї���
//
//=============================================================================
#ifndef _MAP_EDGE_OVERLAY_H_
#define _MAP_EDGE_OVERLAY_H_

#include "scene3d.h"
#include "polygon3d.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
//�N���X��`
//=============================================================================
class CMapEdgeOverlay : public CPolygon3d
{
public:
	CMapEdgeOverlay(int nPriority = 3);
	~CMapEdgeOverlay();

	static CMapEdgeOverlay * Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	int							m_nPatternAnim;			// �A�j���[�V�����p�^�[��
	int							m_nCountAnim;			// �A�j���[�V�����p�^�[��
	const int					m_nTexture = 31;			// �e�N�X�`���ԍ�
};
#endif 


