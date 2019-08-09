#ifndef PUPIL_OPERATION_H
#define PUPIL_OPERATION_H

#include "pupil.h"
#include <fstream>
#include <iostream>
#include <io.h>
#include <map>
#include <QDir>
#include <QFile>
#include <stack>

#include "ui_mainwindow.h"
using namespace cv;

class pupil_operation
{
public:
    pupil_operation();
    void extract_eyeinfo_batchly(int id, QString path);
    ~pupil_operation();

private:
//    void getFiles(std::string path, std::map<std::string, std::string> & files);
//    void pupil_operation::extract_eyeinfo_batch(std::string input_path, std::string out_path);
//    void record(int id, QString path);
//    stack<std::string> path_analysis(QString path);
    //    void record(QString path);

};

#endif // PUPIL_OPERATION_H
