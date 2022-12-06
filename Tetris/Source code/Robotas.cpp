#include "Robotas.h"

Plan bestPlan(0, 0);

void Robotas::CalculatePlanScore(Plan &plan) {
	// CALCULATE SOMEHOW
	// ...
	// ...
	//turn.score = 0;
}

Robotas::Robotas(int XPOSITION, int ROTATION)
{
	xposition = XPOSITION; rotation = ROTATION; score = -10000;
}
