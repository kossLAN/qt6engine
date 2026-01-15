// #include <QLatin1String>
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

#include "platformtheme.hpp"

class QtEngineThemePlugin: public QPlatformThemePlugin {
	Q_OBJECT;
	Q_PLUGIN_METADATA(
	    IID "org.qt-project.Qt.QPA.QPlatformThemeFactoryInterface.5.1" FILE "engine.json"
	);

public:
	QPlatformTheme* create(const QString& key, const QStringList& params) override {
		(void) params;

		const QVersionNumber v = QLibraryInfo::version();
		constexpr int expectedMajor = QT_VERSION_MAJOR;
		if (v.majorVersion() != expectedMajor) {
			qCritical() << "qtengine was compiled against an incompatible qt version. Compiled against"
			            << expectedMajor << "but has" << v.majorVersion();
			return nullptr;
		}

		if (key.toLower() == QString::fromLatin1("qtengine")) {
			qInfo() << "Initializing qtengine platform theme plugin";
			return new PlatformTheme();
		}

		return nullptr;
	}
};

#include "main.moc"
