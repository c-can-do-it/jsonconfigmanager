#JsonConfigManager 是一个很让你很轻松读写json 配置信息的类，用QT c++编写

##您只要在项目中引入JsonConfigManager.h JsonCofigManager.cpp 就可以轻松使用这个类


###写入例子演示

```c++

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


```


###读入例子演示

```c++

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

		qDebug() << "read done";



	});


```

##B站此项目的讲解说明
https://www.bilibili.com/video/BV1Tt4y1P7dd/?vd_source=0df66f3126bf7396f3931c959b24c099

https://www.bilibili.com/video/BV1cG4y1x7JE/?vd_source=0df66f3126bf7396f3931c959b24c099