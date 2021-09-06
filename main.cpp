#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define L 50
#define G 10
char adminname[5]="lzx";//����Ա�˺ź����룬Ҳ��д���ļ���
char adminpassword[10]="123456";

typedef struct node{
	int num;
	char name[L];
	char password[L];
	long int money;
	char grade[G];
	struct node *next;
}node;

//ȫ�ֵġ�
node *user_head;//�û�ͷָ��
node *user_end;//�û�βָ��---�������
node *userGR;//��¼ʱ��ָ���û�

//�ļ�����
node* Rcreatelink();
void save();

//��½����
int search(char name[L],char password[L]);
int login();
void boundar();

//����Ա����
void looklook();
void increase();
void revise();
void adminmenu();
void admin();

//�û�����
void user();
void usermenu();
//ͨ������Զ����ɻ�Ա�ȼ�
void zidongsc(node *q);

void zidongsc(node *q)
{
	char grade[6][50]={"��ͨ","����","�ƽ�","����","��ʯ","�ڽ�"};
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
		while(fscanf(fp,"%d %s %s %d %s",&num,name,password,&money,grade)!=EOF)//����  EOF�����ļ���β
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

int sreach(char name[],char password[])//ͨ���ļ������Ƿ���ڸ��û�
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
	printf("\t\t\t+---- �� ½ ҳ �� ----+\n");
	printf("\t\t\t-----------------------\n");
	printf("\t\t\t����Ա�� ");
	scanf("%s",&a);
	printf("\t\t\t���룺   ");
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
		printf("\t\t\t�û������������!\n");
		printf("\t\t\t����������!\n");
		FL=login();
	}

	if(FL==1)
	{
		printf("\t\t\t��½�ɹ�!\n");
		system("cls");
		admin();//����Ա

	}
	else if(FL==2)
	{
		printf("\t\t\t��½�ɹ�!\n");
		system("cls");
		user();//�û�
	}
}

void looklook()
{
	int a,num;
	node *p;
	p = user_head->next;
	printf("��ȫ����Ա��Ϣ(1),�鿴ĳ�ض���Ա(2)\n");
	scanf("%d",&a);
	if(a==1)
	{
		printf("********************************************************\n");
		printf("| ��� |�� Ա ��|   �� ��   |���ѽ��| ��Ա�ȼ� |\n");
		while(p!=NULL)
		{
			printf("|%4d  |%-8s| %-10s| %6d |   %s   |\n",p->num,p->name,p->password,p->money,p->grade);
			p=p->next;
		}
	}
	else
	{
		printf("�鿴��Ա���:");
		scanf("%d",&num);
		while(p)
		{
			if(p->num==num)
			{
				printf("********************************************************\n");
				printf("| ��� |�� Ա ��|   �� ��   |���ѽ��| ��Ա�ȼ� |\n");
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
	printf("��Ҫ��Ӽ�����Ϣ:");
	scanf("%d",&n);
	printf("********************************************************\n");
	printf("��� ��Ա��   ����   ���ѽ��(���ݽ�����ɻ�Ա�ȼ�)\n");
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
	printf("\t\t\t1.�޸�  2.ɾ��\n");
	printf("\t\t\t��������Ҫ���в���:");
	scanf("%d",&c);
	if(c==1)
	{
		printf("\t\t\t�������޸Ļ�Ա���:");
		scanf("%d",&d);
		while(q)
		{
			if(q->num==d)
			{
				while(e!=0)
				{
					system("cls");
					printf("\t\t\t������Ҫ�޸���Ϣ:\n");
					printf("1.��Ա��\n");
					printf("2.��Ա����\n");
					printf("3.���ѽ��\n");
					printf("0.�˳�\n");
					scanf("%d",&e);
					switch(e)
					{
					case 1:
						printf("�޸�ǰ��Ա��:%s\n",q->name);
						printf("��Ҫ�޸Ļ�Ա��:");
						scanf("%s",name);
						strcpy(q->name,name);
						printf("\n�޸ĳɹ�");
						break;
					case 2:
						printf("�޸�ǰ��Ա����:%s\n",q->password);
						printf("��Ҫ�޸�����:");
						scanf("%s",password);
						strcpy(q->password,password);
						printf("\n�޸ĳɹ�");
						break;
					case 3:
						printf("�޸�ǰ���ѽ��:%d\n",q->money);
						printf("��Ҫ�޸Ľ��:");
						scanf("%d",&money);
						q->money=money;
						printf("\n�޸ĳɹ�!\n");
						zidongsc(q);
						break;
						//��Ա�ȼ��Ͳ���Ҫ�޸��ˣ�ͨ�������Զ����ɡ�
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
		printf("��������Ҫɾ���ı��:");
		scanf("%d",&d);
		while(p)
		{
			if(q->num==d)
			{
				p->next=q->next;
				printf("ɾ���ɹ�!\n");
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
		printf("\t\t\t ���������¹���:\n");
		printf("\t\t\t*1.�鿴��Ա��Ϣ\n");
		printf("\t\t\t*2.��ӻ�Ա��Ϣ\n");
		printf("\t\t\t*3.�޸Ļ�Ա��Ϣ\n");
		printf("\t\t\t*0.�˳�\n");
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
	printf("\t\t\t��ӭ��,����Ա\n");
	adminmenu();
}

void usermenu()
{
	int a;
	char password[L]={0};
	printf("��ӵ�в鿴������Ϣ���޸������Ȩ��!\n");
	printf("���ĸ�����Ϣ����\n:");
	printf("---------------------------------------------------\n");
	printf("| ��� |�� Ա ��|   �� ��   |���ѽ��| ��Ա�ȼ� |\n");
	printf("|%4d  |%-8s| %-10s| %6d |   %s   |\n",userGR->num,userGR->name,userGR->password,userGR->money,userGR->grade);
	printf("�����Ҫ�޸�����������(1)");
	scanf("%d",&a);
	if(a==1)
	{
		printf("����ԭʼ����Ϊ:%s",userGR->password);
		printf("�������޸ĵ�����:");
		scanf("%s",password);
		strcpy(userGR->password,password);
		printf("�޸ĳɹ�!\n");
	}
	save();
}

void user()
{
	printf("��ӭ��,%s��Ա\n",userGR->grade);
	usermenu();
	printf("�ټ�!");
}

int main()
{
	node *head=Rcreatelink();
	user_head = NULL;
	user_head = head;
	boundar();
	printf("��л����ʹ��!");
}
