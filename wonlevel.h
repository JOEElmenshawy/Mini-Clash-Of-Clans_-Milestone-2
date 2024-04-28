#ifndef WONLEVEL_H
#define WONLEVEL_H

#include <QDialog>

namespace Ui {
class WonLevel;
}

class WonLevel : public QDialog
{
    Q_OBJECT

public:
    explicit WonLevel(QWidget *parent = nullptr);
    ~WonLevel();
public slots:
    void nextLevel();
private:
    Ui::WonLevel *ui;
};

#endif // WONLEVEL_H
