#ifndef ADLITIEVENTEDITOR_H
#define ADLITIEVENTEDITOR_H

#include "properties.h"
#include "variantpropertymanager.h"
#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class AdlitiEventEditor;
}

namespace Tiled {
    class AdlitiEventEditor : public QDialog
    {
        Q_OBJECT

    public:
        explicit AdlitiEventEditor(const DisplayAdlitiScript &startingValue, QWidget *parent = nullptr);
        ~AdlitiEventEditor();

        void setValue(const DisplayAdlitiScript &value);
        const DisplayAdlitiScript &value() const;

    private slots:
        void on_buttonBox_clicked(QAbstractButton *button);

    private:
        Ui::AdlitiEventEditor *ui;

        DisplayAdlitiScript mValue;
    };

    inline const DisplayAdlitiScript &AdlitiEventEditor::value() const
    {
        return mValue;
    }
}

#endif // ADLITIEVENTEDITOR_H
