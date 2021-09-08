/*!
 * \file be_window.h
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
#ifndef BEWINDOW_H
#define BEWINDOW_H

#include <QObject>

#include "interpreter.h"

class QThread;

class BeWindow : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString	result		READ result	  /*WRITE setResult*/	NOTIFY resultChanged)
	Q_PROPERTY(QString	textArea	READ textArea	WRITE setTextArea	NOTIFY textAreaChanged)
	Q_PROPERTY(int		valueIn		READ valueIn	WRITE setValueIn	NOTIFY valueInChanged)
	Q_PROPERTY(int		valueOut	READ valueOut /*WRITE setValueOut*/	NOTIFY valueOutChanged)
	Q_PROPERTY(bool		busy		READ busy	  /*WRITE setBusy*/		NOTIFY busyChanged)

	Q_PROPERTY(QString	path		READ path	  /*WRITE setPath*/		NOTIFY pathChanged)

public:
	explicit	BeWindow	(QObject * parent = nullptr);
	~BeWindow();

	static void	classQmlRegistration	();

	QString		result			() const	{	return m_result;	}
	QString		textArea		() const	{	return m_textArea;	}
	int			valueIn			() const	{	return m_valueIn;	}
	int			valueOut		() const	{	return m_valueOut;	}
	bool		busy			() const	{	return m_busy;		}

	QString		path			() const	{	return m_path;	}

public slots:
	void		init			();
	void		load			(const QString & fileName);
	void		clear			();
	void		run				();
	void		start			();
	void		stop			();

	void		setTextArea		(const QString & textArea);
	void		setValueIn		(int valueIn);

signals:
	void		resultChanged	(const QString & result);
	void		textAreaChanged	(const QString & textArea);
	void		valueInChanged	(int valueIn);
	void		valueOutChanged	(int valueOut);
	void		busyChanged		(bool busy);

	void		pathChanged		(const QString & path);

	void		sigStartEval	(const QString & code);
	void		sigSetVariable	(const QString & varName, const QVariant & value);

private:
	void		setResult		(const QString & result);
	void		setValueOut		(int valueOut);
	void		setBusy			(bool busy);
	void		setPath			(const QString & path);

	void		runScript		();

	void		sltUpdateApiSlider		(int value);
	void		sltApiVariableChanged	(const QString & varName, const QVariant & value);
	void		sltRunDone				(const QVariant & value);

	QString		m_textArea;
	int			m_valueIn;
	int			m_valueOut;
	bool		m_busy;
	QString		m_path;
	QString		m_result;
	bool		m_loop;
	Interpreter	* m_interpreter;
};

#endif // BEWINDOW_H
