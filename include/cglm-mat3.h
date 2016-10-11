/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef cglm_mat3_h
#define cglm_mat3_h

#include "cglm.h"
#include "cglm-mat3-simd-sse2.h"

#define GLM_MAT3_IDENTITY_INIT  {{1.0f, 0.0f, 0.0f},                          \
                                 {0.0f, 1.0f, 0.0f},                          \
                                 {0.0f, 0.0f, 1.0f}}

/* for C only */
#define GLM_MAT3_IDENTITY (mat3)GLM_MAT3_IDENTITY_INIT

/*!
 * @brief copy all members of [mat] to [dest]
 *
 * @param[in]  mat  source
 * @param[out] dest destination
 */
CGLM_INLINE
void
glm_mat3_dup(mat3 mat, mat3 dest) {
  glm__memcpy(float, dest, mat, sizeof(mat3));
}

/*!
 * @brief multiply m1 and m2 to dest
 *
 * m1, m2 and dest matrices can be same matrix, it is possible to write this:
 *
 * @code
 * mat3 m = GLM_MAT3_IDENTITY_INIT;
 * glm_mat3_mul(m, m, m);
 * @endcode
 *
 * @param[in]  m1   left matrix
 * @param[in]  m2   right matrix
 * @param[out] dest destination matrix
 */
CGLM_INLINE
void
glm_mat3_mul(mat3 m1, mat3 m2, mat3 dest) {
#if defined( __SSE__ ) || defined( __SSE2__ )
  glm_mat3_mul_sse2(m1, m2, dest);
#else
  float a00, a01, a02,    b00, b01, b02,
        a10, a11, a12,    b10, b11, b12,
        a20, a21, a22,    b20, b21, b22;

  a00 = m1[0][0], a01 = m1[0][1], a02 = m1[0][2],
  a10 = m1[1][0], a11 = m1[1][1], a12 = m1[1][2],
  a20 = m1[2][0], a21 = m1[2][1], a22 = m1[2][2],

  b00 = m2[0][0], b01 = m2[0][1], b02 = m2[0][2],
  b10 = m2[1][0], b11 = m2[1][1], b12 = m2[1][2],
  b20 = m2[2][0], b21 = m2[2][1], b22 = m2[2][2],

  dest[0][0] = a00 * b00 + a10 * b01 + a20 * b02;
  dest[0][1] = a01 * b00 + a11 * b01 + a21 * b02;
  dest[0][2] = a02 * b00 + a12 * b01 + a22 * b02;
  dest[1][0] = a00 * b10 + a10 * b11 + a20 * b12;
  dest[1][1] = a01 * b10 + a11 * b11 + a21 * b12;
  dest[1][2] = a02 * b10 + a12 * b11 + a22 * b12;
  dest[2][0] = a00 * b20 + a10 * b21 + a20 * b22;
  dest[2][1] = a01 * b20 + a11 * b21 + a21 * b22;
  dest[2][2] = a02 * b20 + a12 * b21 + a22 * b22;
#endif
}

/*!
 * @brief transpose mat3 and store in dest
 *
 * source matrix will not be transposed unless dest is m
 *
 * @param m[in]     matrix
 * @param dest[out] result
 */
CGLM_INLINE
void
glm_mat3_transpose_to(mat3 m, mat3 dest) {
  dest[0][0] = m[0][0];
  dest[0][1] = m[1][0];
  dest[0][2] = m[2][0];
  dest[1][0] = m[0][1];
  dest[1][1] = m[1][1];
  dest[1][2] = m[2][1];
  dest[2][0] = m[0][2];
  dest[2][1] = m[1][2];
  dest[2][2] = m[2][2];
}

/*!
 * @brief tranpose mat3 and store result in same matrix
 *
 * @param[in, out] m source and dest
 */
CGLM_INLINE
void
glm_mat3_transpose(mat3 m) {
  mat3 tmp;

  tmp[0][1] = m[1][0];
  tmp[0][2] = m[2][0];
  tmp[1][0] = m[0][1];
  tmp[1][2] = m[2][1];
  tmp[2][0] = m[0][2];
  tmp[2][1] = m[1][2];

  m[0][1] = tmp[0][1];
  m[0][2] = tmp[0][2];
  m[1][0] = tmp[1][0];
  m[1][2] = tmp[1][2];
  m[2][0] = tmp[2][0];
  m[2][1] = tmp[2][1];
}

/*!
 * @brief multiply mat3 with vec3 (column vector) and store in dest vector
 *
 * @param[in]  m    mat3 (left)
 * @param[in]  v    vec3 (right, column vector)
 * @param[out] dest vec3 (result, column vector)
 */
CGLM_INLINE
void
glm_mat3_mulv(mat3 m, vec3 v, vec3 dest) {
  dest[0] = m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2];
  dest[1] = m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2];
  dest[2] = m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2];
}

#endif /* cglm_mat3_h */
