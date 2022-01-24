#ifndef _NUMBER_H_
#define _NUMBER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#define TEXTURE_NUMBER	 "Data/TEXTURE/UI/number.png"

//*****************************************************************************
// クラス定義
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
	int                       m_nPatternAnim;//テクスチャパターン
	int                       m_nAlpha;//透明度
	bool                       m_bShow;//Drawするか
	const int m_nTexture = 20;		// テクスチャ番号
};

#endif // !_NUMBER_H_