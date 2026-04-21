#include "web_content.h"

String int2str(int val)
{
    return (val < 10 ? "0" : "") + String(val);
}

String HTML_main_page(uint8_t temp_min, uint8_t temp_max)
{
    String str = R"ABRACADABRA(
<!DOCTYPE html>
<html style="height: 100%;">
<head>
    <meta charset="UTF-8">
    <title>Balancer</title>
    <style>
        body {
            background-color:
            black;
            color:white;
            height: 100%;
            margin: 0px;
        }
        .div-row{
            text-align: center;
            display: flex;
            align-items: center;
            justify-content: center;
            height: 15%;
            padding: 10px;
            font-size: 5cqh;
        }
        .div-text{
            width: 33%;
            font-size: 14cqh;
            font-weight: bold;
        }
        .big-button{
            width: 100%;
            height: 100%;
            font-size: 4cqh;
        }
        .small-button{
            width: 33%;
            height: 100%;
            font-size: 10cqh;
        }
    </style>
</head>
<body>
    <div class="div-row">Максимальная температура</div>
    <div class="div-row">
        <button class="small-button" onclick="max_temp_dec()">-</button>
        <div class="div-text" style="color: red;" id="max_div">{temp_max}</div>
        <button class="small-button" onclick="max_temp_inc()">+</button>
    </div>
    <div class="div-row">Минимальная температура</div>
    <div class="div-row">
        <button class="small-button" onclick="min_temp_dec()">-</button>
        <div class="div-text" style="color: blue;" id="min_div">{temp_min}</div>
        <button class="small-button" onclick="min_temp_inc()">+</button>
    </div>
    <div class="div-row">
        <button  class="big-button" onclick="send()">Сохранить</button>
    </div>
    <div class="div-row">
        <button class="big-button"  onclick="sync()">Синхронизировать</button>
    </div>
    <script type="text/javascript">
        const maximum = {def_temp_max};
        const minimum = {def_temp_min};
        
        var max_temp = {temp_max};
        var min_temp = {temp_min};
        
        function read_div(){
            max_temp = document.getElementById("max_div").innerText * 1;
            min_temp = document.getElementById("min_div").innerText * 1;
        }

        function update_div(){
            document.getElementById("max_div").innerText = max_temp;
            document.getElementById("min_div").innerText = min_temp;
        }        

        function max_temp_inc(){
            read_div()
            if ((max_temp + 1) <= maximum) max_temp++;
            update_div();
        }

        function max_temp_dec(){
            read_div()
            if ((max_temp - 1) > min_temp) max_temp--;
            update_div();
        }

        function min_temp_inc(){
            read_div()
            if ((min_temp + 1) < max_temp) min_temp++;
            update_div();
        }

        function min_temp_dec(){
            read_div()
            if ((min_temp - 1) >= minimum) min_temp--;
            update_div();
        }

        function send(){
            read_div();
            window.location = `/save?min=${min_temp}&max=${max_temp}`
        }

        function sync(){
            var now = new Date();
            var url = "/sync?";
            url = url + "year=" + (now.getFullYear() - 2000);
            url = url + "&month=" + (now.getMonth() + 1);
            url = url + "&day=" + now.getDate();
            url = url + "&hour=" + now.getHours();
            url = url + "&minute=" + now.getMinutes();
            url = url + "&second=" + now.getSeconds();
            window.location = url;
        }
    </script>
</body>
</html>
    )ABRACADABRA";
    
    str.replace("{temp_min}", String(temp_min));
    str.replace("{temp_max}", String(temp_max));
    str.replace("{def_temp_min}", String(MINIMUM_TEMP));
    str.replace("{def_temp_max}", String(MAXIMUM_TEMP));

    return str;
}