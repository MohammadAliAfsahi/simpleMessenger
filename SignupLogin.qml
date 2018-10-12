import QtQuick 2.4
import QtQuick.Controls 2.2
import com.company.startpage 1.0

ApplicationWindow {

    visible: true
    width: 640
    height: 480
    title: qsTr("Wellcome")
    StartPage {
        id:startpage
    }

    SignupLoginForm {
        Button {
            id: loginbtn
            x: 99
            y: 184
            text: qsTr("Login")
            hoverEnabled: true
            highlighted: true
            onClicked: {
                console.log("LoginBtn Clicked")


            }
        }

    }
}
