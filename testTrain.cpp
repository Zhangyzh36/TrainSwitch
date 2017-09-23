#include "Train.hpp"

int main()
{
	instructions();
	while (getCommand()) {
		Train t;
		t.switchTrain();
	}

	return 0;
}