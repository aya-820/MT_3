#include <Novice.h>
#define _USE_MATH_DEFINES
#include<cmath>
#include<math.h>
#include <assert.h>
#include<imgui.h>
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4x4.h"

const char kWindowTitle[] = "GC2D_12_トミタ_アヤナ";

const Vector2 kWindow = { 1280,720 };

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
//Matrix4x4の数値表示
Vector2 textWH = { 80,20 };
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
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix)
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
	scaleMatrix.m[3][3] = 1.0f;

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
//正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip)
{
	Matrix4x4 orthogeraphicMatrix = {};

	orthogeraphicMatrix.m[0][0] = 2 / (right - left);
	orthogeraphicMatrix.m[1][1] = 2 / (top - bottom);
	orthogeraphicMatrix.m[2][2] = 1 / (farClip - nearClip);
	orthogeraphicMatrix.m[3][0] = (left + right) / (left - right);
	orthogeraphicMatrix.m[3][1] = (top + bottom) / (bottom - top);
	orthogeraphicMatrix.m[3][2] = nearClip / (nearClip - farClip);
	orthogeraphicMatrix.m[3][3] = 1.0f;

	return orthogeraphicMatrix;
}
//透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip)
{
	Matrix4x4 perspectiveFovMatrix = {};

	perspectiveFovMatrix.m[0][0] = (1 / tanf(fovY / 2)) / aspectRatio;
	perspectiveFovMatrix.m[1][1] = 1 / tanf(fovY / 2);
	perspectiveFovMatrix.m[2][2] = farClip / (farClip - nearClip);
	perspectiveFovMatrix.m[3][2] = (-farClip * nearClip) / (farClip - nearClip);
	perspectiveFovMatrix.m[2][3] = 1.0f;

	return perspectiveFovMatrix;
}
//ビューポート行列	
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth)
{
	Matrix4x4 viewportMatrix = {};

	viewportMatrix.m[0][0] = width / 2;
	viewportMatrix.m[1][1] = -height / 2;
	viewportMatrix.m[2][2] = maxDepth - minDepth;
	viewportMatrix.m[3][0] = left + (width / 2);
	viewportMatrix.m[3][1] = top + (height / 2);
	viewportMatrix.m[3][2] = minDepth;
	viewportMatrix.m[3][3] = 1.0f;

	return viewportMatrix;
}

//スクリーン座標系へ変換
Vector3 renderingPipeline(const Vector3& rotate, const  Vector3& translate, const Vector3& cameraTranslate, const Vector3& cameraRotate)
{
	//ワールド変換行列を作る
	Matrix4x4 worldMatrix = MakeAfiineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);

	//ビュー変換行列を作るためにカメラポジションで行列作成
	Matrix4x4 cameraMatrix = MakeAfiineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);

	//↑のカメラ行列を反転してビュー座標系変換行列を作る
	Matrix4x4 viewMatrix = Inverse(cameraMatrix);

	//透視投影行列を作る
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindow.x) / float(kWindow.y), 0.1f, 100.0f);

	//ビュー変換行列と透視投影を掛けてワールド座標系→ビュー座標系→透視投影座標系への変換行列を作る
	Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));

	//ビューポート行列を作る
	Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindow.x), float(kWindow.y), 0.0f, 1.0f);

	//スクリーン座標系へ変換
	//Transfarmを使うと同次座標系→デカルト座標系の処理が行われる
	Vector3 ndcVertex = Transform({ 0.0f,0.0f,0.0f }, worldViewProjectionMatrix);
	//ビューポート座標系への変換を行ってスクリーン空間へ
	Vector3 screenPos = Transform(ndcVertex, viewportMatrix);

	return screenPos;
}
//ビュープロジェクション行列を生成
Matrix4x4 MakeViewProjectionMatrix(const Vector3& rotate, const  Vector3& translate, const Vector3& cameraRotate, const Vector3& cameraTranslate)
{
	//ワールド変換行列を作る
	Matrix4x4 worldMatrix = MakeAfiineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);

	//ビュー変換行列を作るためにカメラポジションで行列作成
	Matrix4x4 cameraMatrix = MakeAfiineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);

	//↑のカメラ行列を反転してビュー座標系変換行列を作る
	Matrix4x4 viewMatrix = Inverse(cameraMatrix);

	//透視投影行列を作る
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindow.x) / float(kWindow.y), 0.1f, 100.0f);

	//ビュー変換行列と透視投影を掛けてワールド座標系→ビュー座標系→透視投影座標系への変換行列を作る
	Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));

	return worldViewProjectionMatrix;
}
//ビュープロジェクション行列とビューポート行列を使用し、スクリーン座標系へ変換
Vector3 MakeScreenTransform(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, const Vector3& transform)
{
	//スクリーン座標系へ変換
	//Transfarmを使うと同次座標系→デカルト座標系の処理が行われる
	Vector3 ndcVertex = Transform(transform, viewProjectionMatrix);
	//ビューポート座標系への変換を行ってスクリーン空間へ
	Vector3 screenPos = Transform(ndcVertex, viewportMatrix);

	return screenPos;
}

//クロス積
Vector3 Cross(const Vector3& a, const Vector3& b)
{
	return { a.y * b.z - a.z * b.y,a.z * b.x - a.x * b.z,a.x * b.y - a.y * b.x };
}

//3D描画
//グリッド(板of線)
void DrowGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix)
{
	const float kGridHalfWidth = 2.0f;										//Gridの半分の幅
	const uint32_t kSubdivision = 10;										//分割数
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);	//1つ分の長さ

	//奥から手前への線を順々に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex)
	{
		//上の情報を使ってワールド座標系上の始点と終点を求める
		float x = -kGridHalfWidth + (xIndex * kGridEvery);
		Vector3 gridLineStart = { x,0.0f,-kGridHalfWidth };
		Vector3 gridLineEnd = { x,0.0f,kGridHalfWidth };

		//スクリーン座標系まで変換をかける
		Vector3 gridLineStartScreen = MakeScreenTransform(viewProjectionMatrix, viewportMatrix, gridLineStart);
		Vector3 gridLineEndScreen = MakeScreenTransform(viewProjectionMatrix, viewportMatrix, gridLineEnd);

		//変換した座標を使って表示。色は薄い灰色(0xaaaaaaff)、原点は黒ぐらいがいい
		if (xIndex == kSubdivision / 2.0f)
		{
			Novice::DrawLine(
				int(gridLineStartScreen.x), int(gridLineStartScreen.y),
				int(gridLineEndScreen.x), int(gridLineEndScreen.y),
				BLACK);
		}
		else
		{
			Novice::DrawLine(
				int(gridLineStartScreen.x), int(gridLineStartScreen.y),
				int(gridLineEndScreen.x), int(gridLineEndScreen.y),
				0xaaaaaaff);
		}
	}

	//左から右も同じように順々に引いていく
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex)
	{
		//奥から手前が左右になるだけ
		//上の情報を使ってワールド座標系上の始点と終点を求める
		float z = -kGridHalfWidth + (zIndex * kGridEvery);
		Vector3 gridLineStart = { -kGridHalfWidth ,0.0f,z };
		Vector3 gridLineEnd = { kGridHalfWidth,0.0f,z };

		//スクリーン座標系まで変換をかける
		Vector3 gridLineStartScreen = MakeScreenTransform(viewProjectionMatrix, viewportMatrix, gridLineStart);
		Vector3 gridLineEndScreen = MakeScreenTransform(viewProjectionMatrix, viewportMatrix, gridLineEnd);

		//変換した座標を使って表示。色は薄い灰色(0xaaaaaaff)、原点は黒ぐらいがいい
		if (zIndex == kSubdivision / 2.0f)
		{
			Novice::DrawLine(
				int(gridLineStartScreen.x), int(gridLineStartScreen.y),
				int(gridLineEndScreen.x), int(gridLineEndScreen.y),
				BLACK);
		}
		else
		{
			Novice::DrawLine(
				int(gridLineStartScreen.x), int(gridLineStartScreen.y),
				int(gridLineEndScreen.x), int(gridLineEndScreen.y),
				0xaaaaaaff);
		}
	}
}

//スフィア(球)
struct Sphere
{
	Vector3 center;	//中心点
	float radius; //半径
};
void DrowSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	const uint32_t kSubdivision = 12;							//分割数
	const float kLonEvery = float(M_PI) * 2.0f / int(kSubdivision);	//経度分割1つ分の角度
	const float kLatEvery = float(M_PI) / int(kSubdivision);	//緯度分割1つ分の角度

	//緯度の方向に分割　-π/2~π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; latIndex++)
	{
		float lat = -float(M_PI) / 2.0f + kLatEvery * latIndex;	//現在の緯度

		//経度の方向に分割　0~2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; lonIndex++)
		{
			float lon = lonIndex * kLonEvery;	//現在の経度

			//world座標系でのa,b,cを求める
			Vector3 a =
			{
				sphere.center.x + sphere.radius * cosf(lat) * cosf(lon),
				sphere.center.y + sphere.radius * sinf(lat),
				sphere.center.z + sphere.radius * cosf(lat) * sinf(lon),
			};
			Vector3 b =
			{
				sphere.center.x + sphere.radius * cosf(lat + kLatEvery) * cosf(lon),
				sphere.center.y + sphere.radius * sinf(lat + kLatEvery),
				sphere.center.z + sphere.radius * cosf(lat + kLatEvery) * sinf(lon),
			};
			Vector3 c =
			{
				sphere.center.x + sphere.radius * cosf(lat) * cosf(lon + kLonEvery),
				sphere.center.y + sphere.radius * sinf(lat),
				sphere.center.z + sphere.radius * cosf(lat) * sinf(lon + kLonEvery),
			};

			//a,b,cをscreen座標系まで変換
			Vector3 screenA = MakeScreenTransform(viewProjectionMatrix, viewportMatrix, a);
			Vector3 screenB = MakeScreenTransform(viewProjectionMatrix, viewportMatrix, b);
			Vector3 screenC = MakeScreenTransform(viewProjectionMatrix, viewportMatrix, c);

			//ab,acで線を引く
			Novice::DrawLine(int(screenA.x), int(screenA.y), int(screenB.x), int(screenB.y), color);
			Novice::DrawLine(int(screenA.x), int(screenA.y), int(screenC.x), int(screenC.y), color);
		}
	}
}

//カメラの初期位置と角度
Vector3 cameraTranslate = { 0.0f,1.9f,-6.49f };
Vector3 cameraRotate = { 0.26f,0.0f,0.0f };

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, int(kWindow.x), int(kWindow.y));

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Sphere sphere = { {0.0f,0.0f,0.0f},1.0f };

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

		Matrix4x4 viewProjectionMatrix = MakeViewProjectionMatrix({ 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f }, cameraRotate, cameraTranslate);
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindow.x), float(kWindow.y), 0.0f, 1.0f);

		//グリッド
		DrowGrid(viewProjectionMatrix, viewportMatrix);

		//スフィア(球)
		DrowSphere(sphere, viewProjectionMatrix, viewportMatrix, BLACK);

		//imgui
		ImGui::Begin("Window");
		ImGui::DragFloat3("cameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("sphereCenter", &sphere.center.x, 0.01f);
		ImGui::DragFloat("sphereRadius", &sphere.radius, 0.01f);
		ImGui::End();

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