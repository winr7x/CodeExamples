import QtQuick 1.1

import "../../Core.js" as Core
import "../../SettingsPage/SettingsPage.js" as SettingsPage

import "../Component"

Item {
    property string labelText
    property int columnNumber

    width: (columnNumber === 1) ? col1Width : col2Width
    height: SettingsPage.ELEMENT_HEIGHT

    SettingsPageLabel {
        text: labelText
        anchors {
            bottom: parent.bottom
            bottomMargin: SettingsPage.MARGIN
        }
    }
}
