#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <list>
#include <string>
#include <fstream>
#include "sqlite3.h"




class DataBase
{
public:
	DataBase() { open(); }
	~DataBase() { sqlite3_close(DB); }
	bool open();
	bool freeName(std::string name);
	bool checkLogin(std::string name, std::string pass);
	bool regist(std::string name, std::string pass);
	void updateStatistic(std::string name, std::list<float> inf);
	std::list<float> getStatistic(std::string name);
	std::list<std::string> getTopPlayers(std::string name);
	int getUserId(std::string name);


	void cleareDB();

private:
	sqlite3* DB;
};


