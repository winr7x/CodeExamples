import QtQuick 1.1

import "../Core.js" as Core
import "SettingsPage.js" as SettingsPage

Item {
    id: slider

    property int minimum: SettingsPage.SLIDER_MINIMUM
    property int maximim: SettingsPage.SLIDER_MAXIMUM
    property int step: SettingsPage.SLIDER_STEP

    // read/write property
    property int value: 0

    function updatePosition()
    {
        if (value >= minimum && value <= maximim) {
            var count = Math.round((maximim - minimum) / step) + 1;
            var shift = Math.round(width / count);
            var left = Math.round((value - minimum) / step) * shift;
            var pos = Math.round(left - handle.width / 2);
            handle.x = pos;
        }
    }

    width: SettingsPage.SLIDER_WIDTH
    height: 50
    onWidthChanged: updatePosition();
    onValueChanged: updatePosition();

    Rectangle {
        id: plot

        property int count: (maximim-minimum) / step + 1
        property int shift: plot.width/plot.count

        width: parent.width
        height: 30
        color: "transparent"
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            topMargin: 15
        }

        Repeater {
            anchors.bottom: plah.bottom
            model: plot.count

            Rectangle {
                x: plot.x + index * plot.shift
                z: 0
                width: 1
                height: 18
                color: "black"

                Text {
                    text: minimum + index*step
                    font {
                        family: Core.APP_FONT
                        pointSize: 9
                    }
                    anchors {
                        horizontalCenter: parent.left
                        bottom: parent.top
                    }
                }
            }
        }

        Rectangle {
            id: plah

            z: 1
            width: (plot.count - 1) * plot.shift
            height: 8
            border.color: "black"
            anchors {
                bottom: parent.bottom
                bottomMargin: 4
            }
            color: "transparent"
        }
    }

    Image {
        id: handle

        property int value: slider.minimum

        x: plot.x - width / 2
        width: 42
        height: 39
        source: "../images/handle.png"
        anchors {
            verticalCenter: plot.verticalCenter
            verticalCenterOffset: 10
        }

        MouseArea {
            id: mouse

            anchors.fill: parent;
            drag.target: parent
            drag.axis: Drag.XAxis;
            drag.minimumX: plot.x - handle.width / 2
            drag.maximumX: drag.minimumX + (plot.count - 1) * plot.shift
            onPositionChanged: handle.value = (slider.maximim - slider.minimum) * (handle.x + handle.width / 2)
                               / ((plot.count - 1) * plot.shift) + slider.minimum;
            onReleased: slider.value = handle.value
        }
    }
}
