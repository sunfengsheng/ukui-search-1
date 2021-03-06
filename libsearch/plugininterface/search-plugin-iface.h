#ifndef SEARCHPLUGINIFACE_H
#define SEARCHPLUGINIFACE_H
#define SearchPluginIface_iid "org.ukui.ukui-search.plugin-iface.SearchPluginInterface"

#include <QString>
#include <QIcon>
#include <QMap>
#include "plugin-iface.h"

namespace Zeeker {
class SearchPluginIface : public PluginInterface
{
public:
    struct DescriptionInfo
    {
        QString key;
        QString value;
    };
    /**
     * @brief The ResultInfo struct
     */
    struct ResultInfo
    {
        QIcon icon;
        QString name;
        QVector<DescriptionInfo> description;
        QStringList actionList; //all actions, take fist for double click action.
        QString key;
    };
    virtual ~SearchPluginIface() {}
    virtual QString getPluginName() = 0;
    virtual void KeywordSearch(QString keyword,QQueue<ResultInfo> *searchResult) = 0;
    virtual void openAction(QString action, QString key) = 0;

};
}

Q_DECLARE_INTERFACE(Zeeker::SearchPluginIface, SearchPluginIface_iid)

#endif // SEARCHPLUGINIFACE_H
