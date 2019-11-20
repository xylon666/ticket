/*
K234 8:00 南京 广州 12 1100 30
K211 6:30 南京西 成都 18 1500 40
T25 7:00 北京 广州 24 1700 20
T58 10:00 南京 上海 2 800 2
*/
#include<time.h>
#include<iostream>
#include<string.h>
#include<fstream>
#include<stdlib.h>
#include<conio.h>
using namespace std;
class Time;
class Ticket;
void CreatFile(char*);
void ChangNo(Ticket*p[],int *number);
void AddNo(Ticket*p[],int *number);
void NewNo(Ticket*p[],int *number);
void ShowTrain(Ticket*p[],int *number);
int FindTrain(Ticket*p[],int *number,int *,int *);
int FindNoTrain(Ticket*p[],int *,int *,int *);
int FindaTrain(Ticket*p[],int *,int *,int *);
void ShowTimeTrain(Ticket*p[],int *number);
void SellReturnTicket(Ticket*p[],int *number,int i,int j);
void SellTicket(Ticket*p[],int *number,int i,int j);
void ReturnTicket(Ticket*p[],int *number,int i,int j);
//定义时间类
class Time {
	private:
		int hour;
		int minute;
	public:
		Time(int h=0,int m=0) {
			hour=h;
			minute=m;
		}
		void SetTime() { //设置时间
			cout<<"请输入发车时间:"<<endl;
			//cin>>hour>>minute;
			scanf("%d:%d",&hour,&minute);
		}
		void PrintTime() { //显示时间
			{
				if(minute==0)
					cout<<hour<<":"<<minute<<minute;
				else
					cout<<hour<<":"<<minute;
			}
		}
		int GetHour() { //获得时
			return hour;
		}
		int GetMinute() { //获得分钟
			return minute;
		}
		void ChangTime(int h,int m) { //修改时间
			hour=h;
			minute=m;
		}
};
//定义车次类
class Ticket {
	private:
		char no[9];//车次
		char name_b[10];//起点站
		char name_a[10];//终点站
		Time time_o;//发车时间
		int load;//额定载量
		int reminder;//余票数量
		int time;//行车时间
	public:
		Ticket(char*No,int h,int m,char*Name_b,char*Name_a,int t,int Load,int Reminder):time_o(h,m) {
			strcpy(no,No);
			strcpy(name_b,Name_b);
			strcpy(name_a,Name_a);
			time=t;
			load=Load;
			reminder=Reminder;
		}
		Ticket() {
		}
		void SetTicket() { //设置时间
			cout<<"请输入车次:"<<endl;
			cin>>no;
			time_o.SetTime();
			cout<<"请输入起点站:"<<endl;
			cin>>name_b;
			cout<<"请输入终点站:"<<endl;
			cin>>name_a;
			cout<<"请输入行车时间:"<<endl;
			cin>>time;
			cout<<"请输入额定载量:"<<endl;
			cin>>load;
			cout<<"请输入余票数量:"<<endl;
			cin>>reminder;
		}
		void ChangTicket(Ticket ticket) { //修改车次信息
			strcpy(no,ticket.GetNo());
			strcpy(name_b,ticket.GetName_b());
			strcpy(name_a,ticket.GetName_a());
			time=ticket.Gettime();
			load=ticket.GetLoad();
			reminder=ticket.GetReminder();
			time_o.ChangTime((ticket.time_o).GetHour(),(ticket.time_o).GetMinute());
		}
		void PrintTicket() { //显示车次信息
			cout<<no<<" ";
			time_o.PrintTime();
			cout<<" "<<name_b<<" "<<name_a<<" "<<time<<" "<<load<<" "<<reminder;
		}
		friend void AddReminder(Ticket&,int n);//定义添加余票数为类的友元函数
		friend void MinReminder(Ticket&,int n);//定义减少余票数为类的友元函数
		char*GetNo() { //获得车次
			return no;
		}
		char*GetName_b() { //获得起始站
			return name_b;
		}
		char*GetName_a() { //获得终点站
			return name_a;
		}
		int Gettime() { //获得时间
			return time;
		}
		int GetLoad() { //获得额定载量
			return load;
		}
		int GetReminder() { //获得余票数
			return reminder;
		}
		int GetTimeHour() { //获得小时
			return time_o.GetHour();
		}
		int GetTimeMinute() { //获得分钟数
			return time_o.GetMinute();
		}
};
void MinReminder(Ticket&t,int n) { //定义减少余票数
	t.reminder=t.reminder-n;
}
void AddReminder(Ticket&t,int n) { //定义添加余票数
	t.reminder=t.reminder+n;
}
int count=0;//定义全局变量用来统计指针数组的长度
int main() 
{
	CreatFile("车票信息.dat");
	//ofstream outf("车票信息.dat");//第一次以后使用
	CreatFile("sort.dat");
	//ofstream outf("sort.dat");//第一次以后使用
	int choice;
	int flag=1;
	int i,j;
	int number[100];//用来存每个指针中元素的个数
	Ticket *p[100];//定义指针数组
	while(flag) { //菜单控制
		system("cls"); 
		cout<<"----------*-----*----------欢迎使用票务管理系统----------*-----*---------"<<endl;
		cout<<"*				1.更新车次				*"<<endl;
		cout<<"*				2.浏览信息				*"<<endl;
		cout<<"*				3.查询票务				*"<<endl;
		cout<<"*				4.显示时间表				*"<<endl;
		cout<<"*				5.售、退票办理				*"<<endl;
		cout<<"*				6.退出系统				*"<<endl;
		cout<<"----------*-----*----------------------------------------*-----*---------"<<endl;
		cout<<"请选择:"<<endl;
		cin>>choice;
		switch(choice) {
			case 1:
				ChangNo(p,number);
				break;
			case 2:
				ShowTrain(p,number);
				break;
			case 3:
				FindTrain(p,number,&i,&j);
				break;
			case 4:
				ShowTimeTrain(p,number);
				break;
			case 5:
				SellReturnTicket(p,number,i,j);
				break;
			case 6:
				flag=0;
				cout<<"感谢使用！"<<endl;
				break;
			default:
				cout<<"请根据提示输入正确选择"<<endl;
		}
	}
	return 0;
}
//文件创建函数
void CreatFile(char *s) {
	ofstream outf(s);
	if(!outf) {
		cout<<"无法创建文件\n"<<endl;
		return;
	}
	outf<<"车次  发车时间  起点站  终点站  行车时间  额定载量  票数量"<<'\n';//向文件中输入表头
	outf.close();
}
//更新车次函数
void ChangNo(Ticket *p[],int *number) {
	int choice;//菜单控制
	system("cls"); //刷屏
	cout<<"*********************1.新增车次******************************"<<endl;
	cout<<"*********************2.修改车次******************************"<<endl;
	cout<<"请选择:"<<endl;
	cin>>choice;
	switch(choice) {
		case 1:
			AddNo(p,number);
			break;
		case 2:
			NewNo(p,number);
			break;
	}
}
//增加车次
void AddNo(Ticket *p[],int *number) {
	int n,i,j;
	cout<<"请输入要增加的车次的数量:";
	cin>>n;
	p[count]=(Ticket*)malloc(n*sizeof(Ticket));//为此次增加分配内存
	if(p[count]==NULL) {
		cout<<"内存超限！\n";
		exit(0);
	} else
		number[count]=n;//记录每个指针中元素的个数
	for(i=0; i<n; i++) {
		(p[count]+i)->SetTicket();//输入增加车次
		ofstream outf("车票信息.dat",ios::app);//向文件中写入新增车次
		outf<<(p[count]+i)->GetNo()<<" "<<(p[count]+i)->GetTimeHour()<<":"<<(p[count]+i)->GetTimeMinute()<<" "<<(p[count]+i)->GetName_b()<<" "<<(p[count]+i)->GetName_a()<<" "<<(p[count]+i)->Gettime()<<" "<<(p[count]+i)->GetLoad()<<" "<<(p[count]+i)->GetReminder()<<'\n';
	}
    //显示此次的票务信息
	system("cls"); //刷屏
	cout<<"------------------------------当前票务信息:-------------------------------"<<endl;
	cout<<"车次"<<" "<<"发车时间"<<" "<<"起点站"<<" "<<"终点站"<<" "<<"行车时间"<<" "<<"额定载量"<<" "<<"余票数量"<<'\n';
	for(i=0; i<=count; i++) {
		for(j=0; j<number[i]; j++) {
			(p[i]+j)->PrintTicket();
			cout<<endl;
		}
	}
	count++;//记录指针数组中元素的个数
	cout<<endl<<"按任意键继续...."<<endl; 
	getch();
}
//修改车次
void NewNo(Ticket *p[],int *number) {
	int i,j,flag=1;
	char No[20];
	cout<<"请输入车次:"<<endl;
	cin>>No;//输入需要修改的车次
	for(i=0; i<count&&flag; i++) { //查找需要修改的车次
		for(j=0; j<number[i]; j++) {
			if(strcmp((p[i]+j)->GetNo(),No)==0)
				flag=0;
			break;
		}
	}
	if(flag==0) {
		i--;
	}
	cout<<"请输入修改后的车次信息:"<<endl;
	Ticket ticket;
	ticket.SetTicket();//输入修改以后的车次
	(p[i]+j)->ChangTicket(ticket);//修改
	//显示此次的票务信息
	system("cls"); //刷屏
	cout<<"-------------------------当前票务信息:-------------------------"<<endl;
	cout<<"车次"<<" "<<"发车时间"<<" "<<"起点站"<<" "<<"终点站"<<" "<<"行车时间"<<" "<<"额定载量"<<" "<<"余票数量"<<'\n';
	for(i=0; i<=count; i++) {
		for(j=0; j<number[i]; j++) {
			(p[i]+j)->PrintTicket();
			cout<<endl;
			ofstream outf("车票信息.dat",ios::app);//向文件中写入新内容
			outf<<(p[i]+j)->GetNo()<<" "<<(p[i]+j)->GetTimeHour()<<":"<<(p[i]+j)->GetTimeMinute()<<" "<<(p[i]+j)->GetName_b()<<" "<<(p[i]+j)->GetName_a()<<" "<<(p[i]+j)->Gettime()<<" "<<(p[i]+j)->GetLoad()<<" "<<(p[i]+j)->GetReminder()<<'\n';
		}
	}
	cout<<endl<<"按任意键继续...."<<endl; 
	getch();
}
//显示票务信息
void ShowTrain(Ticket *p[],int *number) {
	int i,j;
	struct tm *local;
	long long t;
	time(&t);
	local=localtime(&t);
	system("cls"); //刷屏
	cout<<"-------------------------当前时间:"<<local->tm_hour<<":"<<local->tm_min<<"-------------------------"<<endl;//显示此时时间
	//判断车是否开出
	cout<<"车次"<<" "<<"发车时间"<<" "<<"起点站"<<" "<<"终点站"<<" "<<"行车时间"<<" "<<"额定载量"<<" "<<"余票数量"<<'\n';
	for(i=0; i<count; i++) {
		for(j=0; j<number[i]; j++) {
			(p[i]+j)->PrintTicket();
			cout<<endl;
			if((p[i]+j)->GetTimeHour()<local->tm_hour)
				cout<<'\t'<<"此车已发出"<<endl;
			else if((p[i]+j)->GetTimeHour()==local->tm_hour) {
				if((p[i]+j)->GetTimeMinute()<local->tm_min)
					cout<<'\t'<<"此车已发出"<<endl;
				else
					cout<<'\t'<<"此车未发出"<<endl;
			} 
			else
				cout<<'\t'<<"此车未发出"<<endl;
		}
	}
	cout<<endl<<"按任意键继续...."<<endl; 
	getch();
}
//查询票务
int FindTrain(Ticket *p[],int *number,int *i,int *j) {
	int flag=1,choice,f=0;
	while(flag) { //显示菜单
		system("cls"); //刷屏
		cout<<"****************1.按班次查询*****************************"<<endl;
		cout<<"****************2.按终点站查询****************************"<<endl;
		cout<<"****************3.退出查询系统****************************"<<endl;
		cout<<"请选择:"<<endl;
		cin>>choice;
		switch(choice) {
			case 1:
				f=FindNoTrain(p,number,i,j);
				break;
			case 2:
				f=FindaTrain(p,number,i,j);
				break;
			case 3:
				flag=0;
				return f;
				break;
			default:
				cout<<"请根据提示输入正确选择"<<endl;
		}
		if(f==0)
			break;
	}
	return f;
}
//按车次查询
int FindNoTrain(Ticket *p[],int *number,int *i,int *j) {
	int flag=1;
	char No[20];
	cout<<"请输入需要查询的车次："<<endl;
	cin>>No;
	//车次查询并显示查询结果
	for((*i)=0; (*i)<count&&flag; (*i)++) {
		for((*j)=0; (*j)<number[(*i)]; (*j)++) {
			if(strcmp((p[(*i)]+(*j))->GetNo(),No)==0) {
				system("cls"); //刷屏
				cout<<"--------------------您查询到的车次:--------------------"<<endl;
				cout<<"车次"<<" "<<"发车时间"<<" "<<"起点站"<<" "<<"终点站"<<" "<<"行车时间"<<" "<<"额定载量"<<" "<<"余票数量"<<'\n';
				(p[(*i)]+(*j))->PrintTicket();
				cout<<endl;
				flag=0;
				break;
			}
		}
	}
	if(flag!=0)
		cout<<"未查询到该车次"<<endl;
	cout<<endl<<"按任意键继续...."<<endl; 
	getch();
	return flag;
}
//按终点站查询
int FindaTrain(Ticket *p[],int *number,int *i,int *j) {
	int flag=1;
	char Name_a[20];
	cout<<"请输入需要查询的终点站:"<<endl;
	cin>>Name_a;
	//查询并显示查询结果
	for((*i)=0; (*i)<count&&flag; (*i)++) {
		for((*j)=0; (*j)<number[(*i)]; (*j)++) {
			if(strcmp((p[(*i)]+(*j))->GetName_a(),Name_a)==0) {
				system("cls"); //刷屏
				cout<<"--------------------您查询到的车次:--------------------"<<endl;
				cout<<"车次"<<" "<<"发车时间"<<" "<<"起点站"<<" "<<"终点站"<<" "<<"行车时间"<<" "<<"额定载量"<<" "<<"余票数量"<<'\n';
				(p[(*i)]+(*j))->PrintTicket();
				cout<<endl;
				flag=0;
				break;
			}
		}
	}
	if(flag)
		cout<<"未查询到该车次"<<endl;
	cout<<endl<<"按任意键继续...."<<endl; 
	getch();
	return flag;
}
//显示时间表
void ShowTimeTrain(Ticket *p[],int *number) {
	int i,j,k;
	int cow=0,total=0;
	Ticket temp;
	for(i=0; i<count; i++) { //统计总共对象
		total=total+number[i];
	}
	//创建一个新的对象数组并把原有车次信息存入该数组中
	Ticket *q=(Ticket*)malloc(total *sizeof(Ticket));
	for(i=0; i<count; i++) {
		for(j=0; j<number[i]; j++) {
			q[cow]=*(p[i]+j);
			cow++;
		}
	}
	//按时间进行排序
	for(i=0; i<total-1; i++) {
		int ti=i;
		k=ti;
		for(j=i+1; j<total; j++) 
		{
			if(q[j].GetTimeHour()<q[i].GetTimeHour())
				k=j;
			else 
				if(q[j].GetTimeHour()==q[i].GetTimeHour()&&q[j].GetTimeMinute()<q[i].GetTimeMinute())
						k=j;
			if(k!=ti) {
				temp=q[k];
				q[k]=q[i];
				q[i]=temp;
				k=ti;
			}
		}
	}
	//显示排序后的结果
	system("cls"); //刷屏
	cout<<"---------------------------发车时间表:---------------------------"<<endl;
	cout<<"车次"<<" "<<"发车时间"<<" "<<"起点站"<<" "<<"终点站"<<" "<<"行车时间"<<" "<<"额定载量"<<" "<<"余票数量"<<'\n';
	for(i=0; i<total; i++) {
		q[i].PrintTicket();
		cout<<endl;
		ofstream outf("sort.dat",ios::app);
		outf<<(q+i)->GetNo()<<" "<<(q+i)->GetTimeHour()<<":"<<(q+i)->GetTimeMinute()<<" "<<(q+i)->GetName_b()<<" "<<(q+i)->GetName_a()<<" "<<(q+i)->Gettime()<<" "<<(q+i)->GetLoad()<<" "<<(q+i)->GetReminder()<<'\n';
	}
	cout<<endl<<"按任意键继续...."<<endl; 
	getch();
}
//售退票系统 
void SellReturnTicket(Ticket *p[],int *number,int i,int j) {
	int flag=1,choice;
	while(flag) { //菜单显示
		system("cls"); //刷屏
		cout<<"*********************1.售票******************************"<<endl;
		cout<<"*********************2.退票******************************"<<endl;
		cout<<"****************3.退出售退票系统*************************"<<endl;
		cout<<"请选择:"<<endl;
		cin>>choice;
		switch(choice) {
			case 1:
				SellTicket(p,number,i,j);
				break;
			case 2:
				ReturnTicket(p,number,i,j);
				break;
			case 3:
				flag=0;
				break;
			default:
				cout<<"请根据提示输入正确选择"<<endl;
		}
	}
}
//售票
void SellTicket(Ticket *p[],int *number,int i,int j) {
	int n,f,flag;
	int hour,minute;
	struct tm *local;
	long long t;
	time(&t);
	local=localtime(&t);
	hour=(p[i-1]+j)->GetTimeHour();
	minute=(p[i-1]+j)->GetTimeMinute();
	if(hour<local->tm_hour)
		flag=1;
	else if(hour==local->tm_hour) {
		if(minute<local->tm_min)
			flag=1;
		else 
			flag=0;
	} 
	else
		flag=0;
	system("cls"); //刷屏
	f=FindTrain(p,number,&i,&j);//寻找所要购买的车次信息
	//若存在输入购买数并进行判断、售票
	if(f==0) {
		if(flag) {
			cout<<"请输入购买的票数:"<<endl;
			cin>>n;
			if(n>(p[i-1]+j)->GetReminder())
			{
				cout<<"抱歉！没有足够的车票"<<endl;
				
			}
			else
			{
				MinReminder((*(p[i-1]+j)),n);
				cout<<"购买成功！"<<endl;
			}
		}
		else
			cout<<"不在售票时间，无法购票"<<endl;
	}
	cout<<endl<<"按任意键继续...."<<endl;
	getch();
}
//退票
void ReturnTicket(Ticket *p[],int *number,int i,int j) {
	int n,flag,hour,minute;
	system("cls"); //刷屏
	FindTrain(p,number,&i,&j);//查询所要退的车次信息
	struct tm *local;
	long long t;
	time(&t);
	local=localtime(&t);
	//(p[i-1]+j)->PrintTicket();//显示所要退的车次信息
	//cout<<endl;
	hour=(p[i-1]+j)->GetTimeHour();
	minute=(p[i-1]+j)->GetTimeMinute();
	if(minute>=30)
		minute=minute-30;
	else {
		hour=hour-1;
		minute=minute+30;
	}
	//判断是否发出从而判断是否可以退票
	if(hour<local->tm_hour)
		flag=1;
	else if(hour==local->tm_hour) {
		if(minute<local->tm_min)
			flag=1;
		else flag=0;
	} else
		flag=0;
	if(flag) {
		cout<<"抱歉!您目前无法退票！"<<endl;
	} else {
		cout<<"请输入要退票的数目:"<<endl;
		cin>>n;
		AddReminder(*(p[i-1]+j),n);
		cout<<"退票成功！"<<endl;
	}
	cout<<endl<<"按任意键继续...."<<endl; 
	getch();
}
