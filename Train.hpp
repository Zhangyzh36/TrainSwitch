#ifndef TRAIN_HPP
#define TRAIN_HPP

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

//�����ʼ��ʾ��Ϣ
void instructions();
//s:��ʼ��������ȣ� q:�������ȳ��򣻷��������ָ� 
char getCommand();
//��������ϵͳ
void end(); 
//����ָ������Ƿ�������� 
bool doCommand(char command);

class Train {
	//ö���ͱ�������Ӧ��ջ��ջ
	enum Action{ PUSH, POP };
public:
	//���캯�������������size�Ƿ�Ϸ����Լ�car�е����ݺϷ��ԣ�1-sizeÿ��������һ�Σ�
	Train();
	//���Ⱥ���
	void switchTrain();
	//�������ջ��������һ���Ĳ���
	void print() const;
	//�����������ͷ��ڴ�
	~Train();
private:
	//�����ַ����Ƿ�Ϊ������ 
	bool isNumber(string &num) const; 
	//����car�е������Ƿ�Ϸ�
	bool isValidData() const;
	//���Ե�ǰ�����Ƿ�Ϊ��һ������վ�ĳ�
	bool isCarToBeOut() const;
	//pop�������ʾ��Ϣ���ı�carToBeOut
	void popFrom(int index);
	//push�������ʾ��Ϣ���ı�cur
	void pushTo(int index);
	//�ҳ�ջ���Ƿ��г���վ�ĳ������з���ջ��index�����򷵻�-1
	int carPopedFrom() const;
	//������ǰ��Ӧ�ý����ĸ�ջ:����ĸ�ջջ��Ԫ�رȳ��Ŵ��Ҳ���С����û��������ջ������ջ��index
	//                         ��û�п�ջ�򷵻�-1
	int carPushedIn() const;
	//��carPopedFrom()����-1ʱ���øú���������һ����ջ����st��β��,�����½�ջ��index
	int createNewStack();
	//�����ʾ��Ϣa==PUSH:��car[cur]ѹ��st[index]��
	//            a==POP: ��index==-1��ֱ�Ӵ�car�г���վ
	//                    �����car[cur]�г���վ
	void printMessage(Action a, int index) const;


	//һά�������������ݣ�car[0]������ջ��
	int *car;
	//�����������car��size)
	int size;
	//��ʼֵΪ0������ǰ��car�Ĳ������±�
	int cur;
	//��һ������վ�ĳ��ĺ��룬��ʼΪ1��1����վ���Ϊ2���Դ����ƣ�ֱ��size
	int carToBeOut;
	//ͳ��һ���õĲ���
	int step;
	//����ջ����������ʼΪ�գ�st.size()�ɴ���ջ�ĸ�����
	vector<stack<int> > st;
};

#endif
