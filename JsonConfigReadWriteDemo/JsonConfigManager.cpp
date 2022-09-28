#include "JsonConfigManager.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <qfile.h>
#include <qfileinfo.h>
#include <qtextcodec.h>
#include <qdebug.h>
JsonConfigManager::JsonConfigManager(QString jsonfilepath) :mJsonFilePath(jsonfilepath)
{
	ReadJsonFile();
}

JsonConfigManager::~JsonConfigManager()
{

}

void JsonConfigManager::ReadJsonFile()
{
	QFileInfo info(mJsonFilePath);

	if (info.exists())
	{

		QString fileNamePath = mJsonFilePath;
		QFile file(fileNamePath);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			qDebug() << "Can't open the file!";
			return;
		}

		QByteArray bytes = file.readAll();

		mJsonTxt = QTextCodec::codecForName("GBK")->toUnicode(bytes);

		file.close();

	}
	else
	{

		QJsonDocument document;

		QJsonObject rootobj;

		document.setObject(rootobj);

		mJsonTxt = document.toJson();

		Save();

	}

}





void JsonConfigManager::Save()
{

	QString fileNamePath = mJsonFilePath;
	QFile file(fileNamePath);
	if (!file.open(QIODevice::WriteOnly)) {
		qDebug() << "Can't open the file!" << endl;
		return;
	}

	QTextStream filestream(&file);//QTextStream 与file关联

	filestream.setCodec("GBK");



	filestream << mJsonTxt;

	file.flush();

	file.close();


}


void JsonConfigManager::SetGroupKeyValue(QString groupname, QString keyname, QString value)
{

	QJsonParseError jsonError;
	// 转化为 JSON 文档
	QJsonDocument document = QJsonDocument::fromJson(mJsonTxt.toStdString().c_str(), &jsonError);
	// 解析未发生错误
	if (!document.isNull() && (jsonError.error == QJsonParseError::NoError))
	{
		if (document.isObject())
		{
			// JSON 文档为对象
			QJsonObject rootobject = document.object();  // 转化为对象


			if (!rootobject.contains(groupname))
			{
				QJsonObject obj;

				rootobject.insert(groupname, obj);
			}

			auto groupobj = rootobject[groupname].toObject();

			groupobj[keyname] = value;


			//需要重新把对象设置回去才能修改生效

			rootobject[groupname] = groupobj;

			document.setObject(rootobject);

			mJsonTxt = document.toJson();

			qDebug() << mJsonTxt;


		}


	}



}

QString JsonConfigManager::GetGroupKeyValue(QString groupname, QString keyname)
{

	QString strRet;
	QJsonParseError jsonError;
	// 转化为 JSON 文档
	QJsonDocument document = QJsonDocument::fromJson(mJsonTxt.toStdString().c_str(), &jsonError);
	// 解析未发生错误
	if (!document.isNull() && (jsonError.error == QJsonParseError::NoError))
	{
		if (document.isObject())
		{
			// JSON 文档为对象
			QJsonObject rootobject = document.object();  // 转化为对象

			if (rootobject.contains(groupname))
			{
				auto groupobj = rootobject[groupname].toObject();

				if (groupobj.contains(keyname))
				{
					strRet = groupobj[keyname].toString();
				}

			}



		}


	}

	return strRet;

}

