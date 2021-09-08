/*!
 * \file js_api.cpp
 * \brief file for the definition of the class "JsApi"
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
#include "js_api.h"

#include <unistd.h>
#include <QDebug>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

JsApi::JsApi(QObject * parent) : QObject(parent)
{
	m_jsEngine.globalObject().setProperty("APP_HOST", "poc-QJSEngine_use");
	m_jsEngine.installExtensions(QJSEngine::ConsoleExtension);

	m_jsValAPI = m_jsEngine.newQObject(this);

	m_jsEngine.globalObject().setProperty("AppAPI", m_jsValAPI);
}

JsApi::~JsApi()
{}


void JsApi::delay(int milliseconds)
{
//	qInfo() << Q_FUNC_INFO;
	usleep(milliseconds * 1000);
}

void JsApi::setValue(const QString & varName, const QJSValue & value)
{
//	qInfo() << Q_FUNC_INFO << varName << value.toVariant();
	if (getValue(varName).equals(value))
		return;

	m_variables[varName] = value;
	emit valueChanged(varName, value);
}

QJSValue JsApi::getValue(const QString & varName)
{
	QJSValue res;

	res = m_variables.value(varName, res);
	return res;
}


void JsApi::evaluate(const QString & program) {
	qInfo() << Q_FUNC_INFO;
	emit evalDone(m_jsEngine.evaluate(program));
}

void JsApi::getVarValue(const QString & varName)
{
	emit valueChanged(varName, getValue(varName));
}

void JsApi::close()
{
	qInfo() << Q_FUNC_INFO;
	emit finished();
}
