#include "pupil_operation.h"

pupil_operation::pupil_operation()
{

}



void pupil_operation::extract_eyeinfo_batchly(int id, QString path) {
//    QCoreApplication::processEvents();
    string output_filename = "extractResult\\"+to_string(id)+".txt";
    ofstream fout(output_filename);
    QDir cur_dir = path;
    QStringList file_filter;
    file_filter << "*.jpg";
    cur_dir.setNameFilters(file_filter);
    cur_dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    foreach(QFileInfo cur_img, cur_dir.entryInfoList()){
        QCoreApplication::processEvents();
        QString cur_img_path = cur_img.filePath();
        Pupil cur_pupil(cur_img_path.toStdString());
        cur_pupil.search_pupil_by_step(cur_pupil.img_info, 65, 5, 7);
        fout << cur_img.fileName().toStdString() << ":pupil_area = " << cur_pupil.pupil_area << ",diameter = " << cur_pupil.diameter << ",pupil_center:("
                   << cur_pupil.pupil_center.x << "," << cur_pupil.pupil_center.y << ")" << std::endl;
        cur_pupil.~Pupil();
    }
    fout.close();
}

pupil_operation::~pupil_operation()
{
}

//void pupil_operation::extract_eyeinfo_batch(std::string input_path, std::string out_path)
//{
//    std::ofstream fout(out_path, std::ios::ate);
//    std::map<std::string, std::string> files;
//    if (fout.fail()) {
//        std::cout << "error occurs when opening file" << std::endl;
//        exit(0);
//    }
//    getFiles(input_path, files);
//    std::map<std::string, std::string>::iterator iter;

//    for (iter = files.begin(); iter != files.end(); iter++) {
//        Pupil cur_pupil = Pupil(iter->first);
//        cur_pupil.search_pupil_by_step(cur_pupil.img_info, 65, 5, 7);

//        int cur_state = blink_detect(cur_area_reference, cur_pupil.pupil_area, change_rate_threshold);
//        if (cur_state == NOT_IN_BLINK) {
//            cur_area_reference = cur_pupil.pupil_area;
//        }

//        string state = cur_state == IN_BLINK ? "blink" : "not in blink";

//        fout << iter->second << ":pupil_area = " << cur_pupil.pupil_area << ",diameter = " << cur_pupil.diameter << ",pupil_center:("
//            << cur_pupil.pupil_center.x << "," << cur_pupil.pupil_center.y << ")" << std::endl;
//        imwrite(out_path + iter->second, cur_pupil.img_result);
//        cur_pupil.~Pupil();
//    }
//    fout.close();
//    fout.clear();
//    return;
//}


//void pupil_operation::record(int id, QString path)
//{
//    std::string path_std = path.toStdString();
//    stack<std::string> level_name = path_analysis(path);


//    Pupil cur_pupil(path_std);
//    cur_pupil.search_pupil_by_step(cur_pupil.img_info, 65, 5, 7);
//    qDebug() << cur_pupil.diameter;
//    imwrite(output_name.toStdString(), cur_pupil.img_result);
//}

//stack<std::string> pupil_operation::path_analysis(QString path)
//{
//    std::string path_std = path.toStdString();
//    std::stack<std::string> path_level_name;
//    std::string cur_level;
//    for(int i = 0; i < path_std.length(); ++i) {
//        if(path_std.at(i) == '/') {
//            path_level_name.push(cur_level);
//            cur_level = "";
//        }else{
//            cur_level = cur_level + path_std.at(i);
//        }
//    }
//    path_level_name.push(cur_level);
//    return path_level_name;
//}


