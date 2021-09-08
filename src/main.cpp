/*!
 * \file main.cpp
 * \brief file for the definition of the main function
 * \author chapet
 * \date 2021-9-3
 *
 * \details
 *
 * \copyright
 ****************************************************************************
 *       Creative Commons Legal Code
 *         -------------------------------------
 *
 * CC0 1.0 Universal
 * read LICENSE file for more information
 *
 ****************************************************************************
 */
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "be_window.h"

int main(int argc, char *argv[])
{
	if (qEnvironmentVariableIsEmpty("QTGLESSTREAM_DISPLAY")) {
		qputenv("QT_QPA_EGLFS_PHYSICAL_WIDTH", QByteArray("213"));
		qputenv("QT_QPA_EGLFS_PHYSICAL_HEIGHT", QByteArray("120"));

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
		QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
	}

	QGuiApplication app(argc, argv);
	app.setOrganizationName("me");
	app.setOrganizationDomain("fr");

	BeWindow::classQmlRegistration();

	QQmlApplicationEngine engine;
	const QUrl url(QStringLiteral("qrc:/main.qml"));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
					 &app, [url](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);
	engine.load(url);

	return app.exec();
}
