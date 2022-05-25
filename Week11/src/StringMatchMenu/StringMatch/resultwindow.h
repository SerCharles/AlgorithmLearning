#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H

#include <QMainWindow>

namespace Ui {
class ResultWindow;
}

class MainWindow;

class ResultWindow : public QMainWindow
{
    Q_OBJECT
friend class MainWindow;
public:
    explicit ResultWindow(QWidget *parent = 0);
    ~ResultWindow();
signals:
    void m_ShowMain();
private:
    Ui::ResultWindow *ui;
};

#endif // RESULTWINDOW_H
