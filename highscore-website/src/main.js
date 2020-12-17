import Vue from 'vue'
import App from './App.vue'
import router from './router.js'
import './assets/scss/main.scss'
import './assets/js/main.js'

Vue.config.productionTip = false

new Vue({
  router: router,
  render: h => h(App),
}).$mount('#app')
