#include <stdio.h>
#include <string>
#include <assert.h>
#include "PowerParser.h"

const int timelen=16;

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

	message.Debug_time=time(st.substr(0, timelen));
	st.erase(0, timelen+1);


#ifdef TIME_DEBUG
	message.Debug_time.print();
#endif

	//printf("%s\n", st.c_str());
	printf("%s\n", st.substr(0, st.find(' ')).c_str());
	int cur_command_type=get_command_type(st.substr(0, st.find(' ')));
	printf("%d\n", cur_command_type);

	return false;
}