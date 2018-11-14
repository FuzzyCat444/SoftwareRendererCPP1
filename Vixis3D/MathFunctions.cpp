#include "MathFunctions.h"

int fastFloor(double x) {
	int i = static_cast<int>(x);
	return i - (x < 0.0);
}

int fastCeil(double x) {
	int i = static_cast<int>(x);
	return i + (x > 0.0);
}

int fastRound(double x) {
	return fastFloor(x + 0.5);
}

int sgn(double x) {
	return (x >= 0) - (x < 0);
}