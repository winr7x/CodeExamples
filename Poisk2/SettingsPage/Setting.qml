import QtQuick 1.1

import "../Core.js" as Core
import "../Components"

import "Sound"
import "Record"
import "Radar"

PageTopRectangle {
    id: settingPage

    PageRow {
        id: row

        ToolBox {
            id: box

            modelEl: buttomModel

            VisualItemModel {
                id: buttomModel

                ToolBoxImageButton {
                    id: soundButton

                    buttonNumber: 1
                    text: qsTr("Sound")
                    iconSource: "../images/sound.png"
                }

                ToolBoxImageButton {
                    id: recordButton

                    buttonNumber: 2
                    text: qsTr("Record")
                    iconSource: "../images/movies.png"
                }

                ToolBoxImageButton {
                    id: radarButton

                    buttonNumber: 3
                    text: qsTr("Radar")
                    iconSource: "../images/radarSett.png"
                }
            }
        }

        ToolBoxStackRectangle {
            id: stackWS

            state: Core.settingTab.SOUND_STATE

            RadarSettingWorkspace { id: radarWS }
            RecordSettingWorkspace { id: recordWS }
            SoundSettingWorkspace { id: soundWS }

            states: [
                State {
                    name: Core.settingTab.RADAR_STATE
                    PropertyChanges { target: radarWS; visible: true }
                    PropertyChanges { target: recordWS; visible: false }
                    PropertyChanges { target: soundWS; visible: false }
                },
                State {
                    name: Core.settingTab.RECORD_STATE
                    PropertyChanges { target: radarWS; visible: false }
                    PropertyChanges { target: recordWS; visible: true }
                    PropertyChanges { target: soundWS; visible: false }
                },
                State {
                    name: Core.settingTab.SOUND_STATE
                    PropertyChanges { target: radarWS; visible: false }
                    PropertyChanges { target: recordWS; visible: false }
                    PropertyChanges { target: soundWS; visible: true }
                }
            ]
        }
    }

    AppKeyboardButton {}
}
