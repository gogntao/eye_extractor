#ifndef FILEOPERATION_H
#define FILEOPERATION_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QDebug>
#include <string>
#include <QDir>
#include <map>
#include <fstream>
#include <iostream>
using namespace std;

class fileoperation : public QObject
{
    Q_OBJECT
public:
    explicit fileoperation(QObject *parent = nullptr);
    ~fileoperation();

signals:
    void subject_pick_finished();

public slots:

private:
    QString pic_root;
    string get_subject_id(string path);
    void get_sub_dir_list(const QString root);
    ofstream subject_list;

private slots:
    void get_sub_dir(const QString root);

};

#endif // FILEOPERATION_H
