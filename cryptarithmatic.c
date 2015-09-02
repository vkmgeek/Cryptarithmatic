/*
 * Look at the LICENSE file for licensing related information
 * Copyrights
 *       Viral Mehta
 *       quactinoids@gmail.com
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LOOPCOUNT 40
#define MINSIZE 4

char chromosome[10], diff_char[10], damn_sure[10];
float global_cnt=0;
int chromosome_cnt=9, diff_char_cnt=0;
char equation[20], operator1[10], operator2[10], answer[10];
float sol_op1[10], sol_op2[10], sol_sum[10];
int global_sol_cnt=0;
int len_op1, len_op2, len_ans;
int loopcount;
void call_findsolution();
int crypt();
void loopit();
void findsolution();
void fill_min_array();

struct find_better{
	float err;
	char chromosome[10];
	int done;
};

struct find_better temp[60];
struct find_better taken,min[MINSIZE];

void arithmetic_propogation(void)
{
	int j = 0;

	for(int t=0;t<10;t++)
		damn_sure[t]=0;

	if(len_ans>len_op1 && len_ans>len_op2)
	{
		damn_sure[1]=1;
		char temp,temp1;
		temp=answer[0];
		for(j=0;j<10;j++)
		{
			if(temp==chromosome[j]) 
				break;
			else 
				continue;
		}
		temp1=chromosome[1];
		chromosome[j]=temp1;
		chromosome[1]=temp;
	}


	int min;
	if(len_op1 < len_op2)
		min=len_op1;
	else
		min=len_op2;

	j=min-1;

	if(operator1[len_op1-1]==answer[len_ans-1])
	{
		int x;
		damn_sure[0]=1;

		char temp,temp1;
		temp=operator2[len_op2-1];
		for(x=0;x<10;x++)
		{
			if(temp==chromosome[x])
				break;
			else
				continue;
		}
		temp1=chromosome[0];
		chromosome[x]=temp1;
		chromosome[0]=temp;
	}

	if(operator2[len_op2-1]==answer[len_ans-1])
	{
		int x;
		damn_sure[0]=1;

		char temp,temp1;
		temp=operator1[len_op1-1];
		for(x=0;x<10;x++)
		{
			if(temp==chromosome[x]) 
				break;
			else 
				continue;
		}
		temp1=chromosome[0];
		chromosome[x]=temp1;
		chromosome[0]=temp;
	}
}


void random(void)
{
	int i;
	while(1)
	{
		taken.err=100000;
		int c,temp[10];
		for(int i=0;i<10;i++)
		{
			chromosome[i]=' ';
			temp[i]=0;
		}
		for(i=0;i<diff_char_cnt;i++)
		{
			while(1)
			{
				c=(rand()%10);
				if(temp[c]==1) continue;
				else
				{
					chromosome[c]=diff_char[i];
					temp[c]=1;
					break;
				}
			}
		}
		if(chromosome[0]==operator1[0]||chromosome[0]==operator2[0]||chromosome[0]==answer[0])
			continue;
		else 
			break;
	}
}

void print_help()
{
	printf("Enter equation without any whitespace\n");
	printf("For e.g., send+more=money\n");
}

void main()
{
	char ch;
	int length;
	int k=2,cnt,i=1;
	int diff_char_flag;

	print_help();
	printf("Enter whole equation : ");

	scanf("%s", &equation);
	diff_char[diff_char_cnt++]=chromosome[chromosome_cnt--]=equation[0];
	ch=equation[1];

	length=strlen(equation);
	while(ch!='\0'){
		diff_char_flag=1;
		for(cnt=0;cnt<k-1;cnt++){
			if(ch==equation[cnt]){
				diff_char_flag=0;
				break;
			}
			else{
				continue;
			}
		}
		if(diff_char_flag==1){
			i++;
			if(ch=='+' || ch=='=');
			else{
				diff_char[diff_char_cnt++]=chromosome[chromosome_cnt--]=ch;
			}
		}
		ch=equation[k++];
	}

	if((i-2)>10){
		printf("Not Possible Error no. 1 \n");
		exit(0);
	}


	int flag=1,j=0;
	//cout<<length;
	for(i=0;i<length;i++){
		if(equation[i]=='+'){
			operator1[j]='\0';
			flag=2;
			j=0;
			continue;
		}
		if(equation[i]=='='){
			operator2[j]='\0';
			flag=3;
			j=0;
			continue;
		}
		if(flag==1)
			operator1[j++]=equation[i];
		if(flag==2)
			operator2[j++]=equation[i];
		if(flag==3)
			answer[j++]=equation[i];
	}
	answer[j]='\0';
	//////////////////////////// input taken ///////////////////////
	//////////////////////////cout<<strlen(operator1);

	len_op1=strlen(operator1);
	len_op2=strlen(operator2);
	len_ans=strlen(answer);

	if(len_ans<len_op1 || len_ans<len_op2){
		printf("Not Possible Error no. 2 \n");
		exit(0);
	}

	if( len_ans>(len_op1+1) && len_ans>(len_op2+1) ){
		printf("Not Possible Error no. 3\n");
		exit(0);
	}
	////////////////////// error checked //////////////////

	//////////whatever input is true now ///////////////////////
	findsolution();


}

void call_findsolution()
{
	char ques;
	while(1)
	{
		printf("\n\nDo u want another solution if exists (y/Y | _ ) : ");
		scanf("%c", &ques);
		if(ques=='y'||ques=='Y') findsolution();
		else exit(0);

	}
}

int crypt(){
	int i;
	int local1,local2;
	//////////////// generate random to change position ///////////
	global_cnt++;
	if(global_cnt>22000000)
	{
		printf("\nIt seems there is not possible solution \n");
		exit(0);
	}
	while(1)
	{
		local1=(rand()%10);
		local2=(rand()%10);
		if(damn_sure[local1]==1||damn_sure[local2]==1) continue;
		if(local1==0 && (chromosome[local2]==operator1[0] ||chromosome[local2]==operator2[0] ||chromosome[local2]==answer[0]))continue;
		if(local2==0 && (chromosome[local1]==operator1[0] ||chromosome[local1]==operator2[0] ||chromosome[local1]==answer[0]))continue;
		else break;
	}
	////////////////over ////////////////////////////////////

	////////////////change position /////////////////////
	char temp1;
	temp1=chromosome[local1];
	chromosome[local1]=chromosome[local2];
	chromosome[local2]=temp1;
	//////////////////////// over ////////////////////////////

	/////////// get absolute error ///////////////////////////
	float op1,op2,sum;
	op1=op2=sum=0.0;
	//cout<<len_op1<<endl;
	for(i=0;i<len_op1;i++){
		for(int j=0;j<10;j++){
			if(operator1[i]==chromosome[j]){
				op1=op1+(j*pow(10,(len_op1-(1+i))));
				//cout<<endl<<op1;
				break;
			}
		}
	}

	//cout<<"\n"<<op1;
	//getch();
	for(i=0;i<len_op2;i++){
		for(int j=0;j<10;j++){
			if(operator2[i]==chromosome[j]){
				op2=op2+(j*pow(10,(len_op2-(1+i))));
				//cout<<endl<<op2;
				break;
			}
		}
	}

	//cout<<"\n"<<op2;
	//getch();

	//cout<<len_ans;
	for(i=0;i<len_ans;i++){
		for(int j=0;j<10;j++){
			if(answer[i]==chromosome[j]){
				sum=sum+(j*pow(10,(len_ans-(1+i))));
				//cout<<endl<<sum;
				break;
			}
		}
	}
	if(global_sol_cnt>9)
	{
		printf("\n\nProgram is limited to find various 10 solutions ... Bye!!!");
		exit(0);
	}
	for(int q=0;q<global_sol_cnt;q++)
		if(op1==sol_op1[q] &&op2==sol_op2[q] &&sum==sol_sum[q])
		{op1=23423;op2=222;sum=333;}
	//////wow how to work out with else superb//////////
	if((op1+op2-sum)==0){
		sol_op1[global_sol_cnt]=op1;sol_op2[global_sol_cnt]=op2;sol_sum[global_sol_cnt++]=sum;
		printf("\nSolution no. %d \n", global_sol_cnt);
		printf("\t%s + %s = %s \n", operator1, operator2, answer);
		printf("\t%.0f + %.0f = %.0f \n", op1, op2, sum);
		global_cnt=0;
		return 0;
		//exit(0);
	}
	else
	{
		char temp1;
		temp1=chromosome[local1];
		chromosome[local1]=chromosome[local2];
		chromosome[local2]=temp1;

		temp[loopcount].err=abs(op1+op2-sum);
		//cout<<" "<<temp[loopcount].err<<" ";
		for(int c=0;c<10;c++)
			temp[loopcount].chromosome[c]=chromosome[c];
		return 1;
	}


}
void loopit()
{
	loopcount=0;int ret_n;
	while(loopcount<LOOPCOUNT)
	{
		ret_n=crypt();
		if(ret_n==0) call_findsolution();
		loopcount++;
	}
}
void fill_min_array()
{
	int temp1;
	for(int v=0;v<MINSIZE;v++)
	{
		for(int t=0;t<LOOPCOUNT;t++)
		{
			if(temp[t].err<min[v].err && temp[t].done!=1)
			{
				temp1=t;
				min[v].err=temp[t].err;
				for(int c=0;c<10;c++)
					min[v].chromosome[c]=temp[t].chromosome[c];

			}

		}
		temp[temp1].done=1;

	}
}
void findsolution()
{
	int c, z;
	arithmetic_propogation();
	int flag_changed=0,d=6,t=0;
	for(int r=0;r<20;r++)
		temp[r].done=0;
	loopcount=0;
	for(int z=0;z<MINSIZE;z++)
		min[z].err=100000;
	taken.err=100000;
	loopit();
	fill_min_array();
	for(int c=0;c<10;c++) chromosome[c]=min[0].chromosome[c];
	loopit();
	while(1)
	{

		for(int d=0;d<(MINSIZE-1);d++)
		{
			//cout<<endl<<"min changed\n"<<min[d].err;getch();
			while(1)
			{
				flag_changed=0;
				for(int t=0;t<LOOPCOUNT;t++)
				{

					if(temp[t].err<taken.err)
					{
						flag_changed=1;
						taken.err=temp[t].err;
						for(c=0;c<10;c++)
							taken.chromosome[c]=temp[t].chromosome[c];
					}
				}
				//cout<<taken.err<<" ";getch();
				if(flag_changed==1)
				{
					for(c=0;c<10;c++) chromosome[c]=taken.chromosome[c];
					loopit();
					continue;
				}
				else
				{
					for(c=0;c<10;c++) chromosome[c]=min[d+1].chromosome[c];
					taken.err=min[d+1].err;
					loopit();
					break;
				}
			}
		}
		for(z=0;z<MINSIZE;z++)
			min[z].err=100000;
		taken.err=100000;
		random();
		arithmetic_propogation();
		loopit();
		fill_min_array();
	}
}

