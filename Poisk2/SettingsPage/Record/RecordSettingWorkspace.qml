import QtQuick 1.1
import QtDesktop 0.1
import com.simicon.qmlcomponents 1.0

import "../../Core.js" as Core
import "../../Components"

import "../SettingsPage.js" as SettingsPage
import "../Component"

SettingsPageWorkspace {
    id: workspace

    property int columnWidth: SettingsPage.SLIDER_WIDTH
    property int cellHeight: scaledWidth(60)
    property int visibleComPortsInList: 2

    function tryUpdateComPorts ()
    {
        if (visible === true) {
            cppComPortModel.updateModel ();
        }
    }

    width: 1235
    height: 508
    color: Core.APP_NON_SELECTION_COLOR
    border {
        width: Core.APP_THIN_BORDER_WIDTH
        color: Core.APP_BORDER_COLOR
    }

    onVisibleChanged: tryUpdateComPorts ()

    RecordProperty {
        id: recProp

        objectName: "RecordSettingProperty"
        threshold: thresholdSlider.value
        durationAutoRecord: durationdSlider.value
        durationManualRecord: manRecordSlider.value
    }

    Grid {
        columns: 2
        rows: 5

        anchors {
            fill: parent
            leftMargin: SettingsPage.MARGIN
            topMargin: SettingsPage.MARGIN
        }
        spacing: 15

        RecordSettingsLabel {
            id: recModeRect

            labelText: qsTr("Recording mode");
            isVerticallyInParentCenter: true
        }
        Rectangle {
            id: groupButton

            width: columnWidth
            height: cellHeight
            color: "transparent"

            Row {
                anchors {
                    left: parent.left
                    verticalCenter: parent.verticalCenter
                }
                spacing: 50

                RecModeRadioButton {
                    id: manual

                    radioButtonSettingState: SettingsPage.MANUAL_RECMODE
                    radioButtonCaption: qsTr("Manual")
                    onToggled: auto.isChecked = !isChecked;
                }

                RecModeRadioButton {
                    id: auto

                    radioButtonSettingState: SettingsPage.AUTO_RECMODE;
                    radioButtonCaption: qsTr("Auto")
                    onToggled: manual.isChecked = !isChecked;
                }
            }
        }

        RecordSettingsLabel {
            id: thresholdRect

            labelText: qsTr("The threshold speed for the automatic recording (km/h)")
        }
        RecordSettingsSlider {
            id: thresholdSlider

            value: recProp.threshold
            maximim: 220
            onValueChanged: recProp.setTreshold(value);
        }

        RecordSettingsLabel {
            id: autoDurationRect

            labelText: qsTr("Duration of automatic recording (sec)");
        }
        RecordSettingsSlider {
            id: durationdSlider

            value: recProp.durationAutoRecord
            onValueChanged: recProp.setDurationAutoRecord(value);
        }

        RecordSettingsLabel {
            id: manualDurationRect

            labelText: qsTr("Duration of manual recording (sec)")
        }
        RecordSettingsSlider {
            id: manRecordSlider

            value: recProp.durationManualRecord
            onValueChanged: recProp.setDurationManualRecord(value);
        }

        RecordSettingsLabel {
            id: comPortComboBox

            labelText: qsTr("GPS COM port")
        }

        Row {
            spacing: 1

            Rectangle {
                id: comPortList

                width: 100
                height: 70
                border {
                    color: Core.APP_BORDER_COLOR
                    width: 1
                }

                Component {
                    id: comPortDelegate

                    Rectangle {
                        width: comPortList.width
                        anchors.horizontalCenter: parent.horizontalCenter
                        height: Math.round(comPortList.height / visibleComPortsInList)
                        border {
                            color: Core.APP_SELECTION_COLOR
                            width: Core.APP_THIN_BORDER_WIDTH
                        }
                        color: (itemView.currentIndex === index) ? Core.APP_SELECTION_COLOR : "white"

                        smooth: true

                        Text {
                            anchors {
                                left: parent.left
                                verticalCenter: parent.verticalCenter
                                leftMargin: 8
                            }

                            text: PortName
                            font.pointSize: 16
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                if (index !== itemView.currentIndex) {
                                    itemView.currentIndex = index;
                                }
                            }
                        }
                    }
                }

                ListView {
                    id: itemView

                    function itemIndex ()
                    {
                        var result = -1;
                        for (var i = 0; i < itemView.count; ++i) {
                            if (itemView.model.portName (i) === recProp.comPort) {
                                result =  i;
                            }
                        }

                        return result;
                    }

                    function triggerToNewPort () {

                        if (currentIndex >= 0) {
                            GpsConnection.reconnect (model.portName (currentIndex));
                            recProp.comPort = model.portName (currentIndex);
                        }
                    }

                    width: parent.width
                    height: parent.height

                    currentIndex: itemIndex();
                    clip: true
                    cacheBuffer: 180
                    boundsBehavior: Flickable.StopAtBounds
                    model: cppComPortModel
                    delegate: comPortDelegate

                    onCurrentIndexChanged: triggerToNewPort ();
                }
            }

            Rectangle {
                id: scroll

                width: 30
                height: parent.height
                color: "#ebebeb"

                Text {
                    anchors {
                        top: parent.top
                        horizontalCenter: parent.horizontalCenter
                    }
                    font.pixelSize: 30
                    text: "▲"

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            itemView.decrementCurrentIndex();
                        }
                    }
                }

                Text {
                    anchors {
                        bottom: parent.bottom
                        horizontalCenter: parent.horizontalCenter
                    }
                    font.pixelSize: 30
                    text: "▼"

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            itemView.incrementCurrentIndex();
                        }
                    }
                }
            }
            
            Rectangle {
                id: trafficLight

                property int lampsCount: 3

                width: height / lampsCount
                height: parent.height
                color: "black"
                radius: 2

                Column {
                    id: bulbs
    
                    function stateName () {
                        var result = "disconnected";
    
                        if (GpsConnection.connectionState === 1) {
                            result = "invalidFix";
                        } else if (GpsConnection.connectionState === 2) {
                            result = "validFix";
                        }
    
                        return result;
                    }
    
                    property int sideWidth: (parent.height - spacing * (trafficLight.lampsCount - 1)) / trafficLight.lampsCount
                    property int cornerRadius: sideWidth / 2
                    property string redDark: "#400000"
                    property string yellowDark: "#404000"
                    property string greenDark: "#004000"
    
                    anchors {
                        horizontalCenter: parent.horizontalCenter
                    }
                    spacing: 3
                    state: stateName ()
    
                    BulbRectangle { id: redBulb }
                    BulbRectangle { id: yellowBulb }
                    BulbRectangle { id: greenBulb }
                    
                    states: [
                        State {
                            name: "disconnected"
                            PropertyChanges { target: redBulb; color: "red"}
                            PropertyChanges { target: yellowBulb; color: bulbs.yellowDark}
                            PropertyChanges { target: greenBulb; color:  bulbs.greenDark}
                        },
                        State {
                            name: "invalidFix"
                            PropertyChanges { target: redBulb; color: bulbs.redDark}
                            PropertyChanges { target: yellowBulb; color: "yellow"}
                            PropertyChanges { target: greenBulb; color:  bulbs.greenDark}
                        },
                        State {
                            name: "validFix"
                            PropertyChanges { target: redBulb; color: bulbs.redDark}
                            PropertyChanges { target: yellowBulb; color: bulbs.yellowDark}
                            PropertyChanges { target: greenBulb; color:  "lime"}
                        }
                    ]
                }
            }
        }
    }
}
