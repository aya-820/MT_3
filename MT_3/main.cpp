#include <Novice.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include <assert.h>
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4x4.h"

const char kWindowTitle[] = "GC2D_12_トミタ_アヤナ";

//平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate)
{
	Matrix4x4 result = {};

	for (int i = 0; i < 4; i++)
	{
		result.m[i][i] = 1;
	}

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;

	return result;
}
//拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale)
{

	Matrix4x4 result = {};

	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;
	result.m[3][3] = 1;

	return result;
}
//座標変更行列
Vector3 TransForm(const Vector3& vector, const Matrix4x4& matrix)
{
	Vector3 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.x * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.x * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.x * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.x * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}

//Matrix4x4の数値表示
Vector2 textWH = { 60,20 };
void MatrixScreenPrinsf(const Vector2& pos, const Matrix4x4& m, const char* label)
{
	Novice::ScreenPrintf((int)pos.x, (int)pos.y, "%s", label);
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			Novice::ScreenPrintf(
				(int)(pos.x + j * textWH.x), (int)(pos.y + (i + 1) * textWH.y),
				"%6.02f", m.m[i][j]
			);
		}
	}
}
void Vector3Printf(const Vector2& pos, const Vector3& v, const char* label)
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

	Vector3 translate = { 4.1f,2.6f,0.8f };
	Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);

	Vector3 scale = { 1.5f,5.2f,7.3f };
	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);

	Vector3 point = { 2.3f,3.8f,1.4f };
	Matrix4x4 transformMatrix = {
		1.0f,2.0f,3.0f,4.0f,
		3.0f,1.0f,1.0f,2.0f,
		1.0f,4.0f,2.0f,3.0f,
		2.0f,2.0f,1.0f,3.0f
	};
	Vector3 transformed = TransForm(point, transformMatrix);


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

		Vector3Printf({ 0,0 }, transformed, "transformed");
		MatrixScreenPrinsf({ 0,textWH.y }, transformMatrix, "transformMatrix");
		MatrixScreenPrinsf({ 0,textWH.y + (textWH.y * 5) }, scaleMatrix, "scaleMatrix");

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