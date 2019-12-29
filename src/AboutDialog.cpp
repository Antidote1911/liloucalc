/*
 *  Copyright (C) 2012 Felix Geyer <debfx@fobos.de>
 *  Copyright (C) 2017 KeePassXC Team <team@keepassxc.org>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 or (at your option)
 *  version 3 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "AboutDialog.h"
#include "ui_AboutDialog.h"
#include "Constants.h"

#include <QClipboard>

static const QString aboutMaintainers = R"(
<p><ul>
    <li>Fabrice Corraire (<a href="https://github.com/Antidote1911">Antidote1911</a>)</li>
</ul></p>
)";

static const QString aboutContributors = R"(
<h3>VIP Patreon Supporters:</h3>
<ul>

</ul>
<h3>Notable Code Contributions:</h3>
<ul>

</ul>
<h3>Patreon Supporters:</h3>
<ul>

</ul>
<h3>Translations:</h3>
<ul>

</ul>
)";

AboutDialog::AboutDialog(QWidget* parent)
    : QDialog(parent)
    , m_ui(new Ui::AboutDialog())
{
    m_ui->setupUi(this);

    resize(minimumSize());
    setWindowFlags(Qt::Sheet);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    m_ui->nameLabel->setText(m_ui->nameLabel->text().replace("${VERSION}", lil::APP_VERSION));
    QFont nameLabelFont = m_ui->nameLabel->font();
    nameLabelFont.setPointSize(nameLabelFont.pointSize() + 4);
    m_ui->nameLabel->setFont(nameLabelFont);

    QString debugInfo;
    debugInfo.append(lil::APP_NAME).append("\n");
    debugInfo.append("Qt ").append(QString::fromLocal8Bit(qVersion())).append("\n");
    debugInfo.append(QObject::tr("Operating system: %1\nCPU architecture: %2\nKernel: %3 %4 \nHostname: %5\n")
                                 .arg(QSysInfo::prettyProductName(),
                                      QSysInfo::currentCpuArchitecture(),
                                      QSysInfo::kernelType(),
                                      QSysInfo::kernelVersion(),
                                      QSysInfo::machineHostName()));

    m_ui->iconLabel->setPixmap(qApp->windowIcon().pixmap(48));

    //QString debugInfo = Tools::debugInfo().append("\n").append(Crypto::debugInfo());
    m_ui->debugInfo->setPlainText(debugInfo);

    m_ui->maintainers->setText(aboutMaintainers);
    m_ui->contributors->setText(aboutContributors);

    setAttribute(Qt::WA_DeleteOnClose);
    connect(m_ui->buttonBox, SIGNAL(rejected()), SLOT(close()));
    connect(m_ui->copyToClipboard, SIGNAL(clicked()), SLOT(copyToClipboard()));
}

AboutDialog::~AboutDialog()
{
}

void AboutDialog::copyToClipboard()
{
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(m_ui->debugInfo->toPlainText());
}
