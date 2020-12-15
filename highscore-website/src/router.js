import Vue from "vue";
import Router from "vue-router";

import UsersList from './components/UsersList.vue';

Vue.use(Router);

export default new Router({
  mode: "history",
  routes: [
    {
      path: "/",
      alias: "/users",
      name: "users",
      component: UsersList
    }
  ]
});