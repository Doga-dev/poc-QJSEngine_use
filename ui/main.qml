import QtQuick 2.12
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12

import MyLib 1.0

Window {
	id: window
	width: 800
	height: 600
	visible: true
	title: qsTr("POC - QJsEngine use")

	BeWindow {
		id: be
	}

	Load_file {
		id: loadFile
		folder: be.path
		onFileSelected: be.load(fileName);
	}
	RowLayout {
		id: buttons
		anchors.top: parent.top
		anchors.topMargin: 16
		anchors.left: parent.left
		anchors.leftMargin: 16
		anchors.right: parent.right
		anchors.rightMargin: 16
		spacing: 16

		Button {
			id: btInit
			text: qsTr("Init")
			font.pointSize: 12
			onClicked: be.init();
			enabled: ! be.busy
			Layout.fillWidth: true
		}
		Button {
			id: btLoad
			text: qsTr("Load")
			font.pointSize: 12
			onClicked: loadFile.open();
			enabled: ! be.busy
			Layout.fillWidth: true
		}
		Button {
			id: btClear
			text: qsTr("Clear")
			font.pointSize: 12
			onClicked: be.clear();
			enabled: ! be.busy
			Layout.fillWidth: true
		}
		Button {
			id: btRun
			text: qsTr("Run")
			font.pointSize: 12
			onClicked: be.run();
			enabled: ! be.busy
			Layout.fillWidth: true
		}
		Button {
			id: btStart
			text: qsTr("Start")
			font.pointSize: 12
			onClicked: be.start();
			enabled: ! be.busy
			Layout.fillWidth: true
		}
		Button {
			id: btStop
			text: qsTr("Stop")
			font.pointSize: 12
			onClicked: be.stop();
			enabled: be.busy
			Layout.fillWidth: true
		}
	}

	TextArea {
		id: retText
		height: 40
		anchors.top: buttons.bottom
		anchors.topMargin: 8
		anchors.left: parent.left
		anchors.leftMargin: 16
		anchors.right: parent.right
		anchors.rightMargin: 16

		text: be.result
		font.pointSize: 12
		readOnly: true
		background:
			Rectangle {
//			//id: retRect
//			//anchors.fill: parent
//			//anchors.margins: -1
//			border.color: "grey"
//			border.width: 1
			color: "seashell"
		}
	}

/**/
	TextArea {
		id: textArea
//		height: 320
		text: be.textArea
		font.pointSize: 12
//		onTextChanged: be.textArea = text
		anchors.top: retText.bottom
		anchors.topMargin: 8
		anchors.bottom: slider.top
		anchors.bottomMargin: 8
		anchors.left: parent.left
		anchors.leftMargin: 16
		anchors.right: parent.right
		anchors.rightMargin: 16
		enabled: ! be.busy
		background:
			Rectangle {
//			border.color: "red"
			border.width: 1
		}
	}
	/**/

	Slider {
		id: slider
		height: 40
		anchors.bottom: parent.bottom
		anchors.bottomMargin: 16
		anchors.left: parent.left
		anchors.leftMargin: 16
		anchors.right: parent.horizontalCenter
		anchors.rightMargin: 8
		to: 100
		value: be.valueIn
		onValueChanged: be.valueIn = value
//		enabled: ! be.busy

		Text {
			id: lblSlider
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.verticalCenter: parent.bottom
			text: "var: slider ; [0 - 100 ] ; " + be.valueIn
			font.pixelSize: 12
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter
		}
	}

	ProgressBar {
		id: progressBar
		height: 40
		anchors.bottom: parent.bottom
		anchors.bottomMargin: 16
		anchors.left: parent.horizontalCenter
		anchors.leftMargin: 8
		anchors.right: parent.right
		anchors.rightMargin: 16
		to: 100
		font.pointSize: 12
		value: be.valueOut

		Text {
			id: lblProgressBar
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.verticalCenter: parent.bottom
			text: "var: result ; [0 - 100 ] ; " + be.valueOut
			font.pixelSize: 12
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter
		}
	}

	BusyIndicator {
		id: busyIndicator
		anchors.centerIn: parent
		running: be.busy
	}
}
