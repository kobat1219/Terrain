#pragma once
#include <DirectXMath.h>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <DirectXMath.h>
//#include <minwindef.h>
// DWORDが入ってるけど、この書き方だと怒られる
#include <Windows.h>
#include "Memory.h"

#define PI 3.1415926f

namespace MyEngine {
	inline namespace Variables {
		struct float2 :public DirectX::XMFLOAT2 {

			using XMFLOAT2::XMFLOAT2;
			float2 operator-() {
				float2 tmp(-this->x, -this->y);
				return tmp;
			}

			float2 operator+(int _i) {
				float2 tmp = *this;
				tmp.x += _i;
				tmp.y += _i;
				return tmp;
			}
			float2 operator-(int _i) {
				float2 tmp = *this;
				tmp.x -= _i;
				tmp.y -= _i;
				return tmp;
			}
			float2 operator*(int _i) {
				float2 tmp = *this;
				tmp.x *= _i;
				tmp.y *= _i;
				return tmp;
			}
			float2 operator/(int _i) {
				float2 tmp = *this;
				tmp.x /= _i;
				tmp.y /= _i;
				return tmp;
			}

			float2 operator+(float _i) {
				float2 tmp = *this;
				tmp.x += _i;
				tmp.y += _i;
				return tmp;
			}
			float2 operator-(float _i) {
				float2 tmp = *this;
				tmp.x -= _i;
				tmp.y -= _i;
				return tmp;
			}
			float2 operator*(float _i) {
				float2 tmp = *this;
				tmp.x *= _i;
				tmp.y *= _i;
				return tmp;
			}
			float2 operator/(float _i) {
				float2 tmp = *this;
				tmp.x /= _i;
				tmp.y /= _i;
				return tmp;
			}

			float2 operator-(float2 _f2) {
				float2 tmp = *this;
				tmp.x -= _f2.x;
				tmp.y -= _f2.y;
				return tmp;
			}
			float2 operator*(float2 _f2) {
				float2 tmp = *this;
				tmp.x *= _f2.x;
				tmp.y *= _f2.y;
				return tmp;
			}
			float2 operator/(float2 _f2) {
				float2 tmp = *this;
				tmp.x /= _f2.x;
				tmp.y /= _f2.y;
				return tmp;
			}
			float2 operator+(float2 _f2) {
				float2 tmp = *this;
				tmp.x += _f2.x;
				tmp.y += _f2.y;
				return tmp;
			}

			void operator+=(float2 _f2) {
				this->x += _f2.x;
				this->y += _f2.y;
			}
			void operator-=(float2 _f2) {
				this->x -= _f2.x;
				this->y -= _f2.y;
			}
			void operator*=(float2 _f2) {
				this->x *= _f2.x;
				this->y *= _f2.y;
			}
			void operator/=(float2 _f2) {
				this->x /= _f2.x;
				this->y /= _f2.y;
			}
		};

		struct float3 :DirectX::XMFLOAT3 {

			using XMFLOAT3::XMFLOAT3;

			//float3(float _x, float _y){ x = _x; y = _y; z = 0; }

			bool operator!=(float3 _tmp) {
				return _tmp.x != this->x || _tmp.y != this->y || _tmp.z != this->z;
			}
			bool operator==(float3& _tmp) {
				return _tmp.x == this->x && _tmp.y == this->y && _tmp.z == this->z;
			}
			bool operator==(const float3& _tmp) const{
				return _tmp.x == this->x && _tmp.y == this->y && _tmp.z == this->z;
			}
			bool operator<(float3 _tmp) {
				return _tmp.x > this->x && _tmp.y > this->y && _tmp.z > this->z;
			}
			bool operator>(float3 _tmp) {
				return _tmp.x < this->x&& _tmp.y < this->y&& _tmp.z < this->z;
			}

			float3 operator-() {
				float3 tmp(-this->x, -this->y, this->z);
				return tmp;
			}

			float3 operator+(const float2& _f2)const {
				float3 tmp = *this;
				tmp.x += _f2.x;
				tmp.y += _f2.y;
				return tmp;
			}
			float3 operator-(const float2& _f2)const {
				float3 tmp = *this;
				tmp.x -= _f2.x;
				tmp.y -= _f2.y;
				return tmp;
			}
			float3 operator*(const float2& _f2)const {
				float3 tmp = *this;
				tmp.x *= _f2.x;
				tmp.y *= _f2.y;
				return tmp;
			}
			float3 operator/(const float2& _f2)const {
				float3 tmp = *this;
				tmp.x /= _f2.x;
				tmp.y /= _f2.y;
				return tmp;
			}

			float3 operator+(const int& _i)const {
				float3 tmp = *this;
				tmp.x += _i;
				tmp.y += _i;
				tmp.z += _i;
				return tmp;
			}
			float3 operator-(const int& _i)const {
				float3 tmp = *this;
				tmp.x -= _i;
				tmp.y -= _i;
				tmp.z -= _i;
				return tmp;
			}
			float3 operator*(const int& _i)const {
				float3 tmp = *this;
				tmp.x *= _i;
				tmp.y *= _i;
				tmp.z *= _i;
				return tmp;
			}
			float3 operator/(const int& _i)const {
				float3 tmp = *this;
				tmp.x /= _i;
				tmp.y /= _i;
				tmp.z /= _i;
				return tmp;
			}

			float3 operator+(const float& _i) const{
				float3 tmp = *this;
				tmp.x += _i;
				tmp.y += _i;
				tmp.z += _i;
				return tmp;
			}
			float3 operator-(const float& _i) const {
				float3 tmp = *this;
				tmp.x -= _i;
				tmp.y -= _i;
				tmp.z -= _i;
				return tmp;
			}
			float3 operator*(const float& _i) const {
				float3 tmp = *this;
				tmp.x *= _i;
				tmp.y *= _i;
				tmp.z *= _i;
				return tmp;
			}
			float3 operator/(const float& _i) const {
				float3 tmp = *this;
				tmp.x /= _i;
				tmp.y /= _i;
				tmp.z /= _i;
				return tmp;
			}

			float3 operator+(const float3& _f3)const {
				float3 tmp = *this;
				tmp.x += _f3.x;
				tmp.y += _f3.y;
				tmp.z += _f3.z;
				return tmp;
			}
			float3 operator-(const float3& _f3)const {
				float3 tmp = *this;
				tmp.x -= _f3.x;
				tmp.y -= _f3.y;
				tmp.z -= _f3.z;
				return tmp;
			}
			float3 operator*(const float3& _f3)const {
				float3 tmp = *this;
				tmp.x *= _f3.x;
				tmp.y *= _f3.y;
				tmp.z *= _f3.z;
				return tmp;
			}
			float3 operator/(const float3& _f3)const {
				float3 tmp = *this;
				tmp.x /= _f3.x;
				tmp.y /= _f3.y;
				tmp.z /= _f3.z;
				return tmp;
			}

			void operator*=(const float& _f) {
				this->x *= _f;
				this->y *= _f;
				this->z *= _f;
			}
			void operator+=(const float2& _f2) {
				this->x += _f2.x;
				this->y += _f2.y;
			}
			void operator-=(const float2& _f2) {
				this->x -= _f2.x;
				this->y -= _f2.y;
			}
			void operator*=(const float2& _f2) {
				this->x *= _f2.x;
				this->y *= _f2.y;
			}
			void operator/=(const float2& _f2) {
				this->x /= _f2.x;
				this->y /= _f2.y;
			}

			void operator+=(const float3& _f3) {
				this->x += _f3.x;
				this->y += _f3.y;
				this->z += _f3.z;
			}
			void operator-=(const float3& _f3) {
				this->x -= _f3.x;
				this->y -= _f3.y;
				this->z -= _f3.z;
			}
			void operator*=(const float3& _f3) {
				this->x *= _f3.x;
				this->y *= _f3.y;
				this->z *= _f3.z;
			}
			void operator/=(const float3& _f3) {
				this->x /= _f3.x;
				this->y /= _f3.y;
				this->z /= _f3.z;
			}

			/*------------------------
			ベクトルの長さを求める
			--------------------------*/
			static float Length(const XMFLOAT3& vec) {

				using namespace DirectX;

				ALIGN16 XMVECTOR outvec;
				ALIGN16 XMVECTOR invec;
				XMFLOAT4 l;

				l.x = vec.x;
				l.y = vec.y;
				l.z = vec.z;
				l.w = 0.0f;

				invec = XMLoadFloat4(&l);

				outvec = XMVector3Length(invec);

				XMStoreFloat4(&l, outvec);

				return l.x;
			}
		};

		struct float4 :public DirectX::XMFLOAT4
		{
			using XMFLOAT4::XMFLOAT4;
		};

		struct quaternion :public DirectX::XMFLOAT4
		{
			using XMFLOAT4::XMFLOAT4;

			quaternion operator*(quaternion _qt) {
				using namespace DirectX;
				quaternion ans;

				ALIGN16 DirectX::XMVECTOR qtvec1;
				ALIGN16 DirectX::XMVECTOR qtvec2;
				ALIGN16 DirectX::XMVECTOR outqtvec;

				qtvec1 = XMLoadFloat4(this);
				qtvec2 = XMLoadFloat4(&_qt);

				outqtvec = XMQuaternionMultiply(qtvec1, qtvec2);

				XMStoreFloat4(&ans, outqtvec);

				return ans;
			}

			void operator*=(quaternion _qt) {
				using namespace DirectX;
				ALIGN16 DirectX::XMVECTOR qtvec1;
				ALIGN16 DirectX::XMVECTOR qtvec2;
				ALIGN16 DirectX::XMVECTOR outqtvec;

				qtvec1 = XMLoadFloat4(this);
				qtvec2 = XMLoadFloat4(&_qt);

				outqtvec = XMQuaternionMultiply(qtvec1, qtvec2);

				XMStoreFloat4(this, outqtvec);
			}
		};

		struct Color :public DirectX::XMFLOAT4
		{
			using XMFLOAT4::XMFLOAT4;	

			Color operator*(float _v) {
				return {
					this->x * _v,	//r
					this->y * _v,	//g
					this->z * _v,	//b
					this->w			//a
				};
			}
			
			void LoadFromXMFloat4(const XMFLOAT4& _col)
			{
				this->x = _col.x;
				this->y = _col.y;
				this->z = _col.z;
				this->w = _col.w;
			}

		};
		
		struct int2 :public DirectX::XMINT2 {

			using XMINT2::XMINT2;

			bool operator==(int2 _f2) {
				bool ret = false;
				if (this->x == _f2.x
					&& this->y == _f2.y) {
					ret = true;
				}
				return ret;
			}

			bool operator!=(int2 _f2) {
				bool ret = false;
				if (this->x != _f2.x
					|| this->y != _f2.y) {
					ret = true;
				}
				return ret;
			}

			int2 operator-() {
				int2 tmp(-this->x, -this->y);
				return tmp;
			}

			int2 operator-(int2 _f2) {
				int2 tmp = *this;
				tmp.x -= _f2.x;
				tmp.y -= _f2.y;
				return tmp;
			}
			int2 operator*(int2 _f2) {
				int2 tmp = *this;
				tmp.x *= _f2.x;
				tmp.y *= _f2.y;
				return tmp;
			}
			int2 operator/(int2 _f2) {
				int2 tmp = *this;
				tmp.x /= _f2.x;
				tmp.y /= _f2.y;
				return tmp;
			}
			int2 operator+(int2 _f2) {
				int2 tmp = *this;
				tmp.x += _f2.x;
				tmp.y += _f2.y;
				return tmp;
			}

			void operator+=(int2 _f2) {
				this->x += _f2.x;
				this->y += _f2.y;
			}
			void operator-=(int2 _f2) {
				this->x -= _f2.x;
				this->y -= _f2.y;
			}
			void operator*=(int2 _f2) {
				this->x *= _f2.x;
				this->y *= _f2.y;
			}
			void operator/=(int2 _f2) {
				this->x /= _f2.x;
				this->y /= _f2.y;
			}

		};

		struct int3 :public DirectX::XMINT3 {

			using XMINT3::XMINT3;

			//int3(int _x, int _y) { x = _x; y = _y; z = 0; }

			int3 operator-() {
				int3 tmp(-this->x, -this->y, this->z);
				return tmp;
			}

			int3 operator+(int2 _f2) {
				int3 tmp = *this;
				tmp.x += _f2.x;
				tmp.y += _f2.y;
				return tmp;
			}
			int3 operator-(int2 _f2) {
				int3 tmp = *this;
				tmp.x -= _f2.x;
				tmp.y -= _f2.y;
				return tmp;
			}
			int3 operator*(int2 _f2) {
				int3 tmp = *this;
				tmp.x *= _f2.x;
				tmp.y *= _f2.y;
				return tmp;
			}
			int3 operator/(int2 _f2) {
				int3 tmp = *this;
				tmp.x /= _f2.x;
				tmp.y /= _f2.y;
				return tmp;
			}

			int3 operator+(int3 _f3) {
				int3 tmp = *this;
				tmp.x += _f3.x;
				tmp.y += _f3.y;
				tmp.z += _f3.z;
				return tmp;
			}
			int3 operator-(int3 _f3) {
				int3 tmp = *this;
				tmp.x -= _f3.x;
				tmp.y -= _f3.y;
				tmp.z -= _f3.z;
				return tmp;
			}
			int3 operator*(int3 _f3) {
				int3 tmp = *this;
				tmp.x *= _f3.x;
				tmp.y *= _f3.y;
				tmp.z *= _f3.z;
				return tmp;
			}
			int3 operator/(int3 _f3) {
				int3 tmp = *this;
				tmp.x /= _f3.x;
				tmp.y /= _f3.y;
				tmp.z /= _f3.z;
				return tmp;
			}

			void operator+=(int2 _f2) {
				this->x += _f2.x;
				this->y += _f2.y;
			}
			void operator-=(int2 _f2) {
				this->x -= _f2.x;
				this->y -= _f2.y;
			}
			void operator*=(int2 _f2) {
				this->x *= _f2.x;
				this->y *= _f2.y;
			}
			void operator/=(int2 _f2) {
				this->x /= _f2.x;
				this->y /= _f2.y;
			}

			void operator+=(int3 _f3) {
				this->x += _f3.x;
				this->y += _f3.y;
				this->z += _f3.z;
			}
			void operator-=(int3 _f3) {
				this->x -= _f3.x;
				this->y -= _f3.y;
				this->z -= _f3.z;
			}
			void operator*=(int3 _f3) {
				this->x *= _f3.x;
				this->y *= _f3.y;
				this->z *= _f3.z;
			}
			void operator/=(int3 _f3) {
				this->x /= _f3.x;
				this->y /= _f3.y;
				this->z /= _f3.z;
			}

		};

		struct line 
		{
			float3 p;	// ポイント
			float3 vec;	// ベクトル

			line():p(0,0,0),vec(1,0,0) {}
			line(const float3& _p, const float3& _v) :p(_p), vec(_v) {}
		};

		struct PLANE {
			float a, b, c, d;
		};

		struct PLANEINFO {
			PLANE plane;
			float3 p1, p2, p3;
			unsigned int i1, i2, i3;
		};
	}
}