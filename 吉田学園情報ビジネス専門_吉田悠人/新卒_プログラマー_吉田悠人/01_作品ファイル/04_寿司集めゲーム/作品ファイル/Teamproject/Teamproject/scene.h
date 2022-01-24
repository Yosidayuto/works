//=============================================================================
//
// �`�揈�� [scene.h]
// Author : �ѐ�ї���
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SCENE		 (10000)
#define PRIORITY_MAX	 (10)
#define DEFAULT_PRIORITY (3)
#define MAX_POLYGON   (10000)
#define NUM_VERTEX	  (4)
#define NUM_POLYGON	  (2)

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CScene
{
public:
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,
		OBJTYPE_SUSHI,
		OBJTYPE_MODEL,
		OBJTYPE_OBSTACLE,
		OBJTYPE_STAGE,
		OBJTYPE_ITEM
	} OBJTYPE;
	CScene(int nPriority = 0);
	virtual ~CScene();
	virtual HRESULT Init(void) = 0;  
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static void UpdateAll(void);    
	static void DrawAll(void);
	static void ReleaseAll(void);
	void SetObjType(OBJTYPE type);
	static CScene** GetTop(void);
	CScene* GetNext(void);
	CScene* GetPrev(void);
	OBJTYPE GetObjType(void);
protected:
	void Release(void); 
private:
	void Death(void);
	static CScene* m_pTop[PRIORITY_MAX];
	static CScene* m_pCur[PRIORITY_MAX];
	CScene* m_pPrev;
	CScene* m_pNext;
	int m_nPriority;
	bool m_bDestroy;
	OBJTYPE m_objType;
};

#endif