#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <StringMatch.h>
#include "resultwindow.h"
#include "dialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ResultWindow* result_window{NULL};
    Dialog* the_dialog{NULL};
    ~MainWindow();
    void m_LinkSignalAndSlot();
signals:
    void m_InputFileLoaded(QString file);
    void m_LoadNaive(QString result);
    void m_LoadRabinKarp(QString result);
    void m_LoadDFA(QString result);
    void m_LoadKMP(QString result);
    void m_LoadBoyerMoore(QString result);
    void m_ShowResult();
    void m_WrongAnswer();
public slots:
    void m_LoadFile();
    void m_InitFromFile(QString file);
    void m_InitFromInput();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
