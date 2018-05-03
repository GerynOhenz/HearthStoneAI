#include <cstdio>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

const int maxlen=210;
FILE * Power_File=fopen("input.txt", "r");
FILE * const fout=fopen("output.txt", "w");
//#include "record_data.h"
//D 17:23:15.8517996 GameState.DebugPrintPowerList() - Count=109
/*
struct time
{
	double hour, minute, second;

	time()
	{
		hour=minute=second=-1;
	}

	time(char *st)
	{
		char str[maxlen]="";
		int cur=0;
		int idx=0;
		while (st[cur]!=':') str[idx++]=st[cur++];
		str[idx]='\0';
		hour=atof(str);

		idx=0;
		++cur;
		while (st[cur]!=':') str[idx++]=st[cur++];
		str[idx]='\0';
		minute=atof(str);

		idx=0;
		++cur;
		while (st[cur]!=':') str[idx++]=st[cur++];
		str[idx]='\0';
		second=atof(str);
	}
};

struct Power_Debug_message
{
	time Debug_time;
	string Debug_type;
	string tag;
	int value;

	Power_Debug_message()
	{
		Debug_type="";
		tag="";
		value=-1;
	}
};*/

void get_command(char *str)
{
	assert(Power_File!=NULL);
	char ch;
	static int idx=0;
	while (!isalpha(ch=fgetc(Power_File)) && !(ch>='0' && ch<='9'));
	while ((ch=fgetc(Power_File)!='\n'))
	{
		str[idx++]=ch;
		fputc(ch, fout);
	}

	int len=0;
	for (int i=0; i<idx; )
	{
		if (str[i]!=' ' && str[i]!='-') str[len++]=str[i++];
		else
		{
			str[len++]=' ';
			while (i<idx && (str[i]==' ' || str[i]=='-')) ++i;
		}
	}
	str[len]='\0';
}
/*
int calc_type(char *st, Power_Debug_message &message)
{
	if (st[0]>='0' && st[0]<='9')
	{
		char str[maxlen]="";
		strncat(st, ":", 1);
		message.Debug_time=time(st);
	}
	else
	{
	}
}

void Pattern(char *st)
{
	static Pattern_node *cur=Pattern_root;

	int type=calc_type(st, message);
	bool flag=false;
	for (auto &nx: cur->nextPtr)
		if (nx->type==type)
		{
			flag=true;
			cur=nx;
			break;
		}

	assert(flag);

	if (cur->accept==true)
	{
		put_in(message);
		return;
	}
}*/

int main()
{
	while (true)
	{
		char str[maxlen]="";
		get_command(str);
		printf("%s", str);
		//Pattern(str);
	}
	fclose(Power_File);
	return 0;
}