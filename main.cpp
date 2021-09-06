#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define L 50
#define G 10
char adminname[5]="lzx";//管理员账号和密码，也可写入文件中
char adminpassword[10]="123456";

typedef struct node{
	int num;
	char name[L];
	char password[L];
	long int money;
	char grade[G];
	struct node *next;
}node;

//全局的。
node *user_head;//用户头指针
node *user_end;//用户尾指针---方便插入
node *userGR;//登录时，指向用户

//文件函数
node* Rcreatelink();
void save();

//登陆函数
int search(char name[L],char password[L]);
int login();
void boundar();

//管理员函数
void looklook();
void increase();
void revise();
void adminmenu();
void admin();

//用户函数
void user();
void usermenu();
//通过金额自动生成会员等级
void zidongsc(node *q);

void zidongsc(node *q)
{
	char grade[6][50]={"普通","白银","黄金","铂金","钻石","黑金"};
	int num;
	num=q->money/1000;
	if(num<=3)
		strcpy(q->grade,grade[0]);
	else if(num<=6)
		strcpy(q->grade,grade[1]);
	else if(num<=9)
		strcpy(q->grade,grade[2]);
	else if(num<=12)
		strcpy(q->grade,grade[3]);
	else if(num<=15)
		strcpy(q->grade,grade[4]);
	else
		strcpy(q->grade,grade[5]);
}

node* Rcreatelink()
{
	int num,money;
	char name[L],password[L],grade[G];
	node *head =(node*)malloc(sizeof(node));
	node *p;
	FILE *fp = fopen("user.txt","r");
	p = head;
	//p=user_head;
	if(fp==NULL)
	{
		printf("");
	}
	else
	{
		while(fscanf(fp,"%d %s %s %d %s",&num,name,password,&money,grade)!=EOF)//读出  EOF就是文件结尾
		{
		   node *q = (node*)malloc(sizeof(node));
		   q->num = num;
		   strcpy(q->name,name);
		   strcpy(q->password,password);
		   q->money=money;
		   strcpy(q->grade,grade);
		   p->next=q;
		   p=q;
		}
		p->next=NULL;
		user_end = p;
	}
	fclose(fp);
	return head;
}

void save()
{
	node* temp = user_head->next;
	FILE* fp = fopen("user.txt", "w");
	//setbuf(fp,NULL);
	while (temp)
	{
		fprintf(fp,"%d %s %s %d %s \n",temp->num,temp->name,temp->password,temp->money,temp->grade);
		//fflush(fp);
		temp = temp->next;
	}
	fclose(fp);
}

int sreach(char name[],char password[])//通过文件查找是否存在该用户
{
	node *p;
	p=user_head->next;
	if((strcmp(name,adminname)==0)&&(strcmp(password,adminpassword)==0))
		return 1;
	while(p)//
	{

		if(strcmp(name,p->name)==0&&strcmp(password,p->password)==0)
		{
			userGR = p;
			return 2;
		}
		p=p->next;
	}
	return 0;
}

int login()
{
	int flag;
	char a[L],c[L];
	printf("\t\t\t-----------------------\n");
	printf("\t\t\t+---- 登 陆 页 面 ----+\n");
	printf("\t\t\t-----------------------\n");
	printf("\t\t\t管理员： ");
	scanf("%s",&a);
	printf("\t\t\t密码：   ");
	scanf("%s",&c);
	printf("\t\t\t-----------------------\n");
	flag = sreach(a,c);
	return flag;
}

void boundar()
{
	int FL;
	FL=login();
	while(FL==0)
	{
		system("cls");
		printf("\t\t\t用户名或密码错误!\n");
		printf("\t\t\t请重新输入!\n");
		FL=login();
	}

	if(FL==1)
	{
		printf("\t\t\t登陆成功!\n");
		system("cls");
		admin();//管理员

	}
	else if(FL==2)
	{
		printf("\t\t\t登陆成功!\n");
		system("cls");
		user();//用户
	}
}

void looklook()
{
	int a,num;
	node *p;
	p = user_head->next;
	printf("看全部会员信息(1),查看某特定会员(2)\n");
	scanf("%d",&a);
	if(a==1)
	{
		printf("********************************************************\n");
		printf("| 编号 |会 员 名|   密 码   |消费金额| 会员等级 |\n");
		while(p!=NULL)
		{
			printf("|%4d  |%-8s| %-10s| %6d |   %s   |\n",p->num,p->name,p->password,p->money,p->grade);
			p=p->next;
		}
	}
	else
	{
		printf("查看会员编号:");
		scanf("%d",&num);
		while(p)
		{
			if(p->num==num)
			{
				printf("********************************************************\n");
				printf("| 编号 |会 员 名|   密 码   |消费金额| 会员等级 |\n");
				printf("|%4d  |%-8s| %-10s| %6d |   %s   |\n",p->num,p->name,p->password,p->money,p->grade);
			}
			p=p->next;
		}
	}
}
void increase()
{
	int i,n;
	int num,money;
	char name[L],password[L];
	node *p = user_end  ;
	printf("想要添加几人信息:");
	scanf("%d",&n);
	printf("********************************************************\n");
	printf("编号 会员名   密码   消费金额(根据金额生成会员等级)\n");
	for(i=0;i<n;i++)
	{
		node *r = (node *)malloc(sizeof(node));
		scanf("%d %s %s %d",&num,name,password,&money);
		r->num=num;
		strcpy(r->name,name);
		strcpy(r->password,password);
		r->money=money;
		zidongsc(r);
		p->next = r;
		r->next=NULL;
		p=r;
	}
	p->next=NULL;
	user_end = p;
	save();
}
void revise()
{
	int c,d,e=-1;
	int money;
	char name[L],password[L];
	node *p,*q;
	p=user_head;
	q=p->next;
	printf("\t\t\t1.修改  2.删除\n");
	printf("\t\t\t请输入想要进行操作:");
	scanf("%d",&c);
	if(c==1)
	{
		printf("\t\t\t请输入修改会员编号:");
		scanf("%d",&d);
		while(q)
		{
			if(q->num==d)
			{
				while(e!=0)
				{
					system("cls");
					printf("\t\t\t请输入要修改信息:\n");
					printf("1.会员名\n");
					printf("2.会员密码\n");
					printf("3.消费金额\n");
					printf("0.退出\n");
					scanf("%d",&e);
					switch(e)
					{
					case 1:
						printf("修改前会员名:%s\n",q->name);
						printf("想要修改会员名:");
						scanf("%s",name);
						strcpy(q->name,name);
						printf("\n修改成功");
						break;
					case 2:
						printf("修改前会员密码:%s\n",q->password);
						printf("想要修改密码:");
						scanf("%s",password);
						strcpy(q->password,password);
						printf("\n修改成功");
						break;
					case 3:
						printf("修改前消费金额:%d\n",q->money);
						printf("想要修改金额:");
						scanf("%d",&money);
						q->money=money;
						printf("\n修改成功!\n");
						zidongsc(q);
						break;
						//会员等级就不需要修改了，通过函数自动生成。
					case 0:
						break;
					}

				}
			}
			q=q->next;
		}
	}
	else
	{
		system("cls");
		printf("请输入想要删除的编号:");
		scanf("%d",&d);
		while(p)
		{
			if(q->num==d)
			{
				p->next=q->next;
				printf("删除成功!\n");
			}
			q=q->next;
			p=p->next;
		}
		save();
	}
}
void adminmenu()
{
	int a=-1;
	while(a!=0)
	{
		printf("\t\t\t 您具有以下功能:\n");
		printf("\t\t\t*1.查看会员信息\n");
		printf("\t\t\t*2.添加会员信息\n");
		printf("\t\t\t*3.修改会员信息\n");
		printf("\t\t\t*0.退出\n");
		printf("\t\t\t*");
		scanf("%d",&a);
		switch(a)
		{
		case 1:
			system("cls");
			looklook();
			break;
		case 2:
			system("cls");
			increase();
			save();
			break;
		case 3:
			system("cls");
			revise();
			save();
			break;
		case 0:
			break;
		}
	}
}
void admin()
{
	printf("\t\t\t欢迎您,管理员\n");
	adminmenu();
}

void usermenu()
{
	int a;
	char password[L]={0};
	printf("您拥有查看个人信息和修改密码的权限!\n");
	printf("您的个人信息如下\n:");
	printf("---------------------------------------------------\n");
	printf("| 编号 |会 员 名|   密 码   |消费金额| 会员等级 |\n");
	printf("|%4d  |%-8s| %-10s| %6d |   %s   |\n",userGR->num,userGR->name,userGR->password,userGR->money,userGR->grade);
	printf("如果想要修改密码请输入(1)");
	scanf("%d",&a);
	if(a==1)
	{
		printf("您的原始密码为:%s",userGR->password);
		printf("请输入修改的密码:");
		scanf("%s",password);
		strcpy(userGR->password,password);
		printf("修改成功!\n");
	}
	save();
}

void user()
{
	printf("欢迎您,%s会员\n",userGR->grade);
	usermenu();
	printf("再见!");
}

int main()
{
	node *head=Rcreatelink();
	user_head = NULL;
	user_head = head;
	boundar();
	printf("感谢您的使用!");
}
