#include <Novice.h>
#define _USE_MATH_DEFINES
#include<cmath>
#include<math.h>
#include <assert.h>
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4x4.h"

const char kWindowTitle[] = "GC2D_12_トミタ_アヤナ";

///
///Vector3関数
/// 
//加法
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
//減法
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
//スカラー積
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
//内積
float Dot(const Vector3& v1, const Vector3& v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}
//長さ
float Length(const Vector3& v)
{
	return sqrtf(powf(v.x, 2) + powf(v.y, 2) + powf(v.z, 2));
}
//正規化
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
//画面出力
void Vector3Printf(const Vector2& pos, const Vector3& v, const Vector2& textWH, const char* label)
{
	Novice::ScreenPrintf((int)pos.x, (int)pos.y, "x:%.02f,", v.x);
	Novice::ScreenPrintf((int)pos.x + (int)textWH.x, (int)pos.y, "y:%.02f,", v.y);
	Novice::ScreenPrintf((int)pos.x + ((int)textWH.x * 2), (int)pos.y, "z:%.02f", v.z);
	Novice::ScreenPrintf((int)pos.x + ((int)textWH.x * 3), (int)pos.y, ":%s", label);
}


///
///Matrix4x4関数
/// 
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
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}

//加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}

	return result;
}
//減法
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[i][j] = m1.m[i][j] - m2.m[i][j];
		}
	}

	return result;
}
//行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[i][j] = m1.m[i][0] * m2.m[0][j] + m1.m[i][1] * m2.m[1][j] + m1.m[i][2] * m2.m[2][j] + m1.m[i][3] * m2.m[3][j];
		}
	}

	return result;
}
//逆行列
Matrix4x4 Inverse(const Matrix4x4& m1)
{
	Matrix4x4 result;
	float deteminant = {
		  m1.m[0][0] * m1.m[1][1] * m1.m[2][2] * m1.m[3][3]
		+ m1.m[0][0] * m1.m[1][2] * m1.m[2][3] * m1.m[3][1]
		+ m1.m[0][0] * m1.m[1][3] * m1.m[2][1] * m1.m[3][2]
		- m1.m[0][0] * m1.m[1][3] * m1.m[2][2] * m1.m[3][1]
		- m1.m[0][0] * m1.m[1][2] * m1.m[2][1] * m1.m[3][3]
		- m1.m[0][0] * m1.m[1][1] * m1.m[2][3] * m1.m[3][2]
		- m1.m[0][1] * m1.m[1][0] * m1.m[2][2] * m1.m[3][3]
		- m1.m[0][2] * m1.m[1][0] * m1.m[2][3] * m1.m[3][1]
		- m1.m[0][3] * m1.m[1][0] * m1.m[2][1] * m1.m[3][2]
		+ m1.m[0][3] * m1.m[1][0] * m1.m[2][2] * m1.m[3][1]
		+ m1.m[0][2] * m1.m[1][0] * m1.m[2][1] * m1.m[3][3]
		+ m1.m[0][1] * m1.m[1][0] * m1.m[2][3] * m1.m[3][2]
		+ m1.m[0][1] * m1.m[1][2] * m1.m[2][0] * m1.m[3][3]
		+ m1.m[0][2] * m1.m[1][3] * m1.m[2][0] * m1.m[3][1]
		+ m1.m[0][3] * m1.m[1][1] * m1.m[2][0] * m1.m[3][2]
		- m1.m[0][3] * m1.m[1][2] * m1.m[2][0] * m1.m[3][1]
		- m1.m[0][2] * m1.m[1][1] * m1.m[2][0] * m1.m[3][3]
		- m1.m[0][1] * m1.m[1][3] * m1.m[2][0] * m1.m[3][2]
		- m1.m[0][1] * m1.m[1][2] * m1.m[2][3] * m1.m[3][0]
		- m1.m[0][2] * m1.m[1][3] * m1.m[2][1] * m1.m[3][0]
		- m1.m[0][3] * m1.m[1][1] * m1.m[2][2] * m1.m[3][0]
		+ m1.m[0][3] * m1.m[1][2] * m1.m[2][1] * m1.m[3][0]
		+ m1.m[0][2] * m1.m[1][1] * m1.m[2][3] * m1.m[3][0]
		+ m1.m[0][1] * m1.m[1][3] * m1.m[2][2] * m1.m[3][0] };
	assert(deteminant != 0.0f);
	float deteminantRecp = 1.0f / deteminant;

	result.m[0][0] = { (
		  m1.m[1][1] * m1.m[2][2] * m1.m[3][3]
		+ m1.m[1][2] * m1.m[2][3] * m1.m[3][1]
		+ m1.m[1][3] * m1.m[2][2] * m1.m[3][1]
		- m1.m[1][3] * m1.m[2][2] * m1.m[3][1]
		- m1.m[1][2] * m1.m[2][1] * m1.m[3][3]
		- m1.m[1][1] * m1.m[2][3] * m1.m[3][2])
		* deteminantRecp };
	result.m[0][1] = { -(
		  m1.m[0][1] * m1.m[2][2] * m1.m[3][3]
		+ m1.m[0][2] * m1.m[2][3] * m1.m[3][1]
		+ m1.m[0][3] * m1.m[2][1] * m1.m[3][2]
		- m1.m[0][3] * m1.m[2][2] * m1.m[3][1]
		- m1.m[0][2] * m1.m[2][1] * m1.m[3][3]
		- m1.m[0][1] * m1.m[2][3] * m1.m[3][2])
		* deteminantRecp };
	result.m[0][2] = { (
		  m1.m[0][1] * m1.m[1][2] * m1.m[3][3]
		+ m1.m[0][2] * m1.m[1][3] * m1.m[3][1]
		+ m1.m[0][3] * m1.m[1][1] * m1.m[3][2]
		- m1.m[0][3] * m1.m[1][2] * m1.m[3][1]
		- m1.m[0][2] * m1.m[1][1] * m1.m[3][3]
		- m1.m[0][1] * m1.m[1][3] * m1.m[3][2])
		* deteminantRecp };
	result.m[0][3] = { -(
		  m1.m[0][1] * m1.m[1][2] * m1.m[2][3]
		+ m1.m[0][2] * m1.m[1][3] * m1.m[2][1]
		+ m1.m[0][3] * m1.m[1][1] * m1.m[2][2]
		- m1.m[0][3] * m1.m[1][2] * m1.m[2][1]
		- m1.m[0][2] * m1.m[1][1] * m1.m[2][3]
		- m1.m[0][1] * m1.m[1][3] * m1.m[2][2])
		* deteminantRecp };
	result.m[1][0] = { -(
		  m1.m[1][0] * m1.m[2][2] * m1.m[2][3]
		+ m1.m[1][2] * m1.m[2][3] * m1.m[2][0]
		+ m1.m[1][3] * m1.m[2][0] * m1.m[2][2]
		- m1.m[1][3] * m1.m[2][2] * m1.m[2][0]
		- m1.m[1][2] * m1.m[2][0] * m1.m[2][3]
		- m1.m[1][0] * m1.m[2][3] * m1.m[2][2])
		* deteminantRecp };
	result.m[1][1] = { (
		  m1.m[0][0] * m1.m[2][2] * m1.m[3][3]
		+ m1.m[0][2] * m1.m[2][3] * m1.m[3][0]
		+ m1.m[0][3] * m1.m[2][0] * m1.m[3][2]
		- m1.m[0][3] * m1.m[2][2] * m1.m[3][0]
		- m1.m[0][2] * m1.m[2][0] * m1.m[3][3]
		- m1.m[0][0] * m1.m[2][3] * m1.m[3][2])
		* deteminantRecp };
	result.m[1][2] = { -(
		  m1.m[0][0] * m1.m[1][2] * m1.m[3][3]
		+ m1.m[0][2] * m1.m[1][3] * m1.m[3][0]
		+ m1.m[0][3] * m1.m[1][0] * m1.m[3][2]
		- m1.m[0][3] * m1.m[1][2] * m1.m[3][0]
		- m1.m[0][2] * m1.m[1][0] * m1.m[3][3]
		- m1.m[0][0] * m1.m[1][3] * m1.m[3][2])
		* deteminantRecp };
	result.m[1][3] = { (
		  m1.m[0][0] * m1.m[1][2] * m1.m[2][3]
		+ m1.m[0][2] * m1.m[1][3] * m1.m[2][0]
		+ m1.m[0][3] * m1.m[1][0] * m1.m[2][2]
		- m1.m[0][3] * m1.m[1][2] * m1.m[2][0]
		- m1.m[0][2] * m1.m[1][0] * m1.m[2][3]
		- m1.m[0][0] * m1.m[1][3] * m1.m[2][2])
		* deteminantRecp };
	result.m[2][0] = { (
		  m1.m[1][0] * m1.m[2][1] * m1.m[3][3]
		+ m1.m[1][1] * m1.m[2][3] * m1.m[3][0]
		+ m1.m[1][3] * m1.m[2][0] * m1.m[3][1]
		- m1.m[1][3] * m1.m[2][1] * m1.m[3][0]
		- m1.m[1][1] * m1.m[2][0] * m1.m[3][3]
		- m1.m[1][0] * m1.m[2][3] * m1.m[3][1])
		* deteminantRecp };
	result.m[2][1] = { -(
		  m1.m[0][0] * m1.m[2][1] * m1.m[3][3]
		+ m1.m[0][1] * m1.m[2][3] * m1.m[3][0]
		+ m1.m[0][3] * m1.m[2][0] * m1.m[3][1]
		- m1.m[0][3] * m1.m[2][1] * m1.m[3][0]
		- m1.m[0][1] * m1.m[2][0] * m1.m[3][3]
		- m1.m[0][0] * m1.m[2][3] * m1.m[3][1])
		* deteminantRecp };
	result.m[2][2] = { (
		  m1.m[0][0] * m1.m[1][1] * m1.m[3][3]
		+ m1.m[0][1] * m1.m[1][3] * m1.m[3][0]
		+ m1.m[0][3] * m1.m[1][0] * m1.m[3][1]
		- m1.m[0][3] * m1.m[1][1] * m1.m[3][0]
		- m1.m[0][1] * m1.m[1][0] * m1.m[3][3]
		- m1.m[0][0] * m1.m[1][3] * m1.m[3][1])
		* deteminantRecp };
	result.m[2][3] = { -(
		  m1.m[0][0] * m1.m[1][1] * m1.m[2][3]
		+ m1.m[0][1] * m1.m[1][3] * m1.m[2][0]
		+ m1.m[0][3] * m1.m[1][0] * m1.m[2][1]
		- m1.m[0][3] * m1.m[1][1] * m1.m[2][0]
		- m1.m[0][1] * m1.m[1][0] * m1.m[2][3]
		- m1.m[0][0] * m1.m[1][3] * m1.m[2][1])
		* deteminantRecp };
	result.m[3][0] = { -(
		  m1.m[1][0] * m1.m[2][1] * m1.m[3][2]
		+ m1.m[1][1] * m1.m[2][2] * m1.m[3][0]
		+ m1.m[1][2] * m1.m[2][0] * m1.m[3][1]
		- m1.m[1][2] * m1.m[2][1] * m1.m[3][0]
		- m1.m[1][1] * m1.m[2][0] * m1.m[3][2]
		- m1.m[1][0] * m1.m[2][2] * m1.m[3][1])
		* deteminantRecp };
	result.m[3][1] = { (
		  m1.m[0][0] * m1.m[2][1] * m1.m[3][2]
		+ m1.m[0][1] * m1.m[2][2] * m1.m[3][0]
		+ m1.m[0][2] * m1.m[2][0] * m1.m[3][1]
		- m1.m[0][2] * m1.m[2][1] * m1.m[3][0]
		- m1.m[0][1] * m1.m[2][0] * m1.m[3][2]
		- m1.m[0][0] * m1.m[2][2] * m1.m[3][1])
		* deteminantRecp };
	result.m[3][2] = { -(
		  m1.m[0][0] * m1.m[1][1] * m1.m[3][2]
		+ m1.m[0][1] * m1.m[1][2] * m1.m[3][0]
		+ m1.m[0][2] * m1.m[1][0] * m1.m[3][1]
		- m1.m[0][2] * m1.m[1][1] * m1.m[3][0]
		- m1.m[0][1] * m1.m[1][0] * m1.m[3][2]
		- m1.m[0][0] * m1.m[1][2] * m1.m[3][1])
		* deteminantRecp };
	result.m[3][3] = { (
		  m1.m[0][0] * m1.m[1][1] * m1.m[2][2]
		+ m1.m[0][1] * m1.m[1][2] * m1.m[2][0]
		+ m1.m[0][2] * m1.m[1][0] * m1.m[2][1]
		- m1.m[0][2] * m1.m[1][1] * m1.m[2][0]
		- m1.m[0][1] * m1.m[1][0] * m1.m[2][2]
		- m1.m[0][0] * m1.m[1][2] * m1.m[2][1])
		* deteminantRecp };

	return result;
}
//転置行列
Matrix4x4 Transpose(const Matrix4x4& m1)
{
	Matrix4x4 result;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[i][j] = m1.m[j][i];
		}
	}

	return result;
}
//単位行列の作成
Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 result;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
			{
				result.m[i][j] = 1;
			}
			else
			{
				result.m[i][j] = 0;
			}
		}
	}

	return result;
}

//回転行列
//X軸
Matrix4x4 MakeRotateXMatrix(const float& radian)
{
	Matrix4x4 result = {};

	result.m[0][0] = 1.0f;
	result.m[3][3] = 1.0f;

	result.m[1][1] = std::cosf(radian);
	result.m[1][2] = std::sinf(radian);
	result.m[2][1] = -std::sinf(radian);
	result.m[2][2] = std::cosf(radian);

	return result;
}
//Y軸
Matrix4x4 MakeRotateYMatrix(const float& radian)
{
	Matrix4x4 result = {};

	result.m[1][1] = 1.0f;
	result.m[3][3] = 1.0f;

	result.m[0][0] = std::cosf(radian);
	result.m[0][2] = -std::sinf(radian);
	result.m[2][0] = std::sinf(radian);
	result.m[2][2] = std::cosf(radian);

	return result;
}
//Z軸
Matrix4x4 MakeRotateZMatrix(const float& radian)
{
	Matrix4x4 result = {};

	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;

	result.m[0][0] = std::cosf(radian);
	result.m[0][1] = std::sinf(radian);
	result.m[1][0] = -std::sinf(radian);
	result.m[1][1] = std::cosf(radian);

	return result;
}
//XYZを融合
Matrix4x4 MakeRotateXYZMatrix(const Matrix4x4& rotateX, const Matrix4x4& rotateY, const Matrix4x4& rotateZ)
{
	return	Multiply(rotateX, Multiply(rotateY, rotateZ));
}

//アフィン変換
Matrix4x4 MakeAfiineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate)
{
	Matrix4x4 scaleMatrix = {};
	scaleMatrix.m[0][0] = scale.x;
	scaleMatrix.m[1][1] = scale.y;
	scaleMatrix.m[2][2] = scale.z;
	scaleMatrix.m[3][3]=1.0f;

	Matrix4x4 rotateMatrixX = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateMatrixY = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateMatrixZ = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateMatrix = MakeRotateXYZMatrix(rotateMatrixX, rotateMatrixY, rotateMatrixZ);

	Matrix4x4 translateMatrix = {};
	for (int i = 0; i < 4; i++)
	{
		translateMatrix.m[i][i] = 1.0f;
	}
	translateMatrix.m[3][0] = translate.x;
	translateMatrix.m[3][1] = translate.y;
	translateMatrix.m[3][2] = translate.z;

	return Multiply(scaleMatrix, Multiply(rotateMatrix, translateMatrix));
}

//レンダリングパイプライン
//透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY,float aspectRatio,float nearClip,float farClip)
{
	Matrix4x4 perspectiveMatrix = {};
	perspectiveMatrix.m[0][0];

}
//正射影行列
Matrix4x4 MakeOrthographicMatrix(float left,float top,float right,float bottom,float nearClip,float farClip)
{}
//ビューポート行列	
Matrix4x4 MakeViewportMatrix(float left, float top, float width,float height,float minDepth,float maxDepth)
{}

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