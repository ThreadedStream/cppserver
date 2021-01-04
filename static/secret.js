const solveBtn = document.getElementById('solveBtn');
const diffBtn  = document.getElementById('diffBtn');
const diff_form = document.getElementById('dydx');
const multForm = document.getElementById('mult');

function handle_mult(){
    const res = document.getElementById('result');
    const errorLabel = document.getElementById('errorLbl');
    const number1 = document.getElementById('num1').value;
    const number2 = document.getElementById('num2').value;
    if (number1 == "" || number2 == "" || (number1=="" && number2=="")){
        alert('Fill in the number fields');
        return;
    }
    var hdrs = new Headers();
    var data = "op=mult&num1=" + number1 + "&" + "num2=" + number2;
    const method = "POST";
    //Not a secure way to send POST requests!!!!
    const http = new XMLHttpRequest();
    const url =  "http://127.0.0.1/secret?" + data;
    http.open(method, url);
    http.send();
    //On data retrieved listener
    http.onreadystatechange=function(){
        if (this.status === 200){
            res.innerHTML = http.responseText;
            multForm.reset();
        }
        else{
            alert("something went wrong, duuude")
        }
    }
}

function handle_differentiation(){
    const res = document.getElementById('diff-res');
    var func = document.getElementById('func');
    const at = document.getElementById('dydx-at');

    var fn = new String(func.value)
    fn.replace("%20", "\t");
    var headers = new Headers();
    const data = "op=diff&func="+fn+"&at="+at.value;
    const method = "POST";
    const http = new XMLHttpRequest();
    const url  = "http://127.0.0.1/secret?" + data;
    console.log(url);
    http.open(method, url);
    http.send();
    http.onreadystatechange=function(){
        if (this.status === 200){
            res.className = "success"
            res.innerHTML = http.responseText
            diff_form.reset()
        }
        else{
            alert("something went wrong, dude");
        }
    }
}

solveBtn.addEventListener('click', (e) => {handle_mult()});
diffBtn.addEventListener('click', (e)=>{ handle_differentiation()});
