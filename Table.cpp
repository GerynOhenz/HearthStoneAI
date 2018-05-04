#include <stdio.h>
#include <string>
#include <assert.h>
#include "Table.h"

sEntities::sEntities()
{
	entityName=cardType=zone=cardId="";
	id=zonePos=player=-1;
}

sEntities::sEntities(std::string &st)
{
	st.erase(0, st.find('=')+1);

	assert(st.substr(0, 12)=="[entityName=");
	st.erase(0, 12);
	if (st.find("[cardType=")!=std::string::npos)
	{
		entityName=st.substr(0, st.find('[')-1);
		st.erase(0, st.find('[')+10);

		cardType=st.substr(0, st.find(']'));
		st.erase(0, st.find(']')+1);
	}
	else
	{
		entityName=st.substr(0, st.find("id=")-1);
		st.erase(0, st.find("id="));
	}

	assert(st.substr(0, 3)=="id=");
	st.erase(0, 3);
	id=atoi(st.substr(0, st.find(' ')).c_str());
	st.erase(0, st.find(' ')+1);

	assert(st.substr(0, 5)=="zone=");
	st.erase(0, 5);
	zone=st.substr(0, st.find(' '));
	st.erase(0, st.find(' ')+1);

	assert(st.substr(0, 8)=="zonePos=");
	st.erase(0, 8);
	zonePos=atoi(st.substr(0, st.find(' ')).c_str());
	st.erase(0, st.find(' ')+1);

	assert(st.substr(0, 7)=="cardId=");
	st.erase(0, 7);
	cardId=st.substr(0, st.find(' '));
	st.erase(0, st.find(' ')+1);

	assert(st.substr(0, 7)=="player=");
	st.erase(0, 7);
	player=atoi(st.substr(0, st.find(']')).c_str());
}

soption::soption()
{
	type=error=errorParam="";
	mainEntity=sEntities();
}

sCommand::sCommand()
{
	Player=ChoiceType="";
	id=EntitiesCount=TaskList=CountMin=CountMax=-1;
	Entities.clear();
	option.clear();
}

void sCommand::clear()
{
	Player=ChoiceType="";
	id=EntitiesCount=TaskList=CountMin=CountMax=-1;
	Entities.clear();
	option.clear();
}

bool sCommand::empty()
{
	return (Player=="" && ChoiceType=="" &&
		id==-1 && EntitiesCount==-1 && TaskList==-1 && 
		CountMin==-1 && CountMax==-1);
}

void TableModify(sCommand command)
{
}