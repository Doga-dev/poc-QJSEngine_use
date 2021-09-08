/*!
 * \file interpreter.h
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
#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <QJSValue>
#include <QObject>
#include <QString>
#include <QVariant>

#include "js_api.h"

class JsApi;
class QThread;

class Interpreter : public QObject
{
	Q_OBJECT
public:
	explicit 	Interpreter		(QObject * parent = nullptr);
				~Interpreter	();

	void		runScript		(const QString & code);

public slots:
	void		getProperty		(const QString & name);
	void		setProperty		(const QString & name, const QVariant & value);

signals:
	void		scriptDone		(const QVariant & result);
	void		propertyValue	(const QString & name, const QVariant & value);

	// private signals:
	void		sigStartEval	(const QString & code);
	void		sigGetVariable	(const QString & varName);
	void		sigSetVariable	(const QString & varName, const QJSValue & value);

private:
	void		sltVariableChanged	(const QString & varName, const QJSValue & value);
	void		sltRunDone			(const QJSValue & value);

	JsApi		* m_jsApi;
	QThread		* m_thread;
};

#endif // INTERPRETER_H
