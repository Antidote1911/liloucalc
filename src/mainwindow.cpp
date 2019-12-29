#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include <QRegularExpression>
#include <QShortcut>
#include <QToolTip>
#include <QStyleFactory>
#include <QStyle>
#include <QDebug>
#include <QLineEdit>
#include "solve.h"
#include "utils.h"
#include "core/numberformatter.h"
#include "AboutDialog.h"
#include "history.h"


typedef Quantity::Format Format;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //connect(ui->num_0,  &QPushButton::clicked, this, &MainWindow::numberButtonClicked);
    connect(ui->num_0, &QPushButton::clicked, this, [=]{ ui->expression->insert("0"); });
    connect(ui->num_1, &QPushButton::clicked, this, [=]{ ui->expression->insert("1"); });
    connect(ui->num_2, &QPushButton::clicked, this, [=]{ ui->expression->insert("2"); });
    connect(ui->num_3, &QPushButton::clicked, this, [=]{ ui->expression->insert("3"); });
    connect(ui->num_4, &QPushButton::clicked, this, [=]{ ui->expression->insert("4"); });
    connect(ui->num_5, &QPushButton::clicked, this, [=]{ ui->expression->insert("5"); });
    connect(ui->num_6, &QPushButton::clicked, this, [=]{ ui->expression->insert("6"); });
    connect(ui->num_7, &QPushButton::clicked, this, [=]{ ui->expression->insert("7"); });
    connect(ui->num_8, &QPushButton::clicked, this, [=]{ ui->expression->insert("8"); });
    connect(ui->num_9, &QPushButton::clicked, this, [=]{ ui->expression->insert("9"); });
    connect(ui->num_pi,&QPushButton::clicked, this, [=]{ ui->expression->insert("π"); });

    connect(ui->expr_add,  &QPushButton::clicked, this, [=]{ ui->expression->insert("+"); });
    connect(ui->expr_sub,  &QPushButton::clicked, this, [=]{ ui->expression->insert("-"); });
    connect(ui->expr_mul,  &QPushButton::clicked, this, [=]{ ui->expression->insert("x"); });
    connect(ui->expr_div,  &QPushButton::clicked, this, [=]{ ui->expression->insert("÷"); });

    connect(ui->paren_begin,  &QPushButton::clicked, this, [=]{ ui->expression->insert("("); });
    connect(ui->paren_end,    &QPushButton::clicked, this, [=]{ ui->expression->insert(")"); });

    connect(ui->func_sin,  &QPushButton::clicked, this, [=]{ ui->expression->insert("sin("); });
    connect(ui->func_cos,  &QPushButton::clicked, this, [=]{ ui->expression->insert("cos("); });
    connect(ui->func_tan,  &QPushButton::clicked, this, [=]{ ui->expression->insert("tan("); });
    connect(ui->func_sinh,  &QPushButton::clicked, this, [=]{ ui->expression->insert("sinh("); });
    connect(ui->func_cosh,  &QPushButton::clicked, this, [=]{ ui->expression->insert("cosh("); });
    connect(ui->func_tanh,  &QPushButton::clicked, this, [=]{ ui->expression->insert("tanh("); });

    connect(ui->pow_2,  &QPushButton::clicked, this, [=]{ ui->expression->insert("^2"); });
    connect(ui->pow_3,  &QPushButton::clicked, this, [=]{ ui->expression->insert("^3"); });
    connect(ui->pow_n,  &QPushButton::clicked, this, [=]{ ui->expression->insert("^"); });
    connect(ui->pow_half,  &QPushButton::clicked, this, [=]{ ui->expression->insert("sqrt("); });
    connect(ui->pow_minus_one,  &QPushButton::clicked, this, [=]{ ui->expression->insert("^-1"); });

    connect(ui->backspace,  &QPushButton::clicked, this, [=]{ ui->expression->backspace(); });
    connect(ui->num_dot,  &QPushButton::clicked, this, [=]{ ui->expression->insert("."); });
    connect(ui->eval,  &QPushButton::clicked, this, [=]{ evaluate(); });
    connect(ui->factorial,  &QPushButton::clicked, this, [=]{ ui->expression->insert("!"); });
    connect(ui->all_clear,  &QPushButton::clicked, this, [=]{ acButtonClicked(); });

    // Menu connexions
    connect(ui->actionSolve,  &QAction::triggered, this, [=]{ solver(); });
    connect(ui->actionShow_pinpad,  &QAction::triggered, this, [=]{ show_pinpad(); });
    connect(ui->actionHide_pinpad,  &QAction::triggered, this, [=]{ hide_pinpad(); });
    connect(ui->actionDark_theme,  &QAction::triggered, this, [=]{ dark_theme(); });
    connect(ui->actionNo_theme,  &QAction::triggered, this, [=]{ no_theme(); });
    connect(ui->actionAbout_LilouCalc,  &QAction::triggered, this, [=]{ showAboutDialog(); });
    connect(ui->actionAbout_Qt,  &QAction::triggered, this, [=]{ qApp->aboutQt(); });
    //connect(ui->expression, SIGNAL(textChanged(QString)), this, SLOT(lineEditTextChanged(QString)));

    connect( ui->expression, &QLineEdit::textChanged, this,[=]( const QString &newValue ) { lineEditTextChanged(newValue); });

    connect(ui->result, &QPlainTextEdit::selectionChanged, this, [=] { ui->expression->setFocus(); });

    setWindowTitle("Lilou Calc");

    m_evaluator = Evaluator::instance();

    ui->expression->setFocus();
    loadHistory();
    initTheme();
    initMenu();


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::acButtonClicked()
{
    if (ui->result->toPlainText().isEmpty())
        return;

    bool result=history.clearhistory();
    if (result)
    {
        ui->result->clear();
        ui->expression->clear();
    }
    ui->expression->setFocus();
}

void MainWindow::evaluate()
{
    ui->expression->setFocus();
    if (ui->expression->text().isEmpty())
    {

        return;
    }

    m_evaluator->initializeBuiltInVariables();
    m_evaluator->autoFix(ui->expression->text());
    m_evaluator->setExpression(ui->expression->text()
                               .replace("×", "*")
                               .replace("÷", "/")
                               .replace(":", "/")
                               .replace("x", "*")
                               .replace("X", "*")
                               .replace("π", "pi"));

    Quantity rn = m_evaluator->evalUpdateAns();
    if (m_evaluator->error().isEmpty())
    {
        QString result = DMath::format(rn, Format::Fixed());

        //ui->result->appendPlainText(result);
        ui->result->appendPlainText(ui->expression->text());
        ui->result->appendPlainText(QString("= %1").arg(result));
        ui->result->appendPlainText(QLatin1String(""));
        ui->result->moveCursor(QTextCursor::End);
        ui->expression->setFocus();


    }
    else
    {
        ui->result->appendPlainText(ui->expression->text());
        ui->result->appendPlainText(QString("= %1").arg(m_evaluator->error()));
        ui->result->appendPlainText(QLatin1String(""));
        ui->result->moveCursor(QTextCursor::End);
        ui->expression->setFocus();



    }


}

void MainWindow::show_pinpad()
{
    ui->gridFrame->show();
    ui->backspace->show();
    ui->expression->setFocus();
    ui->actionShow_pinpad->setVisible(false);
    ui->actionHide_pinpad->setVisible(true);
    config.setOption("keyboard", "show");

}
void MainWindow::hide_pinpad()
{

        ui->gridFrame->hide();
        ui->backspace->hide();
        ui->expression->setFocus();
        ui->actionShow_pinpad->setVisible(true);
        ui->actionHide_pinpad->setVisible(false);
        config.setOption("keyboard", "hide");


}

void MainWindow::solver()
{
    Solve solve;
    solve.exec();
    ui->expression->setFocus();
}


void MainWindow::dark_theme()
{
    skin.setSkin("dark");


    ui->actionDark_theme->setVisible(false);
    ui->actionNo_theme->setVisible(true);

}

void MainWindow::no_theme()
{
    skin.setSkin("notheme");
    ui->actionDark_theme->setVisible(true);
    ui->actionNo_theme->setVisible(false);

}

void MainWindow::lineEditTextChanged(const QString &text)
{
    if (text.isEmpty())
    {

        ui->statusbar->showMessage("");
    }
    else
    {

        m_evaluator->setExpression(ui->expression->text()
                                   .replace("×", "*")
                                   .replace("÷", "/")
                                   .replace(":", "/")
                                   .replace("x", "*")
                                   .replace("X", "*")
                                   .replace("π", "pi"));
        auto quantity = m_evaluator->evalNoAssign();

        if (m_evaluator->error().isEmpty())
        {
            if (quantity.isNan() && m_evaluator->isUserFunctionAssign())
            {


            }else
            {
                auto formatted = NumberFormatter::format(quantity);
                auto message = QString(tr("Current result: %1")).arg(formatted);

                ui->statusbar->showMessage(message);
            }
        }else
        {

            ui->statusbar->showMessage(m_evaluator->error());
        }

    }

    ui->expression->setFocus();

}

void MainWindow::loadHistory()
{
    ui->result->setPlainText(history.readhistory());
    ui->result->moveCursor(QTextCursor::End);
}

void MainWindow::closeEvent(QCloseEvent *)
{

    history.savehistory(ui->result->toPlainText());
}
void MainWindow::initTheme()
{
    if (config.getOption("theme") == "notheme") {
        ui->actionNo_theme->setVisible(false);
        ui->actionDark_theme->setVisible(true);
        no_theme();
    }
    else if (config.getOption("theme") == "dark")
    {
        ui->actionNo_theme->setVisible(true);
        ui->actionDark_theme->setVisible(false);
        dark_theme();
    }

}
void MainWindow::initMenu()
{
    if (config.getOption("keyboard") == "show") {
        ui->actionShow_pinpad->setVisible(false);
        ui->actionHide_pinpad->setVisible(true);
        show_pinpad();
    }else {
        ui->actionShow_pinpad->setVisible(true);
        ui->actionHide_pinpad->setVisible(false);
        hide_pinpad();
    }

}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        ui->eval->clicked(true);
    }
}
void MainWindow::showAboutDialog()
{
    auto* aboutDialog = new AboutDialog(this);
    aboutDialog->open();
}
