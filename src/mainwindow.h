#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtCore>
#include <QtSql>

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void lista();
private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void eliminaAlunni();
    void esportaCSV();
    void esportaExcel();
    void insertAlunni();
    void informazioni();
    void editLineFinishedGruppo();

private:
    Ui::MainWindow *ui;
    QSqlQueryModel *model;
};
#endif // MAINWINDOW_H
