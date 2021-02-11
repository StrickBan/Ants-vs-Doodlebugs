#pragma once

#ifndef ANT_H
#define ANT_H

#include <iostream>
#include "Organism.h"

using namespace std;

	class ant : public organism
	{
	public:
		ant(int yPos, int xPos);
		virtual void move(organism *** grid);
		virtual void breed(organism *** grid);
	};

#endif // !ANT_H

