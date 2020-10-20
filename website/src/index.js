import './styles/main.scss'
import { human } from "../js/human";

var refreshTime = localStorage.getItem('refreshTime');

console.log(human('Dude'));

document.addEventListener('DOMContentLoaded', () => {

  if (refreshTime == undefined) {
    // Automatic reload page
    setTimeout("location.href = '/'", 10000);
  }
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
