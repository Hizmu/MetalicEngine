#pragma once
#include <DirectXColors.h>
enum class Color
{

};
/*
using Color = DirectX::XMVECTORF32 ;
class Shape
{
public:
	Shape() { }
	Shape(Color color, float width, float height, int x, int y) :color(color), width(width), height(height), x(x), y(x) {};
	Shape(Color color, float width, float height) :color(color), width(width), height(height) {};
	Shape(float width, float height) : width(width), height(height) {};
	~Shape() {}
public:

	virtual void setColor(Color color) { this->color = color; };
	virtual Color getColor() { return color; };
	virtual Vertex getVertex() = 0;

	virtual void setWidth(float width) { this->width = width; }
	virtual void setHeight(float height) { this->height = height; }
	virtual float getWidth() { return width; }
	virtual float getHeight() { return height; }


	virtual void setX(int X) { this->x = x; };
	virtual void setY(int Y) { this->y = y; };
	virtual int getX() { return this->x; };
	virtual int getY() { return this->y; };
private:
	Color color;
	Vertex vertex;
	float width = 0, height = 0;
	int x = 0, y = 0;
};

class Triangle : public Shape
{
public:
	Triangle() {}
	~Triangle() {};

};*/