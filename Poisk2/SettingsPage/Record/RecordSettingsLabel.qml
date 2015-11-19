import QtQuick 1.1

import "../Component"

Rectangle {
    property string labelText
    property bool isVerticallyInParentCenter: false

    width: columnWidth
    height: cellHeight
    color: "transparent"

    SettingsPageLabel {
        text: labelText
        width: parent.width
        wrapMode: Text.WordWrap
        anchors.verticalCenter: isVerticallyInParentCenter ? parent.verticalCenter : undefined;
        anchors.bottom: isVerticallyInParentCenter ? undefined : parent.bottom
    }
}
