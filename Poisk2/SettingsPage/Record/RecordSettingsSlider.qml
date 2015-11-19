import "../SettingsPage.js" as SettingsPage

SettingSliderV2 {
    width: parent.width - parent.spacing - parent.anchors.leftMargin
           - Math.max(recModeRect.width, thresholdRect.width, autoDurationRect.width, manualDurationRect.width)
    height: cellHeight
}


