#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QtDebug>
#include <QMessageBox>
#include "fileoperation.h"
#include "pupil_operation.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_select_picroot_clicked();
    void get_selected_picroot(const QString pic_root);
    void show_subject_dir();
    void on_begin_pick_clicked();

private:
    Ui::MainWindow *ui;
    QFileDialog *dialog;
    fileoperation *file_op;
    pupil_operation *pupil_op;
    QStringList subject_path_list;
    void begin_extract();
    void init();
signals:
    void send_pic_root(const QString pic_root);
};

#endif // MAINWINDOW_H
