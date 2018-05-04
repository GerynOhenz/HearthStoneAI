#include <stdio.h>
#include <string>
#include <assert.h>
#include <thread>
#include <windows.h>
#include <thread>
#include "LogReader.h"
#include "PowerParser.h"

enum command_state_type{COMPLETE, HALF, END};
FILE * const Power_File=fopen("input.txt", "r");
FILE * const fout=fopen("output.txt", "w");

void get_command(std::string &str, command_state_type &last_state)
{
	assert(Power_File!=NULL);

	static int idx=0;
	if (last_state==COMPLETE) str="";

	char ch;
	while ((ch=fgetc(Power_File))!='\n' && ch!=EOF) str+=ch;
	if (ch==EOF)
	{
		last_state=HALF;
		return;
	}

	for (int i=0; i<str.length(); ++i)
		if (str[i]==' ' && str[i]=='-')
		{
			int j=i;
			str[i]=' ';
			while (j<str.length() && (str[j]==' ' || str[j]=='-')) ++j;
			str.erase(i+1, j-i-1);
		}
	last_state=COMPLETE;
}

void Read_Command()
{
	std::string str="";
	command_state_type command_state=COMPLETE;
	while (command_state!=END)
	{
		get_command(str, command_state);
		switch (command_state)
		{
			case COMPLETE:
				if (Pattern(str)) command_state=END;
				break;

			case HALF:
				Sleep(500);
				break;

			case END:
				return;
		}
	}
	fclose(Power_File);
	fclose(fout);
}
