#include "Point.h"


//IntVector2

int IntVector2::get_x() const {
	return x;
}

int IntVector2::get_y() const {
	return y;
}

IntVector2 IntVector2::operator+(const int n) {
	return IntVector2(x + n, y + n);
}

IntVector2 IntVector2::operator+(const IntVector2& src) {
	return IntVector2(x + src.x, y + src.y);
}

IntVector2 IntVector2::operator-(const int n) {
	return IntVector2(x - n, y - n);
}

IntVector2 IntVector2::operator-(const IntVector2& src) {
	return IntVector2(x - src.x, y - src.y);
}

IntVector2 IntVector2::operator*(const int n) {
	return IntVector2(x * n, y * n);
}

IntVector2 IntVector2::operator/(const int n) {
	return IntVector2(x / n, y / n);
}

bool IntVector2::operator==(const IntVector2& src) {
	return (x == src.x) && (y == src.y);
}

bool IntVector2::operator!=(const IntVector2& src) {
	return (x != src.x) || (y != src.y);
}

bool operator<(const IntVector2& src1, const IntVector2& src2) {
	return (src1.x < src2.x) || (src1.x == src2.x && src1.y < src2.y);
}
