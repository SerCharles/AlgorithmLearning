#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "StringMatch.h"
#include "resultwindow.h"
#include "ui_resultwindow.h"
#include "dialog.h"
#include "ui_dialog.h"

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <string.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    result_window = new ResultWindow();
    the_dialog = new Dialog();
    m_LinkSignalAndSlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::m_LinkSignalAndSlot()
{
    connect(ui->ButtonFile,SIGNAL(clicked(bool)),this,SLOT(m_LoadFile()));
    connect(ui->ButtonEdit,SIGNAL(clicked(bool)),this,SLOT(m_InitFromInput()));
    connect(this,SIGNAL(m_InputFileLoaded(QString)),this,SLOT(m_InitFromFile(QString)));
    connect(this,SIGNAL(m_ShowResult()),result_window,SLOT(show()));
    connect(this,SIGNAL(m_ShowResult()),this,SLOT());
    connect(result_window->ui->ReturnButton,SIGNAL(clicked(bool)),result_window,SLOT(close()));
    connect(result_window->ui->ReturnButton,SIGNAL(clicked(bool)),this,SLOT(show()));
    connect(this,SIGNAL(m_LoadNaive(QString)),result_window->ui->TextNaive,SLOT(setText(QString)));
    connect(this,SIGNAL(m_LoadRabinKarp(QString)),result_window->ui->TextRabinKarp,SLOT(setText(QString)));
    connect(this,SIGNAL(m_LoadDFA(QString)),result_window->ui->TextDFA,SLOT(setText(QString)));
    connect(this,SIGNAL(m_LoadKMP(QString)),result_window->ui->TextKMP,SLOT(setText(QString)));
    connect(this,SIGNAL(m_LoadBoyerMoore(QString)),result_window->ui->TextBoyerMoore,SLOT(setText(QString)));
    connect(this,SIGNAL(m_WrongAnswer()),the_dialog,SLOT(show()));
    connect(this,SIGNAL(m_WrongAnswer()),result_window,SLOT(close()));
    connect(this,SIGNAL(m_WrongAnswer()),this,SLOT(close()));
    connect(the_dialog->ui->Button,SIGNAL(clicked(bool)),this,SLOT(show()));
    connect(the_dialog->ui->Button,SIGNAL(clicked(bool)),the_dialog,SLOT(close()));

}

void MainWindow::m_LoadFile()
{
    QString temp_file = QFileDialog::getOpenFileName(this,tr("Load Input Files"),"",tr("Input files (*.txt)"));
    if(temp_file == "")
    {
        return;
    }
    emit m_InputFileLoaded(temp_file);
}

void MainWindow::m_InitFromInput()
{
    QString the_string = ui->StringEdit->toPlainText();
    QString the_model = ui->ModelEdit->toPlainText();
    std::string t_string = the_string.toStdString();
    std::string t_model = the_model.toStdString();

    ui->StringEdit->clear();
    ui->ModelEdit->clear();
    int size_m = 0,size_n = 0;
    size_n = the_string.size();
    size_m = the_model.size();

    if(size_n <= 0 ||size_m <= 0 || size_n > SIZE_N || size_m > SIZE_M)
    {
        emit m_WrongAnswer();
        return;
    }
    for(int i = 1; i <= size_n; i ++)
    {
        char c = t_string[i-1];
        if(g_Int(c) == -1)
        {
            emit m_WrongAnswer();
            return;
        }
        g_CharList[i] = t_string[i-1];
    }
    for(int i = 1; i <= size_m; i ++)
    {
        char c = t_model[i-1];

        if(g_Int(c) == -1)
        {
            emit m_WrongAnswer();
            return;
        }
        g_Model[i] = t_model[i-1];
    }


    g_MatchNaive(size_n,size_m);
    g_MatchRabinKarp(size_n,size_m);
    g_MatchDFA(size_n,size_m);
    g_MatchKMP(size_n,size_m);
    g_MatchBoyerMoore(size_n,size_m);
    QString result_naive;
    QString result_rabin_karp;
    QString result_dfa;
    QString result_kmp;
    QString result_boyer_moore;
    if(result_place_naive.size() == 0)
    {
        result_naive="No Matching Place";
    }
    else
    {
        for(int i = 0; i < result_place_naive.size(); i ++)
        {
            result_naive.append(QString::number(result_place_naive[i],10));
            result_naive.append(" ");
        }
    }
    if(result_place_rabin_karp.size() == 0)
    {
        result_rabin_karp="No Matching Place";
    }
    else
    {
        for(int i = 0; i < result_place_rabin_karp.size(); i ++)
        {
            result_rabin_karp.append(QString::number(result_place_rabin_karp[i],10));
            result_rabin_karp.append(" ");
        }
    }
    if(result_place_dfa.size() == 0)
    {
        result_dfa="No Matching Place";
    }
    else
    {
        for(int i = 0; i < result_place_dfa.size(); i ++)
        {
            result_dfa.append(QString::number(result_place_dfa[i],10));
            result_dfa.append(" ");
        }
    }
    if(result_place_kmp.size() == 0)
    {
        result_kmp="No Matching Place";
    }
    else
    {
        for(int i = 0; i < result_place_kmp.size(); i ++)
        {
            result_kmp.append(QString::number(result_place_kmp[i],10));
            result_kmp.append(" ");
        }
    }
    if(result_place_boyer_moore.size() == 0)
    {
        result_boyer_moore="No Matching Place";
    }
    else
    {
        for(int i = 0; i < result_place_boyer_moore.size(); i ++)
        {
            result_boyer_moore.append(QString::number(result_place_boyer_moore[i],10));
            result_boyer_moore.append(" ");
        }
    }
    emit m_ShowResult();
    emit m_LoadNaive(result_naive);
    emit m_LoadRabinKarp(result_rabin_karp);
    emit m_LoadDFA(result_dfa);
    emit m_LoadKMP(result_kmp);
    emit m_LoadBoyerMoore(result_boyer_moore);
}

void MainWindow::m_InitFromFile(QString file)
{
    QFile input_file(file);
    input_file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream input_stream(&input_file);
    int size_m = 0,size_n = 0;
    input_stream >> size_n>>size_m;
    if(size_n <= 0 ||size_m <= 0 || size_n > SIZE_N || size_m > SIZE_M)
    {
        //emit m_WrongAnswer();
        return;
    }
    char c = ' ';
    while(c == ' '|| c == '\n')
    {
        input_stream>>c;
    }
    g_CharList[1] = c;
    for(int i = 2; i <= size_n; i ++)
    {
        input_stream>>g_CharList[i];
        if(g_Int(g_CharList[i]) == -1)
        {
            emit m_WrongAnswer();
            return;
        }
    }
    c = ' ';
    while(c == ' '|| c == '\n')
    {
        input_stream>>c;
    }
    g_Model[1] = c;
    for(int i = 2; i <= size_m; i ++)
    {
           input_stream>>g_Model[i];
           if(g_Int(g_Model[i]) == -1)
           {
               emit m_WrongAnswer();
               return;
           }
    }
    g_MatchNaive(size_n,size_m);
    g_MatchRabinKarp(size_n,size_m);
    g_MatchDFA(size_n,size_m);
    g_MatchKMP(size_n,size_m);
    g_MatchBoyerMoore(size_n,size_m);
    QString result_naive;
    QString result_rabin_karp;
    QString result_dfa;
    QString result_kmp;
    QString result_boyer_moore;
    if(result_place_naive.size() == 0)
    {
        result_naive="No Matching Place";
    }
    else
    {
        for(int i = 0; i < result_place_naive.size(); i ++)
        {
            result_naive.append(QString::number(result_place_naive[i],10));
            result_naive.append(" ");
        }
    }
    if(result_place_rabin_karp.size() == 0)
    {
        result_rabin_karp="No Matching Place";
    }
    else
    {
        for(int i = 0; i < result_place_rabin_karp.size(); i ++)
        {
            result_rabin_karp.append(QString::number(result_place_rabin_karp[i],10));
            result_rabin_karp.append(" ");
        }
    }
    if(result_place_dfa.size() == 0)
    {
        result_dfa="No Matching Place";
    }
    else
    {
        for(int i = 0; i < result_place_dfa.size(); i ++)
        {
            result_dfa.append(QString::number(result_place_dfa[i],10));
            result_dfa.append(" ");
        }
    }
    if(result_place_kmp.size() == 0)
    {
        result_kmp="No Matching Place";
    }
    else
    {
        for(int i = 0; i < result_place_kmp.size(); i ++)
        {
            result_kmp.append(QString::number(result_place_kmp[i],10));
            result_kmp.append(" ");
        }
    }
    if(result_place_boyer_moore.size() == 0)
    {
        result_boyer_moore="No Matching Place";
    }
    else
    {
        for(int i = 0; i < result_place_boyer_moore.size(); i ++)
        {
            result_boyer_moore.append(QString::number(result_place_boyer_moore[i],10));
            result_boyer_moore.append(" ");
        }
    }
    emit m_ShowResult();
    emit m_LoadNaive(result_naive);
    emit m_LoadRabinKarp(result_rabin_karp);
    emit m_LoadDFA(result_dfa);
    emit m_LoadKMP(result_kmp);
    emit m_LoadBoyerMoore(result_boyer_moore);

}
