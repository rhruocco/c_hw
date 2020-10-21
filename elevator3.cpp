#include <stdio.h>
#include <iostream>
#include <string>

class Node {
public:
	int data;

	Node *next;
};

int floorSelect() {
	int floorToGoTo = 0;
	std::cout << "What floor would you like to go to? " << std::endl;

	std::cin >> floorToGoTo;

	return floorToGoTo;
}

int print_list(Node * n, int desiredFloor) {
	while (n->data <= desiredFloor && n != NULL)
	{
		std::cout << n->data << "";
		std::cout << "Floor" << std::endl;
		n = n->next;
	}
	return n->data;
}

int main() {
	Node *first = NULL;
	Node *second = NULL;
	Node *third = NULL;
	Node *fourth = NULL;
	Node *fifth = NULL;

	first->data = 1;
	second->data = 2;
	third->data = 3;
	fourth->data = 4;
	fifth->data = 5;

	first->next = second;
	second->next = third;
	third->next = fourth;
	fourth->next = fifth;
	fifth->next = NULL;

	int currentFloor = 0;
	int desiredFloor = 0;
	int done = 0;

	while (done == 0)
	{
		desiredFloor = floorSelect();

		if (desiredFloor == -1)
		{
			done = 1;
		}
		else
		{
			if (desiredFloor > currentFloor)
			{
				int oneUp = 0;
				int twoUp = 0;
				int threeUp = 0;
				int fourUp = 0;
				int fiveUp = 0;

				if ((1 + currentFloor) < 5)
				{
					oneUp = currentFloor + 1;
				}
				if ((2 + currentFloor) < 5)
				{
					twoUp = currentFloor + 2;
				}
				if ((3 + currentFloor) < 5)
				{
					threeUp = currentFloor + 3;
				}
				if ((4 + currentFloor) < 5)
				{
					fourUp = currentFloor + 4;
				}
				if ((5 + currentFloor) < 5)
				{
					fiveUp = currentFloor + 5;
				}

				first->data = oneUp;
				second->data = twoUp;
				third->data = threeUp;
				fourth->data = fourUp;
				fifth->data = fiveUp;

			}
			else if (desiredFloor < currentFloor)
			{
				int oneDown = 0;
				int twoDown = 0;
				int threeDown = 0;
				int fourDown = 0;
				int fiveDown = 0;

				if ((1 - currentFloor) > 0)
				{
					oneDown = currentFloor - 1;
				}
				if ((2 - currentFloor) > 0)
				{
					twoDown = currentFloor - 2;
				}
				if ((3 - currentFloor) > 0)
				{
					threeDown = currentFloor - 3;
				}
				if ((4 - currentFloor) > 0)
				{
					fourDown = currentFloor - 4;
				}
				if ((5 - currentFloor) > 0)
				{
					fiveDown = currentFloor - 5;
				}

				first->data = oneDown;
				second->data = twoDown;
				third->data = threeDown;
				fourth->data = fourDown;
				fifth->data = fiveDown;

			}
			currentFloor = print_list(first, desiredFloor);
		}
	}
	return 0;
}