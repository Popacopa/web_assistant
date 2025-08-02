

let btn = document.querySelector(".btn");
let body = document.getElementById('body');

const IP = window.location.hostname;
console.log("Server: " + IP);

var data = 0;

btn.innerHTML = "OFF"


async function req() {
    if (data == 0) {data = 1;} else {data = 0;}

    
    try 
    {
        const res = await axios.post(`http://${IP}:8000/api`, String(data))

        result = String(res.data);

        if (result.length > 2) {btn.innerHTML = result;} else {
            Number(res.data) ? btn.innerHTML = "OFF" : btn.innerHTML = "ON";
            btn.classList.remove('errorbtn');
            body.classList.remove('errorbody');
        }

    } catch (error) {
        console.error("Error:", error);
        btn.innerHTML = "No connection";
        btn.classList.add('errorbtn');
        body.classList.add('errorbody');
    }
}

btn.addEventListener("click", function() {
    req();
})
