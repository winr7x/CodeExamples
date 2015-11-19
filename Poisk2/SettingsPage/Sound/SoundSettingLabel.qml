import QtQuick 1.1

import "../Component"

Item {
    property string labelText
    width: textColumnWidth
    height: textColumnHeight

    SettingsPageLabel {
        anchors {
            bottom: parent.bottom
            bottomMargin: 10
        }
        text: labelText
    }
}
