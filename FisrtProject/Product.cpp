#include "Product.h"

Product::Product() {}

Product::Product(const QString& name, QString& number, int total, float PurchasePrice, float SalePrice,
                 const QString& Manufacturer, const QDate& ProductionDate, int QualityDate)
    : name(name), number(number), total(total), PurchasePrice(PurchasePrice), SalePrice(SalePrice),
      Manufacturer(Manufacturer), ProductionDate(ProductionDate), QualityDate(QualityDate) {}

Product::Product(const Product& product)
    : name(product.name), number(product.number), total(product.total), PurchasePrice(product.PurchasePrice),
      SalePrice(product.SalePrice), Manufacturer(product.Manufacturer), ProductionDate(product.ProductionDate),
      QualityDate(product.QualityDate) {}

