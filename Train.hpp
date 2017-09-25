#ifndef TRAIN_HPP
#define TRAIN_HPP

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

//输出初始提示信息
void instructions();
//s:开始或继续调度， q:结束调度程序；返回输入的指令； 
char getCommand();
//结束调度系统
void end(); 
//根据指令决定是否继续操作 
bool doCommand(char command);

class Train {
	//枚举型变量，对应入栈出栈
	enum Action{ PUSH, POP };
public:
	//构造函数，需检查输入的size是否合法，以及car中的数据合法性（1-size每个数出现一次）
	Train();
	//调度函数
	void switchTrain();
	//输出所用栈的数量和一共的步数
	void print() const;
	//析构函数，释放内存
	~Train();
private:
	//测试字符串是否为正整数 
	bool isNumber(string &num) const; 
	//测试car中的数据是否合法
	bool isValidData() const;
	//测试当前车辆是否为下一个出火车站的车
	bool isCarToBeOut() const;
	//pop并输出提示信息，改变carToBeOut
	void popFrom(int index);
	//push并输出提示信息，改变cur
	void pushTo(int index);
	//找出栈中是否有出火车站的车，若有返回栈的index，否则返回-1
	int carPopedFrom() const;
	//检索当前车应该进入哪个栈:进入的该栈栈顶元素比车号大且差最小，若没有则进入空栈，返回栈的index
	//                         若没有空栈则返回-1
	int carPushedIn() const;
	//当carPopedFrom()返回-1时调用该函数，创建一个空栈放在st的尾部,返回新建栈的index
	int createNewStack();
	//输出提示信息a==PUSH:把car[cur]压入st[index]内
	//            a==POP: 若index==-1则直接从car中出火车站
	//                    否则从car[cur]中出火车站
	void printMessage(Action a, int index) const;


	//一维数组存放输入数据（car[0]最先入栈）
	int *car;
	//车厢的数量（car的size)
	int size;
	//初始值为0，代表当前对car的操作的下标
	int cur;
	//下一个出车站的车的号码，开始为1，1出车站则变为2，以此类推，直到size
	int carToBeOut;
	//统计一共用的步数
	int step;
	//调度栈的向量，初始为空（st.size()可代表栈的个数）
	vector<stack<int> > st;
};

#endif
