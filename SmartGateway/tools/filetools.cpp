#include "filetools.h"

FileTools::FileTools()
{

}


//QStringList FileTools::getFolderFileNames(const QStringList &filter) {
//    QStringList fileList;
//    QString strFolder = QFileDialog::getExistingDirectory();

//    if (!strFolder.length() == 0) {
//        QDir myFolder(strFolder);

//        if (myFolder.exists()) {
//            fileList = myFolder.entryList(filter);
//        }
//    }

//    return fileList;
//}


/*
说明
    QDir::NoDotAndDotDot
    作用：去除 "."  ".."   它们分别表示为当前目录、上一级目录

    QDir::Files
    作用：显示文件（不是文件夹）

    QDir::Dirs
    作用：显示文件夹

    代码示例：
*/
QStringList FileTools::getFileAbsolutePath(QString file_path,int *nFile){
    QDir dir(file_path);
    QStringList file_list;
    QStringList nameFilters;
    if (!dir.exists()) {
        file_list.clear();
        qDebug() << "该目录不存在！！！";
        return file_list;
    }

    nameFilters << "*.jpg" << "*.png" << "*.jpeg"<<"*.mp4"<<"*.avi"<<"*.mp3";
    dir.setSorting(QDir::DirsFirst);
    QFileInfoList list = dir.entryInfoList(nameFilters,QDir::Files | QDir::NoDotAndDotDot);
    int i = 0;
    do {
        QFileInfo fileInfo = list.at(i);
        if (fileInfo.fileName() == "." | fileInfo.fileName() == "..") {
            i++;
            continue;
        }
        bool bisDir = fileInfo.isDir();
        if (bisDir) {
            getFileAbsolutePath(fileInfo.filePath(),nFile);
        } else {
//            qDebug() << QString("%1/%2")
//                     .arg(fileInfo.path())
//                     .arg(fileInfo.fileName());
            (*nFile)++;
            file_list<<QString("%1/%2").arg(fileInfo.path()).arg(fileInfo.fileName());//添加元素到集合
        }
        i++;
    } while (i < list.size());
    return file_list;
}

QStringList FileTools::getFileNames(QString file_path,int *nFile){
    QDir dir(file_path);
    QStringList file_list;
    QStringList nameFilters;
    if (!dir.exists()) {
        file_list.clear();
        qDebug() << "该目录不存在！！！";
        return file_list;
    }

    nameFilters << "*.jpg" << "*.png" << "*.jpeg"<<"*.mp4"<<"*.avi"<<"*.mp3";
    dir.setSorting(QDir::DirsFirst);
    QFileInfoList list = dir.entryInfoList(nameFilters,QDir::Files | QDir::NoDotAndDotDot);
    int i = 0;
    do {
        QFileInfo fileInfo = list.at(i);
        if (fileInfo.fileName() == "." | fileInfo.fileName() == "..") {
            i++;
            continue;
        }
        bool bisDir = fileInfo.isDir();
        if (bisDir) {
            getFileAbsolutePath(fileInfo.filePath(),nFile);
        } else {
//            qDebug() << QString("%1/%2")
//                     .arg(fileInfo.path())
//                     .arg(fileInfo.fileName());
            (*nFile)++;
            file_list<<QString("%1").arg(fileInfo.fileName());//添加元素到集合
            //qDebug() << QString("%1").arg(fileInfo.fileName());
        }
        i++;
    } while (i < list.size());
    return file_list;
}


//bool FileTools::FindFile(const QString &path) {

//    QDir dir(path);
//    if (!dir.exists()) {
//        return false;
//    }
//    dir.setFilter(QDir::Dirs | QDir::Files);
//    dir.setSorting(QDir::DirsFirst);
//    QFileInfoList list = dir.entryInfoList();
//    int i = 0;
//    do {

//        QFileInfo fileInfo = list.at(i);
//        if (fileInfo.fileName() == "." | fileInfo.fileName() == "..") {
//            i++;
//            continue;
//        }
//        bool bisDir = fileInfo.isDir();
//        if (bisDir) {
//            FindFile(fileInfo.filePath());
//        } else {
//            blog_file_paths_ << fileInfo.path();
//            blog_file_names_ << fileInfo.fileName();
//            qDebug() << QString(" %2  %3  ")
//                        .arg(fileInfo.path())
//                        .arg(fileInfo.fileName());
//            nFiles++;
//        }
//        i++;
//    } while (i < list.size());
//    return true;
//}

