const images = ["01.jpg", "02.jpg", "03.jpg"];

const chooseImage = images[Math.floor(Math.random() * images.length)];

const bgImage = document.createElement("img");

bgImage.src = `img/${chooseImage}`;
bgImage.classList.add("bgImg");
document.body.appendChild(bgImage);