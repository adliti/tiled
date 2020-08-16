#include "adlitieventeditor.h"
#include "ui_adlitieventeditor.h"

AdlitiEventEditor::AdlitiEventEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdlitiEventEditor)
{
    ui->setupUi(this);
}

AdlitiEventEditor::~AdlitiEventEditor()
{
    delete ui;
}
