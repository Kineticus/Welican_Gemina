<template>
  <div id="app">
    <nav class="navbar navbar-expand navbar-dark bg-dark">
      <img src="./assets/logo.png">
      <router-link to="/" class="navbar-brand">Welican</router-link>
      <div class="navbar-nav mr-auto">
        <li class="nav-item">
          <router-link to="/users" class="nav-link">Users</router-link>
        </li>
      </div>
    </nav>

    <div class="container mt-3">
      <h2>Welican Gemina Highscores</h2>
      <router-view />
    </div>
  </div>
</template>

<script>
export default {
  name: "app"
};
</script>

<style scoped>
.container h2 {
  text-align: center;
  margin: 25px auto;
}
</style>