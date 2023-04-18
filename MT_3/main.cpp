#include <Novice.h>
#define _USE_MATH_DEFINES
#include<math.h>

struct Vector3 final {
	float x;
	float y;
	float z;
};

struct Vector2 final {
	float x;
	float y;
};

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

	const Vector3 v1 = Vector3(1.0f, 3.0f, -5.0f);
	const Vector3 v2 = Vector3(4.0f, -1.0f, 2.0f);
	const float k = { 4.0f };

	const Vector2 textWH = { 100.0f,20.0f };

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

		Vector3 addResult = Add(v1, v2);
		Vector3 subResult = Subtract(v1, v2);
		Vector3 mulrResult = Multiply(k, v1);
		float dotResult = Dot(v1, v2);
		float lengthResult = Length(v1);
		Vector3 normalizeResult = Normalize(v1);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Vector3Printf({ 0.0f,0.0f }, addResult, textWH, "Add");
		Vector3Printf({ 0.0f,textWH.y }, subResult, textWH, "Subtract");
		Vector3Printf({ 0.0f,textWH.y * 2 }, mulrResult, textWH, "Multply");
		Novice::ScreenPrintf(0, (int)textWH.y * 3, "%.02f", dotResult);
		Novice::ScreenPrintf((int)textWH.x, (int)textWH.y * 3, ":Dot");
		Novice::ScreenPrintf(0, (int)textWH.y * 4, "%.02f", lengthResult);
		Novice::ScreenPrintf((int)textWH.x, (int)textWH.y * 4, ":Length");
		Vector3Printf({ 0.0f,textWH.y * 5 }, normalizeResult, textWH, "NOrmalize");

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
