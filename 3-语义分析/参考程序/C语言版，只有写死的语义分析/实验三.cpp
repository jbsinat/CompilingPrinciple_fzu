#include <iostream>
#include <algorithm>
#include<conio.h>
using namespace std;

int address=100; 		//ÿ���������ĵ�ַ 
int LID=0;       		//��ʾ����ִ�е���Ӧλ�õĵ�ַ���� 
int tID=0;		 		//�����滻���ʽ�ı�ʶ�� 
int ip=0;
string shuru[666];		//��Ŵ��ļ�������ַ���
int maxsize;			//���ô������ĳ��� 

string biaodashi();

/*****�ַ��������ֵ�����*****/
string l(string a,int b)
{
	string t="";
	do
	{
		t+=b%10+'0';
		b/=10;
	}
	while(b);
	reverse(t.begin(),t.end());
	return a+t;
}

/*****��ȡ���ʽ�е�Ԫ�ض���*****/
string element()
{
	if(shuru[ip]=="expr"||shuru[ip]=="num")
	{
		ip++;
		return shuru[ip-1];
	}
	else if(shuru[ip]=="(")
	{
		ip++;
		string result=biaodashi();
		if(shuru[ip]==")")ip++;
		else puts("Lack)");
		return result;
	}
	else puts("error");
	return "";
} 

/*****������ʽ*****/
string expression_1(string &op)
{
	if(shuru[ip]=="*"||shuru[ip]=="/")
	{
		op=shuru[ip];
		ip++;
		string arg1=element();
		string op_1="",result=l("t",tID++);
		string arg2=expression_1(op_1);
		if(op_1=="")op_1="=";
		if(arg2=="") cout<<address++<<":"<<" "<<result<<" = "<<arg1<<endl;
		else cout<<address++<<":"<<" "<<result<<" = "<<arg1<<" "<<op_1<<" "<<arg2<<endl;
		return result;
	}
	return "";
} 

/*****������ʽ*****/
string expression()
{
	string op="",result=l("t",tID++);
	string arg1=element();
	string arg2=expression_1(op);
	if(op=="")
	{
		op="=";
	} 
	if(arg2=="")
	{
		cout<<address++<<":"<<" "<<result<<" = "<<arg1<<endl;
	}
	else
	{
		cout<<address++<<":"<<" "<<result<<" = "<<arg1<<" "<<op<<" "<<arg2<<endl;
	}
	return result;
} 

/*****�ݹ�---������ʽ��תΪ����ַ���*****/
string biaodashi_1(string &op)
{
	string result="";
	if(shuru[ip]=="+"||shuru[ip]=="-")
	{
		op=shuru[ip];
		ip++;
		string arg1=expression();
		string op_1="";
		string arg2=biaodashi_1(op_1);
		result=l("t",tID++);
		if(op_1=="")
		{
			op_1="=";
		}
		if(arg2=="")
		{
			cout<<address++<<":"<<" "<<result<<" = "<<arg1<<endl;
		}
		else
		{
			cout<<address++<<":"<<" "<<result<<" = "<<arg1<<" "<<op_1<<" "<<arg2<<endl;
		}
	}
	return result;
} 

/*****������ʽ��תΪ����ַ���*****/
string biaodashi()
{
	string arg1="",op="";
	if(shuru[ip]=="+"||shuru[ip]=="-"){arg1=shuru[ip];ip++;}
	arg1+=expression();
	string arg2=biaodashi_1(op);
	string result=l("t",tID++);
	if(op=="")
	{
		op="=";
	}
	if(arg2=="")
	{
		cout<<address++<<":"<<" "<<result<<" = "<<arg1<<endl;
	}
	else
	{
		cout<<address++<<":"<<" "<<result<<" = "<<arg1<<" "<<op<<" "<<arg2<<endl;	
	}
	return result;
}

/*****�жϲ���ȡ�����*****/
string getOperator()
{
	if(shuru[ip]=="="||shuru[ip]=="<>"||shuru[ip]=="<"||shuru[ip]==">"||
		shuru[ip]=="<="||shuru[ip]==">=")
	{
		ip++;
		return shuru[ip-1];
	}
	else
	{
		puts("error");
	} 
	return "";
}

/*****���if��������������ַ����*****/
void con(int L1,int L2)      //L1,L2�ֱ�Ϊif����Ϊtrue��falseʱ�����ת��ַ 
{
	string result=l("t",tID++);
		string arg1=biaodashi();           //��ñ��ʽ���������������� 
		string op=getOperator();		   //��ñ��ʽ������� 
		string arg2=biaodashi();		   //��ñ��ʽ����������ұ����� 
		if(arg2=="")
		{
			cout<<" "<<result<<" = "<<arg1<<endl;
		}
		else
		{
			cout<<address++<<":"<<" "<<result<<" = "<<arg1<<" "<<op<<" "<<arg2<<endl;
		}
		cout<<address++<<":"<<" if true "<<result<<" goto "<<"L"<<L1<<endl;
		cout<<address++<<":"<<" if false "<<result<<" goto "<<"L"<<L2<<endl;
}

/*****�жϹؼ��֣�������Ӧ�Ĳ���ʽ����*****/
void yuyifenxi(int next,int &flag) 
{
	if(shuru[ip]=="expr")
	{
		ip++;
		if(shuru[ip]=="=")			//��ֵ��� ת��Ϊ��Ԫʽ
		{
			ip++;
			string arg1=biaodashi();
			string arg2="";
			if(arg2 == "") cout<<address++<<":"<<" expr = "<<arg1<<endl;
		}
		else puts("error");
	}
	
	else if(shuru[ip]=="if") 		 //if�������ӳ���
	{
		ip++;
		int L1=LID++;
		int L2=LID++;
		if(shuru[ip]=="(")
		{
			ip++;
			con(L1,L2);
		}
		else
		{
			puts("Lack(");return;
		}
		if(shuru[ip]==")") ip++;
		else {
			puts("Lack)");return;
		}
		printf("L%d:\n",L1);
		yuyifenxi(next,flag);
		ip++;
		if(shuru[ip]=="else")
		{
			printf("L%d:\n",L2);
			ip++;
			yuyifenxi(next,flag);
		}
	}
	else if(shuru[ip]=="while")			//while�������ӳ��� 
	{
		ip++;
		int L1=LID++;
		int L2=LID++;
		if(shuru[ip]=="(")
		{
			ip++;
			printf("L%d:\n",L1);
			con(L2,next);
		}
		else
		{
			puts("Lack(");return;
		}
		if(shuru[ip]==")") ip++;
		else {
			puts("Lack)");return;
		}
		printf("L%d:\n",L2);
		yuyifenxi(next,flag);
		printf("goto L%d\n",L1);
		flag=1;
	}
}

/*****�ݹ�---���ɲ�����������ص�ַ*****/
void analysis()
{
	if(shuru[ip]==";")
	{
		ip++;
		int next=LID++;
		int flag=0;
		yuyifenxi(next,flag);
		if(flag)printf("L%d:\n",next);
		analysis();
	}
}

/*****���ɲ�����������ص�ַ*****/
void analysis_list()
{
	int next=LID++;
	int flag=0;
	yuyifenxi(next,flag);
	if(flag)printf("L%d:\n",next);
	analysis();
}

void Modular()
{
	int next=LID++;
	int flag=0;
	analysis_list();
	if(flag)printf("L%d:\n",next);
}

/*****�ļ�����*****/
void readfile() 				//���ַ������뵽shuru��
{
	maxsize=0;
	while(cin>>shuru[maxsize])
		maxsize++;
}

/*****������*****/
int main()
{
	freopen("input.txt","r",stdin);
	cout<<"����������£�"<<endl; 
	readfile();
	Modular();
	return 0;
}

