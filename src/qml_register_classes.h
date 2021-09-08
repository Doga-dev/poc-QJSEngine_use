/*!
 * \file qml_register_classes.h
 * \brief file for the definition of the QML registering macro
 * \author chapet
 * \date 2021-1-7
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
#ifndef QML_REGISTER_CLASSES_H
#define QML_REGISTER_CLASSES_H

#include <QQmlEngine>

#define CALL_THIS_ONCE()		{	\
	static bool done = false;		\
	if (done) return;				\
	done = true;					\
	}

#define QML_LIBRARY_NAME				"MyLib"
#define QML_LIBRARY_MAJ_VERSION			1
#define QML_LIBRARY_MIN_VERSION			0

#define REGISTER_CREATABLE_TYPE(typeName)		\
	qmlRegisterType<typeName>(QML_LIBRARY_NAME, QML_LIBRARY_MAJ_VERSION, QML_LIBRARY_MIN_VERSION, #typeName)

#define REGISTER_UNCREATABLE_TYPE(typeName)		\
	qmlRegisterUncreatableType<typeName>(QML_LIBRARY_NAME, QML_LIBRARY_MAJ_VERSION, QML_LIBRARY_MIN_VERSION, #typeName, "interface")

#define REGISTER_MODELABLE_TYPE(typeName)		\
	qmlRegisterType<typeName>(QML_LIBRARY_NAME, QML_LIBRARY_MAJ_VERSION, QML_LIBRARY_MIN_VERSION, #typeName); \
	qmlRegisterUncreatableType<OLM_##typeName>(QML_LIBRARY_NAME, QML_LIBRARY_MAJ_VERSION, QML_LIBRARY_MIN_VERSION, "ListModel_" #typeName, "interface")


#endif // QML_REGISTER_CLASSES_H
