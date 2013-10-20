#ifndef CG_CW_COMMON_H
#define CG_CW_COMMON_H

#include "Vector3.h"

static const Vector3 DEFAULT_TRI_COLOUR = Vector3(1.0f, 0.0f, 0.0f);
static const Vector3 ALTERNATING_TRIANGLE_COLOURS[] = {
	Vector3(1.0f, 0.0f, 0.0f),
	Vector3(0.0f, 1.0f, 0.0f),
	Vector3(0.0f, 0.0f, 1.0f),
	Vector3(1.0f, 1.0f, 0.0f),
	Vector3(1.0f, 0.0f, 1.0f),
	Vector3(0.0f, 1.0f, 1.0f),
	Vector3(1.0f, 1.0f, 1.0f),
	Vector3(0.0f, 0.0f, 0.0f),
	Vector3(0.5f, 0.5f, 0.5f),
	Vector3(0.9f, 0.1f, 0.6f),
	Vector3(0.4f, 0.3f, 0.9f),
	Vector3(0.2f, 0.8f, 0.2f),
};
static const unsigned int NUM_ALTERNATING_COLOURS = 12;

#endif
