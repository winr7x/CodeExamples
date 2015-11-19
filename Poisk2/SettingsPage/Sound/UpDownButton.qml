import "../../Components"

AppUpDownButton {
    width: scaledWidth(70)
    height: parent.height
    onClicked: view.move(text)
}
