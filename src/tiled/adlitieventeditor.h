#ifndef ADLITIEVENTEDITOR_H
#define ADLITIEVENTEDITOR_H

#include <QDialog>

namespace Ui {
class AdlitiEventEditor;
}

class AdlitiEventEditor : public QDialog
{
    Q_OBJECT

public:
    explicit AdlitiEventEditor(QWidget *parent = nullptr);
    ~AdlitiEventEditor();

private:
    Ui::AdlitiEventEditor *ui;
};

#endif // ADLITIEVENTEDITOR_H
