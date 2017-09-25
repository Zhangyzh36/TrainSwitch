#include "Train.hpp" 
#include <cctype>
#include <cstdlib>
#include <string>
#include <regex>

void instructions()
{
	cout << endl;
	cout << "��ӭʹ�û𳵳������ŵ���ϵͳ��" << endl;
	cout << "**********************************************************" << endl;
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

void end()
{
	cout << "**********************************************************" << endl;
	cout << "��лʹ�ñ�ϵͳ��" << endl << endl; 
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
	cout << endl << "���Ȳ������£�" << endl;
	
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
	cout << endl << "����ʹ��" << step << "����" << st.size() << "�����" << endl << endl;		
}

Train::~Train()
{
	delete []car;
}

bool Train::isNumber(string &num) const
{
	num.erase( 0, num.find_first_not_of(" ") );
	num.erase( num.find_last_not_of(" ") + 1 );
	regex pattern("(\\+|\\-)?[0-9]+");
	return regex_match(num, pattern);
}

void Train::printMessage(Action a, int stackIndex) const
{
	if(stackIndex == -1)
	{
		cout << carToBeOut << "��ֱ��ʻ��" << endl;
		return;
	} 
			
	switch(a)
	{
		case PUSH:
			cout <<  car[cur] << "�ų������" << 
			stackIndex+1 << "�Ź����" << endl;
			break;
		case POP:
			cout <<  carToBeOut <<  "�ų����" << 
			stackIndex+1 << "�Ź����ʻ��" << endl;
			break;
		
	}
		
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
		if ( !valid[i] )
		{
			delete []valid;
			return false;
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
	if(index == -1) printMessage(POP,-1);
	else
	{
		printMessage(POP,index);
		st[index].pop();
	}
	carToBeOut++;
	step++;
	
}

void Train::pushTo(int index)
{
	printMessage(PUSH,index);
	st[index].push(car[cur]);	
	step++;
}

int Train::carPopedFrom() const
{
	for(int i = 0;i < st.size(); i++ )
	{
		if(st[i].empty()) continue;
		if(st[i].top() == carToBeOut) return i;
	}
	return -1;
}

int Train::carPushedIn() const
{
	int lpos = -1,min = 9999;
	for(int i = 0;i < st.size() ;i++)
	{
		if(st[i].empty()) 
		{
			if(min == 9999) lpos = i;
			continue;
		}
		if(st[i].top() < car[cur]) continue;
		if((st[i].top() - car[cur]) < min)
		{
			 min = st[i].top() - car[cur];
			 lpos = i;
		}
	}
	return lpos;
}

int Train::createNewStack()
{
	stack<int> temp;
	st.push_back(temp);
	return st.size()-1;	
}

