//WARNING!!! This code is terrible
console.log("Started");
console.log("Pi is " + Math.PI);

const canvas = document.getElementById("canvas");
const context = canvas.getContext("2d");

var od = document.getElementById("d").addEventListener("input", function (e) {
    ond();
});
var or = document.getElementById("r").addEventListener("input", function (e) {
    onr();
});
var oo = document.getElementById("o").addEventListener("input", function (e) {
    ono();
});
var of = document.getElementById("round").addEventListener("input", function (e) {
    draw(document.getElementById("o").value, document.getElementById("r").value, document.getElementById("d").value);
});

function onr() {    
    var r = document.getElementById("r").value;
    
    document.getElementById("d").value = r*2;

    document.getElementById("o").value = r*2*Math.PI;
    
    var result = r * 2 * Math.PI;

    draw(document.getElementById("o").value, document.getElementById("r").value, document.getElementById("d").value);
    
    console.log(result);
}
function ond() {    
    var d = document.getElementById("d").value;
    
    document.getElementById("r").value = d/2;

    document.getElementById("o").value = d*Math.PI;
    
    var result = d * Math.PI;

    draw(document.getElementById("o").value, document.getElementById("r").value, document.getElementById("d").value);

    console.log(result);
}
function ono() {    
    var o = document.getElementById("o").value;
    
    document.getElementById("d").value = o/Math.PI;

    document.getElementById("r").value = (o/Math.PI)/2;
    
    var result = d * Math.PI;

    draw(document.getElementById("o").value, document.getElementById("r").value, document.getElementById("d").value);
    
    console.log(result);
}
function calc(num, num2) {
    var temp = Math.round(num*Math.pow(10, num2));
    return (temp/Math.pow(10, num2));
}
function draw(o, r, d) {
    var num2 = document.getElementById("round").value;
    //Clear canvas
    context.clearRect(0, 0, canvas.width, canvas.height);
    //Kruznice
    context.beginPath();
    context.arc(175, 175, 125, 0, 2 * Math.PI);
    //Obvod text
    context.font = "15px Arial";
    context.fillText("o ≈ " + calc(o, num2), 10, 70);
    //Obsah text
    context.font = "15px Arial";
    context.fillText("s ≈ " + calc(Math.pow(r, 2) * Math.PI, num2) + "\xB2", 10, 50);
    //Polomer text
    context.font = "15px Arial";
    context.fillText("r ≈ " + calc(r, num2), 180, 250);
    //Prumer text
    context.font = "15px Arial";
    context.fillText("d ≈ " + calc(d, num2), 80, 170);
    //Stred text
    context.font = "15px Arial";
    context.fillText("S", 170, 170);
    //Prumer cara
    context.moveTo(50, 175);
    context.lineTo(300, 175);
    //Polomer cara
    context.moveTo(175, 175);
    context.lineTo(175, 300);
    context.stroke();
}

draw(0, 0 ,0);