#pragma once

#ifndef DOODLEBUG_H
#define DOODLEBUG_H

#include "Organism.h"

	class doodlebug : public organism {
	public:
		doodlebug(int yPos, int xPos);
		virtual void move(organism *** grid);
		virtual void breed(organism *** grid);
		void setStepsStarving(int newStepsStarving);
		int getStepsStarving() const;

	private:
		int stepsStarving;
	};

#endif
