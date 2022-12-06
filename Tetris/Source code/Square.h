#pragma once

#include "Renderer.h"
#include "VertexBufferLayout.h"

class _Square
{
public:
	int nr;
private:
	float x, y;
	float width, length;

	float pozicijos[16];

	static unsigned int indices[];

	//VertexArray va;
	VertexBufferLayout layout;

public:
	_Square(float X, float Y, float WIDHT, float LENGHT, int NR);
	_Square(const _Square &temp);
	void _Draw(Shader &shader, Renderer &renderer);
	void Move(float x, float y);
	void MoveA(float x, float y);
};