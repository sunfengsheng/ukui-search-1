#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

#include <QObject>
#include <QSettings>
#include <QMutex>
#include <QVector>
//#include <QGSettings>
//If use pkg_config, it wont build succes,why?????????
//My demo can build access yet.
//MouseZhangZh
#include <QGSettings/QGSettings>
#include "libsearch_global.h"

#define CONTROL_CENTER_PERSONALISE_GSETTINGS_ID "org.ukui.control-center.personalise"
#define TRANSPARENCY_KEY "transparency"
#define INDEX_DATABASE_STATE "index_database_state"
#define CONTENT_INDEX_DATABASE_STATE "content_index_database_state"
#define INDEX_GENERATOR_NORMAL_EXIT "index_generator_normal_exit"

class LIBSEARCH_EXPORT GlobalSettings : public QObject
{
    Q_OBJECT
public:
    static GlobalSettings *getInstance();
    const QVariant getValue(const QString&);
    bool isExist(const QString&);

Q_SIGNALS:
    void valueChanged (const QString&);
    void transparencyChanged (const double&);

public Q_SLOTS:
    void setValue(const QString&, const QVariant&);
    void reset(const QString&);
    void resetAll();
    /**
     * @brief setBlockDirs
     * set path for blacklist,return true if success,otherwise return false.
     * @param path path to be blocked
     * @param returnMessage this message will be set when return false.
     * @return
     */
    bool setBlockDirs(const QString& path, QString &returnMessage);
    QStringList getBlockDirs();

    void forceSync(const QString& = nullptr);

private:
    explicit GlobalSettings(QObject *parent = nullptr);
    ~GlobalSettings();

    QSettings* m_settings;
    QGSettings* m_gsettings;
    QSettings *m_block_dirs_settings;
    QMap<QString, QVariant> m_cache;

    QMutex m_mutex;



};

#endif // GLOBALSETTINGS_H