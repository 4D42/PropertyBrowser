#include "propertybrowser.h"


PropertyBrowser::PropertyBrowser(QWidget* parent) : QtTreePropertyBrowser(parent)
{
    mVariantManager = new QtVariantPropertyManager(this);
    setFactoryForManager(mVariantManager, new QtVariantEditorFactory);
    connect(mVariantManager, &QtVariantPropertyManager::valueChanged, this, &PropertyBrowser::onValueChanged);
}

PropertyBrowser::~PropertyBrowser()
{
    delete mVariantManager;
}

void PropertyBrowser::clearProperties()
{
    clear();

    mVariantManager->clear();

    mPropertyMap.clear();
    mPropertyIdTypeMap.clear();
}

void PropertyBrowser::addAProperty(QString propertyName, QVariant propertyData, int propertyIdType)
{
    mPropertyMap.insert(propertyName, propertyData);
    mPropertyIdTypeMap.insert(propertyName, propertyIdType);

    QtVariantProperty *property = mVariantManager->addProperty(propertyIdType, propertyName);
    property->setValue(propertyData);
    addProperty(property);

}

QMap<QString, QtVariantProperty *> PropertyBrowser::setProperties(QMap<QString, QVariant> propertyMap, QMap<QString, int> propertyIdTypeMap)
{
    QMap<QString, QtVariantProperty *> properties;

    mPropertyMap = propertyMap;
    mPropertyIdTypeMap = propertyIdTypeMap;

    foreach(QString key, mPropertyMap.keys()){
        QtVariantProperty *property = mVariantManager->addProperty(mPropertyIdTypeMap.value(key), key);
        property->setValue(mPropertyMap.value(key));
        addProperty(property);
        properties.insert(key,property);
    }

    return properties;
}

void PropertyBrowser::onValueChanged(QtProperty *property, const QVariant &value)
{
    if(mPropertyMap.contains(property->propertyName()))
        emit sendPropertyChange(property->propertyName(), value);
}
