#ifndef __GAME_MATH_H__
#define __GAME_MATH_H__

#include <cstdlib>
#include <iostream>
#include <SDL_rect.h>

static const float PI_OVER_180 = (float)(3.14159265358979323846 / 180.0f);
static const float _180_OVER_PI = (float)(180.0f / 3.14159265358979323846);

inline float toRadians(float deg) {
	return deg * PI_OVER_180;
}

inline float toDegrees(float rad) {
	return rad * _180_OVER_PI;
}

/**
* Init srand() before to get different random values every time you start program
*
* @return
*			a random integer value between "min" and "max", both inclusive
*/
inline int getRandom(int min, int max) {
	return (int)(rand() % (max - min)) + min;
}
inline float getRandomFloat(float fmin, float fmax) { //only does randomness rounded to 1dp
	return (float)10 / (float)getRandom(fmin * 10, fmax * 10);
}

struct Vector2f {
	float x;
	float y;

	Vector2f() : Vector2f(0.0f, 0.0f) {}
	Vector2f(float x, float y) : x(x), y(y) {}

	Vector2f& operator+=(const Vector2f& v) {
		x += v.x;
		y += v.y;
		return *this;
	}
	Vector2f& operator+(const Vector2f& v) {
		return *new Vector2f(x + v.x, y+ v.y);
	}
	Vector2f& operator*(const float& f) {
		x *= f;
		y *= f;
		return *this;
	}
	Vector2f* operator-(const Vector2f& v) {
		float newx = x - v.x;
		float newy = y - v.y;
		return new Vector2f(newx, newy);
	}
	static Vector2f* Normalise(const Vector2f& v) {
		float length = Magnitude(v);
		return new Vector2f(v.x / length, v.y / length);
	}
	static Vector2f* Scale(const Vector2f& v, float scale) {
		return new Vector2f(v.x * scale, v.y * scale);
	}
	static Vector2f* GetRandomNormalisedVector() {
		Vector2f* randomVector = new Vector2f((float)getRandom(-10, 10), (float)getRandom(-10,10));
		return Normalise(*randomVector);
	}
	static Vector2f* GetRandomNormalisedVectorPointingTowards(Vector2f* origin, Vector2f* destination) {
		Vector2f* randomVector = GetRandomNormalisedVector();
		//instead of finding the angle between the random vector and the vector to the centre to
		//make sure it is pointing that way, we just add the vector and see if it takes it closer,
		//if it doesnt then we just invert it

		//get the distance before and after adding the random vector
		Vector2f* originalDifference = *origin - *destination;
		float originalDist = Magnitude(*originalDifference);
		*origin += *randomVector;
		Vector2f* newDifference = *origin - *destination;
		float newDist = Magnitude(*newDifference);
		//if adding the vector brings it further from the middle then invert it and return that
		if (newDist > originalDist) {
			return Normalise(*randomVector * -1);
		}
		return Normalise(*randomVector);
	}
	static float Magnitude(const Vector2f& v) {
		return sqrt(v.x * v.x + v.y * v.y);
	}
	static float Vector2fToDegrees(Vector2f& v) {
		double deg =  SDL_atan(v.y/v.x);
		deg = toDegrees(deg);
		//this only represents all angles facing right, so we just check if the angle is facing
		//left (if it has a negative x componenent), and if so we add 180 to flip it
		if (v.x < 0) {
			deg += 180;
		}
		return deg;
	}
};

struct Vector2i {
	int x;
	int y;

	Vector2i() : Vector2i(0, 0) {}
	Vector2i(int x, int y) : x(x), y(y) {}
};

struct Point2 {
	int x, y;

	Point2() : Point2(0, 0) {}
	Point2(int x, int y) : x(x), y(y) {}
	Point2& operator*(const float& f) {
		x = x * f;
		y = y * f;
		return *this;
	}
	Point2& operator*(const int& i) {
		x = x * i;
		y = y * i;
		return *this;
	}

	Point2& operator+=(const Point2& v) {
		x += v.x;
		y += v.y;
		return *this;
	}
	Point2& operator+(const Point2& v) {

		return *new Point2(x + v.x, y + v.y);
	}
	Point2& operator-(const Point2& v) {

		return *new Point2(x - v.x, y - v.y);
	}
	Point2& operator-=(const Point2& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}

    Point2& operator+=(const Vector2f& v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    Point2& operator-=(const Vector2f& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }
};

struct Line2i {
	Point2 start, end;

	Line2i() : Line2i(Point2(), Point2()) {}
	Line2i(const Point2 & start, const Point2 & end) : start(start), end(end) {}
};

struct Rectangle2 {
	int x, y, w, h;

	Rectangle2(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}

	SDL_Rect getSDLRect() const {
		SDL_Rect rect = { x, y, w, h };
		return rect;
	}

	inline bool contains(const Point2 & p) {
		return p.x >= x && p.x <= x + w
			&& p.y >= y && p.y <= y + h;
	}

	inline bool intersects(const Rectangle2 & other) {
        SDL_Rect rect1 = getSDLRect();
        SDL_Rect rect2 = other.getSDLRect();

		return SDL_HasIntersection(&rect1, &rect2) == SDL_TRUE;
	}

	inline bool intersects(const Line2i & line) {
		int x1 = line.start.x, y1 = line.start.y, x2 = line.end.x, y2 = line.end.y;
		SDL_Rect rect = { x, y, w, h };
		return SDL_IntersectRectAndLine(&rect, &x1, &y1, &x2, &y2) == SDL_TRUE;
	}
};

struct Rectangle2f {
    float x, y, w, h;

    Rectangle2f(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

    SDL_Rect getSDLRect() const {
        SDL_Rect rect = { x, y, w, h };
        return rect;
    }

    inline bool contains(const Point2& p) {
        return p.x >= x && p.x <= x + w
            && p.y >= y && p.y <= y + h;
    }

    inline bool intersects(const Rectangle2f& other) {
        SDL_Rect rect1 = getSDLRect();
        SDL_Rect rect2 = other.getSDLRect();

        return SDL_HasIntersection(&rect1, &rect2) == SDL_TRUE;
    }

    inline bool intersects(const Line2i& line) {
        int x1 = line.start.x, y1 = line.start.y, x2 = line.end.x, y2 = line.end.y;
        SDL_Rect rect = { x, y, w, h };
        return SDL_IntersectRectAndLine(&rect, &x1, &y1, &x2, &y2) == SDL_TRUE;
    }
};

typedef Rectangle2 Rect;
typedef Rectangle2f Rectf;

struct Dimension2i {
	int w, h;

	Dimension2i() : Dimension2i(0, 0) {}
	Dimension2i(int w, int h) : w(w), h(h) {}
};


#endif
