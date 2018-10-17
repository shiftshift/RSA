#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGui.h"

class QtGui : public QMainWindow
{
	Q_OBJECT

public:
	QtGui(QWidget *parent = Q_NULLPTR);
	int QtGui::to_size_t(QString str, size_t &temp_num, int flag);
	QString QtGui::to_qstring(size_t num);

private slots:		   //信号槽
	void OnClickCalc();//加密解密按钮
	void OnClickStep();//模重复流程按钮
	void OnClickClean();//清空输入框
	void OnClickClear();//清空表中内容

private:
	Ui::QtGuiClass ui;
	Ui::QtGuiClass step;
	Ui::QtGuiClass clean;
	Ui::QtGuiClass clear;
};
