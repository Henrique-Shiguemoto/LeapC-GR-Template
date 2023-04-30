#pragma once

/**
 *
 * USEFUL TYPEDEFS AND DEFINES FOR EASE OF READABILITY AND ORGANIZATION
 *
 * */

 /**
  *
  * TYPE DEFINITIONS (INSPIRED BY stdint.h)
  *
  * */

typedef char i8;
typedef short i16;
typedef int i32;
typedef long int i64;
typedef float f32;
typedef double f64;
typedef _Bool b8;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct v2
{
    f32 x;
    f32 y;
} v2;

typedef struct v3
{
    f32 x;
    f32 y;
    f32 z;
} v3;

typedef struct v4
{
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} v4;

/**
 *
 * To initialize a matrix, you'll need to assign the number one by one
 *  accessing each element by index OR you can declare a matrix and assign
 *  the "elem" member like this: mat2x2 m = {.elem = {1,2,3,4}} (mat2x2 is just an example)
 *  (This works for C99 or more updated versions of C)
 *
 * */
typedef struct mat2x2
{
    f32 elem[4];
} mat2x2;

typedef struct mat3x3
{
    f32 elem[9];
} mat3x3;

typedef struct mat4x4
{
    f32 elem[16];
} mat4x4;

typedef v2 point2D;
typedef v3 point3D;
typedef v4 quaternion;

typedef struct lineSegment2D {
    point2D start;
    point2D end;
}lineSegment2D;

typedef struct line2D {
    v2 direction;
    point2D arbitraryPoint;
}line2D;

typedef struct triangle2D {
    point2D a;
    point2D b;
    point2D c;
}triangle2D;

// It's important to be consistent with the order of the vertices. The user can only use either 
//      clockwise or anticlockwise ordering for vertices. Some of the functions used for this struct
//      can give you different results if you don't use these orders.
// Same thing applies to quad3D.
typedef struct quad2D {
    point2D a;
    point2D b;
    point2D c;
    point2D d;
}quad2D;

typedef struct AABB2D {
    point2D min;
    point2D max;
}AABB2D;

typedef struct sphere2D {
    point2D center;
    f32 radius;
}sphere2D;

typedef struct lineSegment3D {
    point3D start;
    point3D end;
}lineSegment3D;

typedef struct line3D {
    v3 direction;
    point3D arbitraryPoint;
}line3D;

typedef struct triangle3D {
    point3D a;
    point3D b;
    point3D c;
}triangle3D;

typedef struct quad3D {
    point3D a;
    point3D b;
    point3D c;
    point3D d;
}quad3D;

typedef struct plane {
    v3 normal;
    point3D arbitraryPoint;
}plane;

typedef struct AABB3D {
    point3D min;
    point3D max;
}AABB3D;

typedef struct sphere3D {
    point3D center;
    f32 radius;
}sphere3D;

/**
 *
 * FOR EDGE CASES, LIKE DIVISIONS BY ZERO
 *
 * */

#define MTHLIB_INFINITY ((float)(1e+300)*(1e+300))

 /**
  *
  * FOR EDGE CASES, LIKE DIVISIONS BY ZERO OF SQUARE ROOTS OF NEGATIVE NUMBERS
  *
  * */

#define MTHLIB_NAN (((float)(1e+300)*(1e+300))*(0.0f))

  /**
   *
   * APPROXIMATION OF PI
   *
   * */

#define MTHLIB_PI 3.141592653589793

   /**
    *
    * 1 DEGREE IN RADIANS (VERY USEFUL FOR ANGLE CONVERSIONS)
    *
    * */

#define MTHLIB_DEGREE_IN_RAD (MTHLIB_PI/180)

    /**
     *
     * APPROXIMATION OF SQUARE ROOT OF 2
     *
     * */

#define MTHLIB_SQRT_2 1.414213562373095

     /**
      *
      * APPROXIMATION OF SQUARE ROOT OF 3
      *
      * */

#define MTHLIB_SQRT_3 1.732050807568877

      /**
       *
       * THE AMOUNT OF DECIMAL PLACES NECESSARY FOR SOME OF THE CALCULATIONS IN THE CODE BASE
       *      USED IN SQUARE ROOT CALCULATIONS
       *
       * */

#define MTHLIB_PRECISION 0.0000000001

       /**
        *
        * BIAS USED BY IEEE 754 32 BIT FLOATING POINT SYSTEM TO MAKE EXPONENTS OF FLOATS ALWAYS NON-NEGATIVE
        *      USEFUL FOR SQUARE ROOT CALCULATIONS
        *
        * */

#define MTHLIB_BIAS32 127

        /**
         *
         * BIAS USED BY IEEE 754 64 BIT FLOATING POINT SYSTEM TO MAKE EXPONENTS OF FLOATS ALWAYS NON-NEGATIVE
         *      USEFUL FOR SQUARE ROOT CALCULATIONS
         *
         * */

#define MTHLIB_BIAS64 1023

         /**
          *
          * NOT NECESSARY, JUST TO EASE THE READABILITY
          *
          * */

#define MTHLIB_TRUE 1

          /**
           *
           * NOT NECESSARY, JUST TO EASE THE READABILITY
           *
           * */

#define MTHLIB_FALSE 0

           /**
            *
            * FOR EDGE CASES WHERE A VECTOR RETURN IS NOT DEFINED
            *      USEFUL IN CASES LIKE CALCULATING A UNIT VECTOR OF A ZERO VECTOR
            *
            * */

#define MTHLIB_INVALID_V2 (v2) {MTHLIB_NAN, MTHLIB_NAN}

            /**
             *
             * FOR EDGE CASES WHERE A VECTOR RETURN IS NOT DEFINED
             *      USEFUL IN CASES LIKE CALCULATING A UNIT VECTOR OF A ZERO VECTOR
             *
             * */

#define MTHLIB_INVALID_V3 (v3) {MTHLIB_NAN, MTHLIB_NAN, MTHLIB_NAN}

             /**
              *
              * FOR EDGE CASES WHERE A VECTOR RETURN IS NOT DEFINED
              *      USEFUL IN CASES LIKE CALCULATING A UNIT VECTOR OF A ZERO VECTOR
              *
              * */

#define MTHLIB_INVALID_V4 (v4) {MTHLIB_NAN, MTHLIB_NAN, MTHLIB_NAN, MTHLIB_NAN}

              /**
               *
               * FOR EDGE CASES WHERE A 2x2 MATRIX RETURN IS NOT DEFINED
               *      USEFUL IN CASES LIKE CALCULATING AN INVERSE OF MATRIX
               *      WHICH DOES NOT HAVE AN INVERSE
               *
               * */
#define MTHLIB_INVALID_2X2MATRIX (mat2x2) \
                                {.elem = \
                                {MTHLIB_NAN, MTHLIB_NAN, \
                                 MTHLIB_NAN, MTHLIB_NAN}}

               /**
                *
                * FOR EDGE CASES WHERE A 3x3 MATRIX RETURN IS NOT DEFINED
                *      USEFUL IN CASES LIKE CALCULATING AN INVERSE OF MATRIX
                *      WHICH DOES NOT HAVE AN INVERSE
                *
                * */
#define MTHLIB_INVALID_3X3MATRIX (mat3x3) \
                                {.elem = \
                                {MTHLIB_NAN, MTHLIB_NAN, MTHLIB_NAN, \
                                 MTHLIB_NAN, MTHLIB_NAN, MTHLIB_NAN, \
                                 MTHLIB_NAN, MTHLIB_NAN, MTHLIB_NAN}}

                /**
                 *
                 * FOR EDGE CASES WHERE A 4x4 MATRIX RETURN IS NOT DEFINED
                 *      USEFUL IN CASES LIKE CALCULATING AN INVERSE OF MATRIX
                 *      WHICH DOES NOT HAVE AN INVERSE
                 *
                 * */

#define MTHLIB_INVALID_4X4MATRIX (mat4x4) \
                                {.elem = \
                                {MTHLIB_NAN, MTHLIB_NAN, MTHLIB_NAN, MTHLIB_NAN, \
                                 MTHLIB_NAN, MTHLIB_NAN, MTHLIB_NAN, MTHLIB_NAN, \
                                 MTHLIB_NAN, MTHLIB_NAN, MTHLIB_NAN, MTHLIB_NAN, \
                                 MTHLIB_NAN, MTHLIB_NAN, MTHLIB_NAN, MTHLIB_NAN}}

f64 GetPlatformTime();

/**
 *
 * 2D VECTOR ADDITION
 *
 * */

v2 AddV2(v2 u, v2 v);

/**
 *
 * 2D VECTOR SUBTRACTION
 *
 * */

v2 SubtractV2(v2 u, v2 v);

/**
 *
 * SCALAR MULTIPLICATION WITH 2D VECTOR
 *
 * */

v2 ScaleV2(v2 u, f32 scalar);

/**
 *
 * 2D VECTOR DOT PRODUCT
 *
 * */

f64 DotV2(v2 u, v2 v);

/**
 *
 * NORM OF A 2D VECTOR
 *
 * */

f64 NormV2(v2 u);

/**
 *
 * 2D UNIT VECTOR WITH THE SAME DIRECTION AS THE INPUT 2D VECTOR
 *
 * */

v2 UnitV2(v2 u);

/**
 *
 * COMPARES EACH CORRESPONDING COMPONENT OF TWO 2D VECTORS BASED ON AN ERROR MARGIN
 *
 * */

b8 CompareV2(v2 u, v2 v, f32 errorMargin);

/**
 *
 * 3D VECTOR ADDITION
 *
 * */

v3 AddV3(v3 u, v3 v);

/**
 *
 * 3D VECTOR SUBTRACTION
 *
 * */

v3 SubtractV3(v3 u, v3 v);

/**
 *
 * SCALAR MULTIPLICATION WITH 3D VECTOR
 *
 * */

v3 ScaleV3(v3 u, f32 scalar);

/**
 *
 * 3D VECTOR DOT PRODUCT
 *
 * */

f64 DotV3(v3 u, v3 v);

/**
 *
 * 3D VECTOR CROSS PRODUCT
 *
 * */

v3 CrossV3(v3 u, v3 v);

/**
 *
 * NORM OF A 3D VECTOR
 *
 * */

f64 NormV3(v3 u);

/**
 *
 * 3D UNIT VECTOR WITH THE SAME DIRECTION AS THE INPUT 3D VECTOR
 *
 * */

v3 UnitV3(v3 u);

/**
 *
 * COMPARES EACH CORRESPONDING COMPONENT OF TWO 2D VECTORS BASED ON AN ERROR MARGIN
 *
 * */

b8 CompareV3(v3 u, v3 v, f32 errorMargin);

/**
 *
 * CONVERSION FROM V3 TO V2
 *
 * */

v2 ConvertV3ToV2(v3 u);

/**
 *
 * TRIPLE PRODUCT OF THREE 3D VECTORS
 *
 * */
f64 ScalarTripleProduct(v3 a, v3 b, v3 c);

/**
 *
 * 4D VECTOR ADDITION
 *
 * */

v4 AddV4(v4 u, v4 v);

/**
 *
 * 4D VECTOR SUBTRACTION
 *
 * */

v4 SubtractV4(v4 u, v4 v);

/**
 *
 * SCALAR MULTIPLICATION WITH 4D VECTOR
 *
 * */

v4 ScaleV4(v4 u, f32 scalar);

/**
 *
 * 4D VECTOR DOT PRODUCT
 *
 * */

f64 DotV4(v4 u, v4 v);

/**
 *
 * NORM OF A 4D VECTOR
 *
 * */

f64 NormV4(v4 u);

/**
 *
 * 4D UNIT VECTOR WITH THE SAME DIRECTION AS THE INPUT 4D VECTOR
 *
 * */

v4 UnitV4(v4 u);

/**
 *
 * COMPARES EACH CORRESPONDING COMPONENT OF TWO 3D VECTORS BASED ON AN ERROR MARGIN
 *
 * */

b8 CompareV4(v4 u, v4 v, f32 errorMargin);

/**
 *
 * CONVERSION FROM V4 TO V3
 *
 * */

v3 ConvertV4ToV3(v4 u);

//Matrix Operations

/**
 *
 * 2x2 Matrix Addition
 *
 * */

mat2x2 AddMatrix2x2(mat2x2 m1, mat2x2 m2);

/**
 *
 * 2x2 Matrix Subtraction
 *
 * */

mat2x2 SubMatrix2x2(mat2x2 m1, mat2x2 m2);

/**
 *
 * 2x2 Matrix Multiplication with Scalar
 *
 * */

mat2x2 ScalarMultMatrix2x2(f64 scalar, mat2x2 m1);

/**
 *
 * 2x2 Matrix with 2x2 Matrix Multiplication
 *
 * */

mat2x2 MultMatrix2x2(mat2x2 m1, mat2x2 m2);

/**
 *
 * 2x2 Matrix Determinant
 *
 * */

f32 DetMatrix2x2(mat2x2 m1);

/**
 *
 * 2x2 Matrix Transpose
 *
 * */

mat2x2 TransposeMatrix2x2(mat2x2 m1);

/**
 *
 * 2x2 Matrix Inverse
 *
 * */

mat2x2 InverseMatrix2x2(mat2x2 m1);

/**
 *
 * 2D Vector Multiplication with 2x2 Matrix
 *      Don't really like this function name
 *
 * */

v2 MultV2ByMatrix2x2(v2 u, mat2x2 m1);

/**
 *
 * RETURNS THE 2x2 IDENTITY MATRIX
 *
 * */
mat2x2 CreateIdentity2x2();

/**
 *
 * 3x3 Matrix Addition
 *
 * */

mat3x3 AddMatrix3x3(mat3x3 m1, mat3x3 m2);

/**
 *
 * 3x3 Matrix Subtraction
 *
 * */

mat3x3 SubMatrix3x3(mat3x3 m1, mat3x3 m2);

/**
 *
 * 2x2 Matrix Multiplication with Scalar
 *
 * */

mat3x3 ScalarMultMatrix3x3(f64 scalar, mat3x3 m1);

/**
 *
 * 3x3 Matrix Multiplication
 *
 * */

mat3x3 MultMatrix3x3(mat3x3 m1, mat3x3 m2);

/**
 *
 * 3x3 Matrix Determinant
 *
 * */

f32 DetMatrix3x3(mat3x3 m1);

/**
 *
 * 3x3 Matrix Transpose
 *
 * */

mat3x3 TransposeMatrix3x3(mat3x3 m1);

/**
 *
 * 3x3 Matrix Inverse
 *
 * */

mat3x3 InverseMatrix3x3(mat3x3 m1);

/**
 *
 * 3D Vector Multiplication with 3x3 Matrix
 *      Don't really like this function name
 *
 * */

v3 MultV3ByMatrix3x3(v3 u, mat3x3 m1);

/**
 *
 * RETURNS THE 3x3 IDENTITY MATRIX
 *
 * */
mat3x3 CreateIdentity3x3();

/**
 *
 * 4x4 Matrix Addition
 *
 * */

mat4x4 AddMatrix4x4(mat4x4 m1, mat4x4 m2);

/**
 *
 * 4x4 Matrix Subtraction
 *
 * */

mat4x4 SubMatrix4x4(mat4x4 m1, mat4x4 m2);

/**
 *
 * 4x4 Matrix Multiplication with Scalar
 *
 * */

mat4x4 ScalarMultMatrix4x4(f64 scalar, mat4x4 m1);

/**
 *
 * 4x4 Matrix Multiplication
 *
 * */

mat4x4 MultMatrix4x4(mat4x4 m1, mat4x4 m2);

/**
 *
 * 4x4 Matrix Determinant
 *
 * */

f32 DetMatrix4x4(mat4x4 m1);

/**
 *
 * 4x4 Matrix Transpose
 *
 * */

mat4x4 TransposeMatrix4x4(mat4x4 m1);

/**
 *
 * 4x4 Matrix Inverse
 *
 * */

mat4x4 InverseMatrix4x4(mat4x4 m1);

/**
 *
 * 4D Vector Multiplication with 4x4 Matrix
 *      Don't really like this function name
 *
 * */

v4 MultV4ByMatrix4x4(v4 u, mat4x4 m1);

/**
 *
 * RETURNS THE 4x4 IDENTITY MATRIX
 *
 * */
mat4x4 CreateIdentity4x4();

//Trig functions (we're not going to implement hyperbolics, hell no)

/**
 *
 * SINE FUNCTION WITH 32 BIT FLOAT RETURN
 *
 * */

f32 Sin32(f32 angleInRadians);

/**
 *
 * COSINE FUNCTION WITH 32 BIT FLOAT RETURN
 *
 * */

f32 Cos32(f32 angleInRadians);

/**
 *
 * TANGENT FUNCTION WITH 32 BIT FLOAT RETURN
 *
 * */

f32 Tg32(f32 angleInRadians);

/**
 *
 * COSECANT FUNCTION WITH 32 BIT FLOAT RETURN
 *
 * */

f32 Cosec32(f32 angleInRadians);

/**
 *
 * SECANT FUNCTION WITH 32 BIT FLOAT RETURN
 *
 * */

f32 Sec32(f32 angleInRadians);

/**
 *
 * COTANGENT FUNCTION WITH 32 BIT FLOAT RETURN
 *
 * */

f32 Cotg32(f32 angleInRadians);

/**
 *
 * SINE FUNCTION WITH 64 BIT FLOAT RETURN
 *
 * */

f64 Sin64(f64 angleInRadians);

/**
 *
 * COSINE FUNCTION WITH 64 BIT FLOAT RETURN
 *
 * */

f64 Cos64(f64 angleInRadians);

/**
 *
 * TANGENT FUNCTION WITH 64 BIT FLOAT RETURN
 *
 * */

f64 Tg64(f64 angleInRadians);

/**
 *
 * COSECANT FUNCTION WITH 64 BIT FLOAT RETURN
 *
 * */

f64 Cosec64(f64 angleInRadians);

/**
 *
 * SECANT FUNCTION WITH 64 BIT FLOAT RETURN
 *
 * */

f64 Sec64(f64 angleInRadians);

/**
 *
 * COTANGET FUNCTION WITH 64 BIT FLOAT RETURN
 *
 * */

f64 Cotg64(f64 angleInRadians);

//Other convenient functions

/**
 *
 * ANGLE UNIT CONVERSION FROM DEGREES TO ANGLES WITH 32 BIT FLOAT RETURN
 *
 * */

f32 DegreesToRadians32(f32 degrees);

/**
 *
 * SQUARE ROOT FUNCTION WITH 32 BIT FLOAT RETURN
 *
 * */

f32 Sqrt32(f32 x);

/**
 *
 * ABSOLUTE VALUE WITH 32 BIT FLOAT RETURN
 *
 * */

f32	Abs32(f32 x);

/**
 *
 * CLAMPING FUNCTION WITH 32 BIT FLOAT RETURN
 *
 * */

f32 Clamp32(f32 min, f32 max, f32 value);

/**
 *
 * FUNCTION RETURNS THE BIGGEST VALUE BETWEEN a AND b WITH 32 BIT FLOAT RETURN
 *
 * */

f32	Max32(f32 a, f32 b);

/**
 *
 * FUNCTION RETURNS THE SMALLEST VALUE BETWEEN a AND b WITH 32 BIT FLOAT RETURN
 *
 * */

f32	Min32(f32 a, f32 b);

/**
 *
 * RETURNS THE REMAINDER OF f1 WHEN DIVIDED BY f2 WITH 32 BIT FLOAT RETURN
 * 		IF positiveResult = TRUE, THEN THE RETURN VALUE WILL ALWAYS BE POSITIVE OR 0
 * 		OTHERWISE THE RETURN VALUES COULD BE NEGATIVE
 *
 * */

f32 Mod32(f32 f1, f64 f2, u8 positiveResult);

/**
 *
 * CEILING FUNCTION WITH 32 BIT INTEGER RETURN
 *
 * */

i32 Ceil32(f32 x);

/**
 *
 * FLOOR FUNCTION WITH 32 BIT INTEGER RETURN
 *
 * */

i32 Floor32(f32 x);

/**
 *
 * ROUNDING FUNCTION WITH 32 BIT INTEGER RETURN
 *
 * */

i32 Round32(f32 x);

/**
 *
 * ANGLE UNIT CONVERSION FROM DEGREES TO ANGLES WITH 64 BIT FLOAT RETURN
 *
 * */

f64 DegreesToRadians64(f64 degrees);

/**
 *
 * SQUARE ROOT FUNCTION WITH 64 BIT FLOAT RETURN
 *
 * */

f64	Sqrt64(f64 x);

/**
 *
 * ABSOLUTE VALUE WITH 64 BIT FLOAT RETURN
 *
 * */

f64	Abs64(f64 x);

/**
 *
 * CLAMPING FUNCTION WITH 64 BIT FLOAT RETURN
 *
 * */

f64 Clamp64(f64 min, f64 max, f64 value);

/**
 *
 * FUNCTION RETURNS THE BIGGEST VALUE BETWEEN a AND b WITH 64 BIT FLOAT RETURN
 *
 * */

f64	Max64(f64 a, f64 b);

/**
 *
 * FUNCTION RETURNS THE SMALLEST VALUE BETWEEN a AND b WITH 64 BIT FLOAT RETURN
 *
 * */

f64	Min64(f64 a, f64 b);

/**
 *
 * RETURNS THE REMAINDER OF f1 WHEN DIVIDED BY f2 WITH 64 BIT FLOAT RETURN
 * 		IF positiveResult = TRUE, THEN THE RETURN VALUE WILL ALWAYS BE POSITIVE OR 0
 * 		OTHERWISE THE RETURN VALUES COULD BE NEGATIVE
 *
 * */

f64 Mod64(f64 f1, f64 f2, u8 positiveResult);

/**
 *
 * CEILING FUNCTION WITH 64 BIT INTEGER RETURN
 *
 * */

i64 Ceil64(f64 x);

/**
 *
 * FLOOR FUNCTION WITH 64 BIT INTEGER RETURN
 *
 * */

i64 Floor64(f64 x);

/**
 *
 * ROUNDING FUNCTION WITH 64 BIT INTEGER RETURN
 *
 * */

i64 Round64(f64 x);

/**
 *
 * FUNCTION THAT RETURNS THE SIGN OF A NUMBER
 *      SINCE THE RETURN VALUE CAN ONLY BE -1 OR 1, WE'RE RETURNING A i8 here
 *      ALSO, THE RETURN VALUE FOR 0 IS GOING TO BE 1 IN THIS CASE
 * */

i8 Sign(f64 x);

//RANDOM FUNCTIONS

/**
 *
 * RETURNS A RANDOM 32 BIT UNSIGNED INTEGER
 *
 * */
u32 RandomU32();

/**
 *
 * RETURNS A RANDOM 32 BIT UNSIGNED INTEGER IN AN INTERVAL
 *
 * */
u32 RandomU32InInterval(u32 min, u32 max);

/**
 *
 * RETURNS A RANDOM BOOLEAN VALUE
 *
 * */
b8 RandomBool();

/**
 *
 * RETURNS A RANDOM SIGN (-1 OR 1)
 *
 * */
i8 RandomSign();

//GRAPHICS FUNCTIONS

/**
 *
 * CREATION OF A 3x3 MATRIX WHICH CAN TRANSLATE A 2D POINT (IN HOMOGENEOUS COORDINATE FORM) posDelta UNITS
 *
 * */
mat3x3 CreateTranslationMatrix2D(v2 posDelta);

/**
 *
 * CREATION OF A 3x3 MATRIX WHICH CAN SCALE A 2D POINT (IN HOMOGENEOUS COORDINATE FORM) IN scale UNITS
 *      BASED ON origin
 *
 * */
mat3x3 CreateScaleMatrixWithSetOrigin2D(v2 scale, v2 origin);

/**
 *
 * CREATION OF A 3x3 MATRIX WHICH CAN SCALE A 2D POINT (IN HOMOGENEOUS COORDINATE FORM) IN scale UNITS
 *      BASED ON (0,0) AS ORIGIN
 *
 * */
mat3x3 CreateScaleMatrix2D(v2 scale);

/**
 *
 * CREATION OF A 3x3 MATRIX WHICH CAN ROTATE A 2D POINT (IN HOMOGENEOUS COORDINATE FORM) IN angleVec RAD
 *      BASED ON pos
 *
 * */
mat3x3 CreateRotationAroundPointMatrix2D(f32 angleVec, v2 pos);

/**
 *
 * CREATION OF A 3x3 MATRIX WHICH CAN ROTATE A 2D POINT (IN HOMOGENEOUS COORDINATE FORM) IN angleVec RAD
 *      BASED ON (0,0) AS ORIGIN
 *
 * */
mat3x3 CreateRotationMatrix2D(f32 angleVec);

/**
 *
 * CREATES A 4x4 MATRIX WHICH TRANSLATES A 3D POINT (IN HOMOGENEOUS COORDINATE FORM) IN posDelta UNITS
 *
 * */
mat4x4 CreateTranslationMatrix3D(v3 posDelta);

/**
 *
 * CREATES A 4x4 MATRIX WHICH SCALES A 3D POINT (IN HOMOGENEOUS COORDINATE FORM) IN scale UNITS
 *
 * */
mat4x4 CreateScaleMatrix3D(v3 scale);

/**
 *
 * CREATES A 4x4 MATRIX WHICH ROTATES A 3D POINT (IN HOMOGENEOUS COORDINATE FORM) IN angle UNITS IN THE X AXIS
 *
 * */
mat4x4 CreateEulerRotationInXMatrix3D(f32 angle);

/**
 *
 * CREATES A 4x4 MATRIX WHICH ROTATES A 3D POINT (IN HOMOGENEOUS COORDINATE FORM) IN angle UNITS IN THE Y AXIS
 *
 * */
mat4x4 CreateEulerRotationInYMatrix3D(f32 angle);

/**
 *
 * CREATES A 4x4 MATRIX WHICH ROTATES A 3D POINT (IN HOMOGENEOUS COORDINATE FORM) IN angle UNITS IN THE Z AXIS
 *
 * */
mat4x4 CreateEulerRotationInZMatrix3D(f32 angle);

/**
 *
 * CREATES A 4x4 MATRIX WHICH ROTATES A 3D POINT (IN HOMOGENEOUS COORDINATE FORM) IN angle IN ALL THE AXIS
 *      (AXIS HIERARCHY IS X => Y => Z, Z IS THE MOST SIGNIFICANT)
 *
 * */
mat4x4 CreateEulerRotationInXYZMatrix3D(v3 angles);

/**
 *
 * CREATES A 4x4 MATRIX WHICH PROJECTS A 3D POINT (IN HOMOGENEOUS COORDINATE FORM) ONTO THE NEAR PLANE
 *      WITH PARALLEL PROJECTION
 *
 * */
mat4x4 CreateParallelProjectionMatrix3D(f32 l, f32 r, f32 t, f32 b, f32 f, f32 n);

/**
 *
 * CREATES A 4x4 MATRIX WHICH PROJECTS A 3D POINT (IN HOMOGENEOUS COORDINATE FORM) ONTO THE NEAR PLANE
 *      WITH PERSPECTIVE PROJECTION
 *
 * */
mat4x4 CreatePerspectiveProjectionMatrix3D(f32 fovY, f32 aspectRatio, f32 f, f32 n);

// GEOMETRY FUNCTIONS

/**
 *
 * CALCULATES THE EUCLIDEAN 32 FLOATING POINT DISTANCE BETWEEN TO 2D POINTS
 *
 * */
f32 DistanceBetweenPoints2D(point2D p, point2D q);

/**
 *
 * CALCULATES THE EUCLIDEAN 32 FLOATING POINT DISTANCE BETWEEN TO 3D POINTS
 *
 * */
f32 DistanceBetweenPoints3D(point3D p, point3D q);

/**
 *
 * CALCULATES THE DISTANCE BETWEEN POINT AND LINE IN 2D
 *
 * */
f32 DistanceBetweenPointAndLine2D(point2D p, line2D line);

/**
 *
 * CALCULATES THE DISTANCE BETWEEN TWO LINES IN 2D
 *
 * */
f32 DistanceBetweenLines2D(line2D line1, line2D line2);

/**
 *
 * CALCULATES THE DISTANCE BETWEEN POINT AND LINE IN 3D
 *
 * */
f32 DistanceBetweenPointAndLine3D(point3D p, line3D line);

/**
 *
 * CALCULATES THE DISTANCE BETWEEN TWO LINES IN 3D
 *
 * */
f32 DistanceBetweenLines3D(line3D line1, line3D line2);

/**
 *
 * CALCULATES THE DISTANCE BETWEEN A POINT AND A PLANE
 *
 * */
f32 DistanceBetweenPointAndPlane(point3D p, plane pl);

/**
 *
 * CALCULATES THE DISTANCE BETWEEN A LINE AND A PLANE
 *
 * */
f32 DistanceBetweenLineAndPlane(line3D line, plane pl);

/**
 *
 * CALCULATES THE DISTANCE BETWEEN TWO PLANES
 *
 * */
f32 DistanceBetweenPlanes(plane pl1, plane pl2);

/**
 *
 * CHECKS IF TWO LINES IN 2D ARE PARALLEL
 *
 * */
b8 ParallelLines2D(line2D l1, line2D l2);

/**
 *
 * CHECKS IF TWO LINES IN 3D ARE PARALLEL
 *
 * */
b8 ParallelLines3D(line3D l1, line3D l2);

/**
 *
 * CHECKS IF TWO LINES IN 2D ARE INTERSECTING
 *
 * */
b8 IntersectingLines2D(line2D l1, line2D l2);

/**
 *
 * CHECKS IF TWO LINES IN 3D ARE INTERSECTING
 *
 * */
b8 IntersectingLines3D(line3D l1, line3D l2);

/**
 *
 * CHECKS IF TWO LINES IN 3D ARE SKEW
 *
 * */
b8 SkewLines(line3D l1, line3D l2);

/**
 *
 * CHECKS FOR COLLISION BETWEEN TWO AXIS ALIGNED BOUNDING BOXES IN 2D, RETURNS TRUE IF THERE'S COLLISION
 *
 * */
b8 CollisionAABB2D(AABB2D r1, AABB2D r2);

/**
 *
 * CHECKS IF A CERTAIN POINT IS INSIDE AN AXIS ALIGNED BOUNDING BOX IN 2D, RETURNS TRUE IF THE POINTS IS INSIDE
 *
 * */
b8 CollisionPointAndAABB2D(point2D p, AABB2D r);

/**
 *
 * CHECKS IF A CERTAIN POINT IS INSIDE A CIRCLE, RETURNS TRUE IF THE POINT IS INSIDE
 *
 * */
b8 CollisionPointAndSphere2D(point2D p, sphere2D s);

/**
 *
 * CHECKS IF TWO CIRCLES ARE INTERSECTING EACH OTHER, RETURNS TRUE IF SO
 *
 * */
b8 CollisionSphere2D(sphere2D s1, sphere2D s2);

/**
 *
 * CHECKS FOR COLLISION BETWEEN TWO AXIS ALIGNED BOUNDING BOXES IN 3D, RETURNS TRUE IF THERE'S COLLISION
 *
 * */
b8 CollisionAABB3D(AABB3D r1, AABB3D r2);

/**
 *
 * CHECKS IF A CERTAIN POINT IS INSIDE AN AXIS ALIGNED BOUNDING BOX IN 3D, RETURNS TRUE IF THE POINTS IS INSIDE
 *
 * */
b8 CollisionPointAndAABB3D(point3D p, AABB3D r);

/**
 *
 * CHECKS IF A CERTAIN POINT IS INSIDE A SPHERE, RETURNS TRUE IF THE POINT IS INSIDE
 *
 * */
b8 CollisionPointAndSphere3D(point3D p, sphere3D s);

/**
 *
 * CHECKS IF TWO SPHERES ARE INTERSECTING EACH OTHER, RETURNS TRUE IF SO
 *
 * */
b8 CollisionSphere3D(sphere3D s1, sphere3D s2);

/**
 *
 * CALCULATES THE AREA OF A TRIANGLE IN 2D BASED ON ITS VERTICES COORDINATES
 *
 * */
f32 AreaTriangle2D(triangle2D triangle);

/**
 *
 * CALCULATES THE AREA OF A CIRCLE IN 2D BASED ON ITS RADIUS' LENGTH
 *
 * */
f32 AreaSphere2D(sphere2D sphere);

/**
 *
 * CALCULATES THE AREA OF AN AABB BASED ON ITS MAXIMUM AND MINIMUM POINTS IN 2D
 *
 * */
f32 AreaAABB2D(AABB2D aabb);

/**
 *
 * CALCULATES THE AREA OF A QUAD IN 2D BASED ON ITS VERTICES' COORDINATES
 *
 * */
f32 AreaQuad2D(quad2D quad);

/**
 *
 * CALCULATES THE PERIMETER OF A CIRCLE BASED ON ITS RADIUS' LENGTH
 *
 * */
f32 PerimeterSphere2D(sphere2D sphere);

/**
 *
 * CALCULATES THE PERIMETER OF AN AABB IN 2D BASED ON ITS MAXIMUM AND MINIMUM COORDINATES
 *
 * */
f32 PerimeterAABB2D(AABB2D aabb);

/**
 *
 * CALCULATES THE PERIMETER OF A QUAD BASED ON ITS VERTICES' COORDINATES
 *
 * */
f32 PerimeterQuad2D(quad2D quad);

/**
 *
 * CALCULATES THE PERIMETER OF A TRIANGLE BASED ON ITS VERTICES' COORDINATES
 *
 * */
f32 PerimeterTriangle2D(triangle2D triangle);

/**
 *
 * CALCULATES THE AREA OF A TRIANGLE IN 3D BASED ON ITS VERTICES' COORDINATES
 *
 * */
f32 AreaTriangle3D(triangle3D triangle);

/**
 *
 *  CALCULATES THE AREA OF A QUAD IN 3D BASED ON ITS VERTICES' COORDINATES
 *
 * */
f32 AreaQuad3D(quad3D quad);

/**
 *
 * CALCULATES THE VOLUME OF A SPHERE BASED ON ITS RADIUS' LENGTH
 *
 * */
f32 VolumeSphere3D(sphere3D sphere);

/**
 *
 * CALCULATES THE VOLUME OF AN AABB IN 3D BASED ON ITS MAXIMUM AND MINIMUM POINTS
 *
 * */
f32 VolumeAABB3D(AABB3D aabb);

/**
 *
 * CALCULATES THE PERIMETER OF A TRIANGLE IN 3D BASED ON ITS VERTICES' COORDINATES
 *
 * */
f32 PerimeterTriangle3D(triangle3D triangle);

/**
 *
 * CALCULATES THE SURFACE AREA OF A SPHERE IN 3D BASED ITS RADIUS' LENGTH
 *
 * */
f32 SurfaceAreaSphere3D(sphere3D sphere);

/**
 *
 * CALCULATES THE SURFACE AREA OF AN AABB IN 3D BASED ITS MAXIMUM AND MINIMUM POINTS
 *
 * */
f32 SurfaceAreaAABB3D(AABB3D aabb);

/**
 *
 * PERFORMS THE ADDITION OF TWO LINE SEGMENTS IN 2D
 *
 * */
lineSegment2D AddLineSegment2D(lineSegment2D l1, lineSegment2D l2);

/**
 *
 * PERFORMS THE SUBTRACTION OF TWO LINE SEGMENTS IN 2D
 *
 * */
lineSegment2D SubtractLineSegment2D(lineSegment2D l1, lineSegment2D l2);

/**
 *
 * VERIFIES IF A LINE SEGMENT IS A NULL LINE SEGMENT
 *
 * */
b8 LineSegment2DIsNull(lineSegment2D l);

/**
 *
 * VERIFIES IF TWO LINE SEGMENTS HAVE OPPOSITE START AND END
 *
 * */
b8 LineSegments2DAreOpposite(lineSegment2D l1, lineSegment2D l2);

/**
 *
 * VERIFIES IF TWO LINE SEGMENTS HAVE THE SAME LENGTH
 *
 * */
b8 LineSegments2DHaveEqualLength(lineSegment2D l1, lineSegment2D l2);

/**
 *
 * VERIFIES IF TWO LINE SEGMENTS HAVE THE SAME DIRECTIONS
 *
 * */
b8 LineSegments2DAreParallel(lineSegment2D l1, lineSegment2D l2);

/**
 *
 * VERIFIES IF TWO LINE SEGMENTS HAVE OPPOSITE DIRECTIONS
 *
 * */
b8 LineSegments2DHaveOppositeDirection(lineSegment2D l1, lineSegment2D l2);

/**
 *
 * PERFORMS THE ADDITION OF TWO LINE SEGMENTS IN 3D
 *
 * */
lineSegment3D AddLineSegment3D(lineSegment3D l1, lineSegment3D l2);

/**
 *
 * PERFORMS THE SUBTRACTION OF TWO LINE SEGMENTS IN 2D
 *
 * */
lineSegment3D SubtractLineSegment3D(lineSegment3D l1, lineSegment3D l2);

/**
 *
 * VERIFIES IF A LINE SEGMENT IS A NULL LINE SEGMENT
 *
 * */
b8 LineSegment3DIsNull(lineSegment3D l);

/**
 *
 * VERIFIES IF TWO LINE SEGMENTS HAVE OPPOSITE START AND END
 *
 * */
b8 LineSegments3DAreOpposite(lineSegment3D l1, lineSegment3D l2);

/**
 *
 * VERIFIES IF TWO LINE SEGMENTS HAVE THE SAME LENGTH
 *
 * */
b8 LineSegments3DHaveEqualLength(lineSegment3D l1, lineSegment3D l2);

/**
 *
 * VERIFIES IF TWO LINE SEGMENTS HAVE THE SAME DIRECTIONS
 *
 * */
b8 LineSegments3DAreParallel(lineSegment3D l1, lineSegment3D l2);

/**
 *
 * VERIFIES IF TWO LINE SEGMENTS HAVE OPPOSITE DIRECTIONS
 *
 * */
b8 LineSegments3DHaveOppositeDirection(lineSegment3D l1, lineSegment3D l2);
