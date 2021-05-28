#pragma once
#include <iostream>
#include <map>
#include <string>
#include <list>
using std::list;
using std::string;
using std::map;


class LoggedUsers;
class Question;


class IDatabase
{
public:
	map<LoggedUsers, int> getHighscores();
	bool doesUserExist(string);
	list<Question> getQuestions;
};