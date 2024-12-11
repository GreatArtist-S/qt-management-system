#ifndef MANAGER_H
#define MANAGER_H

#include <QList>
#include <QFile>
#include <QTextStream>
#include "salesrecord.h"
#include "Product.h"
class Manager
{
public:
    Manager();
    QList<Product> products;

};

#endif // MANAGER_H
