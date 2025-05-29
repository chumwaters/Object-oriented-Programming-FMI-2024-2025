#pragma once

#include "Database.h"

class CommandHandler {
private:
	Database& db;

public:
	CommandHandler(Database& db);
};
