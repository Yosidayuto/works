//=============================================================================
//
// textureヘッダ [texture.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************
//インクルード
//*****************************
#include "main.h"

//*****************************
//クラス定義
//*****************************

//テクスチャクラス
class CResourceTexture
{
public:
	// 列挙
	// テクスチャ種類
	typedef enum
	{
		TEXTURE_TITLE = 0,			// タイトル
		TEXTURE_RESULT_KNIGHT,		// リザルト(ナイトの背景)
		TEXTURE_RESULT_LANCER,		// リザルト(ランサーの背景)
		TEXTURE_RESULT_WIZARD,		// リザルト(ウィザードの背景)
		TEXTURE_RESULT_THIEF,		// リザルト(シーフの背景)
		TEXTURE_RESULT_MAGICIAN,	// リザルト(奇術師の背景)
		TEXTURE_RESULT_ARCHER,		// リザルト(アーチャーの背景)
		TEXTURE_RESULT_KILL,		// リザルトのキルUI
		TEXTURE_RESULT_TILE,		// リザルトのタイルUI
		TEXTURE_PARTICLE_SQUARE,    // パーティクル*ダイヤ
		TEXTURE_PARTICLE_SKILL,		// パーティクル*波紋
		TEXTURE_PARTICLE_CIRCLE,	// パーティクル*円	
		TEXTURE_PARTICLE_ARROW,		// パーティクル*矢
		TEXTURE_PARTICLE_TRUMP,		// パーティクル*トランプ
		TEXTURE_PARTICLE_SHOOT,		// パーティクル*弓軌道
		TEXTURE_PARTICLE_METEOR,	// パーティクル*爆発
		TEXTURE_PARTICLE_METEOR_SHADOW,	// パーティクル*爆発
		TEXTURE_PARTICLE_SLASH,		// 斬撃エフェクト
		TEXTURE_PARTICLE_THUKI,
		TEXTURE_PARTICLE_GLITTER,	// キラキラエフェクト
		TEXTURE_PARTICLE_GURUGURU,	// ぐるぐる
		TEXTURE_NUMBER,				// ナンバー
		TEXTURE_FRAME,				// 枠
		TEXTURE_CROSS_MARK,			// ×マーク
		TEXTURE_NEEDLE,				// とげ穴
		TEXTURE_MOVE_TILE,			// 移動タイルのテクスチャ
		TEXTURE_WARP,				// ワープタイルのテクスチャ
		TEXTURE_SHADOW,				// 影
		TEXTURE_PLAYERNUMBER,		// プレイヤー番号
		TEXTURE_NONE_UI,			// NONE
		TEXTURE_CONTROLLER,			// コントローラーアイコン
		TEXTURE_KEYBOARD,			// キーボードアイコン
		TEXTURE_CHARASELECT_BACK,	// キャラ選択背景
		TEXTURE_BUTTON_START,		// タイトルのボタン(スタート)
		TEXTYRE_BUTTON_TUTORIAL,	// タイトルのボタン(チュートリアル)
		TEXTURE_MAX_COLOR_EFFECT,	// 最大塗段階時のエフェクト
		TEXTURE_ATTACK_AREA,		// 攻撃範囲
		TEXTURE_CLOCK_FRAME,		// 時計の枠
		TEXTURE_CLOCK_HANDS,		// 時計の針
		TEXTURE_TOON_SHADOW,		// トゥーンシャドウ
		TEXTURE_TILE_CHARGE,		// タイルのチャージ
		TEXTURE_ICON_BG,			// アイコンの背景
		TEXTURE_SWORD_ICON,		 	// 剣アイコン
		TEXTURE_STAGE_NAME_UI,		// ステージ名
		TEXTURE_STAGE_SELECT_BG,
		TEXTURE_READEY,				// ready
		TEXTURE_GO,					// go
		TEXTURE_FINISH,				// finish
		TEXTURE_SECONDS,			// 残り何秒
		TEXTURE_LANCE_ICON,		 	// 槍アイコン
		TEXTURE_ARROW_ICON,		 	// 矢アイコン
		TEXTURE_MAGICSTICK_ICON,	// 魔法杖アイコン
		TEXTURE_KNIFE_ICON,		 	// ナイフアイコン
		TEXTURE_STICK_ICON,		 	// 杖アイコン
		TEXTURE_RESULT_EXPLOSION,   // リザルト*エクスプロ―ジョン
		TEXTURE_COLOR_GAUGE,		// 色のゲージの枠
        TEXTURE_ATTACK_AREA_KNIGHT,      // 攻撃範囲
        TEXTURE_ATTACK_AREA_LANCER,      // 攻撃範囲
        TEXTURE_ATTACK_AREA_WIZARD,      // 攻撃範囲
        TEXTURE_ATTACK_AREA_THIEF,	     // 攻撃範囲
        TEXTURE_ATTACK_AREA_MAGICIAN,    // 攻撃範囲
        TEXTURE_ATTACK_AREA_ARCHER,      // 攻撃範囲
        TEXTURE_DIFFECULT_BEGINNER,    // 初心者
        TEXTURE_DIFFECULT_INTERMEDIATE,// 中級者
        TEXTURE_DIFFECULT_ADVANCED,    // 上級者
        TEXTURE_RANGE_SHORT,           // 近距離
        TEXTURE_RANGE_MEDIAM,          // 中距離
        TEXTURE_RANGE_LONG,            // 遠距離
        TEXTURE_NAVI_ATTACK_AREA,      // 攻撃範囲表示誘導UI
		TEXTURE_TUTRIAL_TEXT,          // チュートリアルで表示するテキスト
		TEXTURE_CHECK,				   // チェック
        TEXTURE_CHARACTER_NAME_KNIGHT,   // キャラクターネーム*騎士
        TEXTURE_CHARACTER_NAME_LANCER,   // キャラクターネーム*槍
        TEXTURE_CHARACTER_NAME_WIZARD,   // キャラクターネーム*魔法
        TEXTURE_CHARACTER_NAME_THIEF,    // キャラクターネーム*盗賊
        TEXTURE_CHARACTER_NAME_MAGICIAN, // キャラクターネーム*奇術
        TEXTURE_CHARACTER_NAME_ARCHER,   // キャラクターネーム*弓
		TEXTURE_PAINTGUIDE,				 // 塗り説明用
		TEXTURE_ATTACKGUIDE,			 // 攻撃説明用
		TEXTURE_FINALATTACKGUIDE,		 // 必殺技説明用
		TEXTURE_TITLEBACK,				 // タイトル戻る用
		TEXTURE_MAX					// テクスチャ数
	}TEXTURE_TYPE;
	// テクスチャ種類
	typedef enum
	{
		TEXTURE_CUBE_SLY,        // キューブテクスチャ(空)
		TEXTURE_CUBE_MAX              // テクスチャ数
	}TEXTURE_CUBE_TYPE;

	// メンバ関数
	static CResourceTexture * Create(void);                  // クラス生成
	static void Release(void);                               // クラス破棄
	static LPDIRECT3DTEXTURE9 GetTexture(TEXTURE_TYPE type); // テクスチャの取得処理*引数：取得したいテクスチャ
	static LPDIRECT3DCUBETEXTURE9 GetCubeTexture(TEXTURE_CUBE_TYPE type); // テクスチャの取得処理*引数：取得したいテクスチャ
private:
	CResourceTexture();//隠しコンストラクタ
public:
	~CResourceTexture();

private:
	void Load(void); // テクスチャ読み込み
	void Unload(void); // テクスチャ破棄

	// メンバ変数
	static const std::string m_aTexPath[TEXTURE_MAX]; // テクスチャのパス
	static const std::string m_aCubeTexPath[TEXTURE_CUBE_MAX]; // テクスチャのパス
	static CResourceTexture *m_pSingleTex;			  // テクスチャクラスのポインタ*シングルトン用
	LPDIRECT3DTEXTURE9 m_apTexture[TEXTURE_MAX];      // テクスチャのポインタ
	LPDIRECT3DCUBETEXTURE9 m_apCubeTexture[TEXTURE_CUBE_MAX];      // テクスチャのポインタ
};

#endif