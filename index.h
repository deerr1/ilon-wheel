const char webpage[] PROGMEM = R"=====(
    <!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>

<body style="background-color: #f9e79f ">
    <center>
        <div>
            <h1>Управление мотором</h1>
            <button class="button" onclick="send(1)">ВПЕРЕД</button>
            <button class="button" onclick="send(-1)">НАЗАД</button>
        </div>
</body>
<script>
    function send(dir) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("state").innerHTML = this.responseText;
            }
        };
        xhttp.open("POST", "/motor_set?dir=" + dir, true);
        xhttp.send();
    }
</script>
<style type="text/css">
    .button {
        background-color: #4CAF50;
        border: none;
        color: white;
        padding: 15px 32px;
        text-align: center;
        text-decoration: none;
        display: inline-block;
        font-size: 16px;
    }

    .button:hover {
        background-color: #3e8e41
    }

    .button:active {
        background-color: #3e8e41;
        box-shadow: 0 2px #666;
        transform: translateY(4px);
    }
</style>

</html>
)=====";