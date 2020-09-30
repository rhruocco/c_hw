// Type your code here, or load an example.

#include <stdio.h>


int howManyFloors() {
	int f;
	printf("How many floors will there be: ");
	f = getchar();
	return f;
}

char upOrDown() {
	char uD;
	printf("Welcome to the elevator!\nWill you [A]scend, or [D]escend?\n(Or [E]xit)");
	uD = getchar();
	return uD;
}

int ascend(int floor)
{
	int howMany = 0;
	printf("How many floors up do you want to go:");
	howMany = getchar();
	return howMany;
}

int descend(int floor)
{
	int howMany = 0;
	printf("How many floors down do you want to go:");
	howMany = getchar();
	printf("howmany");
	return howMany;
}

int moveFloors(int floor)
{
	printf("This is floor", floor);
}



int main() {
	int floorsToMove = 0;
	int floors = howManyFloors();
	int currentFloor = 0;
	char upperDowner = 'n';
	int done = 0;
	upperDowner = upOrDown();
	while (done == 0)
	{
		moveFloors(currentFloor);
		upperDowner = upOrDown();
		switch (upperDowner)
		{
		case 'a':
			floorsToMove = ascend(currentFloor);
			for (int i = 0;i < floorsToMove; i++)
			{
				moveFloors(currentFloor);
				currentFloor++;
			}
		case 'd':
			moveFloors(currentFloor);
			currentFloor--;
		case 'e':
			printf("Bye bye!");
			done = 1;

		}
	}
	return 0;
}