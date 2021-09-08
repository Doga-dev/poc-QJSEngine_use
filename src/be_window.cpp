/*!
 * \file be_window.cpp
 * \brief file for the definition of the class "BeWindow"
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

#include <QDebug>
#include <QCoreApplication>
#include <QFile>

#include "be_window.h"
#include "qml_register_classes.h"

BeWindow::BeWindow(QObject * parent) : QObject(parent)
  , m_textArea("// Started")
  , m_valueIn(0)
  , m_valueOut(10)
  , m_busy(false)
  , m_path()
  , m_loop(false)
  , m_interpreter(new Interpreter(this))
{
	QCoreApplication * app = qApp->instance();
	if (app) {
		m_path = app->applicationDirPath();
	}
	QObject::connect(this, & BeWindow::valueInChanged, this, & BeWindow::sltUpdateApiSlider);
	setValueIn(42);

	QObject::connect(m_interpreter	, & Interpreter::propertyValue	, this			, & BeWindow::sltApiVariableChanged);
	QObject::connect(m_interpreter	, & Interpreter::scriptDone		, this			, & BeWindow::sltRunDone);
	QObject::connect(this			, & BeWindow::sigStartEval		, m_interpreter	, & Interpreter::runScript);
	QObject::connect(this			, & BeWindow::sigSetVariable	, m_interpreter	, & Interpreter::setProperty);
}

BeWindow::~BeWindow()
{
}

void BeWindow::classQmlRegistration()
{
	CALL_THIS_ONCE();
	REGISTER_CREATABLE_TYPE(BeWindow);
}

void BeWindow::init()
{
	qInfo() << Q_FUNC_INFO;
	setTextArea("// Initialized");
}

void BeWindow::load(const QString & fileName)
{
//	qInfo() << Q_FUNC_INFO << fileName;
	QFile	file(QUrl(fileName).toLocalFile());
	if (file.open(QIODevice::ReadOnly)) {
		qInfo() << "Open file :" << file.fileName();
		setTextArea(file.readAll());
		file.close();
	}
}

void BeWindow::clear()
{
	setTextArea("");
}

void BeWindow::run()
{
	qInfo() << Q_FUNC_INFO;
	setResult("");
	m_loop = false;
	runScript();
}

void BeWindow::start()
{
	qInfo() << Q_FUNC_INFO;
	setResult("");
	m_loop = true;
	runScript();
}

void BeWindow::stop()
{
	qInfo() << Q_FUNC_INFO;
	m_loop = false;
}

void BeWindow::setTextArea(const QString & textArea)
{
	if (m_textArea == textArea)
		return;

	m_textArea = textArea;
	emit textAreaChanged(m_textArea);
}

void BeWindow::setValueIn(int valueIn)
{
	if (m_valueIn == valueIn)
		return;

	qInfo() << Q_FUNC_INFO << valueIn;
	m_valueIn = valueIn;
	emit valueInChanged(m_valueIn);
}

void BeWindow::setValueOut(int valueOut)
{
	if (m_valueOut == valueOut)
		return;

	m_valueOut = valueOut;
	emit valueOutChanged(m_valueOut);
//	qInfo() << Q_FUNC_INFO << valueOut;
}

void BeWindow::setBusy(bool busy)
{
	if (m_busy == busy)
		return;

	m_busy = busy;
	emit busyChanged(m_busy);
}

void BeWindow::runScript()
{
	qInfo() << Q_FUNC_INFO;
	setBusy(true);
	emit sigStartEval(m_textArea);
}

void BeWindow::setResult(const QString & result)
{
	qInfo() << Q_FUNC_INFO << result;
	if (m_result == result)
		return;

	m_result = result;
	emit resultChanged(m_result);
}

void BeWindow::setPath(const QString & path)
{
	if (m_path == path)
		return;

	m_path = path;
	emit pathChanged(m_path);
}

void BeWindow::sltUpdateApiSlider(int value)
{
	qInfo() << Q_FUNC_INFO << value;
	emit sigSetVariable("slider", QVariant(value));
}

void BeWindow::sltApiVariableChanged(const QString & varName, const QVariant & value)
{
	if (varName == "result") {
		setValueOut(value.toInt());
	} else {
		qInfo() << Q_FUNC_INFO << varName << value;
	}
}

void BeWindow::sltRunDone(const QVariant & value)
{
	qInfo() << Q_FUNC_INFO << value;
	setResult(value.toString());
	if (m_loop) {
		runScript();
	} else {
		setBusy(false);
	}
}
