//=============================================================================
//
//	2D�|���S��[object2d.cpp]
//	Author:�g�c�I�l
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "object2d.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FADE_RATE 0.1f

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CObject2D::CObject2D(int nPriority)
  : CObject(nPriority)
{
    m_pTexture = NULL;    // �e�N�X�`���ւ̃|�C���^
    m_pVtxBuff = NULL;    // ���_�o�b�t�@�ւ̃|�C���^

    m_pos  = D3DXVECTOR3(0, 0, 0);    // �|���S���̈ʒu
	m_size = D3DXVECTOR3(0, 0, 0);    // �|���S���̃T�C�Y
    m_fRot = 0.0f;
    m_col  = D3DCOLOR_RGBA(255, 255, 255, 255);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObject2D::~CObject2D()
{
}

//=============================================================================
// ��������
//=============================================================================
CObject2D* CObject2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float frot, LPDIRECT3DTEXTURE9 pTexture, int nPriority)
{
	CObject2D* pScene2d = NULL;
	pScene2d = new CObject2D(nPriority);
	//�ʒu�ݒ�
	pScene2d->SetPos(pos);
	//�傫���ݒ�
	pScene2d->SetSize(size);
	//�����ݒ�
	pScene2d->SetRot(frot);
	//�e�N�X�`���̐ݒ�
	pScene2d->BindTexture(pTexture);
	//����������
	pScene2d->Init();

	return pScene2d;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CObject2D::Init(void)
{
    VERTEX_2D* pVtx;
    LPDIRECT3DDEVICE9 pDevice = NULL;
    pDevice                   = CManager::GetRenderer()->GetDevice();

    //���_�o�b�t�@�̐���
    pDevice->CreateVertexBuffer(
      sizeof(VERTEX_2D) * NUM_VERTEX,    //�o�b�t�@�T�C�Y
      D3DUSAGE_WRITEONLY,                //�Œ�
      FVF_VERTEX_2D,                     //���_�t�H�[�}�b�g
      D3DPOOL_MANAGED,                   //�Œ�
      &m_pVtxBuff,                       //�ϐ����ɂ���ĕω�
      NULL);

    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    //���_����ݒ�
    pVtx[0].pos = m_pos + D3DXVECTOR3((float)-m_size.x / 2, (float)-m_size.y / 2, 0.0f);
    pVtx[1].pos = m_pos + D3DXVECTOR3((float)m_size.x / 2, (float)-m_size.y / 2, 0.0f);
    pVtx[2].pos = m_pos + D3DXVECTOR3((float)-m_size.x / 2, (float)m_size.y / 2, 0.0f);
    pVtx[3].pos = m_pos + D3DXVECTOR3((float)m_size.x / 2, (float)m_size.y / 2, 0.0f);

    //�e�N�X�`�����W�̐ݒ�
    pVtx[0].tex = D3DXVECTOR2(0, 0);
    pVtx[1].tex = D3DXVECTOR2(1, 0);
    pVtx[2].tex = D3DXVECTOR2(0, 1);
    pVtx[3].tex = D3DXVECTOR2(1, 1);

    //rhw�̐ݒ�
    pVtx[0].rhw = 1.0f;
    pVtx[1].rhw = 1.0f;
    pVtx[2].rhw = 1.0f;
    pVtx[3].rhw = 1.0f;

    //���_�J���[�̐ݒ�(0�`255)
    pVtx[0].col = m_col;    //a�͓����x
    pVtx[1].col = m_col;    //a�͓����x
    pVtx[2].col = m_col;    //a�͓����x
    pVtx[3].col = m_col;    //a�͓����x

    m_pVtxBuff->Unlock();
    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CObject2D::Uninit(void)
{
    // ���_�o�b�t�@�̔j��
    if(m_pVtxBuff != NULL)
    {
        m_pVtxBuff->Release();
        m_pVtxBuff = NULL;
    }
    Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CObject2D::Update(void)
{
    D3DXMATRIX posMatrix;       // ���_�s��
    D3DXMATRIX rotateMatrix;    // ��]�s��
    VERTEX_2D* pVtx;

    //�s��̏������i�P�ʍs�񐶐��j
    D3DXMatrixIdentity(&posMatrix);
    D3DXMatrixIdentity(&rotateMatrix);

    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	Fade2d();

	//���_���W�X�V
	pVtx[0].pos = D3DXVECTOR3((float)-m_size.x / 2, (float)-m_size.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3((float)m_size.x / 2, (float)-m_size.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3((float)-m_size.x / 2, (float)m_size.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3((float)m_size.x / 2, (float)m_size.y / 2, 0.0f);

    //���_�J���[�X�V
    pVtx[0].col = m_col;
    pVtx[1].col = m_col;
    pVtx[2].col = m_col;
    pVtx[3].col = m_col;

    m_pVtxBuff->Unlock();

    //��]�s�񐶐�
    D3DXMatrixRotationZ(&rotateMatrix, D3DXToRadian(m_fRot));

    for(int nCount = 0; nCount < NUM_VERTEX; nCount++)
    {
        //���_���W���s��ɕϊ�
        D3DXMatrixTranslation(&posMatrix, pVtx[nCount].pos.x, pVtx[nCount].pos.y, pVtx[nCount].pos.z);
        //��]�s����s��ɂ�����
        posMatrix *= rotateMatrix;
        //��]��̍��W�𒸓_���W�ɓ����
        pVtx[nCount].pos.x = posMatrix._41;
        pVtx[nCount].pos.y = posMatrix._42;
        pVtx[nCount].pos.z = posMatrix._43;
        //m_pos���ړ�������
        pVtx[nCount].pos += m_pos;
    }
}

//=============================================================================
// �`�揈��
//=============================================================================
void CObject2D::Draw(void)
{
    LPDIRECT3DDEVICE9 pDevice = NULL;
    pDevice                   = CManager::GetRenderer()->GetDevice();
    //���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
    //���_�t�H�[�}�b�g�̐ݒ�
    pDevice->SetFVF(FVF_VERTEX_2D);
    //�e�N�X�`���̐ݒ�
    pDevice->SetTexture(0, m_pTexture);
    //�|���S���̕`��
    pDevice->DrawPrimitive(
      D3DPT_TRIANGLESTRIP,	//�v���e�B�u�̎��
      0,
      NUM_POLYGON			//�v���e�B�u�̐�
    );
}

//=============================================================================
// �ʒu�Z�b�^�[�֐�
//=============================================================================
void CObject2D::SetPos(D3DXVECTOR3 pos)
{
    m_pos = pos;
}

//=============================================================================
// �T�C�Y�Z�b�^�[�֐�
//=============================================================================
void CObject2D::SetSize(D3DXVECTOR3 size)
{
    m_size = size;
}

//=============================================================================
// �����Z�b�^�[�֐�
//=============================================================================
void CObject2D::SetRot(float rot)
{
    m_fRot = rot;
}

//=============================================================================
// �e�N�X�`���Z�b�^�[�֐�
//=============================================================================
void CObject2D::SetTexPos(D3DXVECTOR2* pTexPos)
{
    VERTEX_2D* pVtx;
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
    for(int nCount = 0; nCount < NUM_VERTEX; nCount++)
    {
        pVtx[nCount].tex = *(pTexPos + nCount);
    }
    m_pVtxBuff->Unlock();
}

//=============================================================================
// �t�F�[�h����
//=============================================================================
void CObject2D::Fade2d(void)
{
	//�t�F�[�h������
	if (m_fade != FADE_NONE)
	{
		//�t�F�[�h�C������
		if (m_fade == FADE_IN)
		{
			m_col.a -= FADE_RATE;//���l�����Z���Č��̉�ʂ𕂂��オ�点��

			if (m_col.a <= 0.0f)
			{
				m_col.a = 0.0f;
				//�t�F�[�h�����I��
				m_fade = FADE_NONE;
			}
		}
		//�t�F�[�h�A�E�g����
		else if (m_fade == FADE_OUT)
		{
			m_col.a += FADE_RATE;//���l�����Z���Č��̉�ʂ������Ă���

			if (m_col.a >= 1.0f)
			{
				m_col.a = 1.0f;
				//�t�F�[�h�C�������ɐ؂�ւ�
				m_fade = FADE_IN;
			}
		}
	}
}

//=============================================================================
// �J���[�Z�b�^�[�֐�
//=============================================================================
void CObject2D::SetCol(D3DCOLOR col)
{
    m_col = col;
}

//=============================================================================
// �ʒu�Q�b�^�[�֐�
//=============================================================================
D3DXVECTOR3 CObject2D::GetPos(void)
{
    return m_pos;
}

//=============================================================================
// �T�C�Y�Q�b�^�[�֐�
//=============================================================================
D3DXVECTOR3 CObject2D::GetSize(void)
{
    return m_size;
}

//=============================================================================
// �T�C�Y�Q�b�^�[�֐�
//=============================================================================
D3DCOLOR CObject2D::GetCol(void)
{
	return m_col;
}

//=============================================================================
// �����Q�b�^�[�֐�
//=============================================================================
float CObject2D::GetRot(void)
{
	return m_fRot;
}

//=============================================================================
//�e�N�X�`���̃Z�b�g�֐�
//=============================================================================
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
    m_pTexture = pTexture;
}
