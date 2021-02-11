#pragma once
#ifndef ORGANISM_H
#define ORGANISM_H
#include <iostream>
#include <string>

using namespace std;
	class organism {
	public:
		organism();
		virtual void move(organism *** grid);
		virtual void breed(organism *** grid);
		void setY(int newY);
		void setX(int newX);
		void setStepsSurvived(int newSteps);
		void setType(string newType);
		void setMoved(bool newMoved);
		int getXPos();
		int getYPos();
		int getStepsSurvived() const;
		string getType() const;
		bool getMoved();

	private:
		int yPos;
		int xPos;
		int stepsSurvived;
		string type;
		bool moved;
};

#endif 

