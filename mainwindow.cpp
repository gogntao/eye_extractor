#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}


MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::on_select_picroot_clicked
 *
 * 该函数用于弹出文件选择对话框，并选择文件目录
 */
void MainWindow::on_select_picroot_clicked()
{
    dialog->setFileMode(QFileDialog::Directory);
    dialog->setViewMode(QFileDialog::List);
    dialog->open();
}

/**
 * @brief MainWindow::init
 * 该函数用于初始化设置，目前的设置有：
 * 1.绑定文件选择框与文本框目录显示
 */
void MainWindow::init()
{
    dialog = new QFileDialog(this);
    ui->pic_root->setReadOnly(true);
    ui->cur_progress->setValue(0);
    connect(dialog, SIGNAL(directoryEntered(const QString)), this, SLOT(get_selected_picroot(const QString)));
    file_op = new fileoperation();
    pupil_op = new pupil_operation();
    connect(this, SIGNAL(send_pic_root(const QString)),file_op, SLOT(get_sub_dir(const QString)));
    connect(file_op, SIGNAL(subject_pick_finished()), this, SLOT(show_subject_dir()));
}

void MainWindow::get_selected_picroot(const QString pic_root)
{
    qDebug() << pic_root;
    ui->pic_root->setText(pic_root);
}

void MainWindow::show_subject_dir()
{
    int subject_num = 0;
//    string output_path = "subjectResultDir";

    string cur_subject_line ;
    ifstream subject_list("subject_list.txt");
    if(!subject_list) {
        qDebug() << "filed to openfile";
        exit(0);
    }
    ui->message_center->clear();

    while(!subject_list.eof()) {
        subject_num++;
        getline(subject_list, cur_subject_line);
        subject_path_list.push_back(QString::fromStdString(cur_subject_line));
        ui->message_center->append(QString::fromStdString(cur_subject_line));
    }
    QString subject_num_info = QString(QString::fromLocal8Bit("一共找到 ") + QString::number(subject_num-1) + QString::fromLocal8Bit(" 个被试，请检查是否符合数目"));
    if(subject_num <= 1) {
        ui->message_center->append(QString::fromLocal8Bit("没有找到被试路径，请重试"));
    }else {
        ui->message_center->append(subject_num_info);
        QMessageBox msgBox;
        msgBox.setText(QString::fromLocal8Bit("被试信息搜集完毕，是否开始采集?"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Yes : {
            ui->cur_progress->setRange(0, subject_num-1);
            ui->cur_progress->setValue(0);
            begin_extract();
            break;
        }
        case QMessageBox::Cancel : {
            break;
        }
        default : break;

        }
    }
}

void MainWindow::on_begin_pick_clicked()
{
    QString cur_root = ui->pic_root->text();
    if(cur_root.isNull()) {
        qDebug() << "不正确的路径";
    }else {
        emit(send_pic_root(cur_root));
    }

}

void MainWindow::begin_extract()
{
    int cur_list_id = 0;
    QDir cur;
    QString dir_path = cur.path() + "extractResult";
    QDir dir_res(dir_path);
    if(!dir_res.exists()) {
        cur.mkdir(QString("extractResult"));
    }
    ui->message_center->append(QString::fromLocal8Bit("============提取程序开始==============="));
    subject_path_list.pop_back();
    while(!subject_path_list.empty()) {
        cur_list_id++;
//        QCoreApplication::processEvents();
        ui->message_center->append(QString::fromLocal8Bit("开始提取第")+QString::number(cur_list_id) + QString::fromLocal8Bit("个被试信息..."));
        QString cur_subject_path = subject_path_list.front();
        pupil_op->extract_eyeinfo_batchly(cur_list_id, cur_subject_path);
        ui->cur_progress->setValue(cur_list_id);
        ui->cur_progress->repaint();
        subject_path_list.pop_front();
    }
    ui->message_center->append(QString::fromLocal8Bit("==============提取过程结束================="));
}


