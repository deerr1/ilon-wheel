const char webpage[] PROGMEM = R"=====(
    <!DOCTYPE html>
<html lang="en">
<head>
    <title>Document</title>
</head>
<body >
    <div  class="gamepad">
        <div id="circle1" class="circle">
            <div id="stick1" class="stick"></div>
        </div>
        <div id="circle2" class="circle">
            <div id="stick2" class="stick"></div>
        </div>
    </div>
    <button id="btn" onclick="fullscreen()">Full screen</button>
</body>
<script>
    function fullscreen() {
        document.documentElement.requestFullscreen();
        document.getElementById('btn').style.display = 'none';
    }

    var stick1 = document.getElementById("stick1"), stick2 = document.getElementById("stick2");
    stick1.x = stick1.y = stick2.x = stick2.y = 0;

    stick1.onpointerdown  = move;
    stick2.onpointerdown  = move;


    setInterval(function()
    {
        var xhttp = new XMLHttpRequest();
        const query = `x1=${stick1.x}&y1=${stick1.y}&x2=${stick2.x}&y2=${stick2.y}`;
        xhttp.open("POST", "/motor_set?" + query, true);
        xhttp.send();
    }, 500);

    function move(e) {
        this.parentNode.onpointermove = moveAt;
        this.onpointerup = function() {
            this.parentNode.onpointermove = null;
            this.onpointerup = null;
            this.style.left = '50%';
            this.style.top = '50%';
            this.x = 0;
            this.y = 0;
        }
    }


    function moveAt(e) {

        var child =  this.childNodes[1];
        var x = e.pageX - this.offsetLeft;
        var y = e.pageY - this.offsetTop;

        if (x < 0) {
            x = 0;
        }
        else if (x > this.offsetWidth) {
            x = this.offsetWidth;
        }
        if (y < 0) {
            y = 0;
        }
        else if (y > this.offsetHeight) {
            y = this.offsetHeight;
        }

        child.style.left = x + 'px';
        child.style.top = y + 'px';

        child.x = x/ this.offsetWidth * 2 - 1;
        child.y = y/this.offsetHeight * (-2) + 1;
    }
</script>
<style>
    html, body {
        height: 90%;
    }
    #btn {
        width:60px;
        height: 40px;
    }
    .stick {
        width: 7vw;
        height: 7vw;
        border-radius: 50%;
        background-color: black;
        position: absolute;
        left:50%;
        top:50%;
        transform: translate(-50%, -50%);
        touch-action: none;
    }
    .circle {
        width: 20vw;
        height: 20vw;
        border-radius: 50%;
        border-color: black;
        border: 1px solid;
        position: relative;
    }
    .gamepad {
        display: flex;
        justify-content: space-between;
        align-items: center ;
        height: 100%;
        margin: 0 7vw;
    }

</style>
</html>
)=====";