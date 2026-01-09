#include <QLatin1String>
#include <QLibraryInfo>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QVersionNumber>
#include <QtPlugin>
#include <qcontainerfwd.h>
#include <qdebug.h>
#include <qlogging.h>
#include <qpa/qplatformtheme.h>
#include <qpa/qplatformthemeplugin.h>
#include <qstringlist.h>
#include <qtmetamacros.h>

#include "platformtheme.hpp"

class QT6EngineThemePlugin: public QPlatformThemePlugin {
	Q_OBJECT;
	Q_PLUGIN_METADATA(
	    IID "org.qt-project.Qt.QPA.QPlatformThemeFactoryInterface.5.1" FILE "engine.json"
	);

public:
	QPlatformTheme* create(const QString& key, const QStringList& params) override {
		(void) params;

		const QVersionNumber v = QLibraryInfo::version();
		if (v.majorVersion() != 6) {
			qCritical() << "qt6engine was compiled against an incompatible qt version. Compiled against"
			            << 6 << "but has" << v.majorVersion();
			return nullptr;
		}

		if (key.toLower() == QLatin1String("qt6engine")) {
			qInfo() << "Initializing qt6engine platform theme plugin";
			return new PlatformTheme();
		}

		return nullptr;
	}
};

#include "main.moc"
