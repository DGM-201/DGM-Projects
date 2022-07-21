<!DOCTYPE html>
<html>
<head>
<title>WeatherMonitoringSystemWebpage</title>
</head>
<style>
*{margin: 0;padding: 0;}
 
body{
  background: #ffffff;
  background-image: url('https://vtu.ac.in/wp-content/uploads/2019/03/vtul-291x300.png'), url('https://www.rrgroupinsts.org/wp-content/uploads/2015/01/rrce_logo.png');
  background-repeat: no-repeat, no-repeat;
  background-size: 100px 100px, 100px 100px;
  background-position: 20% 0px, 80% 0px;
  font-family:Montserrat,Arial,sans-serif;
}

h1{
  font-size:20px;
  font-family: "Times New Roman", Times, serif;
  text-align: center;
  color: #000000;
}

h2{
  font-size:18px;
  font-weight:600;
  color:#811600;
}

h3{
  font-size:10px;
  font-family: "Times New Roman", Times, serif;
  text-align: center;
  color:#000000;
}

h4{
  font-size:20px;
  font-family: "Times New Roman", Times, serif;
  text-align: center;
  color: #800080;
}

h5{
  font-size: 20px;
  font-family: "Times New Roman", Times, serif;
  text-align: center;
  color: #ff0000;
  }
  
p{
  font-size: 16px;
  font-weight: 900;
  position: absolute;
  bottom: 30px;
  font-family: "Times New Roman", Times, serif;
  color: #000000;
}

.widget{
  box-shadow:0 40px 10px 5px rgba(0,0,0,0.4);
  margin:45px auto;
  height: 350px;
  position: relative;
  width: 550px;
}

.upper{
  border-radius:5px 5px 0 0;
  background:#87ceeb;
  height:200px;
  padding:20px;
}

.date{
  font-size:40px;
}

.year{
  font-size:25px;
  color:#ffff00;
}
.place{
  color:#ff7700;
  font-size:40px;
}
.lower{
  background:#00bf00;
  border-radius:0 0 5px 5px;
  font-family:'Roboto';
  font-weight:500;
  height:120px;
  width:100%;
}
.clock{
  background:#fdb813;
  border-radius:100%;
  box-shadow:0 0 0 2px #f5f5f5,0 10px 10px 5px rgba(0,0,0,0.3);
  height:150px;
  position:absolute;
  right:25px;
  top:-35px;
  width:150px;
}
 
.hour{
  background:#f5f5f5;
  height:50px;
  left:50%;  
  position: absolute;
  top:25px;
  width:4px;
}
 
.min{
  background:#f5f5f5;
  height:65px;
  left:50%;  
  position: absolute;
  top:10px;
  transform:rotate(100deg);
  width:4px;
}
 
.min,.hour{
  border-radius:5px;
  transform-origin:bottom center;
  transition:all .5s linear;
}
 
.infos{
  list-style:none;
}
.info{
  color:#811600;
  font-size:23px;
  float:left;
  height:100%;
  padding-top:10px;
  text-align: center;
  width:25%;
}
.info span{
  display: inline-block;
  font-size:26px;
  margin-top:20px;
}
.weather p {
  font-size:20px;padding:10px 0;
}
.anim{animation:fade .8s linear;}
 
@keyframes fade{
  0%{opacity:0;}
  100%{opacity:1;}
}

a{
 text-align: center;
 text-decoration: none;
 color: black;
 font-size: 15px;
 font-weight: 900;
}
 
</style>

<body>
<h1>RajaRajeswari College of Engineering</h1>
<h3>(NBA & NAAC Accredited, Affiliated to VTU, Belagavi, Approved by AICTE, New Delhi)</h3>
<h4>Department of Electronics and Communication Engineering</h4>
<h1>Mini-Project on</h1>
<h5>"A Design of Weather Factors Monitoring System based on IOT"</h5>
<p>Designed and developed by Dinesh Gowda M (1RR18EC024)<br>
Student, Dept. of ECE, RRCE.</p>
<div class="widget"> 
  <div class="clock">
    <div class="min" id="min"></div>
    <div class="hour" id="hour"></div>
  </div>
  <div class="upper">
    <div class="date" id="date">1 January</div>
    <div class="year">Kumbalgudu, Bengaluru</div>
    <div class="place update" id="temperature">23 &deg;C</div>
  </div>
  <div style="text-align: center;"><a href="" style="align:center">Live Weather Monitoring System</a></div>
  <div class="lower">    
    <ul class="infos">
      <li class="info temp">
        <h2 class="title">Temperature</h2>
        <span class='update' id="temp">21 &deg;C</span>
      </li>
      <li class="info weather">
        <h2 class="title">Pressure</h2>
        <span class="update" id="pressure">0 mb</span>
      </li>
      <li class="info wind">
        <h2 class="title">Rain</h2>
        <span class='update' id="rain">Reading</span>
      </li>
      <li class="info humidity">
        <h2 class="title">Humidity</h2>
        <span class='update' id="humidity">23%</span>
      </li>
    </ul>
  </div>
</div>
 
<script>
setInterval(drawClock, 2000);
    
function drawClock(){
    var now = new Date();
    var hour = now.getHours();
    var minute = now.getMinutes();
    var second = now.getSeconds();
    
    //Date
    var options = {year: 'numeric', month: 'long', day: 'numeric' };
    var today  = new Date();
    document.getElementById("date").innerHTML = today.toLocaleDateString("en-US", options);
    
    //hour
    var hourAngle = (360*(hour/12))+((360/12)*(minute/60));
    var minAngle = 360*(minute/60);
    document.getElementById("hour").style.transform = "rotate("+(hourAngle)+"deg)";
    //minute
    document.getElementById("min").style.transform = "rotate("+(minAngle)+"deg)";
 
    //Get Humidity Temperature and Rain Data
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
      var txt = this.responseText;
      var obj = JSON.parse(txt);
        document.getElementById("rain").innerHTML = obj.Rain;
        document.getElementById("temperature").innerHTML = Math.round(obj.Temperature) + "&deg;C";
        document.getElementById("temp").innerHTML = Math.round(obj.Temperature) + "&deg;C";
        document.getElementById("humidity").innerHTML = Math.round(obj.Humidity) + "%";
        document.getElementById("pressure").innerHTML = Math.round(obj.Pressuremb) + " mb";
      }  
    };
   xhttp.open("GET", "readADC", true); //Handle readADC server on ESP8266
   xhttp.send();
}
</script>
</body>
</html>