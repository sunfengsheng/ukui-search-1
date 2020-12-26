#include "file-utils.h"
#include <QDebug>
#include <QFile>
#include <QUrl>

FileUtils::FileUtils()
{
}

std::string FileUtils::makeDocUterm(QString path)
{
    return QCryptographicHash::hash(path.toUtf8(),QCryptographicHash::Md5).toStdString();
}

/**
 * @brief FileUtils::getFileIcon 获取文件图标
 * @param uri "file:///home/xxx/xxx/xxxx.txt"格式
 * @param checkValid
 * @return
 */
QIcon FileUtils::getFileIcon(const QString &uri, bool checkValid)
{
    auto file = wrapGFile(g_file_new_for_uri(uri.toUtf8().constData()));
    auto info = wrapGFileInfo(g_file_query_info(file.get()->get(),
                              G_FILE_ATTRIBUTE_STANDARD_ICON,
                              G_FILE_QUERY_INFO_NONE,
                              nullptr,
                              nullptr));
    if (!G_IS_FILE_INFO (info.get()->get()))
        return QIcon::fromTheme("unknown");
    GIcon *g_icon = g_file_info_get_icon (info.get()->get());
    QString icon_name;
    //do not unref the GIcon from info.
    if (G_IS_ICON(g_icon)) {
        const gchar* const* icon_names = g_themed_icon_get_names(G_THEMED_ICON (g_icon));
        if (icon_names) {
            auto p = icon_names;
            if (*p)
                icon_name = QString (*p);
            if (checkValid) {
                while (*p) {
                    QIcon icon = QIcon::fromTheme(*p);
                    if (!icon.isNull()) {
                        icon_name = QString (*p);
                        break;
                    } else {
                        p++;
                    }
                }
            }
        }
    }
    if (QIcon::fromTheme(icon_name).isNull()) {
        return QIcon::fromTheme("unknown");
    }
    return QIcon::fromTheme(icon_name);
}

/**
 * @brief FileUtils::getAppIcon 获取应用图标
 * @param path .desktop文件的完整路径
 * @return
 */
QIcon FileUtils::getAppIcon(const QString &path) {
    QByteArray ba;
    ba = path.toUtf8();
    GKeyFile * keyfile;
    keyfile = g_key_file_new();
    if (!g_key_file_load_from_file(keyfile, ba.data(), G_KEY_FILE_NONE, NULL)){
        g_key_file_free (keyfile);
        return QIcon::fromTheme("unknown");
    }
    QString icon = QString(g_key_file_get_locale_string(keyfile, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_ICON, NULL, NULL));
    g_key_file_free(keyfile);
    if (QIcon::fromTheme(icon).isNull()) {
        return QIcon(":/res/icons/desktop.png");
    }
    return QIcon::fromTheme(icon);
}

/**
 * @brief FileUtils::getSettingIcon 获取设置图标
 * @param setting 设置项传入参数，格式为 About/About->Properties
 * @param is_white 选择是否返回白色图标
 * @return
 */
QIcon FileUtils::getSettingIcon(const QString& setting, const bool& is_white) {
    QString name = setting.left(setting.indexOf("/"));
    QString path;
    if (is_white) {
        path = QString("/usr/share/ukui-control-center/shell/res/secondaryleftmenu/%1White.svg").arg(name);
    } else {
        path = QString("/usr/share/ukui-control-center/shell/res/secondaryleftmenu/%1.svg").arg(name);
    }
    QFile file(path);
    if (file.exists()) {
        return QIcon(path);
    } else {
        if (is_white) {
            return QIcon(QString("/usr/share/ukui-control-center/shell/res/secondaryleftmenu/%1White.svg").arg("About"));
        } else {
            return QIcon(QString("/usr/share/ukui-control-center/shell/res/secondaryleftmenu/%1.svg").arg("About"));
        }
    }
}

/**
 * @brief FileUtils::getFileName 获取文件名
 * @param uri 文件的url，格式为"file:///home/xxx/xxx/xxxx.txt"
 * @return
 */
QString FileUtils::getFileName(const QString& uri) {
    QUrl url = uri;
    if (url.fileName().isEmpty()) {
        return "Unknown File";
    }
    return url.fileName();
}

/**
 * @brief FileUtils::getAppName 获取应用名
 * @param path .destop文件的完整路径
 * @return
 */
QString FileUtils::getAppName(const QString& path) {
    QByteArray ba;
    ba = path.toUtf8();
    GKeyFile * keyfile;
    keyfile = g_key_file_new();
    if (!g_key_file_load_from_file(keyfile, ba.data(), G_KEY_FILE_NONE, NULL)){
        g_key_file_free (keyfile);
        return "Unknown App";
    }
    QString name = QString(g_key_file_get_locale_string(keyfile, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_NAME, NULL, NULL));
    g_key_file_free(keyfile);
    return name;
}

/**
 * @brief FileUtils::getSettingName 获取设置项名
 * @param setting 设置项传入参数，格式为 About/About->Properties
 * @return
 */
QString FileUtils::getSettingName(const QString& setting) {
    return setting.right(setting.length() - setting.lastIndexOf("/") - 1);
}