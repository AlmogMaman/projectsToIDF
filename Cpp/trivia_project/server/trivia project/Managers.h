#pragma once
#include <iostream>
#include "IDatabase.h"
#include <vector>
using std::vector;
using std::string;


class LoggedUsers
{
public:
	string getUserName()
	{
		return m_username;
	}
private:
	string m_username;
};


class Question
{
public: 
	string getQuestion();
	string getPossibleAnswers();
	string getCorrectAnswer();
private:
	string m_question;
	vector<string> m_possibleAnswers;
};


class LoginManager
{
public:
	void signUp(string username, string password, string email);
	void login(string username, string password);
	void logout();


private:
	IDatabase m_database;
	vector<LoggedUsers> m_loggedUsers;
};


class room
{
public:
	vector<string> usersInRoom;
	string roomName;
	int numQu;
	int numAns;
	int maxPlayers;
	int timePerQu;

	//bool operator==(const room& r/*l, const room&r*/) const {
	//	return this->roomName == r.roomName && this->usersInRoom == r.usersInRoom;
	//}
};


