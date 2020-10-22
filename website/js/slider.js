var slider = document.getElementById("brightness-range");
var output = document.getElementById("brightness-value");
output.innerHTML = slider.value; // Display the default slider value

// Update the current slider value (each time you drag the slider handle)
slider.oninput = function () {
  output.innerHTML = this.value;
}
slider.onchange = debounce(function () {
  window.history.pushState({}, document.title, `/?brightness=${this.value}`);
  httpGet(`/?brightness=${this.value}`);
}, 250);

function debounce(func, wait, immediate) {
  var timeout;
  return function () {
    var context = this, args = arguments;
    var later = function () {
      timeout = null;
      if (!immediate) func.apply(context, args);
    };
    var callNow = immediate && !timeout;
    clearTimeout(timeout);
    timeout = setTimeout(later, wait);
    if (callNow) func.apply(context, args);
  };
};

function httpGet(theUrl) {
  var xmlHttp = new XMLHttpRequest();
  console.log("GET", theUrl);
  xmlHttp.open("GET", theUrl, false); // false for synchronous request
  xmlHttp.send(null);
  return xmlHttp.responseText;
}