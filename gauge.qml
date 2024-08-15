import QtQuick 2.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4

Rectangle
{
    id: rectangle
    color: "#ffffff"
    width: 345
    height: 200
    objectName: "rect"

    CircularGauge {
        id: circularGauge
        objectName: "gauge"
        x: 2
        y: 17
        width: 340
        height: 282
        maximumValue: 90
        minimumValue: -90
        value: 0


        style: CircularGaugeStyle {
                minimumValueAngle: -90
                maximumValueAngle: 90
                labelStepSize: 20

                needle: Item {
                    y: -outerRadius * 0.2
                    height: outerRadius *0.8
                    x: -needle.width / 2.0
                    antialiasing: true

                    Image{
                        id: needle
                        source: "qrc:/image/suzuki-gsxr-1000-2009-vue-arriere.svg"
                        height: parent.height
                        width: height*0.3

                        asynchronous: true
                        antialiasing: true
                    }
                    }
                    Rectangle{
                        color: "#000000"
                    }
                }
    }
}
