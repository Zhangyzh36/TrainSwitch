#include "Train.hpp"

void instructions()
{

}

bool getCommand()
{
	return true;
}

Train::Train()
{

}

void Train::switchTrain()
{
	int index;

	while ( cur < size) {
		
		if ( isCarToBeOut() ) {
			popFrom(-1);
			
			while ( (index = carPopedFrom()) != -1 ) {
				popFrom(index);
			}

		}
		else {
			
			if ( (index = carPushedIn()) == -1 )
				index = createNewStack();
			
			pushTo(index);
		}

		cur++;
	}

}

void Train::print() const
{

}

Train::~Train()
{

}

void Train::printMessage(Action a, int stackIndex) const
{

}

bool Train::isCarToBeOut() const
{
	return true;
}

void Train::popFrom(int stackIndex)
{

}

void Train::pushTo(int stackIndex)
{

}

int Train::carPopedFrom() const
{

}

int Train::carPushedIn() const
{

}

int Train::createNewStack()
{

}
