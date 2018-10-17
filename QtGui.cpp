#include "QtGui.h"
#include "ui_QtGui.h"
#include<QMessageBox>
#include <string.h>
#include<RSA.h>
#include <time.h>

QtGui::QtGui(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.calc, SIGNAL(clicked()), this, SLOT(OnClickCalc()));
	connect(ui.step, SIGNAL(clicked()), this, SLOT(OnClickStep()));
	connect(ui.clean, SIGNAL(clicked()), this, SLOT(OnClickClean()));
	connect(ui.clear, SIGNAL(clicked()), this, SLOT(OnClickClear()));
}

int QtGui::to_size_t(QString str, size_t &temp_num, int flag)//flag用于标记p和q的输入
{
	/*转换成字符串cstr*/
	char*  cstr;
	QByteArray qba = str.toLatin1();
	cstr = qba.data();

	/*检测是否为空串*/
	if (cstr[0] == NULL)
	{
		if (flag)//如果是p和q输入框可能需要产生随机数
		{
			switch (QMessageBox::warning(NULL, "warning", "create q or p randomly?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes))
			{
			case QMessageBox::Yes:
				srand((unsigned)time(NULL));
				while ((temp_num = rand()) % 2 == 0)
					;
				return 0;//temp_num获取到随机数了，但是这里仍然返回0
			case QMessageBox::No:
				temp_num = 0;
				return 0;
			}
		}
		else
			QMessageBox::information(NULL, tr("error"), tr("you should input something"));
		return 0;
	}
	/*检测是否全是数字*/
	if (!(strspn(cstr, "0123456789") == strlen(cstr)))
	{
		QMessageBox::information(NULL, tr("error"), tr("you should input number"));
	}
	/*检测是否是小数*/
	if ((strchr(cstr, '.')))
	{
		QMessageBox::information(NULL, tr("error"), tr("you should input integer"));
		return 0;
	}

	size_t num = atoi(cstr);
	temp_num = num;

	return 1;
}

QString QtGui::to_qstring(size_t num)
{
	char cstr[10];
	itoa(num, cstr, 10);
	QString str = QString(QLatin1String(cstr));
	return str;
}

void QtGui::OnClickCalc()
{
	QString str1 = ui.lineEdit_1->text();
	QString str2 = ui.lineEdit_2->text();
	QString str3 = ui.lineEdit_3->text();
	QString str4 = ui.lineEdit_4->text();

	size_t temp_num = 0;
	size_t num1,num2,num3,num4;
	RSA rsa;

	if (to_size_t(str1, temp_num, 1) || temp_num)//返回值为0才会检查temp_num是否有值
		num1 = temp_num;
	else
		num1 = 0;
	ui.lineEdit_1->setText(QString::number(num1));
	if (to_size_t(str2, temp_num, 1) || temp_num)
		num2 = temp_num;
	else
		num2 = 0;
	ui.lineEdit_2->setText(QString::number(num2));

	num3 = to_size_t(str3, temp_num,0) ? temp_num : NULL;
	num4 = to_size_t(str4, temp_num,0) ? temp_num : NULL;
	
	if (!num1 || !num2 || !num3 || !num4)
		return;
	
	if(!rsa.clac(num1, num2, num3, num4))
	{
		QMessageBox::information(NULL, tr("error"), tr("invail number"));
		return;
	}
	/*往框中填值*/
	ui.lineEdit_5->setText(QString::number(rsa.get_n()));
	ui.lineEdit_6->setText(QString::number(rsa.get_phi_n()));
	ui.lineEdit_7->setText(QString::number(rsa.get_d()));
	ui.lineEdit_8->setText(QString::number(rsa.get_c()));
	ui.lineEdit_9->setText(QString::number(rsa.get_m()));
}

void QtGui::OnClickStep()
{
	QString str3 = ui.lineEdit_3->text();
	QString str6 = ui.lineEdit_6->text();

	size_t temp_num = 0;
	size_t num1 = to_size_t(str3, temp_num,0) ? temp_num : NULL;
	size_t num2 = to_size_t(str6, temp_num,0) ? temp_num : NULL;

	RSA rsa;
	size_t a[8] = { 0 };
	size_t b[8] = { 0 };
	rsa.step(num1,num2,a,b);

	int i, j,row, tmp;
	int inv_a, inv_b;
	i = j = row= 0;
	
	while (a[i] % b[j] != 0)
	{
		row = ui.tableWidget->rowCount();
		ui.tableWidget->setRowCount(row+1);
		ui.tableWidget->setItem(row, 0, new QTableWidgetItem(to_qstring(b[j])));
		ui.tableWidget->setItem(row, 1, new QTableWidgetItem(to_qstring(a[i] % b[j])));
		ui.tableWidget->setItem(row, 2, new QTableWidgetItem(to_qstring(rsa.gcd(a[i], b[j]))));

		i++; j++;
	}
		
	ui.tableWidget->setItem(row, 3, new QTableWidgetItem("0"));
	ui.tableWidget->setItem(row, 4, new QTableWidgetItem("1"));

	i--; j--;
	inv_a = 1;
	inv_b = -(a[i] / b[j]);
	for (; i > 0, j > 0; i--, j--)//回代过程
	{
		row = ui.tableWidget->rowCount();
		ui.tableWidget->setRowCount(row + 1);

		ui.tableWidget->setItem(row, 0, new QTableWidgetItem(to_qstring(a[i])));
		ui.tableWidget->setItem(row, 1, new QTableWidgetItem(to_qstring(b[j])));
		ui.tableWidget->setItem(row, 2, new QTableWidgetItem(to_qstring(rsa.gcd(a[i],b[j]))));
		ui.tableWidget->setItem(row, 3, new QTableWidgetItem(to_qstring(inv_a)));
		ui.tableWidget->setItem(row, 4, new QTableWidgetItem(to_qstring(inv_b)));

		
		tmp = inv_a;
		inv_a = inv_b;
		inv_b = tmp - a[i - 1] / b[j - 1] * inv_b;
	}
}

void QtGui::OnClickClean()
{
	ui.lineEdit_1->clear();
	ui.lineEdit_2->clear();
	ui.lineEdit_3->clear();
	ui.lineEdit_4->clear();
	ui.lineEdit_5->clear();
	ui.lineEdit_6->clear();
	ui.lineEdit_7->clear();
	ui.lineEdit_8->clear();
	ui.lineEdit_9->clear();
}

void QtGui::OnClickClear()
{
	ui.tableWidget->setRowCount(0);
}


