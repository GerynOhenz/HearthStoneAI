#include <stdio.h>
#include <string>
#include <vector>

struct sEntities
{
	std::string entityName, cardType, zone, cardId;
	int id, zonePos, player;

	sEntities();

	sEntities(std::string &st);
};

struct soption
{
	std::string type, error, errorParam;
	sEntities mainEntity;

	soption();
};

struct sCommand
{
	std::string Player, ChoiceType;
	int id, EntitiesCount, TaskList, CountMin, CountMax;
	std::vector<sEntities> Entities;
	std::vector<soption> option;

	sCommand();

	void clear();

	bool empty();
};

void TableModify(sCommand command);