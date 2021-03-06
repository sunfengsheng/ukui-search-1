#include "search-plugin-manager.h"

using namespace Zeeker;

static SearchPluginManager *global_instance = nullptr;
bool SearchPluginManager::registerPlugin(Zeeker::SearchPluginIface *plugin)
{
    if (m_hash.value(plugin->name())) {
        return false;
    }
    m_hash.insert(plugin->name(), plugin);
    return true;
}

SearchPluginManager *SearchPluginManager::getInstance()
{
    if (!global_instance) {
        global_instance = new SearchPluginManager;
    }
    return global_instance;
}

const QStringList SearchPluginManager::getPluginIds()
{
    return m_hash.keys();
}

SearchPluginIface *SearchPluginManager::getPlugin(const QString &pluginId)
{
    return m_hash.value(pluginId);
}

void SearchPluginManager::close()
{
    this->deleteLater();
}

SearchPluginManager::SearchPluginManager(QObject *parent)
{
}

SearchPluginManager::~SearchPluginManager()
{
    m_hash.clear();
}
