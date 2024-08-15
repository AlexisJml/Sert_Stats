import QtQuick 2.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4

//initialise un rectangle
Rectangle {
    width: 20
    height: 80
    color: "#201d1d"
    objectName: "rect"

    //initialise une jauge
    Gauge {
        objectName: "gauge"
        id: gauge1
        anchors.fill: parent
        anchors.margins: 10
        maximumValue: 10
        minimumValue: -10
        value: 0.1

        formatValue: function(value) {
            return value.toFixed(0);
        }
        //défini le style de la jauge
        style:GaugeStyle{
            valueBar: Item{
                implicitWidth: 16
                Rectangle{
                    width: parent.width
                    height: {
                        //si la valeur est positive
                        if(gauge1.value >=0){

                            anchors.top = parent.top
                            anchors.bottom = parent.Center

                            var maxSpan = Math.abs(gauge1.maximumValue) + Math.abs(gauge1.minimumValue)

                            //pour pouvoir aperçevoir où se situe la jauge si la valeur est égal à 0
                            if(gauge1.value == 0){
                                var fill = Math.abs(0.1)
                            }
                            else{
                                fill = Math.abs(gauge1.value)
                            }

                            var fillPercent = fill/maxSpan

                            var fillHeight = gauge1.height * fillPercent

                            return fillHeight - fillHeight/50
                        }
                        //si la valeur est négative
                        if(gauge1.value < 0){

                            anchors.top = parent.Center

                            maxSpan = Math.abs(gauge1.maximumValue) + Math.abs(gauge1.minimumValue)
                            fill = Math.abs(gauge1.value)
                            fillPercent = fill/maxSpan

                            fillHeight = gauge1.height * fillPercent
                            y = -height

                            return fillHeight - fillHeight/50
                        }
                        }
                    /*Component.onCompleted: {
                            if (gauge1.value < 0) {
                                y = -height
                            }
                    }*/
                }
            }
        }
    }
}
