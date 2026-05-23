#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QShortcut>
#include <QMessageBox>
#include <QActionGroup>
#include "core/evaluator.h"
#include "dsettings.h"
#include "skin.h"
#include "history.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void evaluate();
    void acButtonClicked();
    void solver();
    void show_pinpad();
    void hide_pinpad();
    void light_theme();
    void dark_theme();
    void system_theme();

    void lineEditTextChanged(const QString &text);
    void showAboutDialog();

private:
    Ui::MainWindow  *ui;
    Evaluator       * m_evaluator;
    void loadHistory();
    void initTheme();
    void initMenu();
    DSettings config;
    History history;
    Skin skin;
    QMessageBox dialogInfos;
    QActionGroup *themeGroup;


protected:
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent *);
};

#endif // MAINWINDOW_H
