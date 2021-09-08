/*!
 * \file interpreter.cpp
 * \brief file for the definition of the class "Interpreter"
 * \author chapet
 * \date 2021-9-7
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

#include <QDateTime>
#include <QDebug>
#include <QThread>

#include "interpreter.h"
#include "js_api.h"


Interpreter::Interpreter(QObject * parent) : QObject(parent)
  , m_jsApi(new JsApi())
  , m_thread(nullptr)
{
	m_thread = new QThread();
	if (m_thread) {
		m_jsApi->moveToThread(m_thread);
		QObject::connect(m_jsApi	, & JsApi::finished		, m_thread, & QThread::quit);
		QObject::connect(m_thread	, & QThread::finished	, m_thread, & QThread::deleteLater);
		m_thread->start();
	}

	QObject::connect(m_jsApi, & JsApi::valueChanged			, this, & Interpreter::sltVariableChanged);
	QObject::connect(m_jsApi, & JsApi::evalDone				, this, & Interpreter::sltRunDone);
	QObject::connect(m_jsApi, & JsApi::finished				, m_jsApi, & JsApi::deleteLater);
	QObject::connect(this	, & Interpreter::sigStartEval	, m_jsApi, & JsApi::evaluate);
	QObject::connect(this	, & Interpreter::sigGetVariable	, m_jsApi, & JsApi::getVarValue);
	QObject::connect(this	, & Interpreter::sigSetVariable	, m_jsApi, & JsApi::setValue);
}

Interpreter::~Interpreter()
{
	m_jsApi->close();
}

void Interpreter::runScript(const QString & code)
{
	emit sigStartEval(code);
}

void Interpreter::getProperty(const QString & name)
{
	emit sigGetVariable(name);
}

void Interpreter::setProperty(const QString & name, const QVariant & value)
{
	QJSValue val;
	switch (value.type()) {
		case QVariant::Bool:
			val = QJSValue(value.toBool());
			break;
		case QVariant::Date:
		case QVariant::DateTime:
		case QVariant::Time: {
			QDateTime dt = value.toDateTime();
			val = QJSValue(dt.toString());
			break;
		}
		case QVariant::Double:
			val = QJSValue(value.toDouble());
			break;
		case QVariant::Int:
			val = QJSValue(value.toInt());
			break;
		case QVariant::String:
			val = QJSValue(value.toString());
		break;
		case QVariant::UInt:
			val = QJSValue(value.toUInt());
			break;
		default:
			break;
	}
	emit sigSetVariable(name, val);
}

void Interpreter::sltVariableChanged(const QString & varName, const QJSValue & value)
{
	emit propertyValue(varName, value.toVariant());
}

void Interpreter::sltRunDone(const QJSValue & value)
{
	QVariant result = value.toVariant();
	qInfo() << Q_FUNC_INFO << result;
	emit scriptDone(result);
}
