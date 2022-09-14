#ifndef PROPERTYBROWSER_H
#define PROPERTYBROWSER_H

#include <QDebug>
#include <QObject>
#include <QPushButton>
#include <QMap>
#include <QMetaProperty>
#include "qtpropertybrowser/qteditorfactory.h"
#include "qtpropertybrowser/qttreepropertybrowser.h"
#include "qtpropertybrowser/qtpropertymanager.h"
#include "qtpropertybrowser/qtvariantproperty.h"


/*
    Based on
    https://www.codeproject.com/script/Articles/ViewDownloads.aspx?aid=5256485
*/

class PropertyBrowser : public QtTreePropertyBrowser
{
    Q_OBJECT

public:
    PropertyBrowser(QWidget* parent = nullptr);
    virtual ~PropertyBrowser();
    // void setActiveObject(QObject *obj);
    void clearProperties();
    void addAProperty(QString propertyName, QVariant propertyData, int propertyIdType);
    QMap<QString, QtVariantProperty *> setProperties(QMap<QString, QVariant> propertyMap, QMap<QString, int> propertyIdTypeMap);

private:
    QtVariantPropertyManager *mVariantManager;
    QMap<QString, QVariant> mPropertyMap;
    QMap<QString, int> mPropertyIdTypeMap;

signals:
    void sendPropertyChange(QString name, QVariant value);

private slots:
    void onValueChanged(QtProperty *property, const QVariant &value);
};

#endif // PROPERTYBROWSER_H
