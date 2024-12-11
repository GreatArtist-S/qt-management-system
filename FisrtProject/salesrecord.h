#ifndef SALESRECORD_H
#define SALESRECORD_H

#include <QDate>
#include <qstring.h>



class SalesRecord
{
public:
    SalesRecord();
    QString orderID;
    int quantity;
    double discountRate;
    QDate orderDate;
    QString contactNumber;

    SalesRecord(const QString& orderID, int quantity, double discountRate, const QDate& orderDate, const QString& contactNumber);
 };

#endif // SALESRECORD_H
