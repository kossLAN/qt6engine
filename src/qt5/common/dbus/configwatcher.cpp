#include "configwatcher.hpp"

#include <QDBusConnection>
#include <QDBusConnectionInterface>
#include <QFileInfo>

#include "config/configmanager.hpp"

Q_LOGGING_CATEGORY(logConfigWatcher, "qtengine.configwatcher", QtWarningMsg)

static const QString SERVICE_NAME = QStringLiteral("org.qtengine.ConfigWatcher");
static const QString OBJECT_PATH = QStringLiteral("/org/qtengine/ConfigWatcher");
static const QString INTERFACE_NAME = QStringLiteral("org.qtengine.ConfigWatcher");

ConfigWatcher& ConfigWatcher::instance() {
	static ConfigWatcher instance;
	return instance;
}

ConfigWatcher::ConfigWatcher(QObject* parent): QObject(parent) {
	mConfigPath = configManager().configPath;

	if (mConfigPath.isEmpty()) {
		qCWarning(logConfigWatcher) << "No config file path available, config watching disabled";
		return;
	}

	mLastModified = QFileInfo(mConfigPath).lastModified();

	mDebounceTimer = new QTimer(this);
	mDebounceTimer->setSingleShot(true);
	mDebounceTimer->setInterval(250);
	connect(mDebounceTimer, &QTimer::timeout, this, [this]() {
		mLastModified = QFileInfo(mConfigPath).lastModified();
		qCInfo(logConfigWatcher) << "Config file changed, notifying listeners";
		emit configChanged();
	});

	auto bus = QDBusConnection::sessionBus();

	if (!bus.isConnected()) {
		qCWarning(logConfigWatcher) << "D-Bus session bus unavailable, config watching disabled";
		return;
	}

	mServiceWatcher = new QDBusServiceWatcher(
	    SERVICE_NAME,
	    bus,
	    QDBusServiceWatcher::WatchForRegistration | QDBusServiceWatcher::WatchForUnregistration,
	    this
	);
	connect(
	    mServiceWatcher,
	    &QDBusServiceWatcher::serviceUnregistered,
	    this,
	    &ConfigWatcher::onServiceUnregistered
	);

	tryRegister();
}

ConfigWatcher::~ConfigWatcher() {
	if (mIsRegistered) {
		auto bus = QDBusConnection::sessionBus();

		if (bus.isConnected()) {
			bus.unregisterObject(OBJECT_PATH);
			bus.unregisterService(SERVICE_NAME);
		}
	}
}

void ConfigWatcher::tryRegister() {
	auto bus = QDBusConnection::sessionBus();

	if (!bus.registerService(SERVICE_NAME)) {
		connectToRemote();
		return;
	}

	mIsRegistered = true;
	bus.registerObject(OBJECT_PATH, this, QDBusConnection::ExportScriptableSignals);

	mFileWatcher = new QFileSystemWatcher(this);

	bool fileAdded = mFileWatcher->addPath(mConfigPath);
	qCInfo(logConfigWatcher) << "Watching config file:" << mConfigPath << "(inotify:" << fileAdded
	                         << ")";

	const QFileInfo fi(mConfigPath);
	if (fi.absolutePath() != mConfigPath) {
		mFileWatcher->addPath(fi.absolutePath());
	}

	connect(mFileWatcher, &QFileSystemWatcher::fileChanged, this, &ConfigWatcher::onFileChanged);
	connect(mFileWatcher, &QFileSystemWatcher::directoryChanged, this, [this](const QString&) {
		if (QFileInfo::exists(mConfigPath)) {
			if (!mFileWatcher->files().contains(mConfigPath)) {
				mFileWatcher->addPath(mConfigPath);
			}
			mDebounceTimer->start();
		}
	});

	mPollTimer = new QTimer(this);
	mPollTimer->setInterval(2000);
	connect(mPollTimer, &QTimer::timeout, this, &ConfigWatcher::pollForChanges);
	mPollTimer->start();

	qCInfo(logConfigWatcher) << "Registered config watcher on D-Bus";
}

void ConfigWatcher::connectToRemote() {
	auto bus = QDBusConnection::sessionBus();

	bus.connect(
	    SERVICE_NAME,
	    OBJECT_PATH,
	    INTERFACE_NAME,
	    QStringLiteral("configChanged"),
	    this,
	    SLOT(onRemoteConfigChanged())
	);

	qCInfo(logConfigWatcher) << "Connected to existing config watcher instance";
}

void ConfigWatcher::onFileChanged(const QString& path) {
	// Always re-add — editors often delete+recreate files, losing the inotify watch
	QTimer::singleShot(100, this, [this, path]() {
		if (QFileInfo::exists(path) && !mFileWatcher->files().contains(path)) {
			mFileWatcher->addPath(path);
		}
	});

	mDebounceTimer->start();
}

void ConfigWatcher::onRemoteConfigChanged() { emit configChanged(); }

void ConfigWatcher::pollForChanges() {
	const QFileInfo fi(mConfigPath);
	if (!fi.exists()) return;

	const QDateTime currentMtime = fi.lastModified();
	if (currentMtime != mLastModified) {
		mLastModified = currentMtime;

		// Re-add to file watcher in case it was lost
		if (!mFileWatcher->files().contains(mConfigPath)) {
			mFileWatcher->addPath(mConfigPath);
		}

		qCInfo(logConfigWatcher) << "Poll detected config change";
		mDebounceTimer->start();
	}
}

void ConfigWatcher::onServiceUnregistered(const QString& service) {
	Q_UNUSED(service)

	if (!mIsRegistered) {
		qCInfo(logConfigWatcher) << "Config watcher instance unregistered, attempting to take over";

		auto bus = QDBusConnection::sessionBus();
		bus.disconnect(
		    SERVICE_NAME,
		    OBJECT_PATH,
		    INTERFACE_NAME,
		    QStringLiteral("configChanged"),
		    this,
		    SLOT(onRemoteConfigChanged())
		);

		tryRegister();
	}
}
