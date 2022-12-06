#pragma once
struct Plan {
	int xposition;
	int rotation;
	int score;

	Plan(int XPOSITION, int ROTATION) {
		xposition = XPOSITION; rotation = ROTATION; score = 0;
	}

	Plan(const Plan &plan)
	{
		xposition = plan.xposition; rotation = plan.rotation; score = plan.score;
	}
};
#include <iostream>
class Robotas
{
public:
	int xposition;
	int rotation;
	int score;
	int mode = 0;
public:
	Robotas(int XPOSITION, int ROTATION);
private:

	void CalculatePlanScore(Plan &plan);
};