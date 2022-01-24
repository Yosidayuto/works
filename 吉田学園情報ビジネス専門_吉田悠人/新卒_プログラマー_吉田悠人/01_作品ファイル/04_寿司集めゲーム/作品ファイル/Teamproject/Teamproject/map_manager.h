//=============================================================================
//
// �}�b�v�Ǘ� [map_manager.h]
// Author : �ѐ�ї���
//
//=============================================================================
#ifndef _MAP_MANAGER_H_
#define _MAP_MANAGER_H_
//=============================================================================
// �w�b�_�[�t�@�C��
//=============================================================================
#include "food base.h"
#include "item.h"
#include "game.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CLocationPoint;
class CMapEdgeMask;
class CFieldManager;

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************

class CMapManager : public CScene
{
public:
	CMapManager(int nPriority = 8);
	~CMapManager();

	static CMapManager *Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	float GetMapSize(void) { return m_MapSize.x; };
private:
	void SushiSpawn(void);				// ���i�̃����_�����������֐�
	void ItemSpawn(void);				// �A�C�e���̃����_�����������֐�

	D3DXVECTOR3 m_originPos;						//�}�b�v�̌��_�i������{0,0}�Ƃ���j
	CLocationPoint * m_pLocationPoint[MAX_PLAYER];	//���݈ʒu
	D3DXVECTOR3 m_MapSize;							//map�̃T�C�Y
	CMapEdgeMask * m_pMapEdgeMask;					//�}�X�N�|�C���^
	CFieldManager * m_pFieldManager;				//�t�B�[���h�|�C���^
	int m_nShrinkCount;								//���k������
	bool m_bShirnk;									//���k����

	int			m_nSushiSpawn;						// ���i�̃X�|�[�����鎞��
	int			m_nSpawnSushiCount;					// ���i�̃X�|�[�����鎞�Ԃ܂ł̃J�E���g
	static int	m_nSpawnItemCount[CGame::GAMESTATE_MAX];		// �A�C�e���̃X�|�[�����鎞�Ԃ܂ł̃J�E���g

	static int	m_nItemProb[CItem::ITEM_MAX];		// �ǂ̃A�C�e�����o�Ă��邩�̊m��
	static int	m_nMaxItemProb;						// �A�C�e���̍ő�m��
	static int	m_nSushiProb[CFoodBase::TYPE_MAX];	// �ǂ̎��i���o�Ă��邩�̊m��
	static int	m_nMaxSushiProb;					// ���i�̍ő�m��
	CGame::GAME_STATE m_GameState;					// �Q�[���̏��

};
#endif // !_MAP_MANAGER_H_


