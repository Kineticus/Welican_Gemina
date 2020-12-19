import Vue from 'vue'
import App from './App.vue'
import router from './router.js'
import './assets/scss/main.scss'
import './assets/js/main.js'
import Buefy from 'buefy'
import 'buefy/dist/buefy.css'

Vue.use(Buefy)
Vue.config.productionTip = false

new Vue({
  router: router,
  render: h => h(App),
}).$mount('#app')
