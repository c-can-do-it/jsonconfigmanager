#pragma once
#include <qstring.h>

class JsonConfigManager
{
private:
	QString mJsonFilePath;
	QString mJsonTxt;
private:
	void ReadJsonFile();
public:
	JsonConfigManager(QString jsonfilepath);
	~JsonConfigManager();
	void SetGroupKeyValue(QString groupname, QString keyname, QString value);
	QString GetGroupKeyValue(QString groupname, QString keyname);
	void Save();

};
