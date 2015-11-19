import "../SettingsPage.js" as SettingsPage

RadarSettingsRadioButton {
    property string radioButtonSettingState

    radioButtonCaption: radioButtonSettingState.toLowerCase();
    isChecked: (setting.sensivity === SettingsPage.SENSITIVITY_INDEXES_MAP[radioButtonSettingState])
    onToggled: {
        if (isChecked) {
            setting.sensivity = radioButtonSettingState;
        }
    }
}
