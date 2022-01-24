//=============================================================================
//
//	プレイヤーパーツ[player parts.cpp]
//	Author:吉田悠人
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "player parts.h"
#include "resource manager.h"
#include "manager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PARENT_DISTANCE (5.0f)	//親パーツまでの距離
#define ROT_COUNT		(0.3f)	//振り向くまで

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayerParts::CPlayerParts(int nPriority):CBillboard(nPriority)
{
	m_pParent	= NULL;							//親パーツのポインタ初期化
	m_Move		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);//移動量初期化
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayerParts::~CPlayerParts()
{

}

//=============================================================================
// 更新処理関数
//=============================================================================
void CPlayerParts::Update(void)
{
	//追尾処理
	Tracking();
	//向き処理
	Rot();

}

//=============================================================================
// 親データセッター処理関数
//=============================================================================
void CPlayerParts::SetParent(CScene3d* pParent)
{
	m_pParent = pParent;
}

//=============================================================================
// 追尾処理関数
//=============================================================================
void CPlayerParts::Tracking(void)
{
	// 位置取得
	D3DXVECTOR3	pos	= GetPos();			
	//親パーツの位置
	D3DXVECTOR3 PartsPos = m_pParent->GetPos();
	//親パーツの向き
	D3DXVECTOR3 PartsRot = m_pParent->GetRot();
	//目標位置計算
	m_Move = PartsPos + 
		D3DXVECTOR3((float)(cos(PartsRot.y - D3DXToRadian(90.0f))*PARENT_DISTANCE),
			0.0f,
			(float)(sin(PartsRot.y + D3DXToRadian(90.0f))*PARENT_DISTANCE));
	
	//差分取得
	D3DXVECTOR3 Diff = D3DXVECTOR3(m_Move.x - pos.x, 0.0f, m_Move.z - pos.z);
	//移動処理
	pos = D3DXVECTOR3(pos.x + (Diff.x*0.5f), 0.0f, pos.z + (Diff.z*0.5f));
	//位置セット
	SetPos(pos);

}

//=============================================================================
// 向き処理関数
//=============================================================================
void CPlayerParts::Rot(void)
{
	//角度の移動量
	float fRotMove = 0.0f;
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//向き取得
	D3DXVECTOR3 rot = GetRot();
	//向きたい角度
	fRotMove = atan2f((pos.x - m_Move.x), (pos.z - m_Move.z));
	//差分の角度
	float fDiff = ((D3DXToRadian(180.0f) - (fRotMove*-1.0f)) - (D3DXToRadian(180.0f) - (rot.y*-1.0f)))*-1.0f;
	//回転方向の確認(時計周りtrue:反時計回りfalse)
	bool bRotation = fRotMove>rot.y ? !(fRotMove - rot.y > D3DXToRadian(180.0f)) : rot.y - fRotMove  > D3DXToRadian(180.0f);

	//向きの修正
	fDiff = (fDiff + (bRotation ? D3DXToRadian(-360.0f) : D3DXToRadian(360.0f)));
	fDiff = (float)(fmod(fDiff, D3DXToRadian(360.0f)));
	//向き処理
	rot.y = rot.y - (fDiff*ROT_COUNT);
	//角度が一定に達したら修正
	if (D3DXToDegree(rot.y) >= 360.0f
		|| D3DXToDegree(rot.y) <= -360.0f)
	{
		rot.y = 0.0f;
	}
	// 向き保存
	SetRot(rot);
}
