#include "salesrecord.h"

SalesRecord::SalesRecord(const QString& orderID, int quantity, double discountRate, const QDate& orderDate, const QString& contactNumber)
    : orderID(orderID), quantity(quantity), discountRate(discountRate), orderDate(orderDate), contactNumber(contactNumber) {}

