#include <stdio.h>
#include <string>
#include <stdlib.h>

const int Command_Type_Sum=14;

const int timelen=16;

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

struct stime
{
	double hour, minute, second;

	stime();

	stime(std::string st);

	void print();
};

struct Power_Debug_Message
{
	stime Debug_time;
	std::string GameState;
	std::string tag;
	int value;

	Power_Debug_Message();
};

bool Pattern(std::string st);