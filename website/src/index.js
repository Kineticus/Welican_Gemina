import './styles/main.scss'
import { human } from "../js/human";

console.log(human('Dude'));

document.addEventListener('DOMContentLoaded', () => {

  // Automatic reload page
  setTimeout("location.href = '/'", 10000);

});