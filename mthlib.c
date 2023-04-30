#include "mthlib.h"

//GLOBALS
static b8 seeded = MTHLIB_FALSE;
static u32 random_seed = 0;

//Checking which OS we're running on for absolute time query
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)

#include <windows.h>

static b8 systemFrequencySet = MTHLIB_FALSE;
static f64 systemFrequency = 0;

f64 GetPlatformTime() {
	if (systemFrequencySet == MTHLIB_FALSE) {
		LARGE_INTEGER t1;
		QueryPerformanceFrequency(&t1);
		systemFrequency = 1.0 / t1.QuadPart;
	}

	LARGE_INTEGER t2;
	QueryPerformanceCounter(&t2);

	return (f64)t2.QuadPart * systemFrequency;
}

#elif defined(__linux__) || defined(__gnu_linux__)

//Need to add this so we have access to clock_gettime() and CLOCK_MONOTONIC
#define _POSIX_C_SOURCE 199309L
#include <time.h>

f64 GetPlatformTime() {
	struct timespec t;
	clock_gettime(CLOCK_MONOTONIC, &t);
	return t.tv_sec + (t.tv_nsec * 0.000000001);
}

#endif

//V2 IMPLEMENTATIONS

v2 AddV2(v2 u, v2 v) { return (v2) { u.x + v.x, u.y + v.y }; }
v2 SubtractV2(v2 u, v2 v) { return (v2) { u.x - v.x, u.y - v.y }; }
v2 ScaleV2(v2 u, f32 scalar) { return (v2) { scalar* u.x, scalar* u.y }; }
f64 DotV2(v2 u, v2 v) { return (u.x * v.x) + (u.y * v.y); }
f64 NormV2(v2 u) { return Sqrt64((u.x * u.x) + (u.y * u.y)); }
v2 UnitV2(v2 u) {
	f64 vectorNorm = NormV2(u);
	if (vectorNorm == 0.0f) return MTHLIB_INVALID_V2;
	return (v2) { u.x / vectorNorm, u.y / vectorNorm };
}
b8 CompareV2(v2 u, v2 v, f32 errorMargin) {
	if (Abs32(u.x - v.x) > errorMargin || Abs32(u.y - v.y) > errorMargin) return MTHLIB_FALSE;
	return MTHLIB_TRUE;
}

//V3 IMPLEMENTATIONS

v3 AddV3(v3 u, v3 v) { return (v3) { u.x + v.x, u.y + v.y, u.z + v.z }; }
v3 SubtractV3(v3 u, v3 v) { return (v3) { u.x - v.x, u.y - v.y, u.z - v.z }; }
v3 ScaleV3(v3 u, f32 scalar) { return (v3) { scalar* u.x, scalar* u.y, scalar* u.z }; }
f64 DotV3(v3 u, v3 v) { return (u.x * v.x) + (u.y * v.y) + (u.z * v.z); }
v3 CrossV3(v3 u, v3 v) { return (v3) { (u.y * v.z - u.z * v.y), -(u.x * v.z - u.z * v.x), (u.x * v.y - v.x * u.y) }; }
f64 NormV3(v3 u) { return Sqrt64((u.x * u.x) + (u.y * u.y) + (u.z * u.z)); }
v3 UnitV3(v3 u) {
	f64 vectorNorm = NormV3(u);
	if (vectorNorm == 0.0f) return MTHLIB_INVALID_V3;
	return (v3) { u.x / vectorNorm, u.y / vectorNorm, u.z / vectorNorm };
}
b8 CompareV3(v3 u, v3 v, f32 errorMargin) {
	if (Abs32(u.x - v.x) > errorMargin ||
		Abs32(u.y - v.y) > errorMargin ||
		Abs32(u.z - v.z) > errorMargin) return MTHLIB_FALSE;
	return MTHLIB_TRUE;
}
v2 ConvertV3ToV2(v3 u) { return (v2) { u.x, u.y }; }

f64 ScalarTripleProduct(v3 a, v3 b, v3 c) { return DotV3(CrossV3(a, b), c); }

//V4 IMPLEMENTATIONS

v4 AddV4(v4 u, v4 v) { return (v4) { u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w }; }
v4 SubtractV4(v4 u, v4 v) { return (v4) { u.x - v.x, u.y - v.y, u.z - v.z, u.w - v.w }; }
v4 ScaleV4(v4 u, f32 scalar) { return (v4) { scalar* u.x, scalar* u.y, scalar* u.z, scalar* u.w }; }
f64 DotV4(v4 u, v4 v) { return u.x * v.x + u.y * v.y + u.z * v.z + u.w * v.w; }
f64 NormV4(v4 u) { return Sqrt64((u.x * u.x) + (u.y * u.y) + (u.z * u.z) + (u.w * u.w)); }
v4 UnitV4(v4 u) {
	f64 vectorNorm = NormV4(u);
	if (vectorNorm == 0) return MTHLIB_INVALID_V4;
	return (v4) { u.x / vectorNorm, u.y / vectorNorm, u.z / vectorNorm, u.w / vectorNorm };
}
b8 CompareV4(v4 u, v4 v, f32 errorMargin) {
	if (Abs32(u.x - v.x) > errorMargin ||
		Abs32(u.y - v.y) > errorMargin ||
		Abs32(u.z - v.z) > errorMargin ||
		Abs32(u.w - v.w) > errorMargin) return MTHLIB_FALSE;
	return MTHLIB_TRUE;
}
v3 ConvertV4ToV3(v4 u) { return (v3) { u.x, u.y, u.z }; }

//2x2 MATRIX SUPPORT
mat2x2 AddMatrix2x2(mat2x2 m1, mat2x2 m2) {
	mat2x2 output = { 0 };
	for (u8 i = 0; i < 4; i++)
		output.elem[i] = m1.elem[i] + m2.elem[i];
	return output;
}

mat2x2 SubMatrix2x2(mat2x2 m1, mat2x2 m2) {
	mat2x2 output = { 0 };
	for (u8 i = 0; i < 4; i++)
		output.elem[i] = m1.elem[i] - m2.elem[i];
	return output;
}

mat2x2 ScalarMultMatrix2x2(f64 scalar, mat2x2 m1) {
	mat2x2 output = { 0 };
	for (u8 i = 0; i < 4; i++)
		output.elem[i] = scalar * m1.elem[i];
	return output;
}

mat2x2 MultMatrix2x2(mat2x2 m1, mat2x2 m2) {
	mat2x2 output = { 0 };
	output.elem[0] = m1.elem[0] * m2.elem[0] + m1.elem[1] * m2.elem[2];
	output.elem[1] = m1.elem[0] * m2.elem[1] + m1.elem[1] * m2.elem[3];
	output.elem[2] = m1.elem[2] * m2.elem[0] + m1.elem[3] * m2.elem[2];
	output.elem[3] = m1.elem[2] * m2.elem[1] + m1.elem[3] * m2.elem[3];
	return output;
}

f32 DetMatrix2x2(mat2x2 m1) {
	return m1.elem[0] * m1.elem[3] -
		m1.elem[1] * m1.elem[2];
}

mat2x2 TransposeMatrix2x2(mat2x2 m1) {
	mat2x2 output = { 0 };
	output.elem[0] = m1.elem[0];
	output.elem[1] = m1.elem[2];
	output.elem[2] = m1.elem[1];
	output.elem[3] = m1.elem[3];
	return output;
}

mat2x2 InverseMatrix2x2(mat2x2 m1) {
	f64 det = DetMatrix2x2(m1);
	if (det == 0) return MTHLIB_INVALID_2X2MATRIX;

	mat2x2 adjugate = { 0 };
	adjugate.elem[0] = m1.elem[3];
	adjugate.elem[1] = -m1.elem[1];
	adjugate.elem[2] = -m1.elem[2];
	adjugate.elem[3] = m1.elem[0];

	return ScalarMultMatrix2x2(1 / det, adjugate);
}

v2 MultV2ByMatrix2x2(v2 u, mat2x2 m1) {
	return (v2) {
		u.x* m1.elem[0] + u.y * m1.elem[2],
			u.x* m1.elem[1] + u.y * m1.elem[3]
	};
}

mat2x2 CreateIdentity2x2() {
	mat2x2 output = { 0 };

	output.elem[0] = 1.0;
	output.elem[3] = 1.0;

	return output;
}

//3x3 MATRIX SUPPORT
mat3x3 AddMatrix3x3(mat3x3 m1, mat3x3 m2) {
	mat3x3 output = { 0 };
	for (u8 i = 0; i < 9; i++)
		output.elem[i] = m1.elem[i] + m2.elem[i];
	return output;
}

mat3x3 SubMatrix3x3(mat3x3 m1, mat3x3 m2) {
	mat3x3 output = { 0 };
	for (u8 i = 0; i < 9; i++)
		output.elem[i] = m1.elem[i] - m2.elem[i];
	return output;
}

mat3x3 ScalarMultMatrix3x3(f64 scalar, mat3x3 m1) {
	mat3x3 output = { 0 };
	for (u8 i = 0; i < 9; i++)
		output.elem[i] = scalar * m1.elem[i];
	return output;
}

mat3x3 MultMatrix3x3(mat3x3 m1, mat3x3 m2) {
	mat3x3 output = { 0 };

	output.elem[0] = m1.elem[0] * m2.elem[0] + m1.elem[1] * m2.elem[3] + m1.elem[2] * m2.elem[6];
	output.elem[1] = m1.elem[0] * m2.elem[1] + m1.elem[1] * m2.elem[4] + m1.elem[2] * m2.elem[7];
	output.elem[2] = m1.elem[0] * m2.elem[2] + m1.elem[1] * m2.elem[5] + m1.elem[2] * m2.elem[8];
	output.elem[3] = m1.elem[3] * m2.elem[0] + m1.elem[4] * m2.elem[3] + m1.elem[5] * m2.elem[6];
	output.elem[4] = m1.elem[3] * m2.elem[1] + m1.elem[4] * m2.elem[4] + m1.elem[5] * m2.elem[7];
	output.elem[5] = m1.elem[3] * m2.elem[2] + m1.elem[4] * m2.elem[5] + m1.elem[5] * m2.elem[8];
	output.elem[6] = m1.elem[6] * m2.elem[0] + m1.elem[7] * m2.elem[3] + m1.elem[8] * m2.elem[6];
	output.elem[7] = m1.elem[6] * m2.elem[1] + m1.elem[7] * m2.elem[4] + m1.elem[8] * m2.elem[7];
	output.elem[8] = m1.elem[6] * m2.elem[2] + m1.elem[7] * m2.elem[5] + m1.elem[8] * m2.elem[8];

	return output;
}

f32 DetMatrix3x3(mat3x3 m1) {
	return m1.elem[0] * m1.elem[4] * m1.elem[8] +
		m1.elem[1] * m1.elem[5] * m1.elem[6] +
		m1.elem[2] * m1.elem[3] * m1.elem[7] -
		m1.elem[6] * m1.elem[4] * m1.elem[2] -
		m1.elem[7] * m1.elem[5] * m1.elem[0] -
		m1.elem[8] * m1.elem[3] * m1.elem[1];
}

mat3x3 TransposeMatrix3x3(mat3x3 m1) {
	mat3x3 output = { 0 };
	output.elem[0] = m1.elem[0];
	output.elem[1] = m1.elem[3];
	output.elem[2] = m1.elem[6];
	output.elem[3] = m1.elem[1];
	output.elem[4] = m1.elem[4];
	output.elem[5] = m1.elem[7];
	output.elem[6] = m1.elem[2];
	output.elem[7] = m1.elem[5];
	output.elem[8] = m1.elem[8];
	return output;
}

mat3x3 InverseMatrix3x3(mat3x3 m1) {
	f64 det = DetMatrix3x3(m1);
	if (det == 0) return MTHLIB_INVALID_3X3MATRIX;

	mat3x3 t = TransposeMatrix3x3(m1);

	f64 det00 = DetMatrix2x2((mat2x2) { .elem = { t.elem[4], t.elem[5], t.elem[7], t.elem[8] } });
	f64 det01 = -DetMatrix2x2((mat2x2) { .elem = { t.elem[3], t.elem[5], t.elem[6], t.elem[8] } });
	f64 det02 = DetMatrix2x2((mat2x2) { .elem = { t.elem[3], t.elem[4], t.elem[6], t.elem[7] } });
	f64 det10 = -DetMatrix2x2((mat2x2) { .elem = { t.elem[1], t.elem[2], t.elem[7], t.elem[8] } });
	f64 det11 = DetMatrix2x2((mat2x2) { .elem = { t.elem[0], t.elem[2], t.elem[6], t.elem[8] } });
	f64 det12 = -DetMatrix2x2((mat2x2) { .elem = { t.elem[0], t.elem[1], t.elem[6], t.elem[7] } });
	f64 det20 = DetMatrix2x2((mat2x2) { .elem = { t.elem[1], t.elem[2], t.elem[4], t.elem[5] } });
	f64 det21 = -DetMatrix2x2((mat2x2) { .elem = { t.elem[0], t.elem[2], t.elem[3], t.elem[5] } });
	f64 det22 = DetMatrix2x2((mat2x2) { .elem = { t.elem[0], t.elem[1], t.elem[3], t.elem[4] } });

	mat3x3 adjugate = { .elem = {det00, -det01, det02,
								-det10, det11, -det12,
								det20, -det21, det22} };

	return ScalarMultMatrix3x3(1 / det, adjugate);
}

v3 MultV3ByMatrix3x3(v3 u, mat3x3 m1) {
	return (v3) {
		u.x* m1.elem[0] + u.y * m1.elem[3] + u.z * m1.elem[6],
			u.x* m1.elem[1] + u.y * m1.elem[4] + u.z * m1.elem[7],
			u.x* m1.elem[2] + u.y * m1.elem[5] + u.z * m1.elem[8]
	};
}

mat3x3 CreateIdentity3x3() {
	mat3x3 output = { 0 };

	output.elem[0] = 1.0;
	output.elem[4] = 1.0;
	output.elem[8] = 1.0;

	return output;
}

//4x4 MATRIX SUPPORT
mat4x4 AddMatrix4x4(mat4x4 m1, mat4x4 m2) {
	mat4x4 output = { 0 };
	for (u8 i = 0; i < 16; i++)
		output.elem[i] = m1.elem[i] + m2.elem[i];
	return output;
}

mat4x4 SubMatrix4x4(mat4x4 m1, mat4x4 m2) {
	mat4x4 output = { 0 };
	for (u8 i = 0; i < 16; i++)
		output.elem[i] = m1.elem[i] - m2.elem[i];
	return output;
}

mat4x4 ScalarMultMatrix4x4(f64 scalar, mat4x4 m1) {
	mat4x4 output = { 0 };
	for (u8 i = 0; i < 16; i++)
		output.elem[i] = scalar * m1.elem[i];
	return output;
}

mat4x4 MultMatrix4x4(mat4x4 m1, mat4x4 m2) {
	mat4x4 output = { 0 };

	output.elem[0] = m1.elem[0] * m2.elem[0] + m1.elem[1] * m2.elem[4] + m1.elem[2] * m2.elem[8] + m1.elem[3] * m2.elem[12];
	output.elem[1] = m1.elem[0] * m2.elem[1] + m1.elem[1] * m2.elem[5] + m1.elem[2] * m2.elem[9] + m1.elem[3] * m2.elem[13];
	output.elem[2] = m1.elem[0] * m2.elem[2] + m1.elem[1] * m2.elem[6] + m1.elem[2] * m2.elem[10] + m1.elem[3] * m2.elem[14];
	output.elem[3] = m1.elem[0] * m2.elem[3] + m1.elem[1] * m2.elem[7] + m1.elem[2] * m2.elem[11] + m1.elem[3] * m2.elem[15];
	output.elem[4] = m1.elem[4] * m2.elem[0] + m1.elem[5] * m2.elem[4] + m1.elem[6] * m2.elem[8] + m1.elem[7] * m2.elem[12];
	output.elem[5] = m1.elem[4] * m2.elem[1] + m1.elem[5] * m2.elem[5] + m1.elem[6] * m2.elem[9] + m1.elem[7] * m2.elem[13];
	output.elem[6] = m1.elem[4] * m2.elem[2] + m1.elem[5] * m2.elem[6] + m1.elem[6] * m2.elem[10] + m1.elem[7] * m2.elem[14];
	output.elem[7] = m1.elem[4] * m2.elem[3] + m1.elem[5] * m2.elem[7] + m1.elem[6] * m2.elem[11] + m1.elem[7] * m2.elem[15];
	output.elem[8] = m1.elem[8] * m2.elem[0] + m1.elem[9] * m2.elem[4] + m1.elem[10] * m2.elem[8] + m1.elem[11] * m2.elem[12];
	output.elem[9] = m1.elem[8] * m2.elem[1] + m1.elem[9] * m2.elem[5] + m1.elem[10] * m2.elem[9] + m1.elem[11] * m2.elem[13];
	output.elem[10] = m1.elem[8] * m2.elem[2] + m1.elem[9] * m2.elem[6] + m1.elem[10] * m2.elem[10] + m1.elem[11] * m2.elem[14];
	output.elem[11] = m1.elem[8] * m2.elem[3] + m1.elem[9] * m2.elem[7] + m1.elem[10] * m2.elem[11] + m1.elem[11] * m2.elem[15];
	output.elem[12] = m1.elem[12] * m2.elem[0] + m1.elem[13] * m2.elem[4] + m1.elem[14] * m2.elem[8] + m1.elem[15] * m2.elem[12];
	output.elem[13] = m1.elem[12] * m2.elem[1] + m1.elem[13] * m2.elem[5] + m1.elem[14] * m2.elem[9] + m1.elem[15] * m2.elem[13];
	output.elem[14] = m1.elem[12] * m2.elem[2] + m1.elem[13] * m2.elem[6] + m1.elem[14] * m2.elem[10] + m1.elem[15] * m2.elem[14];
	output.elem[15] = m1.elem[12] * m2.elem[3] + m1.elem[13] * m2.elem[7] + m1.elem[14] * m2.elem[11] + m1.elem[15] * m2.elem[15];

	return output;
}

f32 DetMatrix4x4(mat4x4 m1) {
	return m1.elem[0] * m1.elem[5] * m1.elem[10] * m1.elem[15] +
		m1.elem[0] * m1.elem[9] * m1.elem[14] * m1.elem[7] +
		m1.elem[0] * m1.elem[13] * m1.elem[6] * m1.elem[11] -
		m1.elem[0] * m1.elem[13] * m1.elem[10] * m1.elem[7] -
		m1.elem[0] * m1.elem[9] * m1.elem[6] * m1.elem[15] -
		m1.elem[0] * m1.elem[5] * m1.elem[14] * m1.elem[11] -
		m1.elem[4] * m1.elem[1] * m1.elem[10] * m1.elem[15] -
		m1.elem[8] * m1.elem[1] * m1.elem[14] * m1.elem[7] -
		m1.elem[12] * m1.elem[1] * m1.elem[6] * m1.elem[11] +
		m1.elem[12] * m1.elem[1] * m1.elem[10] * m1.elem[7] +
		m1.elem[8] * m1.elem[1] * m1.elem[6] * m1.elem[15] +
		m1.elem[4] * m1.elem[1] * m1.elem[14] * m1.elem[11] +
		m1.elem[4] * m1.elem[9] * m1.elem[2] * m1.elem[15] +
		m1.elem[8] * m1.elem[13] * m1.elem[2] * m1.elem[7] +
		m1.elem[12] * m1.elem[5] * m1.elem[2] * m1.elem[11] -
		m1.elem[12] * m1.elem[9] * m1.elem[2] * m1.elem[7] -
		m1.elem[8] * m1.elem[5] * m1.elem[2] * m1.elem[15] -
		m1.elem[4] * m1.elem[13] * m1.elem[2] * m1.elem[11] -
		m1.elem[4] * m1.elem[9] * m1.elem[14] * m1.elem[3] -
		m1.elem[8] * m1.elem[13] * m1.elem[6] * m1.elem[3] -
		m1.elem[12] * m1.elem[5] * m1.elem[10] * m1.elem[3] +
		m1.elem[12] * m1.elem[9] * m1.elem[6] * m1.elem[3] +
		m1.elem[8] * m1.elem[5] * m1.elem[14] * m1.elem[3] +
		m1.elem[4] * m1.elem[13] * m1.elem[10] * m1.elem[3];
}

mat4x4 TransposeMatrix4x4(mat4x4 m1) {
	mat4x4 output = { 0 };

	output.elem[0] = m1.elem[0];
	output.elem[1] = m1.elem[4];
	output.elem[2] = m1.elem[8];
	output.elem[3] = m1.elem[12];
	output.elem[4] = m1.elem[1];
	output.elem[5] = m1.elem[5];
	output.elem[6] = m1.elem[9];
	output.elem[7] = m1.elem[13];
	output.elem[8] = m1.elem[2];
	output.elem[9] = m1.elem[6];
	output.elem[10] = m1.elem[10];
	output.elem[11] = m1.elem[14];
	output.elem[12] = m1.elem[3];
	output.elem[13] = m1.elem[7];
	output.elem[14] = m1.elem[11];
	output.elem[15] = m1.elem[15];

	return output;
}

mat4x4 InverseMatrix4x4(mat4x4 m1) {
	f32 det = DetMatrix4x4(m1);
	if (det == 0) return MTHLIB_INVALID_4X4MATRIX;

	mat4x4 t = TransposeMatrix4x4(m1);

	f32 det00 = DetMatrix3x3((mat3x3) {
		.elem = { t.elem[5], t.elem[6], t.elem[7],
				 t.elem[9], t.elem[10], t.elem[11],
				 t.elem[13], t.elem[14], t.elem[15] }
	});
	f32 det01 = -DetMatrix3x3((mat3x3) {
		.elem = { t.elem[4], t.elem[6], t.elem[7],
				t.elem[8], t.elem[10], t.elem[11],
				t.elem[12], t.elem[14], t.elem[15] }
	});
	f32 det02 = DetMatrix3x3((mat3x3) {
		.elem = { t.elem[4], t.elem[5], t.elem[7],
				 t.elem[8], t.elem[9], t.elem[11],
				 t.elem[12], t.elem[13], t.elem[15] }
	});
	f32 det03 = -DetMatrix3x3((mat3x3) {
		.elem = { t.elem[4], t.elem[5], t.elem[6],
				t.elem[8], t.elem[9], t.elem[10],
				t.elem[12], t.elem[13], t.elem[14] }
	});
	f32 det10 = -DetMatrix3x3((mat3x3) {
		.elem = { t.elem[1], t.elem[2], t.elem[3],
				t.elem[9], t.elem[10], t.elem[11],
				t.elem[13], t.elem[14], t.elem[15] }
	});
	f32 det11 = DetMatrix3x3((mat3x3) {
		.elem = { t.elem[0], t.elem[2], t.elem[3],
				 t.elem[8], t.elem[10], t.elem[11],
				 t.elem[12], t.elem[14], t.elem[15] }
	});
	f32 det12 = -DetMatrix3x3((mat3x3) {
		.elem = { t.elem[0], t.elem[1], t.elem[3],
				t.elem[8], t.elem[9], t.elem[11],
				t.elem[12], t.elem[13], t.elem[15] }
	});
	f32 det13 = DetMatrix3x3((mat3x3) {
		.elem = { t.elem[0], t.elem[1], t.elem[2],
				 t.elem[8], t.elem[9], t.elem[10],
				 t.elem[12], t.elem[13], t.elem[14] }
	});
	f32 det20 = DetMatrix3x3((mat3x3) {
		.elem = { t.elem[1], t.elem[2], t.elem[3],
				 t.elem[5], t.elem[6], t.elem[7],
				 t.elem[13], t.elem[14], t.elem[15] }
	});
	f32 det21 = -DetMatrix3x3((mat3x3) {
		.elem = { t.elem[0], t.elem[2], t.elem[3],
				t.elem[4], t.elem[6], t.elem[7],
				t.elem[12], t.elem[14], t.elem[15] }
	});
	f32 det22 = DetMatrix3x3((mat3x3) {
		.elem = { t.elem[0], t.elem[1], t.elem[3],
				 t.elem[4], t.elem[5], t.elem[7],
				 t.elem[12], t.elem[13], t.elem[15] }
	});
	f32 det23 = -DetMatrix3x3((mat3x3) {
		.elem = { t.elem[0], t.elem[1], t.elem[2],
				t.elem[4], t.elem[5], t.elem[6],
				t.elem[12], t.elem[13], t.elem[14] }
	});
	f32 det30 = -DetMatrix3x3((mat3x3) {
		.elem = { t.elem[1], t.elem[2], t.elem[3],
				t.elem[5], t.elem[6], t.elem[7],
				t.elem[9], t.elem[10], t.elem[11] }
	});
	f32 det31 = DetMatrix3x3((mat3x3) {
		.elem = { t.elem[0], t.elem[2], t.elem[3],
				 t.elem[4], t.elem[6], t.elem[7],
				 t.elem[8], t.elem[10], t.elem[11] }
	});
	f32 det32 = -DetMatrix3x3((mat3x3) {
		.elem = { t.elem[0], t.elem[1], t.elem[3],
				t.elem[4], t.elem[5], t.elem[7],
				t.elem[8], t.elem[9], t.elem[11] }
	});
	f32 det33 = DetMatrix3x3((mat3x3) {
		.elem = { t.elem[0], t.elem[1], t.elem[2],
				 t.elem[4], t.elem[5], t.elem[6],
				 t.elem[8], t.elem[9], t.elem[10] }
	});

	mat4x4 adjugate = { .elem = { det00, det01, det02, det03,
								 det10, det11, det12, det13,
								 det20, det21, det22, det23,
								 det30, det31, det32, det33} };

	return ScalarMultMatrix4x4(1 / det, adjugate);
}

v4 MultV4ByMatrix4x4(v4 u, mat4x4 m1) {
	return (v4) {
		u.x* m1.elem[0] + u.y * m1.elem[4] + u.z * m1.elem[8] + u.w * m1.elem[12],
			u.x* m1.elem[1] + u.y * m1.elem[5] + u.z * m1.elem[9] + u.w * m1.elem[13],
			u.x* m1.elem[2] + u.y * m1.elem[6] + u.z * m1.elem[10] + u.w * m1.elem[14],
			u.x* m1.elem[3] + u.y * m1.elem[7] + u.z * m1.elem[11] + u.w * m1.elem[15]
	};
}

mat4x4 CreateIdentity4x4() {
	mat4x4 output = { 0 };

	output.elem[0] = 1.0;
	output.elem[5] = 1.0;
	output.elem[10] = 1.0;
	output.elem[15] = 1.0;

	return output;
}

//TRIG FUNCTIONS IMPLEMENTATIONS
static f64 static_Sin64(f64 angle) {
	//McLaurin's Series with Horner's Scheme
	f64 y = angle * angle;

	f64 if3 = -1.0 / 6.0;
	f64 if5 = 1.0 / 120.0;
	f64 if7 = -1.0 / 5040.0;
	f64 if9 = 1.0 / 362880.0;
	f64 if11 = -1.0 / 39916800.0;

	return (angle + angle * y * (if3 + y * (if5 + y * (if7 + y * (if9 + y * if11)))));
}

static f64 static_Cos64(f64 angle) {
	//McLaurin's Series with Horner's Scheme
	f64 y = angle * angle;

	f64 if2 = -0.5;
	f64 if4 = 1.0 / 24.0;
	f64 if6 = -1.0 / 720.0;
	f64 if8 = 1.0 / 40320.0;
	f64 if10 = -1.0 / 3628800.0;
	f64 if12 = 1.0 / 479001600.0;

	return (1 + y * (if2 + y * (if4 + y * (if6 + y * (if8 + y * (if10 + y * if12))))));
}

f32 Sin32(f32 angleInRadians) { return (f32)Sin64(angleInRadians); }
f32 Cos32(f32 angleInRadians) { return (f32)Cos64(angleInRadians); }
f32 Tg32(f32 angleInRadians) { return (f32)Tg64(angleInRadians); }
f32 Cosec32(f32 angleInRadians) { return (f32)Cosec64(angleInRadians); }
f32 Sec32(f32 angleInRadians) { return (f32)Sec64(angleInRadians); }
f32 Cotg32(f32 angleInRadians) { return (f32)Cotg64(angleInRadians); }

f64 Sin64(f64 angleInRadians) {
	//For precision purposes I want to make sure that angleInRadians is in a good interval
	//This interval for us is going to be [-PI/4, PI/4]
	//(the bigger angleInRadians, the less precise our calculations are)
	f64 angle = Mod64(angleInRadians, 2 * MTHLIB_PI, MTHLIB_TRUE);

	if ((MTHLIB_PI < angle) && (angle < 2 * MTHLIB_PI)) angle = -(2 * MTHLIB_PI - angle);

	if ((-MTHLIB_PI / 4 <= angle) && (angle <= MTHLIB_PI / 4)) {
		return static_Sin64(angle);
	}
	else if ((MTHLIB_PI / 4 < angle) && (angle <= 3 * MTHLIB_PI / 4)) {
		return static_Cos64(angle - MTHLIB_PI / 2);
	}
	else if ((3 * MTHLIB_PI / 4 < angle) && (angle <= MTHLIB_PI)) {
		return static_Sin64(angle - MTHLIB_PI) * (-1);
	}
	else if ((-3 * MTHLIB_PI / 4 < angle) && (angle < -MTHLIB_PI / 4)) {
		return static_Cos64(MTHLIB_PI / 2 + angle) * (-1);
	}

	return static_Sin64(MTHLIB_PI + angle) * (-1);
}

f64	Cos64(f64 angleInRadians) {
	//For precision purposes I want to make sure that angleInRadians is in a good interval
	//This interval for us is going to be [-PI/4, PI/4]
	//(the bigger angleInRadians, the less precise our calculations are)
	f64 angle = Mod64(angleInRadians, 2 * MTHLIB_PI, MTHLIB_TRUE);

	if ((MTHLIB_PI < angle) && (angle < 2 * MTHLIB_PI)) angle = -(2 * MTHLIB_PI - angle);

	if ((-MTHLIB_PI / 4 <= angle) && (angle <= MTHLIB_PI / 4)) {
		return static_Cos64(angle);
	}
	else if ((MTHLIB_PI / 4 < angle) && (angle <= 3 * MTHLIB_PI / 4)) {
		return static_Sin64(angle - MTHLIB_PI / 2) * (-1);
	}
	else if ((-MTHLIB_PI / 4 > angle) && (angle >= -3 * MTHLIB_PI / 4)) {
		return static_Sin64(angle + MTHLIB_PI / 2);
	}
	else if ((3 * MTHLIB_PI / 4 < angle) && (angle <= MTHLIB_PI)) {
		return static_Cos64(angle - MTHLIB_PI) * (-1);
	}
	return static_Cos64(angle + MTHLIB_PI) * (-1);
}

//Unfortunetely I couldn't get it to be as precise as Sin and Cos.
//All the 4 next functions are not as precise as Sin and Cos, but we still have good results for
//		simples problems at least, We are getting error in the 6+th decimal place
//All the series expansions I tried are only good for very limited intervals of angles 
//		(Which I definetely don't want)
f64 Tg64(f64 angleInRadians) {
	f64 s = Sin64(angleInRadians);
	f64 c = Cos64(angleInRadians);
	if (c == 0.0f) return MTHLIB_INFINITY;
	return s / c;
}

f64	Cosec64(f64 angleInRadians) {
	f64 s = Sin64(angleInRadians);
	if (s == 0.0) return MTHLIB_NAN;
	return 1 / s;
}

f64	Sec64(f64 angleInRadians) {
	f64 c = Cos64(angleInRadians);
	if (c == 0.0) return MTHLIB_NAN;
	return 1.0 / c;
}

f64	Cotg64(f64 angleInRadians) {
	f64 t = Tg64(angleInRadians);
	if (t == 0.0) return MTHLIB_NAN;
	return 1.0 / t;
}

//CONVENIENT FUNCTIONS IMPLEMENTATIONS

//This is for the implementation of static_Sqrt64
typedef union unionF64 {
	f64 n;
	struct {
		u64 mantissa : 52;
		u64 exponent : 11;
		u64 sign : 1;
	}bits;
} unionF64;

static f64 static_Sqrt64(unionF64 x) {
	//The number we want to know the square root of
	f64 arg = x.n;

	//We are extracting the exponent part of the floating point number (We are also getting rid of the BIAS)
	i64 e = x.bits.exponent - MTHLIB_BIAS64;

	//This is going to be the number (1 + f) which is the mantissa plus 1. 
	//This is useful to get a great initial guess for the Newton-Raphson algorithm. 
	f64 f = 0;

	f64 rest = 1;

	if (e > 0) {
		f = arg / (2 << (e - 1));

		//if exponent is even
		if ((e & 1) == 0) {
			rest = 1 << (e / 2);
		}
		else {
			rest = MTHLIB_SQRT_2 * (1 << ((e - 1) / 2));
		}
	}
	else if (e < 0) {
		f = arg * (2 << (-e - 1));

		//if exponent is even
		if ((e & 1) == 0) {
			rest = 1 / (1 << (-e / 2));
		}
		else {
			rest = (MTHLIB_SQRT_2 / 2) * (1.0 / (1 << -((e + 1) / 2)));
		}
	}
	//This is for the case where the input argument is already in the correct scientific notation
	//For example, 1.5 (base 10) = 1.1 (base 2) = 1.1 * 2^(0) (e = 0) . No need to change the number at all.
	else {
		f = arg;
	}

	//Newton Raphson Algorithm
	f64 xk = ((f - 1) / 2) + 1;
	f64 xk1 = (xk + (f / xk)) / 2;
	f64 error = Abs64(xk1 - xk);

	while (error > MTHLIB_PRECISION)
	{
		xk = xk1;
		xk1 = (xk + (f / xk)) / 2;
		error = Abs64(xk1 - xk);
	}

	return xk1 * rest;
}

f32 DegreesToRadians32(f32 degrees) { return (f32)DegreesToRadians64(degrees); }
f32 Sqrt32(f32 x) { return (f32)Sqrt64(x); }
f32	Abs32(f32 x) { return (f32)Abs64(x); }
f32 Clamp32(f32 min, f32 max, f32 value) { return (f32)Clamp64(min, max, value); }
f32	Max32(f32 a, f32 b) { return (f32)Max64(a, b); }
f32	Min32(f32 a, f32 b) { return (f32)Min64(a, b); }
f32 Mod32(f32 f1, f64 f2, u8 positiveResult) { return (f32)Mod64(f1, f2, positiveResult); }
i32 Ceil32(f32 x) { return (f32)Ceil64(x); }
i32 Floor32(f32 x) { return (i32)Floor64(x); }
i32 Round32(f32 x) { return (i32)Round64(x); }

f64 DegreesToRadians64(f64 degrees) {
	return degrees * MTHLIB_DEGREE_IN_RAD;
}

f64	Sqrt64(f64 x) {
	if (x == 0.0f || x == 1.0f) return x;
	if (x < 0.0f) return MTHLIB_NAN;

	unionF64 x_union = { .n = x };

	return static_Sqrt64(x_union);
}

f64	Abs64(f64 x) {
	if (x < 0) return -x;
	return x;
}

f64 Clamp64(f64 min, f64 max, f64 value) {
	if (value < min) return min;
	if (value > max) return max;
	return value;
}

f64	Max64(f64 a, f64 b) {
	if (a > b) return a;
	return b;
}

f64	Min64(f64 a, f64 b) {
	if (a < b) return a;
	return b;
}

f64 Mod64(f64 f1, f64 f2, u8 positiveResult) {
	f64 result = f1 - (i64)(f1 / f2) * f2;
	if (positiveResult && result < 0) return (f2 + result);
	return result;
}

i64 Ceil64(f64 x) {
	if (x < 0) return (i64)x;

	i64 i_x = (i64)x;
	if (x == (f64)i_x) return i_x;
	return i_x + 1;
}

i64 Floor64(f64 x) {
	i64 n = (i64)x;
	f64 d = (f64)n;
	if (d == x || x >= 0) return (i64)d;
	return (i64)d - 1;
}

i64 Round64(f64 x) {
	if (x < 0) return (i64)(x - 0.5f);
	return (i64)(x + 0.5f);
}

i8 Sign(f64 x) {
	if (x < 0) return -1;
	return 1;
}

//RANDOM IMPLEMENTATIONS

static void static_SetSeed() {
	random_seed = (u32)GetPlatformTime();
	seeded = MTHLIB_TRUE;
}

static u32 static_XORShift() {
	u32 temp = random_seed;
	temp ^= temp << 13;
	temp ^= temp >> 17;
	temp ^= temp << 5;
	random_seed = temp;
	return random_seed;
}

u32 RandomU32() {
	if (seeded == MTHLIB_FALSE) static_SetSeed();
	return static_XORShift();
}

u32 RandomU32InInterval(u32 min, u32 max) {
	return (RandomU32() % (max - min + 1)) + min;
}

b8 RandomBool() {
	return (RandomU32() & 1) == 0;
}

i8 RandomSign() {
	if (RandomBool() == MTHLIB_FALSE) return 1;
	return -1;
}

//GRAPHICS IMPLEMENTATIONS

mat3x3 CreateTranslationMatrix2D(v2 posDelta) {
	mat3x3 output = CreateIdentity3x3();

	output.elem[2] = posDelta.x;
	output.elem[5] = posDelta.y;

	return output;
}

mat3x3 CreateScaleMatrixWithSetOrigin2D(v2 scale, v2 origin) {
	mat3x3 output = CreateIdentity3x3();

	output.elem[0] = scale.x;
	output.elem[2] = origin.x - origin.x * scale.x;
	output.elem[4] = scale.y;
	output.elem[5] = origin.y - origin.y * scale.y;

	return output;
}

mat3x3 CreateScaleMatrix2D(v2 scale) {
	return CreateScaleMatrixWithSetOrigin2D(scale, (v2) { 0, 0 });
}

mat3x3 CreateRotationAroundPointMatrix2D(f32 angle, v2 pos) {
	mat3x3 output = CreateIdentity3x3();

	f32 s = Sin32(angle);
	f32 c = Cos32(angle);

	output.elem[0] = c;
	output.elem[1] = -s;
	output.elem[2] = (pos.y * s) - (pos.x * c) + pos.x;
	output.elem[3] = s;
	output.elem[4] = c;
	output.elem[5] = -(pos.x * s) - (pos.y * c) + pos.y;

	return output;
}

mat3x3 CreateRotationMatrix2D(f32 angle) {
	return CreateRotationAroundPointMatrix2D(angle, (v2) { 0, 0 });
}

mat4x4 CreateTranslationMatrix3D(v3 posDelta) {
	mat4x4 output = CreateIdentity4x4();

	output.elem[3] = posDelta.x;
	output.elem[7] = posDelta.y;
	output.elem[11] = posDelta.z;

	return output;
}

mat4x4 CreateScaleMatrix3D(v3 scale) {
	mat4x4 output = CreateIdentity4x4();

	output.elem[0] = scale.x;
	output.elem[5] = scale.y;
	output.elem[10] = scale.z;

	return output;
}

mat4x4 CreateEulerRotationInXMatrix3D(f32 angle) {
	mat4x4 output = CreateIdentity4x4();

	f32 s = Sin32(angle);
	f32 c = Cos32(angle);

	output.elem[5] = c;
	output.elem[6] = -s;
	output.elem[9] = s;
	output.elem[10] = c;

	return output;
}

mat4x4 CreateEulerRotationInYMatrix3D(f32 angle) {
	mat4x4 output = CreateIdentity4x4();

	f32 s = Sin32(angle);
	f32 c = Cos32(angle);

	output.elem[0] = c;
	output.elem[2] = s;
	output.elem[10] = -s;
	output.elem[12] = c;

	return output;
}

mat4x4 CreateEulerRotationInZMatrix3D(f32 angle) {
	mat4x4 output = CreateIdentity4x4();

	f32 s = Sin32(angle);
	f32 c = Cos32(angle);

	output.elem[0] = c;
	output.elem[1] = -s;
	output.elem[4] = s;
	output.elem[5] = c;

	return output;
}

mat4x4 CreateEulerRotationInXYZMatrix3D(v3 angles) {
	mat4x4 output = { 0 };

	mat4x4 rotationMatrixInX = CreateEulerRotationInXMatrix3D(angles.x);
	mat4x4 rotationMatrixInY = CreateEulerRotationInYMatrix3D(angles.y);
	mat4x4 rotationMatrixInZ = CreateEulerRotationInZMatrix3D(angles.z);

	output = MultMatrix4x4(rotationMatrixInX, rotationMatrixInY);
	output = MultMatrix4x4(output, rotationMatrixInZ);

	return output;
}

mat4x4 CreateParallelProjectionMatrix3D(f32 l, f32 r, f32 t, f32 b, f32 f, f32 n) {
	mat4x4 output = CreateIdentity4x4();

	output.elem[0] = 2.0 / (r - l);
	output.elem[5] = 2.0 / (t - b);
	output.elem[10] = 2.0 / (f - n);

	output.elem[12] = -(r + l) / (r - l);
	output.elem[13] = -(t + b) / (t - b);
	output.elem[14] = -(f + n) / (f - n);

	return output;
}

mat4x4 CreatePerspectiveProjectionMatrix3D(f32 fovY, f32 aspectRatio, f32 f, f32 n) {
	mat4x4 output = { 0 };

	f32 tg = Tg32(fovY / 2);

	output.elem[0] = aspectRatio * (1 / tg);
	output.elem[5] = (1 / tg);
	output.elem[10] = f / (f - n);
	output.elem[11] = -(f * n) / (f - n);
	output.elem[14] = 1.0;

	return output;
}

// GEOMETRY IMPLEMENTATIONS

f32 DistanceBetweenPoints2D(point2D p, point2D q) {
	return Sqrt32((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y));
}

f32 DistanceBetweenPoints3D(point3D p, point3D q) {
	return Sqrt32((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y) + (p.z - q.z) * (p.z - q.z));
}

f32 DistanceBetweenPointAndLine2D(point2D p, line2D line) {
	v2 vectorAux = SubtractV2(p, line.arbitraryPoint);
	v2 lineNormal = { line.direction.y, -line.direction.x };
	return Abs32(DotV2(vectorAux, lineNormal) / NormV2(lineNormal));
}

f32 DistanceBetweenLines2D(line2D line1, line2D line2) {
	if (IntersectingLines2D(line1, line2)) {
		return 0;
	}
	return DistanceBetweenPointAndLine2D(line1.arbitraryPoint, line2);
}

f32 DistanceBetweenPointAndLine3D(point3D p, line3D line) {
	v3 aux = SubtractV3(p, line.arbitraryPoint);
	return NormV3(CrossV3(aux, line.direction)) / NormV3(line.direction);
}

f32 DistanceBetweenLines3D(line3D line1, line3D line2) {
	if (IntersectingLines3D(line1, line2)) {
		return 0;
	}
	if (ParallelLines3D(line1, line2)) {
		return DistanceBetweenPointAndLine3D(line1.arbitraryPoint, line2);
	}

	v3 arbitraryPointSub = SubtractV3(line1.arbitraryPoint, line2.arbitraryPoint);
	return Abs32(ScalarTripleProduct(line1.direction, line2.direction, arbitraryPointSub)) / NormV3(CrossV3(line1.direction, line2.direction));
}

f32 DistanceBetweenPointAndPlane(point3D p, plane pl) {
	v3 arbitraryPointSub = SubtractV3(p, pl.arbitraryPoint);
	return Abs32(DotV3(arbitraryPointSub, pl.normal)) / NormV3(pl.normal);
}

f32 DistanceBetweenLineAndPlane(line3D line, plane pl) {
	//Check if the line is parallel to the plane
	if (DotV3(line.direction, pl.normal) == 0) {
		return DistanceBetweenPointAndPlane(line.arbitraryPoint, pl);
	}
	//Here it means that the line is intersecting the plane in one point, since it's not parallel
	return 0;
}

f32 DistanceBetweenPlanes(plane pl1, plane pl2) {
	line3D normalLine1 = { .direction = pl1.normal, .arbitraryPoint = {0} };
	line3D normalLine2 = { .direction = pl2.normal, .arbitraryPoint = {0} };
	if (ParallelLines3D(normalLine1, normalLine2) == MTHLIB_TRUE) {
		return DistanceBetweenPointAndPlane(pl1.arbitraryPoint, pl2);
	}
	//Here it means that planes are intersecting, since they're not parallel
	return 0;
}

b8 ParallelLines2D(line2D l1, line2D l2) {
	f32 l1dx = l1.direction.x;
	f32 l1dy = l1.direction.y;
	f32 l2dx = l2.direction.x;
	f32 l2dy = l2.direction.y;

	if ((((l1dx == 0) && (l2dx == 0)) &&
		((l1dy != 0) && (l2dy != 0))) ||
		(((l1dy == 0) && (l2dy == 0)) &&
			((l1dx != 0) && (l2dx != 0)))) {
		return MTHLIB_TRUE;
	}
	if ((l2dx != 0) && (l2dy != 0) &&
		((l1dx / l2dx) == (l1dy / l2dy))) {
		return MTHLIB_TRUE;
	}
	return MTHLIB_FALSE;
}

b8 ParallelLines3D(line3D l1, line3D l2) {
	//The arbitrary points don't matter, since we only need the direction vectors
	if ((l1.direction.x == 0) && (l2.direction.x == 0)) {
		line2D aux1 = { .arbitraryPoint = (point2D){0}, .direction = (v2){l1.direction.y, l1.direction.z} };
		line2D aux2 = { .arbitraryPoint = (point2D){0}, .direction = (v2){l2.direction.y, l2.direction.z} };
		return ParallelLines2D(aux1, aux2);
	}
	if ((l1.direction.y == 0) && (l2.direction.y == 0)) {
		line2D aux1 = { .arbitraryPoint = (point2D){0}, .direction = (v2){l1.direction.x, l1.direction.z} };
		line2D aux2 = { .arbitraryPoint = (point2D){0}, .direction = (v2){l2.direction.x, l2.direction.z} };
		return ParallelLines2D(aux1, aux2);
	}
	if ((l1.direction.z == 0) && (l2.direction.z == 0)) {
		line2D aux1 = { .arbitraryPoint = (point2D){0}, .direction = (v2){l1.direction.x, l1.direction.y} };
		line2D aux2 = { .arbitraryPoint = (point2D){0}, .direction = (v2){l2.direction.x, l2.direction.y} };
		return ParallelLines2D(aux1, aux2);
	}
	if (((l1.direction.x / l2.direction.x) == 0) &&
		((l1.direction.y / l2.direction.y) == 0) &&
		((l1.direction.z / l2.direction.z) == 0)) {
		return MTHLIB_TRUE;
	}
	return MTHLIB_FALSE;
}

b8 IntersectingLines2D(line2D l1, line2D l2) {
	return !ParallelLines2D(l1, l2);
}

b8 IntersectingLines3D(line3D l1, line3D l2) {
	v3 directionCross = CrossV3(l1.direction, l2.direction);
	v3 directionSub = SubtractV3(l1.arbitraryPoint, l2.arbitraryPoint);
	return !ParallelLines3D(l1, l2) && (DotV3(directionCross, directionSub) == 0);
}

b8 SkewLines(line3D l1, line3D l2) {
	return !ParallelLines3D(l1, l2) && !IntersectingLines3D(l1, l2);
}

b8 CollisionAABB2D(AABB2D r1, AABB2D r2) {
	return((r1.min.x < r2.max.x) &&
		(r1.max.x > r2.min.x) &&
		(r1.min.y < r2.min.y) &&
		(r1.max.y > r2.min.y));
}

b8 CollisionPointAndAABB2D(point2D p, AABB2D r) {
	return (p.x >= r.min.x && p.x <= r.max.x) &&
		(p.y >= r.min.y && p.y <= r.max.y);
}

b8 CollisionPointAndSphere2D(point2D p, sphere2D s) {
	return DistanceBetweenPoints2D(p, s.center) < s.radius;
}

b8 CollisionSphere2D(sphere2D s1, sphere2D s2) {
	return DistanceBetweenPoints2D(s1.center, s2.center) < (s1.radius + s2.radius);
}

b8 CollisionAABB3D(AABB3D r1, AABB3D r2) {
	return((r1.max.x > r2.min.x) &&
		(r1.min.x < r2.max.x) &&
		(r1.max.y > r2.min.y) &&
		(r1.min.y < r2.max.y) &&
		(r1.max.z > r2.min.z) &&
		(r1.min.z < r2.max.z));
}

b8 CollisionPointAndAABB3D(point3D p, AABB3D r) {
	return (p.x >= r.min.x && p.x <= r.max.x) &&
		(p.y >= r.min.y && p.y <= r.max.y) &&
		(p.z >= r.min.z && p.z <= r.max.z);
}

b8 CollisionPointAndSphere3D(point3D p, sphere3D s) {
	return DistanceBetweenPoints3D(p, s.center) < s.radius;
}

b8 CollisionSphere3D(sphere3D s1, sphere3D s2) {
	return DistanceBetweenPoints3D(s1.center, s2.center) < (s1.radius + s2.radius);
}

f32 AreaTriangle2D(triangle2D triangle) {
	mat2x2 output = { 0 };

	output.elem[0] = triangle.a.x - triangle.b.x;
	output.elem[1] = triangle.a.x - triangle.c.x;
	output.elem[2] = triangle.a.y - triangle.b.y;
	output.elem[3] = triangle.a.y - triangle.c.y;

	return 0.5f * DetMatrix2x2(output);
}

f32 AreaSphere2D(sphere2D sphere) {
	return MTHLIB_PI * sphere.radius * sphere.radius;
}

f32 AreaAABB2D(AABB2D aabb) {
	return (aabb.max.x - aabb.min.x) * (aabb.max.y - aabb.min.y);
}

f32 AreaQuad2D(quad2D quad) {
	mat2x2 output = { 0 };

	output.elem[0] = quad.a.x - quad.c.x;
	output.elem[1] = quad.a.y - quad.c.y;
	output.elem[2] = quad.b.x - quad.d.x;
	output.elem[3] = quad.b.y - quad.d.y;

	return 0.5f * DetMatrix2x2(output);
}

f32 PerimeterSphere2D(sphere2D sphere) {
	return sphere.radius * 2 * MTHLIB_PI;
}

f32 PerimeterAABB2D(AABB2D aabb) {
	return 2 * (aabb.max.x - aabb.min.x) + 2 * (aabb.max.y - aabb.min.y);
}

f32 PerimeterQuad2D(quad2D quad) {
	f32 d1 = DistanceBetweenPoints2D(quad.a, quad.b);
	f32 d2 = DistanceBetweenPoints2D(quad.b, quad.c);
	f32 d3 = DistanceBetweenPoints2D(quad.c, quad.d);
	f32 d4 = DistanceBetweenPoints2D(quad.d, quad.a);
	return d1 + d2 + d3 + d4;
}

f32 PerimeterTriangle2D(triangle2D triangle) {
	f32 d1 = DistanceBetweenPoints2D(triangle.a, triangle.b);
	f32 d2 = DistanceBetweenPoints2D(triangle.b, triangle.c);
	f32 d3 = DistanceBetweenPoints2D(triangle.c, triangle.a);
	return d1 + d2 + d3;
}

f32 AreaTriangle3D(triangle3D triangle) {
	v3 u = SubtractV3(triangle.b, triangle.a);
	v3 v = SubtractV3(triangle.c, triangle.a);
	v3 c = CrossV3(u, v);
	f32 n = NormV3(c);
	return 0.5f * n;
}

f32 AreaQuad3D(quad3D quad) {
	triangle3D t1 = (triangle3D){ quad.a, quad.b, quad.c };
	triangle3D t2 = (triangle3D){ quad.a, quad.d, quad.c };
	f32 areaTriangle1 = AreaTriangle3D(t1);
	f32 areaTriangle2 = AreaTriangle3D(t2);
	return areaTriangle1 + areaTriangle2;
}

f32 VolumeSphere3D(sphere3D sphere) {
	f32 r = sphere.radius;
	return (4.0f / 3.0f) * MTHLIB_PI * (r * r * r);
}

f32 VolumeAABB3D(AABB3D aabb) {
	return Abs32((aabb.max.x - aabb.min.x) * (aabb.max.y - aabb.min.y) * (aabb.max.z - aabb.min.z));
}

f32 PerimeterTriangle3D(triangle3D triangle) {
	f32 d1 = DistanceBetweenPoints3D(triangle.a, triangle.b);
	f32 d2 = DistanceBetweenPoints3D(triangle.b, triangle.c);
	f32 d3 = DistanceBetweenPoints3D(triangle.c, triangle.a);
	return d1 + d2 + d3;
}

f32 SurfaceAreaSphere3D(sphere3D sphere) {
	return 4.0f * MTHLIB_PI * sphere.radius * sphere.radius;
}

f32 SurfaceAreaAABB3D(AABB3D aabb) {
	AABB2D aabb1 = (AABB2D){ .min = {aabb.min.x, aabb.min.y}, .max = {aabb.max.x, aabb.max.y} };
	AABB2D aabb2 = (AABB2D){ .min = {aabb.min.x, aabb.min.y}, .max = {aabb.max.y, aabb.max.z} };
	AABB2D aabb3 = (AABB2D){ .min = {aabb.min.x, aabb.min.y}, .max = {aabb.max.x, aabb.max.z} };
	f32 areaFace1 = AreaAABB2D(aabb1);
	f32 areaFace2 = AreaAABB2D(aabb2);
	f32 areaFace3 = AreaAABB2D(aabb3);
	return (2 * areaFace1) + (2 * areaFace2) + (2 * areaFace3);
}

lineSegment2D AddLineSegment2D(lineSegment2D l1, lineSegment2D l2) {
	return (lineSegment2D) { l1.start, l2.end };
}

lineSegment2D SubtractLineSegment2D(lineSegment2D l1, lineSegment2D l2) {
	return (lineSegment2D) { l2.end, l1.end };
}

b8 LineSegment2DIsNull(lineSegment2D l) {
	return CompareV2(l.start, l.end, MTHLIB_PRECISION);
}

b8 LineSegments2DAreOpposite(lineSegment2D l1, lineSegment2D l2) {
	return (CompareV2(l1.end, l2.start, MTHLIB_PRECISION) && CompareV2(l1.start, l2.end, MTHLIB_PRECISION));
}

b8 LineSegments2DHaveEqualLength(lineSegment2D l1, lineSegment2D l2) {
	return DistanceBetweenPoints2D(l1.start, l1.end) == DistanceBetweenPoints2D(l2.start, l2.end);
}

b8 LineSegments2DAreParallel(lineSegment2D l1, lineSegment2D l2) {
	//this should probably be a function
	line2D line1 = (line2D){ .direction = SubtractV2(l1.end, l1.start), .arbitraryPoint = l1.start };
	line2D line2 = (line2D){ .direction = SubtractV2(l2.end, l2.start), .arbitraryPoint = l2.start };
	return ParallelLines2D(line1, line2);
}

b8 LineSegments2DHaveOppositeDirection(lineSegment2D l1, lineSegment2D l2) {
	line2D line1 = (line2D){ .direction = SubtractV2(l1.end, l1.start), .arbitraryPoint = l1.start };
	line2D line2 = (line2D){ .direction = SubtractV2(l2.end, l2.start), .arbitraryPoint = l2.start };
	return CompareV2(line1.direction, ScaleV2(line2.direction, -1), MTHLIB_PRECISION);
}

lineSegment3D AddLineSegment3D(lineSegment3D l1, lineSegment3D l2) {
	return (lineSegment3D) { l1.start, l2.end };
}

lineSegment3D SubtractLineSegment3D(lineSegment3D l1, lineSegment3D l2) {
	return (lineSegment3D) { l2.end, l1.end };
}

b8 LineSegment3DIsNull(lineSegment3D l) {
	return CompareV3(l.start, l.end, MTHLIB_PRECISION);
}

b8 LineSegments3DAreOpposite(lineSegment3D l1, lineSegment3D l2) {
	return (CompareV3(l1.end, l2.start, MTHLIB_PRECISION) && CompareV3(l1.start, l2.end, MTHLIB_PRECISION));
}

b8 LineSegments3DHaveEqualLength(lineSegment3D l1, lineSegment3D l2) {
	return DistanceBetweenPoints3D(l1.start, l1.end) == DistanceBetweenPoints3D(l2.start, l2.end);
}

b8 LineSegments3DAreParallel(lineSegment3D l1, lineSegment3D l2) {
	//this should probably be a function
	line3D line1 = (line3D){ .direction = SubtractV3(l1.end, l1.start), .arbitraryPoint = l1.start };
	line3D line2 = (line3D){ .direction = SubtractV3(l2.end, l2.start), .arbitraryPoint = l2.start };
	return ParallelLines3D(line1, line2);
}

b8 LineSegments3DHaveOppositeDirection(lineSegment3D l1, lineSegment3D l2) {
	line3D line1 = (line3D){ .direction = SubtractV3(l1.end, l1.start), .arbitraryPoint = l1.start };
	line3D line2 = (line3D){ .direction = SubtractV3(l2.end, l2.start), .arbitraryPoint = l2.start };
	return CompareV3(line1.direction, ScaleV3(line2.direction, -1), MTHLIB_PRECISION);
}
