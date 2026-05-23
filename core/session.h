// SPDX-FileCopyrightText: 2015-2016, 2024, 2026 SpeedCrunch developers
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef CORE_SESSION_H
#define CORE_SESSION_H

#include "variable.h"
#include "userfunction.h"
#include "userunit.h"
#include <QList>
#include <QHash>
#include <QString>

class Session {
private:
    typedef QHash<QString, Variable> VariableContainer;
    typedef QHash<QString, UserFunction> FunctionContainer;
    typedef QHash<QString, UserUnit> UnitContainer;
    VariableContainer m_variables;
    FunctionContainer m_userFunctions;
    UnitContainer m_userUnits;

public:
    Session() {}
    Session& operator=(const Session&) = default;

    void addVariable(const Variable & var);
    bool hasVariable(const QString & id) const;
    void removeVariable(const QString & id);
    void clearVariables();
    Variable getVariable(const QString & id) const;
    QList<Variable> variablesToList() const;
    bool isBuiltInVariable(const QString &id) const;

    void addUserFunction(const UserFunction & func);
    void removeUserFunction(const QString & str);
    void clearUserFunctions();
    bool hasUserFunction(const QString & str) const;
    QList<UserFunction> UserFunctionsToList() const;
    const UserFunction * getUserFunction(const QString & fname) const;

    void addUserUnit(const UserUnit& unit);
    void removeUserUnit(const QString& name);
    void clearUserUnits();
    bool hasUserUnit(const QString& name) const;
    QList<UserUnit> userUnitsToList() const;
    const UserUnit* getUserUnit(const QString& name) const;
};

#endif // CORE_SESSION_H
