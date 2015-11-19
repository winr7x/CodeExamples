import QtQuick 1.1
import com.simicon.qmlcomponents 1.0

import "../../Core.js" as Core
import "../../Components"
import "."

import "../SettingsPage.js" as SettingsPage
import "../Component"

SettingsPageWorkspace {
    id: radarSettingsWs

    property int col1Width: scaledWidth(400)
    property int col2Width: radioItemWidth * 3
    property int radioItemWidth: 160

    property bool visibleMeasurerInfo: false

    width: 1196
    height: 508
    color: Core.APP_NON_SELECTION_COLOR
    border {
        width: Core.APP_THIN_BORDER_WIDTH
        color: Core.APP_BORDER_COLOR
    }

    RadarProperty {
        id: setting

        objectName: "RadarSettingBinding"
    }

    Connections {
        target: app
        onConnectedToDevice: visibleMeasurerInfo = isConnected;
    }

    Grid {
        width: parent.width
        columns: 2
        rows: 4
        anchors {
            fill: parent
            topMargin: SettingsPage.MARGIN
            leftMargin: SettingsPage.MARGIN
        }
        spacing: 30

        RadarSettingHideableLabel { columnNumber: 1; labelText: qsTr("Measurer"); }
        RadarSettingHideableLabel { columnNumber: 2; labelText: "RCF3 v. 0.78" }

        RadarSettingHideableLabel { columnNumber: 1; labelText: qsTr("Check-sum firmware measurer") }
        RadarSettingHideableLabel { columnNumber: 2; labelText: "82960633" }

        RadarSettingLabel {
            columnNumber: 1
            labelText: qsTr("Velocity range")
            visible: false
        }
        ItemWithRadioButtons {
            visible: false
            radioButtons: [
                VelocityRadioButton {
                    id: range1

                    radioButtonSettingState: SettingsPage.V_10_300
                    radioButtonCaption: qsTr("10-300 km/h")
                    onToggled: range2.isChecked = !isChecked;
                },
                VelocityRadioButton {
                    id: range2

                    radioButtonSettingState: SettingsPage.V_30_240
                    radioButtonCaption: qsTr("30-240 km/h")
                    onToggled: range1.isChecked = !isChecked;
                }
            ]
        }

        RadarSettingLabel {
            columnNumber: 1
            labelText: qsTr("Sensitivity of the radar")
        }
        ItemWithRadioButtons {
            radioButtons: [
                SensitivityRadioButton {
                    id: rowRadioItem1

                    radioButtonSettingState: SettingsPage.LOW_SENSITIVITY
                    onToggled: {
                        rowRadioItem2.isChecked = !isChecked;
                        rowRadioItem3.isChecked = false;
                    }
                },
                SensitivityRadioButton {
                    id: rowRadioItem2

                    radioButtonSettingState: SettingsPage.MEDIUM_SENSITIVITY
                    onToggled: {
                        rowRadioItem1.isChecked = !isChecked;
                        rowRadioItem3.isChecked = false;
                    }
                },
                SensitivityRadioButton {
                    id: rowRadioItem3

                    radioButtonSettingState: SettingsPage.HIGH_SENSITIVITY
                    onToggled: {
                        rowRadioItem1.isChecked = !isChecked;
                        rowRadioItem2.isChecked = false;
                    }
                }
            ]
        }
    }

    SmoothArea {
        id: smoothArea
    }
}
