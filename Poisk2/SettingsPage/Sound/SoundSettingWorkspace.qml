import QtQuick 1.1
import QtDesktop 0.1
import com.simicon.qmlcomponents 1.0

import "../../Core.js" as Core
import "../../Components"
import "../../TestData"

import "../Component"

SettingsPageWorkspace {
    id: workspace

    property int textColumnWidth: 480
    property int textColumnHeight: 40

    property int tableRowHeight: scaledHeigh(40)

    AppDialogWindow {
        id: selectSoundDirWindow

        windowFrameText: qsTr("Selection directory")
        onVisibleChanged: {
            selectSoundDir.open = visible;
        }

        SoundSettingFileDialog {
            id: selectSoundDir

            onlyDir: true
            root: sounOption.dir
            onCanceled: selectSoundDirWindow.visible = false;
            onSelected: {
                sounOption.dir = path;
                selectSoundDirWindow.visible = false;
            }
        }
    }

    AppDialogWindow {
        id: selectSoundFileWindow

        windowFrameText: qsTr("Select a file")
        onVisibleChanged: {
            selectSoundFile.open = visible;
        }

        SoundSettingFileDialog {
            id: selectSoundFile

            root: settingsStorage.workPath ()
            onCanceled: selectSoundFileWindow.visible = false;
            onSelected: {
                cppSoundBaseModel.setFileName(view.currentIndex, path);
                soundPanel.enableSoundButtons ();
                selectSoundFileWindow.visible = false;
            }
        }
    }

    SoundProperty {
        id: sounOption

        objectName: "SountSettingBinding"
    }

    Rectangle {
        id: soundPanel

        signal disableSoundButtons
        signal enableSoundButtons

        function activatePlayButton (button, mouseArea)
        {
            mouseArea.enabled = true;
            button.state = "enable";
        }

        function deactivatePlayButton (button, mouseArea)
        {
            mouseArea.enabled = false;
            button.state = "disable";
        }

        anchors.fill: parent
        
        Rectangle {
            id: soundRec

            width: 590
            height: parent.height
            color: Core.APP_NON_SELECTION_COLOR
            border {
                width: Core.APP_THIN_BORDER_WIDTH
                color: Core.APP_BORDER_COLOR
            }

            Column {
                anchors {
                    fill: parent
                    leftMargin: 10
                    rightMargin: 10
                    topMargin: 10
                }
                spacing: 20

                Grid {
                    columns: 3
                    rows: 3
                    spacing: 0

                    SoundSettingLabel { labelText: qsTr("The sound of sirens") }
                    CheckBoxItem {
                        id: sirens

                        togle: sounOption.sirens
                        onTogled: sounOption.sirens = value;
                    }
                    TestSoundButton {
                        id: testSirenButton

                        state: fileUtils.fileExist(warningSpeedingFileName) ? "enable" : "disable"

                        MouseArea {
                            id: testSirenMouseArea

                            anchors.fill: parent
                            enabled: fileUtils.fileExist(warningSpeedingFileName)
                            onClicked: {
                                soundPanel.disableSoundButtons ();
                                app.playWarningSpeedingSound();
                            }
                        }

                        Connections {
                            target: app
                            onSpeakFinished: soundPanel.enableSoundButtons();
                        }

                        Connections {
                            target: soundPanel
                            onDisableSoundButtons: {
                                soundPanel.deactivatePlayButton(testSirenButton, testSirenMouseArea);
                            }
                            onEnableSoundButtons: {
                                if (fileUtils.fileExist(warningSpeedingFileName)) {
                                    soundPanel.activatePlayButton(testSirenButton, testSirenMouseArea);
                                }
                            }
                        }
                    }

                    SoundSettingLabel { labelText: qsTr("Pronunciation of the name of the database") }
                    CheckBoxItem {
                        togle: sounOption.pronunciationBase
                        onTogled: sounOption.pronunciationBase = value;
                    }
                    TestSoundButton {
                        id: testDatabasePronunciationButton

                        MouseArea {
                            id: testDatabasePronunciationMouseArea

                            anchors.fill: parent
                            onClicked: {
                                soundPanel.disableSoundButtons ();
                                app.playTestSpeechOfDatabase();
                            }
                        }

                        Connections {
                            target: app
                            onSpeakFinished: soundPanel.enableSoundButtons();
                        }
                        
                        Connections {
                            target: soundPanel
                            onDisableSoundButtons: {
                                soundPanel.deactivatePlayButton(testDatabasePronunciationButton, testDatabasePronunciationMouseArea);
                            }
                            onEnableSoundButtons: {
                                soundPanel.activatePlayButton(testDatabasePronunciationButton, testDatabasePronunciationMouseArea);
                            }
                        }
                    }

                    SoundSettingLabel { labelText: qsTr("Pronunciation of the names of numbers") }
                    CheckBoxItem {
                        togle: sounOption.pronunciationNumber
                        onTogled: sounOption.pronunciationNumber = value;
                    }
                    TestSoundButton {
                        id: testNumberPronunciationButton

                        MouseArea {
                            id: testNumberSpeakingMouseArea

                            anchors.fill: parent
                            onClicked: {
                                soundPanel.disableSoundButtons ();
                                app.playTestSpeechNumber();
                            }
                        }

                        Connections {
                            target: app
                            onSpeakFinished: soundPanel.enableSoundButtons();
                        }

                        Connections {
                            target: soundPanel
                            onDisableSoundButtons: soundPanel.deactivatePlayButton(testNumberPronunciationButton, testNumberSpeakingMouseArea);
                            onEnableSoundButtons: soundPanel.activatePlayButton(testNumberPronunciationButton, testNumberSpeakingMouseArea);
                        }
                    }
                }

                Column {
                    width: parent.width

                    spacing: 10
                    SettingsPageLabel {
                        text: qsTr("Directory with sound files")
                    }

                    Row {
                        spacing: 15
                        width: parent.width

                        LineEdit {
                            id: soundPath

                            text: sounOption.dir
                            width: textColumnWidth
                            height: scaledHeigh(30)
                            readOnly: true
                            font {
                                pixelSize: 19
                                family: Core.APP_FONT
                            }
                        }

                        IconButton {
                            id: openFolderButton

                            iconSourceEnable: "../images/folder.png"
                            iconSourceDisable: "../images/folderOff.png"
                            iconWidth: 42
                            iconHeight: 44
                            anchors.verticalCenter: soundPath.verticalCenter
                            onClicked: selectSoundDirWindow.visible = true;
                        }
                        
                        Connections {
                            target: soundPanel
                            onEnableSoundButtons: {
                                openFolderButton.enabled = true;
                                openFolderButton.state = "enable";
                            }
                            onDisableSoundButtons: {
                                openFolderButton.enabled = false;
                                openFolderButton.state = "disable";
                            }
                        }
                    }
                }
            }
        }

        Rectangle {
            id: soundBaseTableRec

            height: parent.height
            color: Core.APP_NON_SELECTION_COLOR
            border {
                width: Core.APP_THIN_BORDER_WIDTH
                color: Core.APP_BORDER_COLOR
            }
            anchors {
                left: soundRec.right
                leftMargin: 10
                right: parent.right
            }

            Column {
                anchors {
                    fill: parent
                    leftMargin: 1
                    topMargin: 1
                }

                TableView {
                    id: view

                    function move(direction)
                    {
                        verticalScrollBar.value = verticalScrollBar.value + verticalScrollBar.pageStep
                                * (direction === "▲" ? -1 : 1);
                    }

                    width: parent.width
                    height: parent.height - buttonGroup.height
                    horizontalScrollBar.visible: false
                    verticalScrollBar.visible: false
                    alternateRowColor: true
                    frame: false
                    model: cppSoundBaseModel

                    SounSettingsTableColumn {
                        role: "dbName"
                        title: qsTr("BASE")
                    }

                    SounSettingsTableColumn {
                        role: "soundFile"
                        title: qsTr("AUDIO FILE")
                    }

                    headerDelegate: Rectangle {
                        anchors.fill: parent
                        color: Core.APP_NON_SELECTION_COLOR

                        Text {
                            text: itemValue
                            anchors {
                                left: parent.left
                                verticalCenter: parent.verticalCenter
                                leftMargin: 10
                            }
                            color: "black"
                            font {
                                family: Core.APP_FONT
                                pointSize: 11
                                bold: true
                            }
                        }
                    }

                    rowDelegate: Rectangle {
                        x: -1
                        width: view.width + 1
                        color: itemSelected ? Core.APP_SELECTION_COLOR : "white"
                        border {
                            color: Core.APP_BORDER_COLOR
                            width: Core.APP_THIN_BORDER_WIDTH
                        }
                    }

                    itemDelegate: Item {
                        id: ceil

                        width: view.width / 2
                        height: tableRowHeight
                        anchors.fill: parent

                        Text {
                            id: label

                            anchors.margins: Core.APP_ITEM_DELEGATE_MARGIN
                            anchors.left: parent.left
                            anchors.rightMargin: 10
                            anchors.verticalCenter: parent.verticalCenter
                            width: ceil.width - button.width - testButton.width - anchors.rightMargin
                            elide: Text.ElideRight
                            text: itemValue /*? itemValue : ""*/
                            color: itemSelected ? "white" : "black"
                            font {
                                family: Core.APP_FONT
                                pointSize: Core.APP_ITEM_DELEGATE_TEXT_SIZE
                            }
                        }
                        ImgButton {
                            id: button

                            width: scaledWidth(18)
                            height: parent.height - 2
                            iconSource: "../images/edit.svg"
                            iconWidth: Core.APP_EDIT_ICON_SIZE
                            iconHeight: Core.APP_EDIT_ICON_SIZE
                            anchors {
                                verticalCenter: label.verticalCenter
                                right: testButton.left
                                rightMargin: 6
                            }
                            backgroundColor: itemSelected ? Core.APP_SELECTION_COLOR : "white"
                            borderColor: itemSelected ? Core.APP_SELECTION_COLOR : "white"
                            border.width: 0
                            text: ""
                            visible: (columnIndex === 1)
                        }
                        TestSoundButton {
                            id: testButton

                            state: fileUtils.fileExist (itemValue) ? "enable" : "disable"
                            iconSize: button.height
                            anchors {
                                verticalCenter: label.verticalCenter
                                right: parent.right
                            }
                            visible: (columnIndex === 1)
                        }

                        MouseArea {
                            id: databaseFileSelectionMouseArea

                            anchors {
                               top: parent.top
                               bottom: parent.bottom
                               left: parent.left
                               right: testButton.left
                            }

                            onClicked: {
                                view.currentIndex = rowIndex
                                selectSoundFile.root = fileUtils.fileExist(itemValue)
                                                        ? pathProvider.path(itemValue)
                                                        : settingsStorage.workPath();
                                selectSoundFileWindow.visible = true
                            }

                            Connections {
                                target: soundPanel
                                onDisableSoundButtons: databaseFileSelectionMouseArea.enabled = false
                                onEnableSoundButtons: databaseFileSelectionMouseArea.enabled = true;
                            }
                        }
                        
                        MouseArea {
                            id: testButtonMouseArea
                            
                            anchors.fill: testButton
                            onClicked: {
                                if (fileUtils.fileExist(itemValue)) {
                                    soundPanel.disableSoundButtons ();
                                    app.playSoundFile(itemValue);
                                }
                            }
                        }
                        
                        Connections {
                            target: app
                            onSpeakFinished: soundPanel.enableSoundButtons ();
                        }
                        
                        Connections {
                            target: soundPanel
                            onDisableSoundButtons: soundPanel.deactivatePlayButton(testButton, testButtonMouseArea);
                            onEnableSoundButtons: {
                                if (fileUtils.fileExist(itemValue)) {
                                    soundPanel.activatePlayButton(testButton, testButtonMouseArea);
                                }
                            }
                        }
                    }
                }

                Rectangle {
                    id: buttonGroup

                    width: parent.width
                    height: tableRowHeight
                    color: Core.APP_NON_SELECTION_COLOR
                    anchors {
                        left: parent.left
                        leftMargin: -1
                        right: parent.right
                        rightMargin: 0
                    }
                    border {
                        color: Core.APP_BORDER_COLOR
                        width: Core.APP_THIN_BORDER_WIDTH
                    }

                    UpDownButton {
                        text: "▲"
                        anchors.right: down.left
                    }

                    UpDownButton {
                        id: down

                        text: "▼"
                        anchors.right: parent.right
                    }
                }
            }
        }
    }

    SmoothArea {
        id: smoothArea
    }

    SettingsStorage {
        id: settingsStorage
    }
}
