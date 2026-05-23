// SPDX-FileCopyrightText: 2015-2016, 2026 SpeedCrunch developers
// SPDX-License-Identifier: GPL-2.0-or-later

#include "session.h"
#include "evaluator.h"
#include <functions.h>

void Session::addVariable(const Variable &var)
{
    m_variables[var.identifier()] = var;
}

bool Session::hasVariable(const QString &id) const
{
    return m_variables.contains(id);
}

void Session::removeVariable(const QString &id)
{
    m_variables.remove(id);
}

void Session::clearVariables()
{
    m_variables.clear();
}

Variable Session::getVariable(const QString &id) const
{
    return m_variables.value(id);
}

QList<Variable> Session::variablesToList() const
{
    return m_variables.values();
}

bool Session::isBuiltInVariable(const QString &id) const
{
    if (FunctionRepo::instance()->find(id))
        return true;
    if (!m_variables.contains(id))
        return false;
    return m_variables.value(id).type() == Variable::BuiltIn;
}

void Session::addUserFunction(const UserFunction &func)
{
    if (func.opcodes.isEmpty()) {
        QString expression = func.name() + "(" + func.arguments().join(";") + ")=" + func.expression();
        if (!func.description().isEmpty())
            expression += " ? " + func.description();
        Evaluator::instance()->setExpression(expression);
        Evaluator::instance()->eval();
    } else {
        m_userFunctions[func.name()] = func;
    }
}

void Session::removeUserFunction(const QString &str)
{
    m_userFunctions.remove(str);
}

void Session::clearUserFunctions()
{
    m_userFunctions.clear();
}

bool Session::hasUserFunction(const QString &str) const
{
    return m_userFunctions.contains(str);
}

QList<UserFunction> Session::UserFunctionsToList() const
{
    return m_userFunctions.values();
}

const UserFunction* Session::getUserFunction(const QString &fname) const
{
    return &*m_userFunctions.find(fname);
}

void Session::addUserUnit(const UserUnit &unit)
{
    if (unit.name().isEmpty())
        return;
    m_userUnits[unit.name()] = unit;
}

void Session::removeUserUnit(const QString &name)
{
    m_userUnits.remove(name);
}

void Session::clearUserUnits()
{
    m_userUnits.clear();
}

bool Session::hasUserUnit(const QString &name) const
{
    return m_userUnits.contains(name);
}

QList<UserUnit> Session::userUnitsToList() const
{
    return m_userUnits.values();
}

const UserUnit* Session::getUserUnit(const QString &name) const
{
    return &*m_userUnits.find(name);
}
