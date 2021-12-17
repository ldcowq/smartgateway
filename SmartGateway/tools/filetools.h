#ifndef FILETOOLS_H
#define FILETOOLS_H
#include<QDir>
#include<QDebug>
class FileTools
{
public:
    FileTools();

    //static bool FindFile(const QString &path);
    //static QStringList getFolderFileNames(const QStringList &filter);
    static QStringList getFileAbsolutePath(QString file_path,int *nFile);
    static QStringList getFileNames(QString file_path,int *nFile);
};

#endif // FILETOOLS_H
