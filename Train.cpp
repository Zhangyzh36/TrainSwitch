#include "Train.hpp"
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <string>
#include <regex>

void instructions()
{
	cout << endl;
	cout << "��ӭʹ�û𳵳������ŵ���ϵͳ" << endl;
	cout << "*****************************" << endl;
	cout << endl;
	cout << "������" << endl;
	cout << "  [s] ��ʼ���������" << endl;
	cout << "  [q] �˳�ϵͳ" << endl << endl;
}

char getCommand()
{
	fflush(stdin);
	string command;
	bool waiting = true;
	cout << "������ָ��:~$ ";
	while ( waiting ) {
		getline(cin, command);
		
		if (command[0] == 's' || command[0] == 'q' || command[0] == 'S' || command[0] == 'Q')
			waiting = false; 
		else
			cout << "��������ȷ��ָ��(s��q):~$ ";
			
	} 
	return (command[0] == 's' || command[0] == 'S') ? 's' : 'q';
}

bool doCommand(char command)
{
	return command == 's';
}

Train::Train()
{
	car = NULL;
	cur = 0;
	carToBeOut = 1;
	step = 0;
	bool valid = false;
	string sizeString;
	string carString;
	
	cout << "�����복�������(������):~$ ";
	getline(cin, sizeString);
	while ( !isNumber(sizeString) || atoi(sizeString.c_str()) <= 0 ) {
		cout << "�����복�������(������):~$ ";
		getline(cin, sizeString);
	}
	size = atoi(sizeString.c_str());
	car = new int[size];
	
	for (int i = 0; i < size; ++i)
		car[i] = 0;
	
	while (!valid) {
		valid = true;
		cout << "�����복�������(" << size << "������):~$ ";
		for (int i = 0; i < size; ++i)
		{
			cin >> carString;
			if ( !isNumber(carString) ) 
				valid = false;
				
			car[i] = atoi(carString.c_str());
		}
		valid = valid && isValidData();
		
	}
	
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
	delete []car;
}

bool Train::isNumber(string &num) const
{
	regex pattern("(\\+|\\-)?[0-9]+");
	return regex_match(num, pattern);
}

void Train::printMessage(Action a, int index) const
{

}

bool Train::isValidData() const
{
	int *valid = new int[size];
	for (int i = 0; i < size; ++i)
		valid[i] = 0;
	for (int i = 0; i < size; ++i)
	{
		if ( car[i] > size || car[i] < 1 )
		{
			delete []valid;
			return false;
		}
		valid[car[i] - 1] = 1;
	}
	for (int i = 0; i < size; ++i)
	{
		if ( !valid[i] )
		{
			delete []valid;
			return false;
		}
	}
	
	delete []valid;
	return true;
}

bool Train::isCarToBeOut() const
{
	return car[cur] == carToBeOut;
}

void Train::popFrom(int index)
{

}

void Train::pushTo(int index)
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
