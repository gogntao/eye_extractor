#include "fileoperation.h"

fileoperation::fileoperation(QObject *parent) : QObject(parent)
{
    subject_list.open("subject_list.txt", ios::ate);
}

fileoperation::~fileoperation()
{
    subject_list.close();
}

/**
 * @brief fileoperation::get_sub_dir
 * @param root
 * @return
 * 返回选中目录下的所有子目录，并计入列表中
 */
void fileoperation::get_sub_dir(const QString root)
{
    get_sub_dir_list(root);
    emit(subject_pick_finished());
}

void fileoperation::get_sub_dir_list(const QString root)
{
    QStringList subdirs;
    QDir cur_dirs = QDir(root);

    cur_dirs.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);

    if(cur_dirs.entryInfoList().isEmpty()) {
        qDebug() << cur_dirs;
        QStringList pic_type_filter;
        pic_type_filter << "*.jpg" ;
        cur_dirs.setNameFilters(pic_type_filter);
        cur_dirs.setFilter(QDir::Files);
        if(cur_dirs.entryInfoList().empty()) {
        }else {
            string subject_path = root.toStdString();
            subject_list << subject_path << endl;
        }
        return;
    }else {
        foreach(QFileInfo dir_elem, cur_dirs.entryInfoList()) {
            get_sub_dir_list(dir_elem.filePath());
        }
    }
}

/**
 * @brief fileoperation::get_subject_id
 * @param path
 * @return
 */
string fileoperation::get_subject_id(string path)
{
    string subject_id;
    return subject_id;
}
