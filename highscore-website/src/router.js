import Vue from 'vue'
import VueRouter from 'vue-router'
Vue.use(VueRouter);
import Home from "@/components/Home.vue";
import UsersList from "@/components/UsersList.vue";

const routes = [
  {
    path: "/",
    name: "home",
    component: Home,
  },
  {
    path: "/users",
    name: "users",
    component: UsersList,
  },
];

export default new VueRouter({
  mode: "history",
  routes: routes
})
