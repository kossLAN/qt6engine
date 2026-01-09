#pragma once

#include <optional>

#include <QPalette>
#include <QSet>
#include <QString>
#include <QStringList>

#if QT_VERSION < QT_VERSION_CHECK(6, 4, 0)

#include <QLatin1String>

namespace Qt {
inline namespace Literals {
inline namespace StringLiterals {

inline QString operator""_s(const char16_t* str, size_t size) noexcept {
	return QString(QStringPrivate(nullptr, const_cast<char16_t*>(str), qsizetype(size)));
}

constexpr inline QLatin1String operator""_L1(const char* str, size_t size) noexcept {
	return QLatin1String(str, int(size));
}

inline QByteArray operator""_ba(const char* str, size_t size) noexcept {
	return QByteArray(QByteArrayData(nullptr, const_cast<char*>(str), qsizetype(size)));
}

} // namespace StringLiterals
} // namespace Literals
} // namespace Qt

using QLatin1StringView = QLatin1String;

#endif

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

	static std::optional<QPalette> loadColorScheme(const QString& filePath);

	static void registerStyleInstance(CStyleInstance* instance);
	static void unregisterStyleInstance(CStyleInstance* instance);
	static void reloadStyleInstanceSettings();

private:
	static QSet<CStyleInstance*> styleInstances;
};

bool isKColorScheme(const QString& filePath);
