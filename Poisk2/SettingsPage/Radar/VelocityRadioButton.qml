import "../SettingsPage.js" as SettingsPage

RadarSettingsRadioButton {
    property string radioButtonSettingState

    isChecked: (setting.velocityRange === SettingsPage.VELOCITY_INDEXES_MAP[radioButtonSettingState])
    onToggled: {
        if (isChecked) {
            setting.velocityRange = radioButtonSettingState;
        }
    }
}
