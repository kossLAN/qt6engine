#pragma once
//
// #include "../helpers/Memory.hpp"
//
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QString>

class ConfigManager {
public:
	void init();

	QString colorScheme;
	QString iconTheme;
	QString style;
	QString fontFixed;
	int fontFixedSize = 11;
	QString font;
	int fontSize = 11;

	bool singleClickActivate = true;
	bool menusHaveIcons = true;
	bool shortcutsForContextMenus = true;
};

const ConfigManager& configManager();
