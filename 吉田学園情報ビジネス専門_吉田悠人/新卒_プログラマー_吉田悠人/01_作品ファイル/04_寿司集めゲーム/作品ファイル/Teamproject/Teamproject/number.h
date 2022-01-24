#ifndef _NUMBER_H_
#define _NUMBER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#define TEXTURE_NUMBER	 "Data/TEXTURE/UI/number.png"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CNumber
{
public:
	CNumber();
	~CNumber();
	static CNumber * Create(D3DXVECTOR3 pos, float fSizeWidth, float fSizeHeight);
	HRESULT Init(D3DXVECTOR3 pos, float fSizeWidth, float fSizeHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNumber(int nNumber);
	void ShowNumber(bool show);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9   m_pVtxBuff;
	int                       m_nPatternAnim;//�e�N�X�`���p�^�[��
	int                       m_nAlpha;//�����x
	bool                       m_bShow;//Draw���邩
	const int m_nTexture = 20;		// �e�N�X�`���ԍ�
};

#endif // !_NUMBER_H_