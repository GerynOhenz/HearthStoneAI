#include <stdio.h>
#include <string>
#include <stdlib.h>

const int Command_Type_Sum=14;

const std::string Command_Type[Command_Type_Sum]=
{
	"GameState.DebugPrintEntitiesChosen()",
	"GameState.DebugPrintEntityChoices()",
	"GameState.DebugPrintGame()",
	"GameState.DebugPrintOptions()",
	"GameState.DebugPrintPower()",
	"GameState.DebugPrintPowerList()",
	"GameState.SendChoices()",
	"GameState.SendOption()",
	"PowerProcessor.DoTaskListForCard()",
	"PowerProcessor.EndCurrentTaskList()",
	"PowerProcessor.PrepareHistoryForCurrentTaskList()",
	"PowerSpellController",
	"PowerTaskList.DebugDump()",
	"PowerTaskList.DebugPrintPower()",
};

struct time
{
	double hour, minute, second;

	time()
	{
		hour=minute=second=-1;
	}

	time(std::string st)
	{
		hour=atof(st.substr(0, 2).c_str());
		minute=atof(st.substr(3, 2).c_str());
		second=atof(st.substr(6, 10).c_str());
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

	Power_Debug_Message()
	{
		GameState="";
		tag="";
		value=-1;
	}
};

bool Pattern(std::string st);