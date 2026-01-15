#pragma once

#include <optional>

#include <QPalette>
#include <QSet>
#include <QString>
#include <QStringList>

// #if QT_VERSION < QT_VERSION_CHECK(6, 4, 0)
// #endif

class Style {
public:
	class CStyleInstance {
	public:
		CStyleInstance() = default;
		CStyleInstance(const CStyleInstance&) = delete;
		CStyleInstance& operator=(const CStyleInstance&) = delete;
		CStyleInstance(CStyleInstance&&) = delete;
		CStyleInstance& operator=(CStyleInstance&&) = delete;
		virtual ~CStyleInstance() = default;
		virtual void reloadSettings() = 0;
	};

	static QPalette loadColorScheme(const QString& filePath);

	static void registerStyleInstance(CStyleInstance* instance);
	static void unregisterStyleInstance(CStyleInstance* instance);
	static void reloadStyleInstanceSettings();

private:
	static QSet<CStyleInstance*> styleInstances;
};
