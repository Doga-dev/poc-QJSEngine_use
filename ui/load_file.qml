import QtQuick 2.0
import QtQuick.Dialogs 1.0

FileDialog {
	id: fileDialog
	title: "Please choose a file"
	folder: shortcuts.home

	signal fileSelected(string fileName);

	onAccepted: {
//		console.log("You chose: " + fileDialog.fileUrls);
		close();
		fileSelected(fileDialog.fileUrls);
	}
	onRejected: {
		console.log("Canceled");
		close();
	}
}
