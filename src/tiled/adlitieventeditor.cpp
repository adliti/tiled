#include "adlitieventeditor.h"
#include "ui_adlitieventeditor.h"

namespace Tiled {

AdlitiEventEditor::AdlitiEventEditor(const DisplayAdlitiScript &startingValue, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdlitiEventEditor)
{
    ui->setupUi(this);
}

AdlitiEventEditor::~AdlitiEventEditor()
{
    delete ui;
}

}

void Tiled::AdlitiEventEditor::on_buttonBox_clicked(QAbstractButton *button)
{

}
