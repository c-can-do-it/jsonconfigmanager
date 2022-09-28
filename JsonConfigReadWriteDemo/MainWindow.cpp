#include "MainWindow.h"
#include "JsonConfigManager.h"
#include <qdebug.h>

QString ConfigFilePath()
{
	return QApplication::applicationDirPath() + "/appconfig/config.json";
}






#pragma region 子类继承演示
class ConfigManager :public JsonConfigManager
{

public:
	ConfigManager(QString jsonfilepath) :JsonConfigManager(jsonfilepath)
	{

	}

public:
	void SetUserName(QString username)
	{
		SetGroupKeyValue("bilibili", "username", username);
	}
	QString GetUserName()
	{
		return	GetGroupKeyValue("bilibili", "username");
	}


};
#pragma endregion




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowClass())
{
    ui->setupUi(this);

	connect(ui->pushButton_2, &QPushButton::clicked, this, [&]() {
	
		qDebug() << "click";

		JsonConfigManager config(ConfigFilePath());

		QString username = ui->lineEdit->text();
		QString password = ui->lineEdit_2->text();

		QString chromedriver = ui->lineEdit_3->text();
		QString chromeuserdir = ui->lineEdit_4->text();

		//config.SetGroupKeyValue("bilibibli", "username", QString::fromLocal8Bit("C语言也能干大事"));
		//config.SetGroupKeyValue("bilibibli", "password", QString::fromLocal8Bit("123123"));

		config.SetGroupKeyValue("bilibibli", "username", username);
		config.SetGroupKeyValue("bilibibli", "password", password);
		config.SetGroupKeyValue("chrome", "driver", chromedriver);
		config.SetGroupKeyValue("chrome", "userdir", chromeuserdir);

		config.Save();

		qDebug() << "save done";

	
	
	});


	connect(ui->pushButton, &QPushButton::clicked, this, [&]() {

		qDebug() << "click";

		JsonConfigManager config(ConfigFilePath());

	    QString username=config.GetGroupKeyValue("bilibibli", "username");
		QString password=config.GetGroupKeyValue("bilibibli", "password");
		QString chromedriver = config.GetGroupKeyValue("chrome", "driver");
		QString chromeuserdir = config.GetGroupKeyValue("chrome", "userdir");
		ui->lineEdit->setText(username);
		ui->lineEdit_2->setText(password);
		ui->lineEdit_3->setText(chromedriver);
		ui->lineEdit_4->setText(chromeuserdir);

		qDebug() << "save done";



	});




}

MainWindow::~MainWindow()
{
    delete ui;
}
