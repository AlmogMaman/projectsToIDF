#include "SqlManager.h"

static int callback(void *data, int argc, char **argv, char **azColName)
{
	return 0;
}
/*
	func checks if the user exists in the db query(of exist users) output
*/
static int ifUserExsist(void *data, int argc, char **argv, char **azColName)
{
	std::list<int> *found = (std::list<int>*)data;
	found->insert(found->begin(), atoi(argv[0]));
	return 0;
}
/*
	function analyzes the output of the statistic query 
*/
static int getStatist(void *data, int argc, char **argv, char **azColName)
{
	std::list<float> *stat = (std::list<float>*)data;
	for (int i = 0; i < 5; i++)
	{
		stat->insert(stat->end(), atoi(argv[i + 1]));
	}
	return 0;
}
/*
	the func returns the names of matching results(after the sql query)
*/
static int getName(void *data, int argc, char **argv, char **azColName)
{
	std::list<std::string> *stat = (std::list<std::string>*)data;
	for (int i = 0; i < argc; i++)
	{
		stat->insert(stat->end(), argv[i]);
	}
	return 0;
}



bool DataBase::open()
{
	int exit = 0;
	exit = sqlite3_open("Trivia.VC.db", &DB);

	if (exit)
	{
		std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
		return false;
	}

	char *zErrMsg = 0;
	const char* sql[2] = { "CREATE TABLE if not exists user (id INTEGER PRIMARY KEY, name TEXT, pass TEXT);",
	"CREATE TABLE if not exists user_statistics(name TEXT PRIMARY KEY, games_played INTEGER, games_win INTEGER, right_ans INTEGER, wrong_ans INTEGER, avr_ans REAL);" };

	for (int i = 0; i < 2; i++) {
		int rc = sqlite3_exec(DB, sql[i], callback, 0, &zErrMsg);
	}
	return true;
}

bool DataBase::freeName(std::string name)
{
	char *zErrMsg = 0;

	std::string sql = "SELECT id FROM user where name='" + name + "';";

	std::list<int> found;
	int rc = sqlite3_exec(DB, sql.c_str(), ifUserExsist, &found, &zErrMsg);

	if (found.size())
	{
		return false;
	}
	return true;
}

bool DataBase::checkLogin(std::string name, std::string pass)
{
	char *zErrMsg = 0;

	std::string sql = "SELECT id FROM user where name='" + name + "' and pass='" + pass + "';";

	std::list<int> found;
	int rc = sqlite3_exec(DB, sql.c_str(), ifUserExsist, &found, &zErrMsg);

	if (found.size())
	{
		return true;
	}
	return false;

}

bool DataBase::regist(std::string name, std::string pass)
{
	char *zErrMsg = 0;
	if (freeName(name))
	{
		std::string sql = "INSERT INTO user(name,pass) VALUES('" + name + "','" + pass + "');";
		int rc = sqlite3_exec(DB, sql.c_str(), callback, 0, &zErrMsg);
		sql = "INSERT INTO user_statistics VALUES('" + name + "',0,0,0,0,0);";
		rc = sqlite3_exec(DB, sql.c_str(), callback, 0, &zErrMsg);
		return true;
	}
	return false;
}


std::list<float> DataBase::getStatistic(std::string name)
{
	char *zErrMsg = 0;
	std::string sql = "select * from user_statistics where name='" + name + "';";
	std::list<float> found;
	int rc = sqlite3_exec(DB, sql.c_str(), getStatist, &found, &zErrMsg);
	return found;
}




void DataBase::updateStatistic(std::string name, std::list<float> inf)
{
	std::list<float> found = getStatistic(name);
	float stat[5];
	char *zErrMsg = 0;
	for (int i = 0; i < 4; i++)
	{
		stat[i] = found.front() + inf.front();
		found.pop_front();
		inf.pop_front();
	}
	stat[4] = (found.front() + inf.front())/2;
	std::string sql = "update user_statistics set games_played = "+ std::to_string((int)stat[0])+", games_win = " + std::to_string((int)stat[1]) + ", right_ans = " + std::to_string((int)stat[2]) + ", wrong_ans = " + std::to_string((int)stat[3]) + ", avr_ans = " + std::to_string(stat[4]) +" where name= '" + name + "';";
	int rc = sqlite3_exec(DB, sql.c_str(), callback, 0, &zErrMsg);

	sql = "select top 3 * from user_statistics;";
	rc = sqlite3_exec(DB, sql.c_str(), callback, 0, &zErrMsg);

}

int DataBase::getUserId(std::string name)
{
	char *zErrMsg = 0;

	std::string sql = "SELECT id FROM user where name='" + name + "';";

	std::list<int> found;
	int rc = sqlite3_exec(DB, sql.c_str(), ifUserExsist, &found, &zErrMsg);
	return found.front();
}




std::list<std::string> DataBase::getTopPlayers(std::string name)
{
	char *zErrMsg = 0;
	std::string sql = "SELECT name FROM user_statistics ORDER BY games_win;";
	std::list<std::string> players;
	int rc = sqlite3_exec(DB, sql.c_str(), getName, &players, &zErrMsg);
	std::list<std::string> top;
	int i;
	for (i = 0; players.size(); i++)
	{
		if (i < 3)
			top.insert(top.end(), players.back());
		if (players.back() == name)
			top.insert(top.begin(), std::to_string(i+1));
		players.pop_back();
	}
	while (i < 3)
	{
		top.insert(top.end(), "");
		i++;
	}
	return top;
}



void DataBase::cleareDB()
{
	sqlite3_close(DB);
	std::ofstream newFile("Trivia.VC.db", std::ios_base::binary);
	newFile.close();
	open();
}
