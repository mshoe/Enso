#pragma once
class Shape
{
public:
	Shape();
	virtual ~Shape();

	float radius;
	float width;
	float height;
};

class Circle : public Shape
{
public:
	Circle(float radius_);
	virtual ~Circle();

private:
	Circle() {}
};

class Rectangle : public Shape
{
public:
	Rectangle(float width_, float height_);
	virtual ~Rectangle();

private:
	Rectangle() {}
};