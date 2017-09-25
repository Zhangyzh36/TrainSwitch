#include "Train.hpp" 
#include <cctype>
#include <cstdlib>
#include <string>
#include <regex>

void instructions()
{
	cout << endl;
	cout << "欢迎使用火车车厢重排调度系统" << endl;
	cout << "*****************************" << endl;
	cout << endl;
	cout << "请输入" << endl;
	cout << "  [s] 开始或继续调度" << endl;
	cout << "  [q] 退出系统" << endl << endl;
}

char getCommand()
{
	string command;
	bool waiting = true;
	cout << "请输入指令:~$ ";
	while ( waiting ) {
		getline(cin, command);
		if (command[0] == 's' || command[0] == 'q' || command[0] == 'S' || command[0] == 'Q')
			waiting = false; 
		else
			cout << "请输入正确的指令(s或q):~$ ";
	} 
	return (command[0] == 's' || command[0] == 'S') ? 's' : 'q';
}

bool doCommand(char command)
{
	return command == 's';
}

Train::Train()
{
	cur = 0;
	carToBeOut = 1;
	step = 0;
	string sizeString;
	
	cout << "请输入车厢的数量(正整数):~$ ";
	getline(cin, sizeString);
	while ( !isNumber(sizeString) || atoi(sizeString.c_str()) <= 0 ) {
		cout << "请输入车厢的数量(正整数):~$ ";
		getline(cin, sizeString);
	}
	size = atoi(sizeString.c_str());
	
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
	cout << "Totally take " << step << "steps to finish the job." << endl;
	cout << "Totally take " << st.size() << "stacks to finish the job." << endl;
}

Train::~Train()
{

}

bool Train::isNumber(string &num) const
{
	regex pattern("(\\+|\\-)?[0-9]+");
	return regex_match(num, pattern);
}

void Train::printMessage(Action a, int stackIndex) const
{
	switch(a)
	{
		case PUSH:
			cout << "Push NO." << car[cur] << " in stack NO." << 
			stackIndex << endl;
			break;
		case POP:
			cout << "Pop NO." << st[stackIndex].top() <<  " in stack NO." << 
			stackIndex << endl;
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
		if(st[i].top() == car[cur]) return i;
	}
	return -1;
}

int Train::carPushedIn() const
{
	int lpos = -1,min = 99;
	for(int i = 0;i < st.size() ;i++)
	{
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
	return st.size();	
}

