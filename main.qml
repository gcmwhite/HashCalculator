import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.3
import app.HashTool 1.0

Window {
    width: 930
    height: 420
    visible: true
    title: "文件Hash计算器"

    onWidthChanged: console.log("width:",width)
    onHeightChanged: console.log("height:",height)
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5
        RowLayout {
            Layout.fillWidth: true
            Label {
                text: "计算方式："
            }

            CheckBox {
                id: md5CheckBox
                text: "MD5"
                checked: true
            }
            CheckBox {
                id: sha256CheckBox
                text: "SHA256"
                checked: true
            }
        }
        RowLayout {
            Layout.fillWidth: true
            Label {
                id: fileNameLabel
                leftPadding: 5
                rightPadding: 5
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                Layout.fillWidth: true
                Layout.preferredHeight: selectFileButton.height
                background: Rectangle {
                    border { color: "gray"; width: 1 }
                }
                ToolTip {
                    id: toolTip
                    text: parent.text
                    delay: 1000
                    timeout: 5000
                }
                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: toolTip.visible = true
                    onExited: toolTip.visible = false
                }
            }
            Button {
                id: selectFileButton
                text: "..."
                Layout.preferredWidth: 50
                onClicked: fileDialog.open()
                hoverEnabled: true
                ToolTip.text: "打开文件"
                ToolTip.visible: hovered
                ToolTip.delay: 1000
                ToolTip.timeout: 5000
            }
            Button {
                id: startBtn
                text: "计算"
                Layout.preferredWidth: 80
                onClicked: hashTool.start(fileNameLabel.text,md5CheckBox.checked,sha256CheckBox.checked)
            }
        }
        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            TextArea {
                id: logTextArea
                wrapMode: TextEdit.WrapAnywhere
                background: Rectangle {
                    border { color: "gray"; width: 1 }
                }
            }
        }
    }

    function appendMsg(msg) {
        logTextArea.append(new Date().toLocaleString(Qt.locale(),"[yyyy-MM-dd HH:mm:ss.zzz] ") + msg + "\r\n");
    }

    FileDialog {
        id: fileDialog
        title: "请选择一个文件"
        onAccepted: {
            fileNameLabel.text = fileUrl.toString().substring(8)
            appendMsg("选择文件：" + fileNameLabel.text)
        }
    }

    HashTool {
        id: hashTool
        onSignalMsg: appendMsg(msg)
    }

}
