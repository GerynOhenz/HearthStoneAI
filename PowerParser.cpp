#include <stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <windows.h>
//#include "record_data.h"

const int maxlen=210;
const int timelen=16;
enum command_state_type{COMPLETE, HALF, END};
FILE *Power_File=fopen("input.txt", "r");
FILE * const fout=fopen("output.txt", "w");


struct time
{
	double hour, minute, second;

	time()
	{
		hour=minute=second=-1;
	}

	time(char *st)
	{
		char str[timelen];
		str[0]=st[0]; str[1]=st[1]; str[2]='\0';
		hour=atof(str);

		str[0]=st[3]; str[1]=st[4]; str[2]='\0';
		minute=atof(str);

		for (int i=0; i<10; ++i) str[i]=st[6+i];
		str[10]='\0';
		second=atof(str);
	}

	void print()
	{
		printf("%lf %lf %lf\n", hour, minute, second);
	}
};

struct Power_Debug_Message
{
	time Debug_time;
	std::string GameState;
	std::string tag;
	int value;

	Power_Debug_message()
	{
		GameState="";
		tag="";
		value=-1;
	}
};

void get_command(char (&str)[maxlen], command_state_type &last_state)
{
	assert(Power_File!=NULL);

	static int idx=0;
	if (last_state==COMPLETE) idx=0;

	char ch;
	while ((ch=fgetc(Power_File))!='\n' && ch!=EOF) str[idx++]=ch;
	if (ch==EOF)
	{
		last_state=HALF;
		return;
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
	last_state=COMPLETE;
}

void Pattern(char *st, command_state_type &cur_state)
{
	Power_Debug_Message message;

	assert(st[0]=='D');

	char timestr[timelen];
	memcpy(timestr, st+2, timelen);
	message.Debug_time=time(timestr);
#ifdef TIME_DEBUG
	message.Debug_time.print();
#endif

	int idx=2;
}

int main()
{
	char str[maxlen]="";
	bool refresh=false;
	command_state_type command_state=COMPLETE;
	while (command_state!=END)
	{
		get_command(str, command_state);
		switch (command_state)
		{
			case COMPLETE:
				Pattern(str, command_state);
				break;

			case HALF:
				Sleep(500);
				break;

			case END:
				return 0;
		}
	}
	fclose(Power_File);
	return 0;
}
