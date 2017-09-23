#include "Train.hpp"

int main()
{
	instructions();
	while (getCommand()) {
		Train t;
		t.switchTrain();
		t.print();
	}

	return 0;
}