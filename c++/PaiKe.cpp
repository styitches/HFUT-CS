#include<iostream>
#include<cstdlib>
#include<fstream>
#include<cstring>
#include<ctime>
using namespace std;

int N, M; 
typedef struct tcnode
{
	char name[20];
	int  ipri;
}tclist,*ptclist;

typedef struct node
{
	char name[20];
	char num[20];
	int  work_time;
	tclist tc[1000];
    char cbuf[1000];
    struct node *next; 
}tlist,*ptlist;

typedef struct Node
{
	char name[20];
	char num[20];
	int week_time;
	int all_time;
	int priority;
	bool mc;		//是否被选
	struct Node *next;
}clist,*pclist;
 
class teacher
{
public:
	 teacher();
    ~teacher();
	void initdata();
	void save();
	friend void print(teacher&,ptlist);
	tlist* pt;

};

class course
{
public:
	 course();
	 ~course();
	void initdata();
	void save();
	friend pclist convert(course&,char * s);
private:
	clist* pc;
};

 teacher::teacher()
{
	pt=NULL;
}
 teacher::~teacher()
{
	ptlist p;
	while(pt)
	{
       p=pt;
	   pt=pt->next;
	   delete p;
	}
	
}
void teacher::initdata()
{
	char tag;
	ptlist p=pt;
	ptlist s;
	int t=0;
	cout<<"请输入教师信息:"<<endl;
	cout<<"姓名\t教师号\t工作量"<<endl;
     do
	 {
		 if(t>=1)
		 {
			 cout<<"请输入教师信息:"<<endl;
			 cout<<"姓名\t教师号\t工作量"<<endl;
		 }
		 s = (ptlist)malloc(sizeof(tlist));
		 cin >> s->name >> s->num >> s->work_time;
		 cout << "请输入相应课程名及期望值:" << endl;
		 for(int i=0;i<M;i++)
			 cin>>s->tc[i].name>>s->tc[i].ipri;
		 fflush(stdin);
		 s->next=NULL;
		 if(!pt)
		 {
		   pt=s;
		   p=pt;
		 }
		 else
		 {
		  p->next=s;
		  p=p->next;
		 }
		 t++;
		 cout<<"是否继续输入信息:"<<endl;
		 fflush(stdin);
		 cin>>tag; 
		 system("cls");
	 }while((tag=='y'||tag=='Y')&&t<N);

}

void teacher::save()
{
	ptlist p=pt;
	char path[20]="D:\\teacher.txt";
	char str[50]={'\0'};
	cout<<"请选择保存教师信息文件的路径:"<<endl;
	cin>>path;
	ofstream outfile(path);
	if(!outfile)
	{
		cerr<<"保存失败,请检查所选路径是否正确!"<<endl;
		return;
	}
	sprintf(str,"姓名\t教师号\t工作量\n");
	outfile.write((char*)str,strlen(str));
	while(p)
	{
	sprintf(str,"%s\t%s\t%d\n",p->name,p->num,p->work_time);
	outfile.write((char*)str,strlen(str));
	sprintf(str,"对相应课程的期望值:\n");
	outfile.write((char*)str,strlen(str));
	for(int i=0;i<M;i++)
	{
     sprintf(str,"%s\t%d\n",p->tc[i].name,p->tc[i].ipri);
	 outfile.write((char*)str,strlen(str));
	}
	sprintf(str,"\n");
    outfile.write((char*)str,strlen(str));
	p=p->next;
	}
	outfile.close();
	cout<<"保存成功!"<<endl;

}


 course::course()
{
	pc=NULL;
}

 course::~course()
{
	pclist p;
	while(pc)
	{
		p=pc;
		pc=pc->next;
		delete p;
	}
}

void course::initdata()
{

	pclist p=pc;
	pclist s;
	char tag;
	int i=0;
	cout<<"请输入课程信息:"<<endl;
	cout<<"课程名\t课程号\t周学时\t总学时\t优先级"<<endl;
	do{
		if(i>=1)
		{
			cout<<"请输入课程信息:"<<endl;
	        cout<<"课程名\t课程号\t周学时\t总学时\t优先级"<<endl;
		}
		s=(pclist)malloc(sizeof(clist));
		cin>>s->name>>s->num>>s->week_time>>s->all_time>>s->priority;
		fflush(stdin);
		s->mc=true;
		s->next=NULL;
		i++;
		if(!pc)
		{
			pc=s;
			p=pc;
		}
	  else
	  {
		  p->next=s;
		  p=p->next;
	  }
	  cout<<"是否继续载入课程信息? y/Y"<<endl;
	  cin>>tag;
	  system("cls");
	}while(tag=='y'||tag=='Y');
}

void course::save()
{
	char path[20]="D:\\course.txt";
	pclist p=pc;
	char str[100]={'\0'};
	cout<<"请输入文件保存路径:"<<endl;
	cin>>path;
	ofstream outfile(path);
	if(!outfile)
	{
		cerr<<"保存失败,请检查输入路径是否正确";
		return;
	}
	sprintf(str,"课程名\t课程号\t周学时\t总学时\t优先级\n");
	outfile.write((char*)str,strlen(str));
    while(p)
	{
	    sprintf(str,"%s\t%s\t%d\t%d\t%d\n",p->name,p->num,p->week_time,p->all_time,p->priority);
		outfile.write((char*)str,strlen(str));
		p=p->next;

	}
	outfile.close();
	cout<<"保存成功!"<<endl;
}

void sort(teacher& t,course& c)
{
  
  ptlist q=t.pt;
  ptlist n=t.pt;
  ptlist m=n;
  int sum=0;
  int num=-1;
  srand(time(0)); 

  for(int i=0;i<M;i++)
  {
     while(m)  
	 {
		 m=n->next;
		 
		 if(m==NULL)
			 break;
		 for(int j=0;j<M;j++)
		 if((m->tc[i].ipri==n->tc[j].ipri)&&(0==strcmp(m->tc[i].name,n->tc[j].name)))
		 {
			 num=rand()%2;
			 switch(num)
			 {
			 case 0:
				 (convert(c,q->tc[num].name))->mc=false;
				 break;
			 case 1:
				 (convert(c,q->tc[num].name))->mc=false;
				 break;
			 default:
				 break;
			 }
		 }
        n=n->next;
	 }
  while(q)
  {

  for(int i=0;i<M;i++)
  {
	  if((convert(c,q->tc[i].name))->mc) 
	  {
		  sum+=(convert(c,q->tc[i].name))->all_time;
		  (convert(c,q->tc[i].name))->mc=false;
		  if(i==0)
		  strcpy(q->cbuf,q->tc[i].name);
		  else
		  {
		  strcat(q->cbuf," ");
	      strcat(q->cbuf,q->tc[i].name);
		  }
	 
	    if(sum>=q->work_time)
		  break;
	  }
  }
  sum=0;
  q=q->next;
  }
  }
cout<<"课程已排好!"<<endl;

}
//test
void print(teacher& t)
{
	ptlist p=t.pt;
	cout<<"最终排课情况:"<<endl;
	cout<<"教师姓名\t工作量\t教授课程"<<endl;
	while(p)
	{
	  cout<<p->name<<"\t\t"<<p->work_time<<"\t"<<p->cbuf<<endl;
	  p=p->next;
	}
}

pclist convert(course& c,char * s)
{
	pclist p=c.pc;
	while(p)
	{
		if(0==strcmp(p->name,s))
			return p;
		else
			p=p->next;
	}
	cout<<"应用程序出错!"<<endl;
	return NULL;
}

teacher tea;
course  cou;

void menu()
{
    bool ttag=false;
	bool ctag=false;
	char tag;
	int choice=0;
	do{
		system("cls");
		cout<<">>>>>>>欢迎使用教师排课系统,请根据提示完成相关操作<<<<<<<<<<<<<<<<<<<<"<<endl;
		cout<<">>>>>>>1:载入教师信息"<<endl;
		cout<<">>>>>>>2:载入课程信息"<<endl;
		cout<<">>>>>>>3:存储教师信息"<<endl;
		cout<<">>>>>>>4:存储课程信息"<<endl;
		cout<<">>>>>>>5:教师排课"<<endl;
		cout<<">>>>>>>6:打印排课结果"<<endl;
		cout<<">>>>>>>0:退出"<<endl;
		fflush(stdin);
		cout<<"请输入选择:"<<endl;
		cin>>choice;
		switch(choice)
		{
		case 1:
			system("cls");
			cout<<"***********教师信息载入******************"<<endl;
            tea.initdata();
			ttag=true;
			break;
		case 2:
			system("cls");
			cout<<"***********课程信息载入******************"<<endl;
			cou.initdata();
			ctag=true;
			break;
		case 3:
			system("cls");
			cout<<"***********教师信息保存******************"<<endl;
			if(!ttag)
				cout<<"请先载入教师信息"<<endl;
			else
				tea.save();
			break;
        case 4:
			system("cls");
			cout<<"***********课程信息保存******************"<<endl;
			if(!ctag)
			  cout<<"请先载入课程信息"<<endl;
			else
				cou.save();
			break;
		case 5:
			system("cls");
			cout<<"***********教师排序界面*****************"<<endl;
			if(!ttag||!ctag)
				cout<<"请先载入相关信息"<<endl;
			else
				sort(tea,cou);
			break;
		case 6:
			system("cls");
			cout<<"***********排课信息打印******************"<<endl;
			if(!ttag||!ctag)
				cout<<"请先载入相关信息"<<endl;
			else
				print(tea);
			break;
		default:
			system("cls");
			cout<<"\t****************THANKS FOR YOUR USE***********"<<endl;
			cout<<"\t*****************感谢使用本系统!*************"<<endl;
			exit(0);
		}
		cout<<"系统使用中........."<<endl;
		cout<<"是否继续其他操作? y/Y"<<endl;
		cin>>tag;
	}while(tag=='y'||tag=='Y');

}

int main()
{
	cout << "请输入教师人数: ";
	cin >> N;
	cout << "请输入课程数: ";
	cin >> M; 
	menu();
	return 0;
}
