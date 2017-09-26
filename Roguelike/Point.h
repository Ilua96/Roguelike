#pragma once


class IntVector2
{
private:
	int x;
	int y;
public:
	IntVector2() : x(0), y(0) {};
	IntVector2(const int x, const int y) : x(x), y(y) {};
	IntVector2(const IntVector2& src) : x(src.x), y(src.y) {};
	~IntVector2() {};
	int get_x() const;
	int get_y() const;
	IntVector2 operator+(const int n);
	IntVector2 operator+(const IntVector2& src);
	IntVector2 operator-(const int n);
	IntVector2 operator-(const IntVector2& src);
	IntVector2 operator*(const int n);
	IntVector2 operator/(const int n);
	bool operator==(const IntVector2& src);
	bool operator!=(const IntVector2& src);
	friend bool operator<(const IntVector2& src1, const IntVector2& src2);
};