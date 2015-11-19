import "../SettingsPage.js" as SettingsPage

RecordSettingsRadioButton {
    property string radioButtonSettingState

    isChecked: (recProp.mode === SettingsPage.RECMODE_INDEXEX_MAP[radioButtonSettingState])
    onToggled: {
        if (isChecked) {
            recProp.mode = radioButtonSettingState;
        }
    }
}
