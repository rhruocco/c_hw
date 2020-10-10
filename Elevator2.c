#include <stdio.h>

int howManyFloors() {
	int f = 0;
	printf("%s", "How many floors will there be: ");
	scanf("%d", &f);
	return f;
}

int floorSelect() {
	int floorToGoTo = 0;
	printf("%s", "\nWhich Floor will you go to?\n(0 to quit)\n");
	scanf("%d", &floorToGoTo);
	return floorToGoTo;
}

int ascend(int currentFloor, int *floors, int goTo)
{
	while (currentFloor < goTo)
	{
		currentFloor++;
		printf("%s", "This is the ", currentFloor, " floor.");
	}

	printf("%s", "You've arrived at floor ", goTo);
	return goTo;
}

int descend(int currentFloor, int *floors, int goTo)
{
	while (currentFloor < goTo)
	{
		currentFloor--;
		printf("%s", "This is the ", currentFloor, " floor.");
	}

	printf("%s", "You've arrived at floor ", goTo);
	return goTo;
}

int main() {
	int floorAmount = howManyFloors();

	int * floors = (int *)malloc(sizeof(int)*floorAmount);

	int currentFloor = 0;
	int desiredFloor = 1;
	int done = 0;

	while (done == 0)
	{
		desiredFloor = floorSelect();

		if (desiredFloor > currentFloor) {
			currentFloor = ascend(currentFloor, floors, desiredFloor);
		}
		else if (desiredFloor < currentFloor)
		{
			currentFloor = descend(currentFloor, floors, desiredFloor);
		}
		else if (desiredFloor == 0)
		{
			done = 1;
		}

	}
	return 0;
}