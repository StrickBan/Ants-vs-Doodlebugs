// hw13.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Organism.h"
#include "Doodlebug.h"
#include "Ant.h"

using namespace std;
int const GRIDSIZE = 20;

/*Functions*/
void draw(organism *** grid);
void initialize(organism *** grid);
void moveGrid(organism *** grid);
void breedGrid(organism *** grid);


/*Organism Class*/

	organism::organism() {
		setStepsSurvived(0);
		setMoved(true);
	}
	void organism::setX(int newX) {
		xPos = newX;
	}
	void organism::setY(int newY) {
		yPos = newY;
	}
	void organism::setStepsSurvived(int newSteps) {
		stepsSurvived = newSteps;
	}
	void organism::setType(string newType) {
		type = newType;
	}
	void organism::setMoved(bool newMoved) {
		moved = newMoved;
	}
	int organism::getXPos()  {
		return xPos;
	}
	int organism::getYPos()  {
		return yPos;
	}
	int organism::getStepsSurvived() const {
		return stepsSurvived;
	}
	string organism::getType() const {
		return type;
	}
	bool organism::getMoved() {
		return moved;
	}
	void organism::move(organism *** grid) {
		cout << "not available for organism class";
	}
	void organism::breed(organism *** grid) {
		cout << "not available for organism class";
	}

/*Doodlebug Class*/

	doodlebug::doodlebug(int yPos, int xPos) {
		organism();
		setX(xPos);
		setY(yPos);
		setStepsStarving(0);
		setType("doodlebug");
	}
	void doodlebug::move(organism *** grid) {
		setStepsSurvived(getStepsSurvived() + 1);
		setMoved(true);
		bool hasEaten = false;

		/*looks for ants*/	 /*chose to program a clockwise search as it does not specify that it's a random direction search*/
		int antDirection = 1;
		while (antDirection <=4){ 
			if (hasEaten == false) {
				/*1 = Up*/
				if (antDirection == 1) {
					if (getYPos() - 1 >= 0) {
						if (grid[getYPos() - 1][getXPos()] != NULL) {
							if (grid[getYPos() - 1][getXPos()]->getType() == "ant") {
								grid[getYPos() - 1][getXPos()] = NULL;
								grid[getYPos() - 1][getXPos()] = this;
								grid[getYPos()][getXPos()] = NULL;
								setStepsStarving(0);
								setY(getYPos() - 1);
								hasEaten = true;
							}
						}
					}
				}
				/* 2 = Right*/
				if (antDirection == 2) {
					if ((getXPos() + 1) < GRIDSIZE){
					if (grid[getYPos()][getXPos() + 1] != NULL) {
						if (grid[getYPos()][getXPos() + 1]->getType() == "ant") {
							grid[getYPos()][getXPos() + 1] = NULL;
							grid[getYPos()][getXPos() + 1] = this;
							grid[getYPos()][getXPos()] = NULL;
							setStepsStarving(0);
							setX(getXPos() + 1);
							hasEaten = true;
						}
					}
				}
				}
				/* 3 = Down*/
				if (antDirection == 3) {
					if ((getYPos() + 1) < GRIDSIZE) {
						if (grid[getYPos() + 1][getXPos()] != NULL) {
							if (grid[getYPos() + 1][getXPos()]->getType() == "ant") {
								grid[getYPos() + 1][getXPos()] = NULL;
								grid[getYPos() + 1][getXPos()] = this;
								grid[getYPos()][getXPos()] = NULL;
								setStepsStarving(0);
								setY(getYPos() + 1);
								hasEaten = true;
							}
						}
					}
				}
				/* 4 = Left*/
				else {
					if ((getXPos() - 1) >= 0) {
						if (grid[getYPos()][getXPos() - 1] != NULL) {
							if (grid[getYPos()][getXPos() - 1]->getType() == "ant") {
								grid[getYPos()][getXPos() - 1] = NULL;
								grid[getYPos()][getXPos() - 1] = this;
								grid[getYPos()][getXPos()] = NULL;
								setStepsStarving(0);
								setX(getXPos() - 1);
								hasEaten = true;
							}
						}
					}
				}
			}
			antDirection++;
		}
		/*setting random direction*/
		srand((unsigned int)time(0));
		int direction;
		direction = (rand() %  4) +1;

		if (hasEaten == false) {
			/*if 1 = Up*/
			if (direction == 1) {
				if (getYPos() - 1 >= 0) {
					if (grid[getYPos()][getXPos() + 1] == NULL) {
						grid[getYPos() - 1][getXPos()] = this;
						grid[getYPos()][getXPos()] = NULL;
						setY(getYPos() - 1);
					}
				}
			}

			/*if 2 = Right*/
			else if (direction == 2) {
				if (getXPos() + 1 < GRIDSIZE) {
					if (grid[getYPos()][getXPos() + 1] == NULL){
						grid[getYPos()][getXPos() + 1] = this;
						grid[getYPos()][getXPos()] = NULL;
						setX(getXPos() + 1);
					}
				}
			}
			/*if 3 = Down*/
			else if (direction == 3) {
				if (getYPos() + 1 < GRIDSIZE) {
					if (grid[getYPos()][getXPos() + 1] == NULL) {
						grid[getYPos() + 1][getXPos()] = this;
						grid[getYPos()][getXPos()] = NULL;
						setY(getYPos() + 1);
					}
				}
			}

			else {
				/* 4 = Left*/
				if (getXPos() - 1 >= 0) {
					if (grid[getYPos()][getXPos() + 1] == NULL) {
						grid[getYPos()][getXPos() - 1] = this;
						grid[getYPos()][getXPos()] = NULL;
						setX(getXPos() - 1);
					}
				}
			}
		}

		/*If the doodlebug didn't eat, starving counter goes up*/
		if (hasEaten == false) {
			setStepsStarving(getStepsStarving() + 1);
		}

		/*if it hasn't eaten for 3 days, it dies*/
		if (getStepsStarving() >= 3) {
			grid[getYPos()][getXPos()] = NULL;
		}
	}
	void doodlebug::breed(organism *** grid) {
		if (getStepsSurvived() % 8 == 0) {
			bool hasBred = false;
			/*implementing a clockwise search as it does not say that a random direction is set */
			for (int direction = 1; direction <= 4; direction++) {
				if (hasBred == false) {
					/* 1 = Up*/
					if (direction == 1) {
						if (getYPos() - 1 >= 0) {
							if (grid[getYPos() - 1][getXPos()]== NULL) {
								grid[getYPos() - 1][getXPos()] = new doodlebug(getYPos() - 1, getXPos());
								hasBred = true;
							}
						}
					}
					/* 2 = Right*/
					else if (direction == 2) {
						if (getXPos() + 1 < GRIDSIZE) {
							if (grid[getYPos()][getXPos() + 1] == NULL) {
								grid[getYPos()][getXPos() + 1] = new doodlebug(getYPos(), getXPos() + 1);
								hasBred = true;
							}
						}
					}
					/* 3 = Down*/
					else if (direction == 3) {
						if (getYPos() + 1 < GRIDSIZE) {
							if (grid[getYPos() + 1][getXPos()] == NULL) {
								grid[getYPos() + 1][getXPos()] = new doodlebug(getYPos() + 1, getXPos());
								hasBred = true;
							}
						}
					}
					/* 4 = Left*/
					else {
						if (getXPos() - 1 >= 0) {
							if (grid[getYPos()][getXPos() - 1]== NULL) {
								grid[getYPos()][getXPos() - 1] = new doodlebug(getYPos(), getXPos() - 1);
								hasBred = true;
							}
						}
					}
				}
			}
	   }
	}
	void doodlebug::setStepsStarving(int newStepsStarving) {
		stepsStarving = newStepsStarving;
	}
	int doodlebug::getStepsStarving() const {
		return stepsStarving;
	}


/* Ant Class*/

	ant::ant(int yPos, int xPos) {
		organism();
		setX(xPos);
		setY(yPos);
		setType("ant");
	}
	void ant::move(organism *** grid) {
		int direction;
		
		setStepsSurvived(getStepsSurvived() + 1);
		setMoved(true);
		srand((unsigned int)time(0));
		direction = (rand() % 4) + 1;
		
		/* if 1 = Up */
		if (direction == 1) {
			if (getYPos() - 1 >= 0) {
				if (grid[getYPos() - 1][getXPos()] == NULL) {
					grid[getYPos() - 1][getXPos()] = this;
					grid[getYPos()][getXPos()] = NULL;
					setY(getYPos() - 1);
				}
			}
		}

		/* if 2 = Right */
		else if (direction == 2) {
			if (getXPos() + 1 < GRIDSIZE) {
				if (grid[getYPos()][getXPos() + 1] == NULL) {
					grid[getYPos()][getXPos() + 1] = this;
					grid[getYPos()][getXPos()] = NULL;
					setX(getXPos() + 1);
				}
			}
		}

		/* if 3 = Down */
		else if (direction == 3) {
			if (getYPos() + 1 < GRIDSIZE) {
				if (grid[getYPos() + 1][getXPos()] == NULL) {
					grid[getYPos() + 1][getXPos()] = this;
					grid[getYPos()][getXPos()] = NULL;
					setY(getYPos() + 1);
				}
			}
		}
		/* if 4 = Left*/
		else  {
			if (getXPos() - 1 >= 0) {
				if (grid[getYPos()][getXPos() - 1] == NULL) {
					grid[getYPos()][getXPos() - 1] = this;
					grid[getYPos()][getXPos()] = NULL;
					setX(getXPos() - 1);
				}
			}
		}
	}
	void ant::breed(organism *** grid) {
		if (getStepsSurvived() % 3 == 0) {
			bool hasBred = false;
			/*implementing a clockwise search as it does not specify that a random direction is set */
			int direction = 1;
			while(direction <= 4) {
				if (hasBred == false) {
					/* 1 = Up*/
					if (direction == 1) {
						if (getYPos() - 1 >= 0) {
							if (grid[getYPos() - 1][getXPos()] == NULL) {
								grid[getYPos() - 1][getXPos()] = new ant(getYPos() - 1, getXPos());
								hasBred = true;
							}
						}
					}

					/* 2 = Right*/
					if (direction == 2) {
						if (getXPos() - 1 < GRIDSIZE) {
							if (grid[getYPos()][getXPos() - 1] == NULL) {
								grid[getYPos()][getXPos() - 1] = new ant(getYPos(), getXPos() - 1);
								hasBred = true;
							}
						}
					}
					/* 3 = Down*/
					if (direction == 3) {
						if (getYPos() + 1 < GRIDSIZE) {
							if (grid[getYPos() + 1][getXPos()] == NULL) {
								grid[getYPos() + 1][getXPos()] = new ant(getYPos() + 1, getXPos());
								hasBred = true;
							}
						}
					}
					/* 4 = Left*/
					if (direction == 4) {
						if (getXPos() + 1 >= 0) {
							if (grid[getYPos()][getXPos() + 1] == NULL) {
								grid[getYPos()][getXPos() + 1] = new ant(getYPos(), getXPos() + 1);
								hasBred = true;
							}
						}
					}
				}
				direction++;
			}
		}
	}


int main()
{
	organism *** grid;
	grid = new organism**[GRIDSIZE];
	for (int i = 0; i < GRIDSIZE; i++) {
		grid[i] = new organism*[GRIDSIZE];
	}

	for (int i = 0; i < GRIDSIZE; i++) {
		for (int j = 0; j < GRIDSIZE; j++) {
			grid[i][j] = NULL;
		}
	}

	initialize(grid);

	cout << "Welcome to the doodlebug-ant predator-prey simulation" << endl;
	bool end;
	end = false;
	

	while (end == false) {
		
		cout << "Press [enter] to continue the simulation" << endl;
		
		cin.get();
		system("CLS");
		draw(grid);
		moveGrid(grid);
		breedGrid(grid);
		
	}

	delete[] grid;
	
	return 0;
}
void draw(organism *** grid) {
	for (int yPos = 0; yPos < GRIDSIZE; yPos++)
	{
		for (int xPos = 0; xPos < GRIDSIZE; xPos++)
		{
			if (grid[yPos][xPos]== NULL) {
				cout << "-";
			}
			else if (grid[yPos][xPos]->getType() == "ant") {
				cout << "O";
			}
			else {
				cout << "X";
			}
		}
		cout << endl;
	}
}
void initialize(organism*** grid) {
	int maxAnts, maxDoodlebugs, randomI, randomJ;
	maxAnts = 100;
	maxDoodlebugs = 5;
	srand((unsigned int)time(0));

	/*Print Ants*/
	while (maxAnts > 0) {
		randomI = (rand() % GRIDSIZE);
		randomJ = (rand() % GRIDSIZE);

		if (grid[randomI][randomJ] == NULL ) {
			grid[randomI][randomJ] = new ant(randomI,randomJ);
			maxAnts--;
		}
	}
	
	/*Print Doodlebugs*/
	while (maxDoodlebugs > 0) {
		randomI = (rand() % GRIDSIZE);
		randomJ = (rand() % GRIDSIZE);

		if (grid[randomI][randomJ] == NULL) {
			grid[randomI][randomJ] = new doodlebug(randomI, randomJ);
			maxDoodlebugs--;
		}
	}
}
void moveGrid(organism *** grid) {
	/*move doodlebugs first*/
	for (int yPos = 0; yPos < GRIDSIZE; yPos++) {
		for (int xPos = 0; xPos < GRIDSIZE; xPos++) {
			if (grid[yPos][xPos] != NULL) {
				if (grid[yPos][xPos]->getType() == "doodlebug") {
					grid[yPos][xPos]->move(grid);
				}
			}
		}
	}

	/*move ants*/
	for (int yPos = 0; yPos < GRIDSIZE; yPos++) {
		for (int xPos = 0; xPos < GRIDSIZE; xPos++) {
			if (grid[yPos][xPos] != NULL) {
				if (grid[yPos][xPos]->getType() == "ant") {
					grid[yPos][xPos]->move(grid);
				}
			}
		}
	}
}

void breedGrid(organism *** grid) {
	/*breed doodlebugs*/
	for (int yPos = 0; yPos < GRIDSIZE; yPos++) {
		for (int xPos = 0; xPos < GRIDSIZE; xPos++) {
			if (grid[yPos][xPos] != NULL) {
				if (grid[yPos][xPos]->getType() == "doodlebug") {
					grid[yPos][xPos]->breed(grid);
				}
			}
		}
	}
	
	/*breed ants*/
	for (int yPos = 0; yPos < GRIDSIZE; yPos++) {
		for (int xPos = 0; xPos < GRIDSIZE; xPos++) {
			if (grid[yPos][xPos] != NULL) {
				if (grid[yPos][xPos]->getType() == "ant") {
					grid[yPos][xPos]->breed(grid);
				}
			}
		}
	}
}



