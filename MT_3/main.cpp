#include <Novice.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include "Matrix4x4.h"
#include "Vector2.h"

const char kWindowTitle[] = "GC2D_12_トミタ_アヤナ";

//1.行列の加法
Matrix4x4 Add()
{

}
//2.行列の減法
Matrix4x4 Subtract()
{

}
//3.行列の積
Matrix4x4 Multtply()
{

}
//4.逆行列
Matrix4x4 Inverse()
{

}
//5.転置行列
Matrix4x4 Transpote()
{

}
//6.単位行列の作成
Matrix4x4 MakeIdentity4x4()
{

}

//Matrix4x4の数値表示
void MatrixPrintf4x4(const Vector2& pos, const Matrix4x4& m)
{

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
