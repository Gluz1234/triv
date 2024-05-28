#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
class SqliteDatabase : public IDatabase
{
public:
	bool open();
	bool doesUserExist(std::string name) override;
	bool doesPasswordMatch(std::string name, std::string password)override;
	void addNewUser(std::string name, std::string password, std::string mail)override;

	void DoSQL(std::string statement);
	void DoSqlCallback(std::string statement, int(*callback)(void*, int, char**, char**), void* data);
	std::list<Question> getQuestions(int num)override;
	float getAverageAnswerTime(std::string name)override;
	int getNumOfCorrectAnswers(std::string name)override;
	int getNumOfTotalAnswers(std::string name)override;
	int getNumOfPlayerGames(std::string name)override;
	std::vector<std::string> getHighScores()override;
private:

	static int isExistsCallback(void* data, int argc, char** argv, char** azColName);
	void ExecuteSqlCallback(std::string statement, int(*callback)(void*, int, char**, char**), void* data);
	static int fillQuestionsCallback(void* data, int argc, char** argv, char** azColName);
	static int getFloatCallback(void* data, int argc, char** argv, char** azColName);
	static int getIntCallback(void* data, int argc, char** argv, char** azColName);
	static int fillScoreCallback(void* data, int argc, char** argv, char** azColName);
	sqlite3* _db;
	std::string _dbFileName = "UserDB.sqlite";
};