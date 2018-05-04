#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <assert.h>
#include <thread>
#include "PowerParser.h"
#include "Table.h"

stime::stime()
{
	hour=minute=second=-1;
}

stime::stime(std::string st)
{
	hour=atof(st.substr(0, 2).c_str());
	minute=atof(st.substr(3, 2).c_str());
	second=atof(st.substr(6, 10).c_str());
}

Power_Debug_Message::Power_Debug_Message()
{
	GameState="";
	tag="";
	value=-1;
}

void stime::print()
{
	printf("%lf %lf %lf\n", hour, minute, second);
}

int get_command_type(std::string st)
{
	for (int i=0; i<Command_Type_Sum; ++i)
		if (Command_Type[i]==st) return i;
	return -1;
}

bool Pattern(std::string st)
{
	std::string End="TAG_CHANGE Entity=GameEntity tag=STATE value=COMPLETE";
	if (st.find(End)!=std::string::npos) return true;

	Power_Debug_Message message;

	assert(st[0]=='D');
	st.erase(0, 2);

	message.Debug_time=stime(st.substr(0, timelen));
	st.erase(0, timelen+1);


#ifdef TIME_DEBUG
	message.Debug_time.print();
#endif

	int cur_command_type=get_command_type(st.substr(0, st.find(' ')));
	st.erase(0, st.find(' ')+1);

	static sCommand command;
	static int count=-1;
	int OptionId=-1;

	switch (cur_command_type)
	{
		case 0:
			if (count==-1)
			{
				assert(st.substr(0, 3)=="id=");
				st.erase(0, 3);
				command.id=atoi(st.substr(0, st.find(' ')).c_str());
				st.erase(0, st.find(' ')+1);

				assert(st.substr(0, 7)=="Player=");
				st.erase(0, 7);
				assert(st.find("EntitiesCount")!=std::string::npos);
				command.Player=st.substr(0, st.find("EntitiesCount")-1);
				st.erase(0, st.find("EntitiesCount")+14);

				command.EntitiesCount=atoi(st.c_str());
				count=0;
			}
			else
			{
				command.Entities.push_back(sEntities(st));

				if (++count==command.EntitiesCount)
				{
					count=0;
					std::thread (TableModify, command).detach();
					command.clear();
				}
			}
			break;
		case 1:
			if (count==-1)
			{
				assert(st.substr(0, 3)=="id=");
				st.erase(0, 3);
				command.id=atoi(st.substr(0, st.find(' ')).c_str());
				st.erase(0, st.find(' ')+1);

				assert(st.substr(0, 7)=="Player=");
				st.erase(0, 7);
				command.Player=st.substr(0, st.find(' '));
				st.erase(0, st.find(' ')+1);

				assert(st.substr(0, 9)=="TaskList=");
				st.erase(0, 9);
				command.TaskList=atoi(st.substr(0, st.find(' ')).c_str());
				st.erase(0, st.find(' ')+1);

				assert(st.substr(0, 11)=="ChoiceType=");
				st.erase(0, 11);
				command.ChoiceType=st.substr(0, st.find(' '));
				st.erase(0, st.find(' ')+1);

				assert(st.substr(0, 9)=="CountMin=");
				st.erase(0, 9);
				command.CountMin=atoi(st.substr(0, st.find(' ')).c_str());
				st.erase(0, st.find(' ')+1);

				assert(st.substr(0, 9)=="CountMax=");
				st.erase(0, 9);
				command.CountMax=atoi(st.c_str());

				count=-2;
			}
			if (count==-2)
			{
				assert(st=="Source=GameEntity");
				count=0;
			}
			else
			{
				command.Entities.push_back(sEntities(st));

				if (++count==command.CountMax)
				{
					count=0;
					std::thread (TableModify, command).detach();
					command.clear();
				}
			}
			break;
		case 2:
			//ignore
			break;
		case 3:
			if (st.substr(0, 3)=="id=") break;

			assert(st.substr(0, 6)=="option");
			st.erase(0, 7);
			OptionId=atoi(st.substr(0, st.find(' ')).c_str());
			st.erase(0, st.find(' ')+1);

			command.option.push_back(soption());

			assert(st.substr(0, 5)=="type=");
			command.option[OptionId].type=st.substr(0, st.find(' '));
			st.erase(0, st.find(' ')+1);
			
			command.option[OptionId].mainEntity=sEntities(st);

			assert(st.find("error=")!=std::string::npos);
			st.erase(0, st.find("error=")+6);

			command.option[OptionId].error=st.substr(0, st.find(' '));
			st.erase(0, st.find(' ')+1);

			assert(st.substr(0, 11)=="errorParam=");
			st.erase(0, 11);
			command.option[OptionId].errorParam=st;

			break;

		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			if (!command.empty())
			{
				std::thread (TableModify, command).detach();
				command.clear();
			}
			break;
		case 10:
			break;
		case 11:
			break;
		case 12:
			break;
		case 13:
			break;
	}
	return false;
}