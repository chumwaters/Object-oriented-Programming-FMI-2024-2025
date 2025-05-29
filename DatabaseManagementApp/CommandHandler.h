#pragma once

#include "Database.h"

class CommandHandler {
private:
	Database& db;

public:
	/// @brief CommandHandler constructor from Database reference.
	/// @param db Database reference to construct CommandHandler object from.
	CommandHandler(Database& db);


};
