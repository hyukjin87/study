const API_KEY = "5c288c973ab26ca183eb677e219c30e9"

function geoLocationSuccess(position) {
    const lat = position.coords.latitude;
    const lon = position.coords.longitude;
    const url = `https://api.openweathermap.org/data/2.5/weather?lat=${lat}&lon=${lon}&appid=${API_KEY}`
    fetch(url).then((response) => response.json()).then((data) => {
        const weather = document.querySelector("#weather span:first-child");
        const city = document.querySelector("#weather span:last-child");
        city.innerText = data.name;
        weather.innerText = data.weather[0].main;
    });
}

function geoLocationError() {
    alert("Can't find you");
}

navigator.geolocation.getCurrentPosition(geoLocationSuccess, geoLocationError);