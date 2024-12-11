#ifndef ITEM_H
#define ITEM_H

#include <QDate>
#include <QString>
#include <QList>
#include <QFile>
#include <QTextStream>
#include "salesrecord.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class Product
{
public:
    QString name;
    QString number;
    int total;
    float PurchasePrice;
    float SalePrice;
    QString Manufacturer;
    QDate ProductionDate;
    int QualityDate;
    QList<SalesRecord> salesRecords;

    Product();
    Product(const QString& name, QString& number, int total, float PurchasePrice, float SalePrice,
            const QString& Manufacturer, const QDate& ProductionDate, int QualityDate);
    Product(const Product& product);

    // New method to save product data to a file

};

#endif // ITEM_H

