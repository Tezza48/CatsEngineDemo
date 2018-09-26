#pragma once

struct Rect
{
	union
	{
		struct
		{
			float x;
			float y;
			float width;
			float height;
		};
		float data[4];
	};

	Rect(float _x, float _y, float _width, float _height) : x(_x), y(_y), width(_width), height(_height){}

};
//
//struct Vector2
//{
//	union
//	{
//		struct
//		{
//			float x;
//			float y;
//		};
//		float data[2];
//	};
//
//	Vector2() : x(0.0f), y(0.0f) {}
//	Vector2(float _x, float _y) : x(_x), y(_y) {}
//};
//
//struct Vector3
//{
//	union
//	{
//		struct
//		{
//			float x;
//			float y;
//			float z;
//		};
//		float data[3];
//	};
//
//	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
//	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
//};
//
//struct Vector4
//{
//	union
//	{
//		struct
//		{
//			float x;
//			float y;
//			float z;
//			float w;
//		};
//		struct
//		{
//			float r;
//			float g;
//			float b;
//			float a;
//		};
//		float data[4];
//	};
//
//	inline Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
//	inline Vector4(const Vector4 & other)
//	{ 
//		this->x = other.x;
//		this->y = other.y; 
//		this->z = other.z; 
//		this->w = other.w;
//	}
//};
//typedef Vector4 Color;