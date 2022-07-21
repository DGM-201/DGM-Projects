<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=1300px, initial-scale=1.0, user-scalable=yes">
    <title>Greenhouse Monitoring and Controlling using IoT</title>
    <style>
        *{
            margin: 0%;
            padding: 0%;
        }
        .header{
            position: fixed;
            margin-top: 10px;
            margin-left: 175px;
            height: 100px;
            width: 1000px;
            border-radius: 30px;
            background: rgba(255, 255, 255, 0.9);
            text-align: center;
            z-index: 1;
            transition: 1s;
        }
        .header:hover{
            transform: scale(1.1);
        }
        .leftlogo{
            margin-left: 100px;
            height: 80px;
            width: 80px;
            float: left;
            padding: 10px 10px 10px 10px;
        }
        .rightlogo{
            margin-right: 100px;
            height: 80px;
            width: 80px;
            float: right;
            padding: 10px 10px 10px 10px;
        }
        .college{
            font-size: 20px;
        }
        .department{
            font-size: 20px;
            color: indigo;
        }
        .project{
            font-size: 12px;
        }
        .title{
            font-size: 20px;
            color: red;
        }
        .paragraph{
            font-size: 10px;
            font-weight: bold;
        }
        .container{
            height: 700px;
            width: 1200px;
            margin-left: 75px;
            margin-right: 75px;
            background-image: linear-gradient(to bottom right, indigo, rgb(60, 0, 100));
        }
        .body{
            position: absolute;
            height: 700px;
            width: 1200px;
        }
        .card1{
            position: relative;
            margin-top: 200px;
            margin-left: 75px;
            height: 300px;
            width: 500px;
            background-color: rgba(255, 255, 255, 0.7);
            border-radius: 20px;
            float: left;
            transition: 1s;
        }
        .card1:hover{
            transform: scale(1.1);
        }
        .card1heading{
            color: white;
            text-align: center;
            height: 30px;
            background-color: darkgreen;
            width: 150px;
            margin-left: 175px;
            border-radius: 20px 20px 20px 20px;
            margin-top: -15px;
        }
        .temperatureinfo{
            margin-top: 10px;
            margin-left: 25px;
            height: 80px;
            width: 450px;
            border-radius: 10px 10px 10px 10px;
            background-image: linear-gradient(to right, orangered, orange);
        }
        .temperatureinfo h2{
            color: white;
            padding-top: 5px;
            padding-left: 15px;
        }
        .temperatureinfo h2 span{
            font-size: larger;
            color: black;
            padding-right: 15px;
            float: right;
        }
        .humidityinfo{
            margin-top: 10px;
            margin-left: 25px;
            height: 80px;
            width: 450px;
            border-radius: 10px 10px 10px 10px;
            background-image: linear-gradient(to right, rgb(0, 174, 255), rgb(70, 70, 190));
        }
        .humidityinfo h2{
            color: black;
            padding-top: 5px;
            padding-left: 15px;
        }
        .humidityinfo h2 span{
            font-size: larger;
            color: white;
            padding-right: 15px;
            float: right;
        }
        .soilinfo{
            margin-top: 10px;
            margin-left: 25px;
            height: 80px;
            width: 450px;
            border-radius: 10px 10px 10px 10px;
            background-image: linear-gradient(to right, rgb(156, 100, 100), rgb(94, 30, 30));
        }
        .soilinfo h2{
            color: black;
            padding-top: 5px;
            padding-left: 15px;
        }
        .soilinfo h2 span{
            font-size: larger;
            color: white;
            padding-right: 15px;
            float: right;
        }
        .card2{
            position: relative;
            margin-top: 200px;
            margin-right: 75px;
            height: 300px;
            width: 500px;
            border-radius: 20px;
            background-color: rgba(255, 255, 255, 0.7);
            float: right;
            transition: 1s;
        }
        .card2:hover{
            transform: scale(1.1);
        }
        .card2heading{
            color: white;
            height: 30px;
            text-align: center;
            background-color: red;
            width: 150px;
            margin-left: 175px;
            margin-top: -15px;
            border-radius: 20px 20px 20px 20px;
        }
        .lightcontrol{
            margin-left: 25px;
            background-image: linear-gradient(to right, orangered, orange);
            margin-top: 10px;
            height: 80px;
            width: 450px;
            color: white;
            border-radius: 10px;
        }
        .lightcontrol h3{
            padding-top: 15px;
            padding-left: 15px;
            padding-right: 15px;
        }
        .fancontrol{
            margin-left: 25px;
            background-image: linear-gradient(to right, rgb(54, 78, 88), rgb(135, 181, 207));
            margin-top: 10px;
            height: 80px;
            width: 450px;
            color: white;
            border-radius: 10px;
        }
        .fancontrol h3{
            padding-top: 15px;
            padding-left: 15px;
            padding-right: 15px;
        }
        .pumpcontrol{
            margin-left: 25px;
            background-image: linear-gradient(to left, rgb(0, 174, 255), rgb(70, 70, 190));
            margin-top: 10px;
            height: 80px;
            width: 450px;
            color: white;
            border-radius: 10px;
        }
        .pumpcontrol h3{
            padding-top: 15px;
            padding-left: 15px;
            padding-right: 15px;
        }
        .status{
            color: black;
            text-align: center;
            padding-top: 3px;
        }
        .button1{
            background-color: green;
            height: 30px;
            width: 70px;
            border-radius: 25px;
            text-align: center;
            color: black;
            font-size: 15px;
            font-weight: bold;
        }
        .button1:hover{
            color: white;
            background-color: darkgreen;
        }
        .button2{
            background-color: red;
            height: 30px;
            width: 70px;
            border-radius: 25px;
            text-align: center;
            color: white;
            font-size: 15px;
            font-weight: bold;
        }
        .button2:hover{
            color: black;
            background-color: darkred;
        }
        .footer{
            width: 1200px;
            color: white;
            position: relative;
            margin-top: 600px;
            text-align: center;
            background-color: rgba(0, 0, 0, 0.8);
            font-size: smaller;
        }
    </style>
</head>
<body>
    <div class="header">
        <img class="leftlogo" src="https://vtu.ac.in/wp-content/uploads/2019/03/vtul-291x300.png" alt="vtulogo">
        <img class="rightlogo" src="https://www.rrgroupinsts.org/wp-content/uploads/2015/01/rrce_logo.png" alt="rrcelogo">
        <h1 class="college">Rajarajeswari College of Engineering</h1>
        <p class="paragraph">(NBA & NAAC Accredited; Affiliated to VTU, Belagavi; Approved by AICTE, New Delhi.)</p>
        <h1 class="department">Department of Electronics and Communication Engineering</h1>
        <h1 class="project">A final project on</h1>
        <h1 class="title">"Greenhouse Monitoring and Controlling System using IoT"</h1>
    </div>
    <div class="container">
        <div class="body">
            <div class="card1">
                <div class="card1heading">
                    <h2>Monitoring</h2>
                </div>
                <div class="temperatureinfo">
                    <h2>Temperature:<br>
                        <span class="update" id="Temperature">0&deg;C</span>
                    </h2>
                </div>
                <div class="humidityinfo">
                    <h2>Humidity:<br>
                        <span class="update" id="Humidity">0%</span>     
                    </h2>
                </div>
                <div class="soilinfo">
                    <h2>Soil Moisture:<br>
                        <span class="update" id="SoilMoisture">Reading</span>     
                    </h2>
                </div>
            </div>
            <div class="card2">
                <div class="card2heading">
                    <h2>Controlling</h2>
                </div>
                <div class="lightcontrol">
                    <h3>Turn Light
                        <button type="button" class="button1">ON</button>
                        or
                        <button type="button" class="button2">OFF</button>
                        ?
                        <br>
                        <div class="status">
                            Status: Light is currently <span id="lightstatus">OFF</span>
                        </div>
                    </h3>
                </div>
                <div class="fancontrol">
                    <h3>Turn Fan
                        <button type="button" class="button1">ON</button>
                        or
                        <button type="button" class="button2">OFF</button>
                        ?
                        <br>
                        <div class="status">
                            Status: Fan is currently <span id="fanstatus">OFF</span>
                        </div>
                    </h3>
                </div>
                <div class="pumpcontrol">
                    <h3>Turn Waterpump
                        <button type="button" class="button1">ON</button>
                        or
                        <button type="button" class="button2">OFF</button>
                        ?
                        <br>
                        <div class="status">
                            Status: Pump is currently <span id="pumpstatus">OFF</span>
                        </div>
                    </h3>
                </div>
            </div>
            <div class="footer">
                <h4>Designed and developed by:<br>
                D G M<br>
                Student, Dept. of ECE, RRCE, Bengaluru.</h4>
            </div>
        </div>
    </div>
<script>
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            var txt = this.responseText;
            var obj = JSON.parse(txt);
            document.getElementById("Temperature").innerHTML = Math.round(obj.Temperature) + "&deg;C";
            document.getElementById("Humidity").innerHTML = Math.round(obj.Humidity) + "%";
            document.getElementById("SoilMoisture").innerHTML = obj.SoilMoisture;
        }
    };
    xhttp.open("GET", "readADC", true);
    xhttp.send();
</script>
</body>
</html>
