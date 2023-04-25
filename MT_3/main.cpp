#include <Novice.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4x4.h"

const char kWindowTitle[] = "GC2D_12_トミタ_アヤナ";

Vector3 Add(const Vector3& v1, const Vector3& v2)
{
	Vector3 result =
	{
		v1.x + v2.x,
		v1.y + v2.y,
		v1.z + v2.z
	};

	return result;
}

Vector3 Subtract(const Vector3& v1, const Vector3& v2)
{
	Vector3 result =
	{
		v1.x - v2.x,
		v1.y - v2.y,
		v1.z - v2.z
	};

	return result;
}

Vector3 Multiply(float scalar, const Vector3& v)
{
	Vector3 result =
	{
		v.x * scalar,
		v.y * scalar,
		v.z * scalar
	};

	return result;
}

float Dot(const Vector3& v1, const Vector3& v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

float Length(const Vector3& v)
{
	return sqrtf(powf(v.x, 2) + powf(v.y, 2) + powf(v.z, 2));
}

Vector3 Normalize(const Vector3& v)
{
	Vector3 result =
	{
		v.x / Length(v),
		v.y / Length(v),
		v.z / Length(v)
	};

	return result;
}

void Vector3Printf(const Vector2& pos, const Vector3& v, const Vector2& textWH, const char* label)
{
	Novice::ScreenPrintf((int)pos.x, (int)pos.y, "x:%.02f,", v.x);
	Novice::ScreenPrintf((int)pos.x + (int)textWH.x, (int)pos.y, "y:%.02f,", v.y);
	Novice::ScreenPrintf((int)pos.x + ((int)textWH.x * 2), (int)pos.y, "z:%.02f", v.z);
	Novice::ScreenPrintf((int)pos.x + ((int)textWH.x * 3), (int)pos.y, ":%s", label);
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
