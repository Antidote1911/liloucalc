#include "solve.h"
#include "ui_solve.h"
#include <math.h>
#include <QDoubleSpinBox>
#include <iostream>

#include <QtCore/QVector>
#include <gsl/gsl_poly.h>
#include <gsl/gsl_complex.h>

#include <gsl/gsl_errno.h>

using namespace std;

Solve::Solve(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Solve)
{
    ui->setupUi(this);
    //connect(ui->aBox, SIGNAL(valueChanged(double)), this, SLOT(resolve()));
    connect(ui->aBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [=](double a){ resolve(); });
    connect(ui->bBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [=](double b){ resolve(); });
    connect(ui->cBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [=](double c){ resolve(); });
    //connect(ui->aBox, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this, &Solve::resolve);
    resolve();
}

Solve::~Solve()
{
    delete ui;
}

void Solve::resolve()
{
    double a=ui->aBox->value();
    double b=ui->bBox->value();
    double c=ui->cBox->value();

    double delta=(b*b-4*a*c);
    ui->delta->setNum(delta);

    if (a==0.)
    {
        ui->infos->setText("a=0 résolution de bx+c=0");

        double sol1=(-c/b);
        ui->sol1->setNum(sol1);
        ui->sol2->setText("none");
    }
    else
    {
        if (delta>0)
        {
            ui->infos->setText("delta > 0 donc deux solutions réelles");
            double x0, x1;
            gsl_poly_solve_quadratic(a, b, c, &x0, &x1);
            ui->sol1->setNum(x0);
            ui->sol2->setNum(x1);
        }
        else if (delta<0)
        {
            ui->infos->setText("delta < 0 donc deux solutions imaginaires");
            gsl_complex z0,z1;
            gsl_poly_complex_solve_quadratic(a, b, c, &z0, &z1);

            QString Sol_1_Real, Sol_2_Real;
            QString Sol_1_Imag, Sol_2_Imag;

            Sol_1_Real = QString::number(GSL_REAL(z0));
            Sol_1_Imag = QString::number(GSL_IMAG(z0));

            Sol_2_Real = QString::number(GSL_REAL(z1));
            Sol_2_Imag = QString::number(GSL_IMAG(z1));

            if (GSL_IMAG(z0)<0)
            {
                ui->sol1->setText(Sol_1_Real+Sol_1_Imag+"i");
            }
            else
            {
                ui->sol1->setText(Sol_1_Real+"+"+Sol_1_Imag+"i");
            }

            if (GSL_IMAG(z1)<0)
            {
                ui->sol2->setText(Sol_2_Real+Sol_2_Imag+"i");
            }
            else
            {
                ui->sol2->setText(Sol_2_Real+"+"+Sol_2_Imag+"i");
            }

        }
        else if (delta==0.)
        {
            ui->infos->setText("delta = 0 donc une solution double");
            double x0, x1;
            gsl_poly_solve_quadratic(a, b, c, &x0, &x1);

            ui->sol1->setNum(x0);
            ui->sol2->setNum(x1);
        }
    }
}
