import QtQuick 1.1

import "../../Core.js" as Core

import "../SettingsPage.js" as SettingsPage

Item {
    id: slider

    property int minimum: SettingsPage.SLIDER_MINIMUM
    property int maximim: SettingsPage.SLIDER_MAXIMUM
    property int step: SettingsPage.SLIDER_STEP
    property int value: 50 //read-write

    function updatePosition()
    {
        var val = value;
        handle.x = position(val);
    }

    function position(val)
    {
        return (val - minimum) * width / (maximim - minimum) - handle.width / 2;
    }

    width: scaledWidth(SettingsPage.SLIDER_WIDTH)
    height: scaledHeigh(60)
    onWidthChanged: updatePosition()
    onValueChanged: updatePosition()

    Rectangle {
        x: parent.width - 1
        width: 1
        height: slider.height / 2
        anchors {
            bottom: parent.bottom
            bottomMargin: 6
        }
        color: "black"

        Text {
            anchors {
                bottom: parent.top
                bottomMargin: 6
                horizontalCenter: parent.horizontalCenter
            }
            text: maximim
        }
    }

    Rectangle {
        x: -1;
        anchors {
            bottom: parent.bottom
            bottomMargin: 6
        }
        width: 1
        height: slider.height / 2
        color: "black"

        Text {
            anchors {
                bottom: parent.top
                bottomMargin: 6
                horizontalCenter: parent.horizontalCenter
            }
            text: minimum
        }
    }

    Row {
        id: ruleRow

        property int count: (slider.maximim - slider.minimum)/slider.step;
        property real fcount: (slider.maximim - slider.minimum)/slider.step;
        property real shift: Math.floor(slider.width/fcount);

        anchors.fill: parent

        Repeater {
            model: ruleRow.count - 1

            Item {
                width: ruleRow.shift
                height: slider.height

                Rectangle {
                    anchors {
                        bottom: parent.bottom
                        bottomMargin: 6
                        right: parent.right
                    }
                    width: 1
                    height: slider.height / 2
                    color: "black"

                    Text {
                        anchors {
                            bottom: parent.top
                            bottomMargin: 6
                            horizontalCenter: parent.horizontalCenter
                        }
                        text: minimum + (index + 1) * step
                    }
                }
            }
        }
    }

    Rectangle {
        id: plah

        x: -1
        width: ruleRow.width
        height: 6
        anchors.bottom: parent.bottom
        color: "transparent"
        border {
            color: "black"
            width: 1
        }
    }

    Image {
        id: handle

        property double value: slider.minimum

        x: -width / 2
        width: scaledWidth(42)
        height: scaledHeigh(40)
        source: "../../images/handle.png"
        anchors.verticalCenter: plah.verticalCenter
        smooth: true

        MouseArea {
            id: mouse

            function getValue()
            {
                return Math.ceil((slider.maximim - slider.minimum) * (handle.x + handle.width / 2) / slider.width)
                        + slider.minimum
            }

            anchors.fill: parent;
            drag.target: parent
            drag.axis: Drag.XAxis;
            drag.minimumX: -handle.width / 2
            drag.maximumX: slider.width - handle.width / 2
            onPositionChanged: {
                handle.value = getValue();
                textRect.visible = true;
            }
            onReleased: {
                slider.value = handle.value;
                textRect.visible = false;
            }
            onExited: {
                slider.value = handle.value;
                textRect.visible = false;
            }
        }
    }

    Rectangle {
        id: textRect

        color: "white"
        opacity: 0.8
        radius: 10
        border {
            width: 4
            color: "lightgray"
        }
        width: handle.width * 1.2
        height: handle.height
        anchors {
            bottom: handle.top
            bottomMargin: 10
            horizontalCenter: handle.horizontalCenter
        }
        visible: false
    }

    Text {
        id: valueText

        anchors.centerIn: textRect
        text: handle.value
        visible: textRect.visible
        font {
            family: Core.APP_FONT
            pointSize: 14
        }
    }
}
