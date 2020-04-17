#ifndef PATH_H
#define PATH_H

#include <QObject>
#include "custom_line.h"

class path : public QObject
{
    Q_OBJECT
public:
    explicit path(QObject *parent = nullptr);
    QMap<int, custom_line*> st_dict;

signals:

};

#endif // PATH_H
