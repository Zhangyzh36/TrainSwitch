#include "Train.hpp"

int main()
{
	instructions();
	while (doCommand(getCommand())) {
		Train t;		
		t.switchTrain();
		t.print();
	}
	end();
	return 0;
}
