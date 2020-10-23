import './styles/main.scss';
import '../js/slider';
import { human } from '../js/human';

var refreshTime = localStorage.getItem('refreshTime');

console.log(human('Dude'));

window.addEventListener('popstate', function (event) {
  // Log the state data to the console
  var currentUrl = event.currentTarget.location.href;
  var currentPage = currentUrl.substring(currentUrl.indexOf("#"));
  console.log(currentUrl);
  console.log(currentPage);
  localStorage.setItem('currentPage', currentPage);
});

document.addEventListener('DOMContentLoaded', () => {

  var brightnessValue = localStorage.getItem('brightnessValue');
  if (brightnessValue) {
    var slider = document.getElementById("brightness-range");
    var output = document.getElementById("brightness-value");
    output.innerHTML = brightnessValue; // Display the default slider value
    slider.value = brightnessValue; // Display the default slider value
  }

  // if (refreshTime != undefined) {
  //   // Automatic reload page
  //   var currentPage = localStorage.getItem('currentPage');
  //   // setTimeout(`location.href = '/${currentPage}'`, refreshTime);
  // }
});

function setRefreshTime(newTime) {
  refreshTime = newTime;
  localStorage.setItem('refreshTime', refreshTime);
}

var settingNever = document.getElementById("setting-never");
settingNever.addEventListener("click", function (e) {
  setRefreshTime(null);
}, false);
var setting10 = document.getElementById("setting-10");
setting10.addEventListener("click", function (e) {
  setRefreshTime(10000);
}, false);
var setting30 = document.getElementById("setting-30");
setting30.addEventListener("click", function (e) {
  setRefreshTime(30000);
}, false);
var setting1 = document.getElementById("setting-1");
setting1.addEventListener("click", function (e) {
  setRefreshTime(60000);
}, false);
