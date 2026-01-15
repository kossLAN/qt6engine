#include <QLatin1String>
#include <QObject>
#include <QString>
#include <QStylePlugin>
#include <QtPlugin>

#include "proxystyle.hpp"

class StylePlugin: public QStylePlugin {
	Q_OBJECT;
	Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QStyleFactoryInterface" FILE "engine.json")

public:
	QStyle* create(const QString& key) override {
		if (key == QLatin1String("qtengine")) return new ProxyStyle();
		return nullptr;
	}
};

#include "plugin.moc"
