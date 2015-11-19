import QtQuick 1.1

import "../SettingsPage.js" as SettingsPage

Item {
    property alias radioButtons: radioButtonsRow.data;

    width: col2Width
    height: SettingsPage.ELEMENT_HEIGHT

    Row {
        id: radioButtonsRow

        anchors {
            left: parent.left
            verticalCenter: parent.verticalCenter
        }
        spacing: 80
    }
}
