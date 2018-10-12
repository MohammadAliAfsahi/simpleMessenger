import QtQuick 2.4
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.2
import com.company.startpage 1.0

Item {
    id: item1
    width: 400
    height: 400

    //    header: Label {
    //        text: qsTr("Page 1")
    //        font.pixelSize: Qt.application.font.pixelSize * 2
    //        padding: 10
    //    }
    Button {
        id: loginbtn
        x: 99
        y: 184
        text: qsTr("Login")
        hoverEnabled: true
        highlighted: true
        onClicked:item1.visible = false
    }

    Button {
        id: signupbtn
        x: 263
        y: 184
        text: qsTr("SignUp")
        highlighted: true
        onClicked: item1.visible = false
    }
}
