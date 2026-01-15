#include <optional>
#include <utility>

#include <KColorScheme>
#include <KSharedConfig>
#include <QDir>
#include <QFile>
#include <QLatin1String>
#include <QLocale>
#include <QPalette>
#include <QRegularExpression>
#include <QSet>
#include <QSettings>
#include <QStandardPaths>
#include <QStringList>
#include <QtCore/QDebug>
#include <QtCore/QStringList>
#include <QtCore/QtGlobal>
#include <QtDebug>
#include <QtGlobal>
#include <qdebug.h>

#include "common.hpp"

QSet<Style::CStyleInstance*> Style::styleInstances;

QPalette Style::loadColorScheme(const QString& filePath) {
	return KColorScheme::createApplicationPalette(KSharedConfig::openConfig(filePath));
}

void Style::registerStyleInstance(Style::CStyleInstance* instance) {
	styleInstances.insert(instance);
}

void Style::unregisterStyleInstance(Style::CStyleInstance* instance) {
	styleInstances.remove(instance);
}

void Style::reloadStyleInstanceSettings() {
	for (auto* instance: std::as_const(styleInstances)) instance->reloadSettings();
}
