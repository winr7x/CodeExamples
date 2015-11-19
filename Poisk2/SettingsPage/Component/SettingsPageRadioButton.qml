import QtQuick 1.1

import "../../Core.js" as Core
import "../../Components"

Item {
    property alias isChecked: radioButtonId.togle;
    property string radioButtonCaption;

    signal toggled(bool isChecked)

    Component.onCompleted: radioButtonId.toggled.connect(toggled)

    Row {
        spacing: 10
        anchors.fill: parent
        RadioButton {
            id: radioButtonId

            togle: isChecked
            anchors.verticalCenter: parent.verticalCenter
        }

        SettingsPageLabel {
            anchors.verticalCenter: parent.verticalCenter
            text: radioButtonCaption
        }
    }
}

