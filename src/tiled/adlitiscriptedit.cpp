/*
 * adlitiscriptedit.cpp
 * Copyright 2019, Thorbjørn Lindeijer <bjorn@lindeijer.nl>
 *
 * This file is part of Tiled.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */


#include "adlitiscriptedit.h"

#include "mapdocument.h"
#include "mapobject.h"
#include "adlitieventeditor.h"
#include "objectrefdialog.h"
#include "utils.h"

#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLineEdit>
#include <QToolButton>

#include <climits>

namespace Tiled {

AdlitiScriptEdit::AdlitiScriptEdit(QWidget *parent)
    : QWidget(parent)
    , mLineEdit(new QLineEdit(this))
    , mObjectDialogButton(new QToolButton(this))
    , mPickObjectButton(new QToolButton(this))
{
    QHBoxLayout *layout = new QHBoxLayout(this);

    setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed));
    setFocusProxy(mLineEdit);

    mObjectDialogButton->setText(QStringLiteral("..."));
    mObjectDialogButton->setAutoRaise(true);
    mObjectDialogButton->setEnabled(false);
    mObjectDialogButton->setIconSize(Utils::smallIconSize());
    mObjectDialogButton->setIcon(QIcon(QStringLiteral("://images/scalable/search-object-dialog.svg")));
    mObjectDialogButton->setToolTip(tr("Search Object"));

    mPickObjectButton->setText(QStringLiteral("Pick"));
    mPickObjectButton->setAutoRaise(true);
    mPickObjectButton->setEnabled(false);
    mPickObjectButton->setCheckable(true);
    mPickObjectButton->setFocusPolicy(Qt::StrongFocus);
    mPickObjectButton->setIconSize(Utils::smallIconSize());
    mPickObjectButton->setIcon(QIcon(QStringLiteral("://images/scalable/select-object.svg")));
    mPickObjectButton->setToolTip(tr("Select Object on Map"));

    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(mLineEdit);
    layout->addWidget(mObjectDialogButton);
    layout->addWidget(mPickObjectButton);

    mLineEdit->setValidator(new QIntValidator(0, INT_MAX, this));

    connect(mObjectDialogButton, &QToolButton::clicked, this, &AdlitiScriptEdit::openObjectRefDialog);
    connect(mPickObjectButton, &QToolButton::toggled, this, &AdlitiScriptEdit::pickObjectOnMap);
    connect(mLineEdit, &QLineEdit::editingFinished, this, &AdlitiScriptEdit::onEditFinished);
}

AdlitiScriptEdit::~AdlitiScriptEdit()
{
    // Make sure we're no longer picking any object
    mPickObjectButton->setChecked(false);
}

void AdlitiScriptEdit::setValue(const DisplayAdlitiScript &value)
{
    if (mValue == value)
        return;

    if (mValue.mapDocument)
        mValue.mapDocument->disconnect(this);

    mValue = value;
    mLineEdit->setText(mValue.script());

    mObjectDialogButton->setEnabled(mValue.mapDocument);
    mPickObjectButton->setEnabled(mValue.mapDocument);

    if (mValue.mapDocument) {
        connect(mValue.mapDocument, &MapDocument::mapObjectPicked,
                this, &AdlitiScriptEdit::onMapObjectPicked);
    }

    emit valueChanged(mValue);
}

void AdlitiScriptEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape && mPickObjectButton->isChecked()) {
        mPickObjectButton->setChecked(false);
        return;
    }

    // QWidget::keyPressEvent(event);
}

void AdlitiScriptEdit::openObjectRefDialog()
{
    if (!mValue.mapDocument)
        return;

    AdlitiEventEditor dialog(mValue, this);

    /* if (dialog.exec() == QDialog::Accepted)
        setValue(dialog.value()); */
    dialog.exec();
}

void AdlitiScriptEdit::pickObjectOnMap(bool pick)
{
    if (!mValue.mapDocument)
        return;

    if (pick)
        emit mValue.mapDocument->mapObjectPickRequest();
    else
        emit mValue.mapDocument->cancelMapObjectPickRequest();
}

void AdlitiScriptEdit::onMapObjectPicked(MapObject *object)
{
    if (!mPickObjectButton->isChecked())
        return;

    /* mPickObjectButton->setChecked(false);
    if (object) {
        setValue(DisplayObjectRef {
                     ObjectRef { object->id() },
                     mValue.mapDocument
                 });
    } */
}

void AdlitiScriptEdit::onEditFinished()
{
    auto newValue = fromExportValue(mLineEdit->text(), objectRefTypeId()).value<ObjectRef>();
    // setValue(DisplayObjectRef { newValue, mValue.mapDocument });
}

} // namespace Tiled
