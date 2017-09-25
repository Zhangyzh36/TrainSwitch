#include "Train.hpp" 
#include <cctype>
#include <cstdlib>
#include <string>
#include <regex>

void instructions()
{
	cout << endl;
	cout << "欢迎使用火车车厢重排调度系统！" << endl;
	cout << "**********************************************************" << endl;
	cout << endl;
	cout << "请输入" << endl;
	cout << "  [s] 开始或继续调度" << endl;
	cout << "  [q] 退出系统" << endl << endl;
}

char getCommand()
{
	fflush(stdin);
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

void end()
{
	cout << "**********************************************************" << endl;
	cout << "感谢使用本系统！" << endl << endl; 
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
	
	cout << "请输入车厢的数量(正整数):~$ ";
	getline(cin, sizeString);
	while ( !isNumber(sizeString) || atoi(sizeString.c_str()) <= 0 ) {
		cout << "请输入车厢的数量(正整数):~$ ";
		getline(cin, sizeString);
	}
	size = atoi(sizeString.c_str());
	car = new int[size];
	
	for (int i = 0; i < size; ++i)
		car[i] = 0;
	
	while (!valid) {
		valid = true;
		cout << "请输入车厢号序列(" << size << "的排列):~$ ";
		for (int i = 0; i < size; ++i)
		{
			cin >> carString;
			if ( !isNumber(carString) ) 
				valid = false;
				
			car[i] = atoi(carString.c_str());
		}
		valid = valid && isValidData();
		
	}
	cout << endl << "调度步骤如下：" << endl;
	
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
	cout << endl << "共计使用" << step << "步，" << st.size() << "条轨道" << endl << endl;		
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
		cout << carToBeOut << "号直接驶出" << endl;
		return;
	} 
			
	switch(a)
	{
		case PUSH:
			cout <<  car[cur] << "号车厢进入" << 
			stackIndex+1 << "号轨道中" << endl;
			break;
		case POP:
			cout <<  carToBeOut <<  "号车厢从" << 
			stackIndex+1 << "号轨道中驶出" << endl;
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

