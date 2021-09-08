/*!
 * \file js_api.h
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
#ifndef JSAPI_H
#define JSAPI_H

#include <QJSEngine>
#include <QObject>
#include <QVariantMap>

class JsApi : public QObject
{
	Q_OBJECT


public:
	explicit 	JsApi		(QObject * parent = nullptr);
				~JsApi		();

public:
	// available functions for the JavaScript code
	Q_INVOKABLE void		delay		(int milliseconds);
	Q_INVOKABLE void		setValue	(const QString & varName, const QJSValue & value);
	Q_INVOKABLE QJSValue	getValue	(const QString & varName);


public slots:
	void		close		();
	void		evaluate	(const QString & program);
	void		getVarValue	(const QString & varName);

signals:
	void		finished	();
	void		valueChanged(const QString & varName, const QJSValue & value);
	void		evalDone	(const QJSValue & value);

private:
	QJSEngine					m_jsEngine;
	QJSValue					m_jsValAPI;
	QMap<QString, QJSValue>		m_variables;
};

#endif // JSAPI_H
